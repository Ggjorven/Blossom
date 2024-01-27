project "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"
	
	architecture "x86_64"
	
	-- debugdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}") 
	
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
		"src",

		"%{wks.location}/Blossom/src",
		"%{wks.location}vendor",

		"%{IncludeDir.GLEW}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.assimp}",
		"%{IncludeDir.VulkanSDK}",
		"%{IncludeDir.VMA}"
	}

	links
	{
		"Blossom"
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
			"GL_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "GL_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "GL_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "GL_DIST"
		runtime "Release"
		optimize "on"

	filter { "system:windows", "configurations:Debug" }
		postbuildcommands
		{
			'{COPYFILE} "%{wks.location}/vendor/assimp/bin/windows/Debug/assimp-vc143-mtd.dll" "%{cfg.targetdir}"',
		}

	filter { "system:windows", "configurations:Release" }
		postbuildcommands
		{
			'{COPYFILE} "%{wks.location}/vendor/assimp/bin/windows/Release/assimp-vc143-mt.dll" "%{cfg.targetdir}"',
		}

	-- Dist filter for Windows for Windowed Applications
	filter { "system:windows", "configurations:Dist" }
		kind "WindowedApp"

		postbuildcommands
		{
			'{COPYFILE} "%{wks.location}/vendor/assimp/bin/windows/Release/assimp-vc143-mt.dll" "%{cfg.targetdir}"',
		}