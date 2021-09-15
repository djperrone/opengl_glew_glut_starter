workspace "csc406setup"
	architecture "x32"
	startproject "csc406setup"

	configurations
	{
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- include directories relative to root folder (solution directory)

IncludeDir = {}
IncludeDir["glew"] = "csc406setup/vendor/glew/include"
IncludeDir["freeglut"] = "csc406setup/vendor/freeglut/include"


--include "csc406setup/vendor/glew/include"
--include "csc406setup/vendor/freeglut/include"


project "csc406setup"
	location "csc406setup"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")	

	-- pchheader "mypch.h"
	-- pchsource "csc406setup/src/mypch.cpp"

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"	
	}

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	
	}
	debugenvs { "PATH=%PATH%; %{prj.name}/vendor/freeglut/bin";}

	includedirs
	{
		"%{prj.name}/src",					
		"%{IncludeDir.glew}",
		"%{IncludeDir.freeglut}"		
	}

	libdirs { 
                "%{prj.name}/vendor/glew/lib",
                "%{prj.name}/vendor/freeglut/lib"                
             }

	links
	{
		"glew32.lib",
		"freeglut.lib",		
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{			
			--"GLFW_INCLUDE_NONE"		
		}

	filter "configurations:Debug"			
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
