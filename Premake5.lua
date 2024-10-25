version = "1.0.0"

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

	outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}"
	binDir = "%{wks.location}/Build/bin/" .. outputDir
	binIntDir = "%{wks.location}/Build/bin-int/" .. outputDir

	IncludeDir = {}
	IncludeDir["VegaEngine2"] = "%{wks.location}/VegaEngine2/VegaEngine2"
	IncludeDir["Workspace"] = "%{wks.location}/Workspace/Workspace"

	group "Dependencies"
		include "Vendor/premake5"
	group ""

include "VegaEngine2"
include "Workspace"

