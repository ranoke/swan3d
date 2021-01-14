project "SwanEditor"
    location ""
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"
    
    --pchheader "pch.h"
    --pchsource "Swan/src/pch.cpp"
    
    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	  objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	includedirs
	{
    "%{wks.location}/Swan/vendor/spdlog/include",
		"%{wks.location}/Swan/src",
		"%{wks.location}/Swan/vendor",
		"%{wks.location}/%{IncludeDir.glm}",
    "%{wks.location}/%{IncludeDir.Nuklear}",
    "%{wks.location}/%{IncludeDir.Glad}",
    "%{wks.location}/%{IncludeDir.entt}",
    "%{wks.location}/%{IncludeDir.ImGui}"
	}

	links
	{
    "Swan",
      "GLFW",
      "Glad",
      "ImGui",
      "dl"
      --"opengl32.lib"
    
	}
    

    defines
    {
    "_CRT_SECURE_NO_WARNINGS"
    }


    -- postbuildcommands
    -- {
    --   ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
    -- }

    filter "system:windows"
      system "windows"
      links { "OpenGL32" }
      defines { "SW_PLATFORM_WINDOWS" }
      

    filter "system:linux"
      system "linux"
      linkoptions {"-pthread"}
      defines { "SW_PLATFORM_LINUX" }
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
