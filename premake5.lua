workspace "SwanEngine"
    architecture "x86_64"
    configurations { "Debug", "Release", "Dist" }
    startproject "Sandbox"


outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Swan/vendor/GLFW/include"
IncludeDir["Glad"] = "Swan/vendor/Glad/include"
IncludeDir["ImGui"] = "Swan/vendor/ImGui"
IncludeDir["glm"] = "Swan/vendor/glm/glm"
IncludeDir["Nuklear"] = "Swan/vendor/Nuklear"
IncludeDir["entt"] = "Swan/vendor/entt/single_include"



group "Dependencies"
include "Swan/vendor/GLFW"
include "Swan/vendor/Glad"
include "Swan/vendor/ImGui"


group ""
include "SwanEditor"

project "Swan"
    location "Swan"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "pch.h"
    pchsource "Swan/src/pch.cpp"
    
    files
    {
      "%{prj.name}/src/**.h",
      "%{prj.name}/src/**.cpp",
      "%{prj.name}/vendor/tinyobjloader/tiny_obj_loader.cc",
      "%{prj.name}/vendor/tinyobjloader/tiny_obj_loader.h"
    }

    includedirs
    {
      "%{prj.name}/src",
      "%{prj.name}/vendor/spdlog/include",
      "%{IncludeDir.GLFW}",
      "%{IncludeDir.Glad}",
      "%{IncludeDir.ImGui}",
      "%{IncludeDir.glm}",
      "%{IncludeDir.Nuklear}",
      "%{IncludeDir.entt}",
      "%{prj.name}/vendor/tinyobjloader"
    }

    defines
    {
      "_CRT_SECURE_NO_WARNINGS",
	"GLFW_INCLUDE_NONE", 
    }

    links 
    { 
      "GLFW",
      "Glad",
      "ImGui",
      "dl"
      --"opengl32.lib"
    }

    -- postbuildcommands
    -- {
    --   ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
    -- }

    filter "system:windows"
      system "windows"
      links { "OpenGL32" }
      defines { "SW_PLATFORM_WINDOWS", "SW_BUILD_DLL" }
      

    filter "system:linux"
      system "linux"
      linkoptions {"-pthread"}
      defines { "SW_PLATFORM_LINUX", "SW_BUILD_DLL" }
      links { "GL" }
      

    filter "configurations:Debug"
      defines { "DEBUG" }
      runtime "Debug"
      symbols "On"

    filter "configurations:Release"
      defines { "RDEBUG" }
      runtime "Release"
      optimize "On"

    filter "configurations:Dist"
      defines { "NDEBUG" }
      runtime "Release"
      optimize "On"


