local projectName = "Unreal"

target(projectName)
    set_kind("static")
    set_languages("cxx20")
    set_exceptions("cxx")
    add_rules("ue4ss.dependency")

    add_includedirs("include", { public = true })
    add_includedirs("generated_include", { public = true })
    add_includedirs("include/Unreal", { public = true })
    add_includedirs("include/Unreal/Core", { public = true })
    add_headerfiles("include/**.hpp", "generated_include/**.hpp")

    add_files("src/**.cpp")
    
    add_deps(
        "File", "DynamicOutput", "SinglePassSigScanner", 
        "Constructs", "Helpers", "Function", 
        "ASMHelper"
    )
    add_packages("zydis", "polyhook_2", "fmt")