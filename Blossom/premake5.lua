project "Blossom"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "On"

	architecture "x86_64"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "blpch.h"
	pchsource "src/Blossom/blpch.cpp"

	files
	{
		"src/Blossom/*.h",
		"src/Blossom/*.hpp",
		"src/Blossom/*.cpp",

		"src/Blossom/APIs/APIBuild.cpp",

		"src/Blossom/Core/**.h",
		"src/Blossom/Core/**.hpp",
		"src/Blossom/Core/**.cpp",

		"src/Blossom/ImGui/**.h",
		"src/Blossom/ImGui/**.hpp",
		"src/Blossom/ImGui/**.cpp",

		"src/Blossom/Platforms/**.h",
		"src/Blossom/Platforms/**.hpp",
		"src/Blossom/Platforms/**.cpp",

		"src/Blossom/Renderer/**.h",
		"src/Blossom/Renderer/**.hpp",
		"src/Blossom/Renderer/**.cpp",

		"src/Blossom/Utils/**.h",
		"src/Blossom/Utils/**.hpp",
		"src/Blossom/Utils/**.cpp",
		
		"%{wks.location}/vendor/stb_image/src/stb_image.cpp"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE",
		"GLEW_STATIC",
		"BL_EXPOSE_VULKAN" -- This specifies which API to use another is "BL_EXPOSE_OPENGL"
	}

	includedirs
	{
		"src",
		"src/Blossom",

		"%{IncludeDir.GLEW}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.assimp}",
		"%{IncludeDir.VulkanSDK}",
		"%{IncludeDir.VMA}"
	}

	links
	{
		"%{Library.OpenGL}",
		"%{Library.Vulkan}",

		"GLEW",
		"GLFW",
		"ImGui",
		"spdlog",
		"VMA"
	}

	disablewarnings
	{
		"4005",
		"4996"
	}

	filter "system:windows"
		systemversion "latest"
		staticruntime "on"

		defines
		{
			"BL_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "BL_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "BL_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "BL_DIST"
		runtime "Release"
		optimize "on"

	filter { "system:windows", "configurations:Debug" }
		links
		{
			"%{wks.location}/vendor/assimp/bin/windows/Debug/assimp-vc143-mtd.lib"
		}

	filter { "system:windows", "configurations:Release" }
		links
		{
			"%{wks.location}/vendor/assimp/bin/windows/Release/assimp-vc143-mt.lib"
		}

	filter { "system:windows", "configurations:Dist" }
		links
		{
			"%{wks.location}/vendor/assimp/bin/windows/Release/assimp-vc143-mt.lib"
		}