workspace "Graphics"
    architecture "x86_64"
    startproject "Graphics-APP"
    configurations { "Debug", "Release" }

Projects = {}
Projects["Major"] = "Graphics"
IncludeDirs = {}
IncludeDirs["glfw"] = "Graphics/vendor/glfw/include"
IncludeDirs["imgui"] = "Graphics/vendor/imgui"
IncludeDirs["imgui_backends"] = "Graphics/vendor/imgui/backends"
IncludeDirs["Glad"] = "Graphics/vendor/Glad/include"
IncludeDirs["stb"] = "Graphics/vendor/stb_image"

group "Dependencies"
    include "Graphics/vendor/glfw"
    include "Graphics/vendor/imgui"
    include "Graphics/vendor/Glad"
group ""

--Major Project Graphics
project "Graphics"
    location "Graphics"
    kind "StaticLib"
    language "C++"
    staticruntime "On"

    targetdir "bin/%{cfg.buildcfg}/%{prj.name}-%{cfg.system}-%{cfg.buildcfg}"
    objdir "bin-int/%{cfg.buildcfg}/%{prj.name}-%{cfg.system}-%{cfg.buildcfg}"

    files
    {
        "%{prj.name}/src/**.cpp", 
        "%{prj.name}/src/**.h"
    }

    includedirs 
    {
        "%{IncludeDirs.Glad}",
        "%{IncludeDirs.glfw}",
        "%{IncludeDirs.imgui}",
        "%{IncludeDirs.imgui_backends}",
        "%{IncludeDirs.stb}",
        "%{prj.name}/src"
    }

    links
    {
        "Glad",
        "glfw",
        "imgui",
        "opengl32.lib"
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"

        defines 
        { 
            "GLFW_INCLUDE_NONE",
            "GRAPHICS_API_OPENGL",
            "GRAPHICS_PLATFORM_WINDOWS"
        }

    filter "system:linux"
        cppdialect "C++17"
        systemversion "latest"

        defines 
        { 
            "GLFW_INCLUDE_NONE",
            "GRAPHICS_API_OPENGL",
            "GRAPHICS_PLATFORM_LINUX"
        }

    filter "configurations:Debug"
        defines "GRAPHICS_DEBUG"
        symbols "On"
        buildoptions "/MTd"
        runtime "Debug"

    filter "configurations:Release"
        defines "GRAPHICS_RELEASE"
        symbols "Off"
        optimize "On"
        buildoptions "/MT"
        runtime "Release"

--StartUp Project
project "Graphics-APP"
    location "Graphics-APP"
    kind "ConsoleApp"
    language "C++"
    staticruntime "On"

    targetdir "bin/%{cfg.buildcfg}/%{prj.name}-%{cfg.system}-%{cfg.buildcfg}"
    objdir "bin-int/%{cfg.buildcfg}/%{prj.name}-%{cfg.system}-%{cfg.buildcfg}"

    files 
    { 
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/src/**.h"
    }

    includedirs 
    { 
        "%{IncludeDirs.Glad}",
        "%{IncludeDirs.glfw}",
        "%{IncludeDirs.imgui}",
        "%{IncludeDirs.imgui_backends}",
        "%{IncludeDirs.stb}",
        "Graphics/src"
    }

    links
    {
        "Graphics"
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"


    filter "system:linux"
        cppdialect "C++17"
        systemversion "latest"

    filter "configurations:Debug"
        symbols "On"
        runtime "Debug"
        buildoptions "/MTd"
    
    filter "configurations:Release" 
        symbols "Off"
        optimize "On"
        runtime "Release"
        buildoptions "/MT"