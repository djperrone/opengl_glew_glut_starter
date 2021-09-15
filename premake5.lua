workspace "csc406setup"
	architecture "x64"
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

project "csc406setup"
	location "csc406setup"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")	

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"	
	}

	includedirs
	{
		"%{prj.name}/src",					
		"%{IncludeDir.glew}",
		"%{IncludeDir.freeglut}"		
	}

	libdirs 
	{ 
		"%{prj.name}/vendor/glew/lib/x64",
		"%{prj.name}/vendor/freeglut/lib/x64"  
	}

	links
	{
		"glew32.lib",
		"freeglut.lib",		
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"
		
	filter "configurations:Debug"			
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
