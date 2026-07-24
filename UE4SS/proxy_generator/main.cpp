#include <Constructs/Views/EnumerateView.hpp>
#include <File/File.hpp>

#include <cstdint>
#include <cstring>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
#include <ImageHlp.h>
#include <tchar.h>
#include <Helpers/String.hpp>
#include <Helpers/SysError.hpp>
#else
#include <Helpers/String.hpp>

// Minimal PE structure definitions for cross-platform PE parsing
#pragma pack(push, 1)
struct IMAGE_DOS_HEADER {
    uint16_t e_magic;
    uint16_t e_cblp;
    uint16_t e_cp;
    uint16_t e_crlc;
    uint16_t e_cparhdr;
    uint16_t e_minalloc;
    uint16_t e_maxalloc;
    uint16_t e_ss;
    uint16_t e_sp;
    uint16_t e_csum;
    uint16_t e_ip;
    uint16_t e_cs;
    uint16_t e_lfarlc;
    uint16_t e_ovno;
    uint16_t e_res[4];
    uint16_t e_oemid;
    uint16_t e_oeminfo;
    uint16_t e_res2[10];
    int32_t  e_lfanew;
};

struct IMAGE_FILE_HEADER {
    uint16_t Machine;
    uint16_t NumberOfSections;
    uint32_t TimeDateStamp;
    uint32_t PointerToSymbolTable;
    uint32_t NumberOfSymbols;
    uint16_t SizeOfOptionalHeader;
    uint16_t Characteristics;
};

struct IMAGE_DATA_DIRECTORY {
    uint32_t VirtualAddress;
    uint32_t Size;
};

struct IMAGE_OPTIONAL_HEADER32 {
    uint16_t Magic;
    uint8_t  MajorLinkerVersion;
    uint8_t  MinorLinkerVersion;
    uint32_t SizeOfCode;
    uint32_t SizeOfInitializedData;
    uint32_t SizeOfUninitializedData;
    uint32_t AddressOfEntryPoint;
    uint32_t BaseOfCode;
    uint32_t BaseOfData;
    uint32_t ImageBase;
    uint32_t SectionAlignment;
    uint32_t FileAlignment;
    uint16_t MajorOperatingSystemVersion;
    uint16_t MinorOperatingSystemVersion;
    uint16_t MajorImageVersion;
    uint16_t MinorImageVersion;
    uint16_t MajorSubsystemVersion;
    uint16_t MinorSubsystemVersion;
    uint32_t Win32VersionValue;
    uint32_t SizeOfImage;
    uint32_t SizeOfHeaders;
    uint32_t CheckSum;
    uint16_t Subsystem;
    uint16_t DllCharacteristics;
    uint32_t SizeOfStackReserve;
    uint32_t SizeOfStackCommit;
    uint32_t SizeOfHeapReserve;
    uint32_t SizeOfHeapCommit;
    uint32_t LoaderFlags;
    uint32_t NumberOfRvaAndSizes;
    IMAGE_DATA_DIRECTORY DataDirectory[16];
};

struct IMAGE_OPTIONAL_HEADER64 {
    uint16_t Magic;
    uint8_t  MajorLinkerVersion;
    uint8_t  MinorLinkerVersion;
    uint32_t SizeOfCode;
    uint32_t SizeOfInitializedData;
    uint32_t SizeOfUninitializedData;
    uint32_t AddressOfEntryPoint;
    uint32_t BaseOfCode;
    uint64_t ImageBase;
    uint32_t SectionAlignment;
    uint32_t FileAlignment;
    uint16_t MajorOperatingSystemVersion;
    uint16_t MinorOperatingSystemVersion;
    uint16_t MajorImageVersion;
    uint16_t MinorImageVersion;
    uint16_t MajorSubsystemVersion;
    uint16_t MinorSubsystemVersion;
    uint32_t Win32VersionValue;
    uint32_t SizeOfImage;
    uint32_t SizeOfHeaders;
    uint32_t CheckSum;
    uint16_t Subsystem;
    uint16_t DllCharacteristics;
    uint64_t SizeOfStackReserve;
    uint64_t SizeOfStackCommit;
    uint64_t SizeOfHeapReserve;
    uint64_t SizeOfHeapCommit;
    uint32_t LoaderFlags;
    uint32_t NumberOfRvaAndSizes;
    IMAGE_DATA_DIRECTORY DataDirectory[16];
};

struct IMAGE_NT_HEADERS32 {
    uint32_t Signature;
    IMAGE_FILE_HEADER FileHeader;
    IMAGE_OPTIONAL_HEADER32 OptionalHeader;
};

struct IMAGE_NT_HEADERS64 {
    uint32_t Signature;
    IMAGE_FILE_HEADER FileHeader;
    IMAGE_OPTIONAL_HEADER64 OptionalHeader;
};

struct IMAGE_SECTION_HEADER {
    uint8_t  Name[8];
    uint32_t VirtualSize;
    uint32_t VirtualAddress;
    uint32_t SizeOfRawData;
    uint32_t PointerToRawData;
    uint32_t PointerToRelocations;
    uint32_t PointerToLinenumbers;
    uint16_t NumberOfRelocations;
    uint16_t NumberOfLinenumbers;
    uint32_t Characteristics;
};

struct IMAGE_EXPORT_DIRECTORY {
    uint32_t Characteristics;
    uint32_t TimeDateStamp;
    uint16_t MajorVersion;
    uint16_t MinorVersion;
    uint32_t Name;
    uint32_t Base;
    uint32_t NumberOfFunctions;
    uint32_t NumberOfNames;
    uint32_t AddressOfFunctions;
    uint32_t AddressOfNames;
    uint32_t AddressOfNameOrdinals;
};
#pragma pack(pop)

static constexpr uint32_t IMAGE_DIRECTORY_ENTRY_EXPORT = 0;
static constexpr uint16_t IMAGE_NT_OPTIONAL_HDR32_MAGIC = 0x10b;
static constexpr uint16_t IMAGE_NT_OPTIONAL_HDR64_MAGIC = 0x20b;

static auto rva_to_offset(const uint8_t* data, size_t data_size, uint32_t rva, const IMAGE_SECTION_HEADER* sections, uint16_t num_sections) -> size_t
{
    for (uint16_t i = 0; i < num_sections; i++)
    {
        if (rva >= sections[i].VirtualAddress && rva < sections[i].VirtualAddress + sections[i].VirtualSize)
        {
            size_t offset = sections[i].PointerToRawData + (rva - sections[i].VirtualAddress);
            if (offset >= data_size)
            {
                return SIZE_MAX;
            }
            return offset;
        }
    }
    return SIZE_MAX;
}
#endif

using namespace RC;
namespace fs = std::filesystem;

using std::cerr;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;

using std::string;

struct ExportFunction
{
    uint16_t ordinal;
    bool is_named;
    string name;

    ExportFunction(uint16_t ordinal, bool is_named, string name) : ordinal(ordinal), is_named(is_named), name(name)
    {
    }
};

std::vector<ExportFunction> DumpExports(const fs::path& dll_path)
{
    auto dll_file = File::open(dll_path);
    const auto dll_file_map = dll_file.memory_map();
    const auto* data = dll_file_map.data();
    const auto size = dll_file_map.size();

    if (size < sizeof(IMAGE_DOS_HEADER))
    {
        cerr << "File too small to be a valid PE/DLL file\n";
        return {};
    }

#ifdef _WIN32
    ULONG export_directory_size = 0;
    IMAGE_EXPORT_DIRECTORY* export_directory =
            (IMAGE_EXPORT_DIRECTORY*)ImageDirectoryEntryToData(data, FALSE, IMAGE_DIRECTORY_ENTRY_EXPORT, &export_directory_size);

    if (export_directory == nullptr)
    {
        auto err_msg = to_string(SysError(GetLastError()));
        cerr << std::format("Failed to get export directory, reason: {}", err_msg) << '\n';
        return {};
    }

    IMAGE_DOS_HEADER* dos_header = (IMAGE_DOS_HEADER*)data;
    IMAGE_NT_HEADERS* nt_header = (IMAGE_NT_HEADERS*)(data + dos_header->e_lfanew);

    DWORD* name_rvas = (DWORD*)ImageRvaToVa(nt_header, data, export_directory->AddressOfNames, NULL);
    DWORD* function_rvas = (DWORD*)ImageRvaToVa(nt_header, data, export_directory->AddressOfFunctions, NULL);
    uint16_t* ordinals = (uint16_t*)ImageRvaToVa(nt_header, data, export_directory->AddressOfNameOrdinals, NULL);

    std::vector<ExportFunction> exports;
    std::set<uint16_t> exported_ordinals;

    for (size_t i = 0; i < export_directory->NumberOfNames; i++)
    {
        std::string export_name = (char*)ImageRvaToVa(nt_header, data, name_rvas[i], NULL);
        uint16_t ordinal = ordinals[i] + 1;

        ExportFunction named_export(ordinal, true, export_name);
        exports.push_back(named_export);

        exported_ordinals.insert(ordinal);
    }

    for (size_t i = 0; i < export_directory->NumberOfFunctions; i++)
    {
        uint16_t ordinal = (uint16_t)(export_directory->Base + i);
        uint32_t function_rva = function_rvas[i];

        if (function_rva == 0) continue;
        if (exported_ordinals.contains(ordinal)) continue;

        ExportFunction ordinal_export(ordinal, false, std::format("ordinal{}", ordinal));
        exports.push_back(ordinal_export);
    }

    return exports;
#else
    auto* dos_header = (IMAGE_DOS_HEADER*)data;
    if (dos_header->e_magic != 0x5A4D) // "MZ"
    {
        cerr << "Invalid PE file: missing MZ signature\n";
        return {};
    }

    if (dos_header->e_lfanew <= 0 || (size_t)dos_header->e_lfanew + sizeof(IMAGE_NT_HEADERS32) > size)
    {
        cerr << "Invalid PE file: e_lfanew out of bounds\n";
        return {};
    }

    auto* nt_headers = (IMAGE_NT_HEADERS32*)(data + dos_header->e_lfanew);
    if (nt_headers->Signature != 0x00004550) // "PE\0\0"
    {
        cerr << "Invalid PE file: missing PE signature\n";
        return {};
    }

    // Determine PE32 vs PE32+ and get export directory RVA
    uint32_t export_dir_rva;
    const IMAGE_SECTION_HEADER* sections;
    uint16_t num_sections = nt_headers->FileHeader.NumberOfSections;

    if (nt_headers->OptionalHeader.Magic == IMAGE_NT_OPTIONAL_HDR64_MAGIC)
    {
        auto* nt64 = (IMAGE_NT_HEADERS64*)(data + dos_header->e_lfanew);
        export_dir_rva = nt64->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;
        sections = (IMAGE_SECTION_HEADER*)((uint8_t*)nt64 + sizeof(IMAGE_NT_HEADERS64));
    }
    else
    {
        export_dir_rva = nt_headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;
        sections = (IMAGE_SECTION_HEADER*)((uint8_t*)nt_headers + sizeof(IMAGE_NT_HEADERS32));
    }

    // Validate section headers are within bounds
    size_t sections_end = (uint8_t*)sections - data + (size_t)num_sections * sizeof(IMAGE_SECTION_HEADER);
    if (sections_end > size)
    {
        cerr << "Invalid PE file: section headers out of bounds\n";
        return {};
    }

    if (export_dir_rva == 0)
    {
        cerr << "PE file has no export directory\n";
        return {};
    }

    size_t export_offset = rva_to_offset(data, size, export_dir_rva, sections, num_sections);
    if (export_offset == SIZE_MAX || export_offset + sizeof(IMAGE_EXPORT_DIRECTORY) > size)
    {
        cerr << "Invalid PE file: export directory out of bounds\n";
        return {};
    }
    auto* export_directory = (IMAGE_EXPORT_DIRECTORY*)(data + export_offset);

    size_t names_offset = rva_to_offset(data, size, export_directory->AddressOfNames, sections, num_sections);
    size_t functions_offset = rva_to_offset(data, size, export_directory->AddressOfFunctions, sections, num_sections);
    size_t ordinals_offset = rva_to_offset(data, size, export_directory->AddressOfNameOrdinals, sections, num_sections);

    if (names_offset == SIZE_MAX || functions_offset == SIZE_MAX || ordinals_offset == SIZE_MAX)
    {
        cerr << "Invalid PE file: export arrays out of bounds\n";
        return {};
    }

    auto* name_rvas = (uint32_t*)(data + names_offset);
    auto* function_rvas = (uint32_t*)(data + functions_offset);
    auto* ordinals = (uint16_t*)(data + ordinals_offset);

    std::vector<ExportFunction> exports;
    std::set<uint16_t> exported_ordinals;

    for (size_t i = 0; i < export_directory->NumberOfNames; i++)
    {
        size_t name_offset = rva_to_offset(data, size, name_rvas[i], sections, num_sections);
        if (name_offset == SIZE_MAX || name_offset >= size)
        {
            cerr << "Invalid PE file: export name RVA out of bounds\n";
            break;
        }
        std::string export_name = (char*)(data + name_offset);
        uint16_t ordinal = ordinals[i] + 1;

        ExportFunction named_export(ordinal, true, export_name);
        exports.push_back(named_export);

        exported_ordinals.insert(ordinal);
    }

    for (size_t i = 0; i < export_directory->NumberOfFunctions; i++)
    {
        uint16_t ordinal = (uint16_t)(export_directory->Base + i);
        uint32_t function_rva = function_rvas[i];

        if (function_rva == 0) continue;
        if (exported_ordinals.contains(ordinal)) continue;

        ExportFunction ordinal_export(ordinal, false, std::format("ordinal{}", ordinal));
        exports.push_back(ordinal_export);
    }

    return exports;
#endif
}

std::vector<ExportFunction> ReadExportsFile(const fs::path& exp_path, fs::path& dll_path_out)
{
    dll_path_out.clear();
    ifstream exp_file(exp_path);
    string line;

    std::getline(exp_file, line);
    if (line.find("Path: ") != string::npos)
    {
        dll_path_out = line.substr(6);
    }

    if (dll_path_out.empty())
    {
        cerr << std::format("Failed to read export file (missing file path info)") << endl;
        return {};
    }

    std::vector<ExportFunction> exports;
    while (std::getline(exp_file, line))
    {
        std::istringstream s(line);

        uint16_t ordinal{};
        string export_name;
        s >> ordinal >> export_name;

        // invalid line - let's just hope functions with ordinal 0 don't exist
        if (ordinal == 0) continue;
        auto is_named = !export_name.empty();

        ExportFunction exp(ordinal, is_named, is_named ? export_name : std::format("ordinal{}", ordinal));
        exports.push_back(exp);
    }

    return exports;
}

#ifdef _WIN32
int _tmain(int argc, TCHAR* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    if (argc != 3)
    {
        cerr << "Invalid arguments! Expected: proxy_generator.exe <input_dll_name_or_exports_file> <output_path>" << endl;
        return -1;
    }

    const fs::path input_file = argv[1];
    const fs::path output_path = argv[2];

    if (!fs::exists(input_file))
    {
        cerr << "Input file doesn't exist!\n" << endl;
        return -1;
    }

    fs::path input_dll = input_file;
    fs::path input_dll_name = input_file.filename();
    std::vector<ExportFunction> exports;

    if (input_file.extension() == ".exports")
    {
        cout << std::format("Generating a proxy using {}, output path: {}", input_dll_name.string(), output_path.string()) << endl;
        exports = ReadExportsFile(input_file, input_dll);
        input_dll_name = input_dll.filename();
    }
    else
    {
        cout << std::format("Generating a proxy for {}, output path: {}", input_dll.string(), output_path.string()) << endl;
        exports = DumpExports(input_dll);

        const auto exports_path = (output_path / input_dll_name).replace_extension("exports");
        ofstream exports_file(exports_path);
        exports_file << "Path: " << input_dll.string() << endl << endl;
        for (const auto [e, index] : exports | views::enumerate)
        {
            exports_file << std::format("{} {}", e.ordinal, e.is_named ? e.name : "") << endl;
        }
        exports_file.close();

        cout << std::format("Exports file generated at {}", exports_path.string()) << endl;
    }

    cout << std::format("Export count: {}", exports.size()) << endl;

#ifdef _WIN32
    // Windows: Generate .def, .asm, and dllmain.cpp
    ofstream def_file((output_path / input_dll_name).replace_extension("def"));
    def_file << std::format("LIBRARY {}", fs::path(input_dll_name).replace_extension().string()) << endl;
    def_file << "EXPORTS" << endl;

    for (const auto [e, index] : exports | views::enumerate)
    {
        def_file << std::format("  {}=f{} @{}", e.name, index, e.ordinal) << endl;
    }
    def_file.close();

    ofstream asm_file((output_path / input_dll_name).replace_extension("asm"));
    asm_file << ".code" << endl;
    asm_file << "extern mProcs:QWORD" << endl;

    for (const auto [e, index] : exports | views::enumerate)
    {
        asm_file << std::format("f{} proc", index) << endl;
        asm_file << std::format("  jmp mProcs[8*{}]", index) << endl;
        asm_file << std::format("f{} endp", index) << endl;
    }

    asm_file << "end" << endl;
    asm_file.close();

    ofstream cpp_file(output_path / "dllmain.cpp");
    cpp_file << "#include <File/Macros.hpp>" << endl;
    cpp_file << endl;
    cpp_file << "#include <cstdint>" << endl;
    cpp_file << "#include <fstream>" << endl;
    cpp_file << "#include <string>" << endl;
    cpp_file << endl;
    cpp_file << "#define WIN32_LEAN_AND_MEAN" << endl;
    cpp_file << "#include <Windows.h>" << endl;
    cpp_file << "#include <shellapi.h>" << endl;
    cpp_file << "#include <filesystem>" << endl;
    cpp_file << endl;
    cpp_file << "#pragma comment(lib, \"user32.lib\")" << endl;
    cpp_file << "#pragma comment(lib, \"shell32.lib\")" << endl;
    cpp_file << endl;

    cpp_file << "using namespace RC;" << endl;
    cpp_file << "namespace fs = std::filesystem;" << endl;
    cpp_file << endl;

    cpp_file << "HMODULE SOriginalDll = nullptr;" << endl;
    cpp_file << std::format("extern \"C\" uintptr_t mProcs[{}] = {{0}};", exports.size()) << endl;
    cpp_file << endl;

    cpp_file << "void setup_functions()" << endl;
    cpp_file << "{" << endl;

    for (const auto [e, index] : exports | views::enumerate)
    {
        string getter = e.is_named ? std::format("\"{}\"", e.name) : std::format("MAKEINTRESOURCEA({})", e.ordinal);
        cpp_file << std::format("    mProcs[{}] = (uintptr_t)GetProcAddress(SOriginalDll, {});", index, getter) << endl;
    }

    cpp_file << "}" << endl;
    cpp_file << endl;

    cpp_file << "void load_original_dll()" << endl;
    cpp_file << "{" << endl;
    cpp_file << "    wchar_t path[MAX_PATH];" << endl;
    cpp_file << "    GetSystemDirectory(path, MAX_PATH);" << endl;
    cpp_file << endl;
    cpp_file << std::format("    std::wstring dll_path = std::wstring(path) + L\"\\\\{}\";", input_dll_name.string()) << endl;
    cpp_file << endl;
    cpp_file << "    SOriginalDll = LoadLibrary(dll_path.c_str());" << endl;
    cpp_file << "    if (!SOriginalDll)" << endl;
    cpp_file << "    {" << endl;
    cpp_file << "        MessageBox(nullptr, L\"Failed to load proxy DLL\", L\"UE4SS Error\", MB_OK | MB_ICONERROR);" << endl;
    cpp_file << "        ExitProcess(0);" << endl;
    cpp_file << "    }" << endl;
    cpp_file << "}" << endl;
    cpp_file << endl;

    cpp_file << "bool is_absolute_path(const std::string& path)" << endl;
    cpp_file << "{" << endl;
    cpp_file << "    return fs::path(path).is_absolute();" << endl;
    cpp_file << "}" << endl;
    cpp_file << endl;

    cpp_file << "bool should_disable_ue4ss()" << endl;
    cpp_file << "{" << endl;
    cpp_file << "    int argc = 0;" << endl;
    cpp_file << "    LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);" << endl;
    cpp_file << "    if (!argv)" << endl;
    cpp_file << "    {" << endl;
    cpp_file << "        return false;" << endl;
    cpp_file << "    }" << endl;
    cpp_file << endl;
    cpp_file << "    bool disable = false;" << endl;
    cpp_file << "    for (int i = 0; i < argc; i++)" << endl;
    cpp_file << "    {" << endl;
    cpp_file << "        if (wcscmp(argv[i], L\"--disable-ue4ss\") == 0)" << endl;
    cpp_file << "        {" << endl;
    cpp_file << "            disable = true;" << endl;
    cpp_file << "            break;" << endl;
    cpp_file << "        }" << endl;
    cpp_file << "    }" << endl;
    cpp_file << endl;
    cpp_file << "    LocalFree(argv);" << endl;
    cpp_file << "    return disable;" << endl;
    cpp_file << "}" << endl;
    cpp_file << endl;

    cpp_file << "std::wstring get_ue4ss_path_from_args()" << endl;
    cpp_file << "{" << endl;
    cpp_file << "    int argc = 0;" << endl;
    cpp_file << "    LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);" << endl;
    cpp_file << "    if (!argv)" << endl;
    cpp_file << "    {" << endl;
    cpp_file << "        return L\"\";" << endl;
    cpp_file << "    }" << endl;
    cpp_file << endl;
    cpp_file << "    std::wstring ue4ss_path;" << endl;
    cpp_file << "    for (int i = 0; i < argc - 1; i++)" << endl;
    cpp_file << "    {" << endl;
    cpp_file << "        if (wcscmp(argv[i], L\"--ue4ss-path\") == 0)" << endl;
    cpp_file << "        {" << endl;
    cpp_file << "            ue4ss_path = argv[i + 1];" << endl;
    cpp_file << "            break;" << endl;
    cpp_file << "        }" << endl;
    cpp_file << "    }" << endl;
    cpp_file << endl;
    cpp_file << "    LocalFree(argv);" << endl;
    cpp_file << "    return ue4ss_path;" << endl;
    cpp_file << "}" << endl;
    cpp_file << endl;

    cpp_file << "HMODULE load_ue4ss_dll(HMODULE moduleHandle)" << endl;
    cpp_file << "{" << endl;
    cpp_file << "    HMODULE hModule = nullptr;" << endl;
    cpp_file << "    wchar_t moduleFilenameBuffer[1024]{'\\0'};" << endl;
    cpp_file << "    GetModuleFileNameW(moduleHandle, moduleFilenameBuffer, sizeof(moduleFilenameBuffer) / sizeof(wchar_t));" << endl;
    cpp_file << "    const auto currentPath = std::filesystem::path(moduleFilenameBuffer).parent_path();" << endl;
    cpp_file << "    const fs::path ue4ssPath = currentPath / \"ue4ss\" / \"UE4SS.dll\";" << endl;
    cpp_file << endl;

    cpp_file << "    // Check for --ue4ss-path command line argument" << endl;
    cpp_file << "    std::wstring cmdLineUe4ssPath = get_ue4ss_path_from_args();" << endl;
    cpp_file << "    if (!cmdLineUe4ssPath.empty())" << endl;
    cpp_file << "    {" << endl;
    cpp_file << "        fs::path ue4ssArgPath = cmdLineUe4ssPath;" << endl;
    cpp_file << "        if (!ue4ssArgPath.is_absolute())" << endl;
    cpp_file << "        {" << endl;
    cpp_file << "            ue4ssArgPath = currentPath / ue4ssArgPath;" << endl;
    cpp_file << "        }" << endl;
    cpp_file << endl;
    cpp_file << "        // Attempt to load UE4SS.dll from the command line path" << endl;
    cpp_file << "        hModule = LoadLibrary(ue4ssArgPath.c_str());" << endl;
    cpp_file << "        if (hModule)" << endl;
    cpp_file << "        {" << endl;
    cpp_file << "            return hModule;" << endl;
    cpp_file << "        }" << endl;
    cpp_file << "    }" << endl;
    cpp_file << endl;

    cpp_file << "    // Check for override.txt" << endl;
    cpp_file << "    const fs::path overrideFilePath = currentPath / \"override.txt\";" << endl;
    cpp_file << "    if (fs::exists(overrideFilePath))" << endl;
    cpp_file << "    {" << endl;
    cpp_file << "        std::ifstream overrideFile(overrideFilePath);" << endl;
    cpp_file << "        std::string overridePath;" << endl;
    cpp_file << "        if (std::getline(overrideFile, overridePath))" << endl;
    cpp_file << "        {" << endl;
    cpp_file << "            fs::path ue4ssOverridePath = overridePath;" << endl;
    cpp_file << "            if (!is_absolute_path(overridePath))" << endl;
    cpp_file << "            {" << endl;
    cpp_file << "                ue4ssOverridePath = currentPath / overridePath;" << endl;
    cpp_file << "            }" << endl;
    cpp_file << endl;
    cpp_file << "            ue4ssOverridePath = ue4ssOverridePath / \"UE4SS.dll\";" << endl;
    cpp_file << endl;
    cpp_file << "            // Attempt to load UE4SS.dll from the override path" << endl;
    cpp_file << "            hModule = LoadLibrary(ue4ssOverridePath.c_str());" << endl;
    cpp_file << "            if (hModule)" << endl;
    cpp_file << "            {" << endl;
    cpp_file << "                return hModule;" << endl;
    cpp_file << "            }" << endl;
    cpp_file << "        }" << endl;
    cpp_file << "    }" << endl;
    cpp_file << endl;

    cpp_file << "    // Attempt to load UE4SS.dll from ue4ss directory" << endl;
    cpp_file << "    hModule = LoadLibrary(ue4ssPath.c_str());" << endl;
    cpp_file << "    if (!hModule)" << endl;
    cpp_file << "    {" << endl;
    cpp_file << "        // If loading from ue4ss directory fails, load from the current directory" << endl;
    cpp_file << "        hModule = LoadLibrary(L\"UE4SS.dll\");" << endl;
    cpp_file << "    }" << endl;
    cpp_file << endl;
    cpp_file << "    return hModule;" << endl;
    cpp_file << "}" << endl;
    cpp_file << endl;

    cpp_file << "BOOL WINAPI DllMain(HMODULE hInstDll, DWORD fdwReason, LPVOID lpvReserved)" << endl;
    cpp_file << "{" << endl;
    cpp_file << "    if (fdwReason == DLL_PROCESS_ATTACH)" << endl;
    cpp_file << "    {" << endl;
    cpp_file << "        load_original_dll();" << endl;
    cpp_file << "        setup_functions();" << endl;
    cpp_file << endl;
    cpp_file << "        // Check if UE4SS should be disabled via command line argument" << endl;
    cpp_file << "        if (should_disable_ue4ss())" << endl;
    cpp_file << "        {" << endl;
    cpp_file << "            // UE4SS is disabled, proxy will still forward calls to original DLL" << endl;
    cpp_file << "            return TRUE;" << endl;
    cpp_file << "        }" << endl;
    cpp_file << endl;
    cpp_file << "        HMODULE hUE4SSDll = load_ue4ss_dll(hInstDll);" << endl;
    cpp_file << "        if (!hUE4SSDll)" << endl;
    cpp_file << "        {" << endl;
    cpp_file << "            MessageBox(nullptr, L\"Failed to load UE4SS.dll. Please see the docs on correct installation: "
                "https://docs.ue4ss.com/installation-guide\", L\"UE4SS Error\", MB_OK | MB_ICONERROR);"
             << endl;
    cpp_file << "            ExitProcess(0);" << endl;
    cpp_file << "        }" << endl;
    cpp_file << "    }" << endl;
    cpp_file << "    else if (fdwReason == DLL_PROCESS_DETACH)" << endl;
    cpp_file << "    {" << endl;
    cpp_file << "        FreeLibrary(SOriginalDll);" << endl;
    cpp_file << "    }" << endl;
    cpp_file << "    return TRUE;" << endl;
    cpp_file << "}" << endl;

    cpp_file.close();
#else
    // Linux: Generate GCC export map and proxy_main.cpp using dlopen/dlsym
    ofstream map_file((output_path / input_dll_name).replace_extension("map"));
    map_file << "{\n  global:\n";
    for (const auto& e : exports)
    {
        if (e.is_named)
        {
            map_file << std::format("    {};\n", e.name);
        }
    }
    map_file << "  local: *;\n};\n";
    map_file.close();

    ofstream cpp_file(output_path / "proxy_main.cpp");
    cpp_file << "#include <cstdint>\n";
    cpp_file << "#include <cstring>\n";
    cpp_file << "#include <cstdio>\n";
    cpp_file << "#include <cstdlib>\n";
    cpp_file << "#include <filesystem>\n";
    cpp_file << "#include <fstream>\n";
    cpp_file << "#include <string>\n";
    cpp_file << "#include <dlfcn.h>\n";
    cpp_file << "#include <unistd.h>\n";
    cpp_file << "\n";
    cpp_file << "namespace fs = std::filesystem;\n";
    cpp_file << "\n";
    cpp_file << "static void* g_original_lib = nullptr;\n";
    cpp_file << std::format("static void* g_proxy_funcs[{}] = {{nullptr}};\n", exports.size());
    cpp_file << "\n";

    // Generate forwarder functions
    for (const auto [e, index] : exports | views::enumerate)
    {
        if (e.is_named)
        {
            cpp_file << std::format("extern \"C\" __attribute__((visibility(\"default\"))) void* {}() {{\n", e.name);
            cpp_file << std::format("    return g_proxy_funcs[{}];\n", index);
            cpp_file << "}\n\n";
        }
    }

    cpp_file << "static void setup_functions() {\n";
    for (const auto [e, index] : exports | views::enumerate)
    {
        if (e.is_named)
        {
            cpp_file << std::format("    g_proxy_funcs[{}] = dlsym(g_original_lib, \"{}\");\n", index, e.name);
        }
        else
        {
            cpp_file << std::format("    // ordinal {} - cannot resolve by ordinal on Linux\n", e.ordinal);
        }
    }
    cpp_file << "}\n\n";

    cpp_file << "static void load_original_lib() {\n";
    cpp_file << "    // Try common system library paths\n";
    cpp_file << "    const char* search_paths[] = {\n";
    cpp_file << "        \"/usr/lib/x86_64-linux-gnu/\",\n";
    cpp_file << "        \"/usr/lib/\",\n";
    cpp_file << "        \"/lib/x86_64-linux-gnu/\",\n";
    cpp_file << "        \"/lib/\",\n";
    cpp_file << "        nullptr\n";
    cpp_file << "    };\n";
    cpp_file << std::format("    std::string lib_name = \"{}\";\n", input_dll_name.string());
    cpp_file << "    for (int i = 0; search_paths[i]; ++i) {\n";
    cpp_file << "        std::string full_path = std::string(search_paths[i]) + lib_name;\n";
    cpp_file << "        g_original_lib = dlopen(full_path.c_str(), RTLD_NOW);\n";
    cpp_file << "        if (g_original_lib) return;\n";
    cpp_file << "    }\n";
    cpp_file << "    // Try LD_LIBRARY_PATH\n";
    cpp_file << "    g_original_lib = dlopen(lib_name.c_str(), RTLD_NOW);\n";
    cpp_file << "    if (!g_original_lib) {\n";
    cpp_file << "        fprintf(stderr, \"UE4SS Proxy: Failed to load original library %s: %s\\n\", lib_name.c_str(), dlerror());\n";
    cpp_file << "    }\n";
    cpp_file << "}\n\n";

    cpp_file << "static bool should_disable_ue4ss() {\n";
    cpp_file << "    const char* disable_env = getenv(\"UE4SS_DISABLE\");\n";
    cpp_file << "    return disable_env && disable_env[0] == '1';\n";
    cpp_file << "}\n\n";

    cpp_file << "static void load_ue4ss_lib() {\n";
    cpp_file << "    // Get the directory of this shared library\n";
    cpp_file << "    char exe_path[4096]{};\n";
    cpp_file << "    ssize_t len = readlink(\"/proc/self/exe\", exe_path, sizeof(exe_path) - 1);\n";
    cpp_file << "    if (len <= 0) return;\n";
    cpp_file << "    exe_path[len] = '\\0';\n";
    cpp_file << "    fs::path current_path = fs::path(exe_path).parent_path();\n";
    cpp_file << "\n";
    cpp_file << "    // Check UE4SS_DISABLE env var\n";
    cpp_file << "    if (should_disable_ue4ss()) return;\n";
    cpp_file << "\n";
    cpp_file << "    // Check for override.txt\n";
    cpp_file << "    fs::path override_file = current_path / \"override.txt\";\n";
    cpp_file << "    if (fs::exists(override_file)) {\n";
    cpp_file << "        std::ifstream ofs(override_file);\n";
    cpp_file << "        std::string override_path;\n";
    cpp_file << "        if (std::getline(ofs, override_path)) {\n";
    cpp_file << "            fs::path p(override_path);\n";
    cpp_file << "            if (!p.is_absolute()) p = current_path / override_path;\n";
    cpp_file << "            p = p / \"libUE4SS.so\";\n";
    cpp_file << "            void* h = dlopen(p.c_str(), RTLD_NOW);\n";
    cpp_file << "            if (h) return;\n";
    cpp_file << "        }\n";
    cpp_file << "    }\n";
    cpp_file << "\n";
    cpp_file << "    // Try ue4ss directory\n";
    cpp_file << "    fs::path ue4ss_path = current_path / \"ue4ss\" / \"libUE4SS.so\";\n";
    cpp_file << "    void* h = dlopen(ue4ss_path.c_str(), RTLD_NOW);\n";
    cpp_file << "    if (!h) {\n";
    cpp_file << "        // Try current directory\n";
    cpp_file << "        h = dlopen(\"libUE4SS.so\", RTLD_NOW);\n";
    cpp_file << "    }\n";
    cpp_file << "    if (!h) {\n";
    cpp_file << "        fprintf(stderr, \"UE4SS Proxy: Failed to load libUE4SS.so: %s\\n\", dlerror());\n";
    cpp_file << "    }\n";
    cpp_file << "}\n\n";

    cpp_file << "__attribute__((constructor)) static void proxy_init() {\n";
    cpp_file << "    load_original_lib();\n";
    cpp_file << "    if (g_original_lib) {\n";
    cpp_file << "        setup_functions();\n";
    cpp_file << "        load_ue4ss_lib();\n";
    cpp_file << "    }\n";
    cpp_file << "}\n\n";

    cpp_file << "__attribute__((destructor)) static void proxy_fini() {\n";
    cpp_file << "    if (g_original_lib) {\n";
    cpp_file << "        dlclose(g_original_lib);\n";
    cpp_file << "        g_original_lib = nullptr;\n";
    cpp_file << "    }\n";
    cpp_file << "}\n";
    cpp_file.close();
#endif

    cout << "Finished generating!" << endl;

    return 0;
}
