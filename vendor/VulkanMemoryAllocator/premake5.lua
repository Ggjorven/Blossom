project "VMA"
	kind "StaticLib"
	language "C++"

	architecture "x86_64"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.hpp",
		"src/**.cpp"
	}

	includedirs
	{
		"include",

		"%{IncludeDir.VulkanSDK}"
	}

	filter "system:windows"
		systemversion "latest"
		cppdialect "C++20"
		staticruntime "On"

	filter "system:linux"
		pic "On"
		systemversion "latest"
		cppdialect "C++20"
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
