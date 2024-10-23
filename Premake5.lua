version = "3.1.3"

workspace "Solution"
	startproject "Workspace"
	architecture "x86_64"

	configurations
	{
		"Debug",
		"Release",
	}

	flags
	{
		"MultiProcessorCompile"
	}

	outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	IncludeDir = {};
	IncludeDir["SFML"] = "%{wks.location}/Vendor/SFML-2.6.1"
	IncludeDir["IMGUI"] = "%{wks.location}/Vendor/ImGui"
	IncludeDir["VEGAENGINE"] = "%{wks.location}/Vendor/VegaEngine-"..version
	IncludeDir["WORKSPACE"] = "%{wks.location}/Workspace/Workspace"

	group "Dependencies"
		include "Vendor/premake5"
		include "Vendor/ImGui"
		include "Example"
	group ""

include "VegaEngine"
include "Workspace"

