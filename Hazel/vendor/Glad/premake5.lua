project "Glad"
    kind "StaticLib"
    language "C"

    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objdir("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "include/glad/glad.h",
        "include/KHR/khrplatform.h",
        "include/src/glad.c"
    }

    includedirs {
        "include"
    }

    filter "system:windows"
        systemversion "latest"
        staticruntime "on"

    filter { "system:windows", "configuration:Release" }
        buildoptions "/MT"