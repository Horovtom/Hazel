workspace "Hazel"
    architecture "x64"
    startproject "Sandbox"

    configurations {
        "Debug",    -- Debug - everything enabled
        "Release",  -- Debug with a lot of information stripped, optimizations turned on, but with enabled logging
        "Dist"      -- Everything stripped, with no logging and optimized code
    }

    flags {
        "MultiProcessorCompile"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Hazel/vendor/GLFW/include"

include "Hazel/vendor/GLFW"

project "Hazel"
    location "Hazel" -- Ensure everything will be relative to the path
    kind "SharedLib" -- Specify that it is a dll
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "hzpch.h"
    pchsource "Hazel/src/hzpch.cpp"

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}"
    }

    links {
        "GLFW",
        "opengl32.lib"
    }

    filter "system:windows"
        systemversion "latest"

        defines {
            "HZ_PLATFORM_WINDOWS",
            "HZ_BUILD_DLL"
        }

        postbuildcommands { -- Copy compiled files to Sandbox
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }

    filter "configurations:Debug"
        defines {
            "HZ_DEBUG",
            "HZ_ENABLE_ASSERRTS"
        }
        buildoptions "/MDd" -- Multithreaded debug dll
        symbols "on"

    filter "configurations:Release"
        defines "HZ_RELEASE"
        buildoptions "/MD"
        optimize "on"
        
    filter "configurations:Dist"
        defines "HZ_DIST"
        buildoptions "/MD"
        optimize "on"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    
    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }
    
    includedirs {
        "Hazel/vendor/spdlog/include",
        "Hazel/src"
    }

    links {
        "Hazel" -- It will link the Hazel project to this project (as a dependency)
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines {
            "HZ_PLATFORM_WINDOWS",
            
        }

    filter "configurations:Debug"
        defines "HZ_DEBUG"
        buildoptions "/MDd" -- Multithreaded debug dll
        symbols "on"

    filter "configurations:Release"
        defines "HZ_RELEASE"
        buildoptions "/MD"
        optimize "on"
        
    filter "configurations:Dist"
        defines "HZ_DIST"
        buildoptions "/MD"
        optimize "on"

