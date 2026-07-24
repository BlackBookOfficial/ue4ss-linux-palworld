#ifdef __linux__
#include <fstream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <cstring>
#include <cstdio>

#include <File/File.hpp>
#include <File/FileType/LinuxFile.hpp>
#include <File/HandleTemplate.hpp>
#include <Helpers/String.hpp>
#include <Helpers/SysError.hpp>
#include <fmt/core.h>

namespace RC::File
{
    auto LinuxFile::is_valid() noexcept -> bool
    {
        return m_file != nullptr;
    }

    auto LinuxFile::invalidate_file() noexcept -> void
    {
        m_file = nullptr;
        m_map_handle = nullptr;
        m_memory_map = nullptr;
    }

    auto LinuxFile::delete_file(const std::filesystem::path& file_path_and_name) -> void
    {
        auto path_utf8 = to_string(file_path_and_name.wstring());
        if (::remove(path_utf8.c_str()) != 0)
        {
            THROW_INTERNAL_FILE_ERROR(fmt::format("[LinuxFile::delete_file] Was unable to delete file, error: {}",
                                                  SysError(errno).str()))
        }
    }

    auto LinuxFile::delete_file() -> void
    {
        if (m_is_file_open)
        {
            close_file();
        }
        delete_file(m_file_path_and_name);
    }

    auto LinuxFile::set_file(HANDLE new_file) -> void
    {
        m_file = new_file;
    }

    auto LinuxFile::get_file() -> HANDLE
    {
        return m_file;
    }

    auto LinuxFile::set_is_file_open(bool new_is_open) -> void
    {
        m_is_file_open = new_is_open;
    }

    auto LinuxFile::get_raw_handle() noexcept -> void*
    {
        return m_file;
    }

    auto LinuxFile::get_file_path() const noexcept -> const std::filesystem::path&
    {
        return m_file_path_and_name;
    }

    auto LinuxFile::set_serialization_output_file(const std::filesystem::path& output_file) noexcept -> void
    {
        m_serialization_file_path_and_name = output_file;
    }

    auto LinuxFile::serialization_file_exists() -> bool
    {
        return std::filesystem::exists(m_serialization_file_path_and_name);
    }

    auto LinuxFile::serialize_identifying_properties() -> void
    {
        if (m_serialization_file_path_and_name.empty())
        {
            THROW_INTERNAL_FILE_ERROR("[LinuxFile::serialize_identifying_properties]: Path & file name for serialization file is empty, please call "
                                      "'set_serialization_output_file'")
        }

        struct stat file_stat{};
        if (fstat(static_cast<int>(reinterpret_cast<intptr_t>(m_file)), &file_stat) != 0)
        {
            THROW_INTERNAL_FILE_ERROR(fmt::format("[LinuxFile::serialize_identifying_properties] Failed to stat file: {}",
                                                  SysError(errno).str()))
        }

        serialize_item(GenericItemData{.data_type = GenericDataType::UnsignedLong, .data_ulong = static_cast<unsigned long>(file_stat.st_dev)}, true);
        serialize_item(GenericItemData{.data_type = GenericDataType::UnsignedLong, .data_ulong = static_cast<unsigned long>(file_stat.st_ino)}, true);
        serialize_item(GenericItemData{.data_type = GenericDataType::UnsignedLong, .data_ulong = 0}, true); // file_index_high unused on Linux
        serialize_item(GenericItemData{.data_type = GenericDataType::UnsignedLong, .data_ulong = static_cast<unsigned long>(file_stat.st_ctim.tv_sec)}, true);
        serialize_item(GenericItemData{.data_type = GenericDataType::UnsignedLong, .data_ulong = 0}, true); // creation_time_high
        serialize_item(GenericItemData{.data_type = GenericDataType::UnsignedLong, .data_ulong = static_cast<unsigned long>(file_stat.st_mtim.tv_sec)}, true);
        serialize_item(GenericItemData{.data_type = GenericDataType::UnsignedLong, .data_ulong = 0}, true); // last_write_time_high
        serialize_item(GenericItemData{.data_type = GenericDataType::UnsignedLong, .data_ulong = static_cast<unsigned long>(file_stat.st_size & 0xFFFFFFFF)}, true);
        serialize_item(GenericItemData{.data_type = GenericDataType::UnsignedLong, .data_ulong = static_cast<unsigned long>(file_stat.st_size >> 32)}, true);
    }

    auto LinuxFile::deserialize_identifying_properties() -> void
    {
        m_identifying_properties.volume_serial_number = *static_cast<unsigned long*>(get_serialized_item(sizeof(unsigned long), true));
        m_identifying_properties.file_index_low = *static_cast<unsigned long*>(get_serialized_item(sizeof(unsigned long), true));
        m_identifying_properties.file_index_high = *static_cast<unsigned long*>(get_serialized_item(sizeof(unsigned long), true));
        m_identifying_properties.creation_time_low = *static_cast<unsigned long*>(get_serialized_item(sizeof(unsigned long), true));
        m_identifying_properties.creation_time_high = *static_cast<unsigned long*>(get_serialized_item(sizeof(unsigned long), true));
        m_identifying_properties.last_write_time_low = *static_cast<unsigned long*>(get_serialized_item(sizeof(unsigned long), true));
        m_identifying_properties.last_write_time_high = *static_cast<unsigned long*>(get_serialized_item(sizeof(unsigned long), true));
        m_identifying_properties.file_size_low = *static_cast<unsigned long*>(get_serialized_item(sizeof(unsigned long), true));
        m_identifying_properties.file_size_high = *static_cast<unsigned long*>(get_serialized_item(sizeof(unsigned long), true));

        m_offset_to_next_serialized_item = sizeof(IdentifyingProperties);
        m_has_cached_identifying_properties = true;
    }

    auto LinuxFile::is_deserialized_and_live_equal() -> bool
    {
        if (!m_has_cached_identifying_properties)
        {
            if (!std::filesystem::exists(m_serialization_file_path_and_name))
            {
                return false;
            }
            deserialize_identifying_properties();
        }

        struct stat live_stat{};
        if (fstat(static_cast<int>(reinterpret_cast<intptr_t>(m_file)), &live_stat) != 0)
        {
            return false;
        }

        if (static_cast<unsigned long>(live_stat.st_dev) != m_identifying_properties.volume_serial_number) return false;
        if (static_cast<unsigned long>(live_stat.st_ino) != m_identifying_properties.file_index_low) return false;
        if (static_cast<unsigned long>(live_stat.st_mtim.tv_sec) != m_identifying_properties.last_write_time_low) return false;
        if (static_cast<unsigned long>(live_stat.st_ctim.tv_sec) != m_identifying_properties.creation_time_low) return false;
        if (static_cast<unsigned long>(live_stat.st_size & 0xFFFFFFFF) != m_identifying_properties.file_size_low) return false;
        if (static_cast<unsigned long>(live_stat.st_size >> 32) != m_identifying_properties.file_size_high) return false;
        return true;
    }

    auto LinuxFile::invalidate_serialization() -> void
    {
        if (m_serialization_file_path_and_name.empty())
        {
            THROW_INTERNAL_FILE_ERROR("[LinuxFile::invalidate_serialization] Could not invalidate serialization file because "
                                      "'m_serialization_file_path_and_name' was empty, please call 'set_serialization_output_file'")
        }
        if (std::filesystem::exists(m_serialization_file_path_and_name))
        {
            delete_file(m_serialization_file_path_and_name);
        }
    }

    static auto write_to_file(LinuxFile& file, const void* data, size_t num_bytes_to_write) -> void
    {
        if (!file.is_file_open())
        {
            THROW_INTERNAL_FILE_ERROR("[LinuxFile::write_to_file] Tried writing to file but the file is not open")
        }

        int fd = static_cast<int>(reinterpret_cast<intptr_t>(file.get_file()));
        ssize_t bytes_written = write(fd, data, num_bytes_to_write);
        if (bytes_written < 0 || static_cast<size_t>(bytes_written) != num_bytes_to_write)
        {
            THROW_INTERNAL_FILE_ERROR(fmt::format("[LinuxFile::write_to_file] Tried writing to file but was unable to complete operation. error: {}",
                                                  SysError(errno).str()))
        }
    }

    auto LinuxFile::serialize_item(const GenericItemData& data, bool is_internal_item) -> void
    {
        if (m_serialization_file_path_and_name.empty())
        {
            THROW_INTERNAL_FILE_ERROR(
                    "[LinuxFile::serialize_item]: Path & file name for serialization file is empty, please call 'set_serialization_output_file'")
        }

        if (!serialization_file_exists() && !is_internal_item)
        {
            serialize_identifying_properties();
        }

        Handle serialization_file = open(m_serialization_file_path_and_name, OpenFor::Appending, OverwriteExistingFile::No, CreateIfNonExistent::Yes);

        switch (data.data_type)
        {
        case GenericDataType::UnsignedLong:
            write_to_file(serialization_file.get_underlying_type(), &data.data_ulong, sizeof(unsigned long));
            serialization_file.get_underlying_type().m_offset_to_next_serialized_item += sizeof(unsigned long);
            break;
        case GenericDataType::SignedLong:
            write_to_file(serialization_file.get_underlying_type(), &data.data_long, sizeof(signed long));
            serialization_file.get_underlying_type().m_offset_to_next_serialized_item += sizeof(signed long);
            break;
        case GenericDataType::UnsignedLongLong:
            write_to_file(serialization_file.get_underlying_type(), &data.data_ulonglong, sizeof(unsigned long long));
            serialization_file.get_underlying_type().m_offset_to_next_serialized_item += sizeof(unsigned long long);
            break;
        case GenericDataType::SignedLongLong:
            write_to_file(serialization_file.get_underlying_type(), &data.data_longlong, sizeof(signed long long));
            serialization_file.get_underlying_type().m_offset_to_next_serialized_item += sizeof(signed long long);
            break;
        }

        serialization_file.close();
    }

    auto LinuxFile::get_serialized_item(size_t data_size, bool is_internal_item) -> void*
    {
        if (!m_has_cache_in_memory)
        {
            if (m_serialization_file_path_and_name.empty())
            {
                THROW_INTERNAL_FILE_ERROR(
                        "[LinuxFile::get_serialized_item]: Path & file name for serialization file is empty, please call 'set_serialization_output_file'")
            }

            Handle cache_file = open(m_serialization_file_path_and_name);

            int fd = static_cast<int>(reinterpret_cast<intptr_t>(cache_file.get_raw_handle()));
            ssize_t bytes_read = read(fd, &m_cache, cache_size);
            if (bytes_read < 0)
            {
                THROW_INTERNAL_FILE_ERROR(fmt::format("[LinuxFile::get_serialized_item] Tried deserializing file but was unable to complete operation. error: {}",
                                                      SysError(errno).str()))
            }

            cache_file.close();
            m_has_cache_in_memory = true;
        }

        if (!m_has_cached_identifying_properties && !is_internal_item)
        {
            deserialize_identifying_properties();
        }

        void* data_ptr = &m_cache[m_offset_to_next_serialized_item];
        m_offset_to_next_serialized_item += data_size;
        return data_ptr;
    }

    auto LinuxFile::close_current_file() -> void
    {
        close_file();
    }

    auto LinuxFile::create_all_directories(const std::filesystem::path& file_name_and_path) -> void
    {
        if (file_name_and_path.parent_path().empty())
        {
            return;
        }

        try
        {
            std::filesystem::create_directories(file_name_and_path.parent_path());
        }
        catch (const std::filesystem::filesystem_error& e)
        {
            THROW_INTERNAL_FILE_ERROR(fmt::format("[LinuxFile::create_all_directories] Tried creating directories '{}' but encountered an error. error: {}",
                                                  file_name_and_path.string(),
                                                  e.what()))
        }
    }

    auto LinuxFile::close_file() -> void
    {
        if (m_memory_map)
        {
            munmap(m_memory_map, m_memory_map_size);
            m_memory_map = nullptr;
            m_memory_map_size = 0;
        }

        if (m_map_handle)
        {
            close(static_cast<int>(reinterpret_cast<intptr_t>(m_map_handle)));

            m_map_handle = nullptr;
        }

        if (!is_valid() || !is_file_open())
        {
            return;
        }

        if (close(static_cast<int>(reinterpret_cast<intptr_t>(m_file))) != 0)
        {
            THROW_INTERNAL_FILE_ERROR(fmt::format("[LinuxFile::close_file] Was unable to close file, {}", SysError(errno).str()))
        }
        else
        {
            set_is_file_open(false);
        }
    }

    auto LinuxFile::is_file_open() const -> bool
    {
        return m_is_file_open;
    }

    auto LinuxFile::write_string_to_file(StringViewType string_to_write) -> void
    {
        auto utf8_str = to_string(StringType(string_to_write));
        write_to_file(*this, utf8_str.c_str(), utf8_str.size());
    }

    auto LinuxFile::is_same_as(LinuxFile& other_file) -> bool
    {
        struct stat file_stat{};
        if (fstat(static_cast<int>(reinterpret_cast<intptr_t>(m_file)), &file_stat) != 0)
        {
            THROW_INTERNAL_FILE_ERROR(fmt::format("[LinuxFile::is_same_as] Failed to stat file: {}", SysError(errno).str()))
        }

        struct stat other_stat{};
        if (fstat(static_cast<int>(reinterpret_cast<intptr_t>(other_file.get_file())), &other_stat) != 0)
        {
            THROW_INTERNAL_FILE_ERROR(fmt::format("[LinuxFile::is_same_as] Failed to stat other file: {}", SysError(errno).str()))
        }

        return file_stat.st_dev == other_stat.st_dev && file_stat.st_ino == other_stat.st_ino;
    }

    auto LinuxFile::read_all() const -> StringType
    {
        fprintf(stderr, "[UE4SS] LinuxFile::read_all: reading %s\n", get_file_path().string().c_str());
        // Use narrow stream to read bytes, then convert to wide string
        // Using wifstream directly causes issues because tellg() returns byte offset
        // but resize(size) allocates size wchar_t's (4x the memory on Linux)
        std::ifstream stream{get_file_path(), std::ios::in | std::ios::binary};
        if (!stream)
        {
            THROW_INTERNAL_FILE_ERROR(fmt::format("[LinuxFile::read_all] Tried to read entire file but returned error {}", errno))
        }

        // Check and skip BOM
        std::streamoff start{};
        char bom[3]{};
        stream.read(bom, 3);
        if (bom[0] == 0xEF && bom[1] == 0xBB && bom[2] == 0xBF)
        {
            start = 3;
        }
        else
        {
            stream.seekg(0, std::ios::beg);
        }

        // Read remaining bytes
        stream.seekg(0, std::ios::end);
        auto size = stream.tellg();
        if (size <= 0)
        {
            stream.close();
            return {};
        }
        auto byte_count = static_cast<size_t>(size) - static_cast<size_t>(start);
        std::string raw_bytes;
        raw_bytes.resize(byte_count);
        stream.seekg(start, std::ios::beg);
        stream.read(raw_bytes.data(), byte_count);
        stream.close();

        // Convert each byte to a wchar_t (ASCII-safe conversion)
        // The INI parser works with wchar_t strings on Linux
        StringType file_contents;
        file_contents.reserve(byte_count);
        for (size_t i = 0; i < byte_count; ++i)
        {
            file_contents.push_back(static_cast<CharType>(static_cast<unsigned char>(raw_bytes[i])));
        }
        return file_contents;
    }

    auto LinuxFile::memory_map() -> std::span<uint8_t>
    {
        int prot_flags;
        switch (m_open_properties.open_for)
        {
        case OpenFor::Writing:
        case OpenFor::Appending:
        case OpenFor::ReadWrite:
            prot_flags = PROT_READ | PROT_WRITE;
            break;
        case OpenFor::Reading:
            prot_flags = PROT_READ;
            break;
        default:
            THROW_INTERNAL_FILE_ERROR("[LinuxFile::memory_map] Tried to memory map file but 'm_open_properties' contains invalid data.")
        }

        int fd = static_cast<int>(reinterpret_cast<intptr_t>(m_file));

        struct stat file_stat{};
        if (fstat(fd, &file_stat) != 0)
        {
            THROW_INTERNAL_FILE_ERROR(fmt::format("[LinuxFile::memory_map] Failed to stat file: {}", SysError(errno).str()))
        }

        size_t file_size = static_cast<size_t>(file_stat.st_size);
        m_memory_map = static_cast<uint8_t*>(mmap(nullptr, file_size, prot_flags, MAP_SHARED, fd, 0));
        if (m_memory_map == MAP_FAILED)
        {
            m_memory_map = nullptr;
            THROW_INTERNAL_FILE_ERROR(fmt::format("[LinuxFile::memory_map] mmap failed: {}", SysError(errno).str()))
        }
        m_memory_map_size = file_size;

        return std::span(m_memory_map, file_size);
    }

    auto LinuxFile::open_file(const std::filesystem::path& file_name_and_path, const OpenProperties& open_properties) -> LinuxFile
    {
        fprintf(stderr, "[UE4SS] LinuxFile::open_file: %s\n", file_name_and_path.string().c_str());
        if (file_name_and_path.empty())
        {
            THROW_INTERNAL_FILE_ERROR("[LinuxFile::open_file] Tried to open file but file_name_and_path was empty.")
        }

        int flags;
        switch (open_properties.open_for)
        {
        case OpenFor::Writing:
            create_all_directories(file_name_and_path);
            flags = O_WRONLY | O_CREAT | O_TRUNC;
            break;
        case OpenFor::Appending:
            create_all_directories(file_name_and_path);
            flags = O_WRONLY | O_CREAT | O_APPEND;
            break;
        case OpenFor::Reading:
            flags = O_RDONLY;
            break;
        case OpenFor::ReadWrite:
            create_all_directories(file_name_and_path);
            flags = O_RDWR | O_CREAT;
            break;
        default:
            THROW_INTERNAL_FILE_ERROR("[LinuxFile::open_file] Tried to open file but received invalid data for the 'OpenFor' parameter.")
        }

        if (open_properties.overwrite_existing_file == OverwriteExistingFile::Yes && open_properties.open_for != OpenFor::Writing)
        {
            create_all_directories(file_name_and_path);
            flags |= O_TRUNC;
        }

        fprintf(stderr, "[UE4SS] LinuxFile::open_file: converting path...\n");
        auto path_utf8 = to_string(file_name_and_path.wstring());
        fprintf(stderr, "[UE4SS] LinuxFile::open_file: path converted to: %s\n", path_utf8.c_str());
        int fd = ::open(path_utf8.c_str(), flags, 0644);
        if (fd < 0)
        {
            std::string_view open_type = open_properties.open_for == OpenFor::Writing || open_properties.open_for == OpenFor::Appending ? "writing" : "reading";
            THROW_INTERNAL_FILE_ERROR(fmt::format("[LinuxFile::open_file] Tried opening file for {} but encountered an error. Path & File: {} | error: {}\n",
                                                  open_type, file_name_and_path.string(), SysError(errno).str()))
        }
        fprintf(stderr, "[UE4SS] LinuxFile::open_file: fd=%d\n", fd);

        LinuxFile file{};
        file.set_file(reinterpret_cast<HANDLE>(static_cast<intptr_t>(fd)));
        file.m_file_path_and_name = file_name_and_path;
        file.set_is_file_open(true);
        file.m_open_properties = open_properties;

        return file;
    }
} // namespace RC::File

#endif // ifdef __linux__
