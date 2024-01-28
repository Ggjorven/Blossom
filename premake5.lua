include "Dependencies.lua"

workspace "Blossom"
	architecture "x86_64"
	startproject "Sandbox"

	configurations
	{
		"Vulkan-Debug",
		"Vulkan-Release",
		"Vulkan-Dist",
		"OpenGL-Debug",
		"OpenGL-Release",
		"OpenGL-Dist"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Additional Dependencies"
	include "vendor/GLEW"
	include "vendor/GLFW"
	include "vendor/ImGui"
	include "vendor/spdlog"
	include "vendor/VulkanMemoryAllocator"
group ""

group "Core"
	include "Blossom"
group ""

include "Sandbox"