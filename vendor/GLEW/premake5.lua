project "GLEW"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"

    architecture "x86_64"
	
	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/glew.c",
		"src/glewinfo.c",
		"src/visualinfo.c",
		"auto/src/glew_head.c",
		"auto/src/glewinfo_head.c"

	}

	includedirs
	{
		"auto",
		"include",
		"src"
	}

	defines
	{
		"_CRT_NO_SECURE_WARNINGS",
		"GLEW_STATIC"
	}

	filter "system:windows"
		systemversion "latest"
		staticruntime "On"

	filter "system:linux"
		pic "On"
		systemversion "latest"
		staticruntime "On"

	filter "configurations:Vulkan-Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:OpenGL-Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Vulkan-Release"
		runtime "Release"
		optimize "on"

	filter "configurations:OpenGL-Release"
		runtime "Release"
		optimize "on"

	filter "configurations:Vulkan-Dist"
		runtime "Release"
		optimize "on"

	filter "configurations:OpenGL-Dist"
		runtime "Release"
		optimize "on"

