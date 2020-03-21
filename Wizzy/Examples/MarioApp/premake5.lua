include "Wizzy/premake5.lua"

project "MyInteractiveProject"
	location "MyInteractiveProject"
	kind "ConsoleApp"
	language "C++"
	architecture "x64"
	
	targetdir ("bin/" .. output_dir .. "/%{prj.name}")
	objdir ("bin-int/" .. output_dir .. "/%{prj.name}")
	
	pchheader "pch.h"
	pchsource "MyInteractiveProject/pch.cpp"
	
	files
	{
		"MyInteractiveProject/**.h",
		"MyInteractiveProject/**.cpp"
	}
	
	removefiles
	{
		"%{prj.name}/src/Wizzy/Platform/**"
	}
	
	includedirs
	{
		"Wizzy/Wizzy/src",
		"Wizzy/%{include_dir.imgui}",
		"Wizzy/%{include_dir.glm}",
		"Wizzy/%{include_dir.spdlog}",
		"Wizzy/%{include_dir.glfw}",
		"Wizzy/%{include_dir.glad}",
		"Wizzy/%{include_dir.glm}",
		"Wizzy/%{include_dir.stb}",
		"Wizzy/%{include_dir.lua}",
		"Wizzy/%{include_dir.ulib}",
		"Wizzy/%{include_dir.luabridge}",
		"Wizzy/%{include_dir.pfd}",
		"Wizzy/%{include_dir.ft}"
	}
	
	defines
	{
		"WZ_USE_OPENGL",
		"FREETYPE_STATIC"
	}
	
	links
	{
		"Wizzy",
		"imgui",
		"glfw",
		"glad",
		"lua"
	}
	
	
	-------- Windows
	cppdialect "C++17"
    staticruntime "On"
    systemversion "latest"
	
	links
    {
        "opengl32.lib",
        "glu32.lib",
		"%{wks.location}/Wizzy/vendor/freetype/windows/lib/freetype.lib"
    }

    files
    {
      "%{prj.name}/src/Wizzy/platform/windows/**.h",
      "%{prj.name}/src/Wizzy/platform/windows/**.cpp"
    }

    defines
    {
      "WZ_PLATFORM_WINDOWS",
      "GLFW_INCLUDE_NONE"
    }
	
	filter "configurations:Debug*"
		defines "WZ_CONFIG_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release*"
		defines "WZ_CONFIG_RELEASE"
		runtime "Release"
		symbols "On"
		optimize "On"

	filter "configurations:Dist*"
		defines { "WZ_CONFIG_DIST", "WZ_DISABLE_ASSERTS" }
		runtime "Release"
		optimize "On"
