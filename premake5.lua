include "Dependencies.lua"

workspace "Blossom"
	architecture "x86_64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
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
	include "vendor/VulkanMemoryAllocator"
group ""

group "Core"
	include "Blossom"
group ""

include "Sandbox"