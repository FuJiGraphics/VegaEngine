version = "1.2.0"

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

	-- Include Directories
	IncludeDir = {}
	IncludeDir["SFML"]			= "%{wks.location}/Vendor/SFML-2.6.1/include"
	IncludeDir["Spdlog"]		= "%{wks.location}/Vendor/spdlog/include/" 
	IncludeDir["VegaEngine2"]	= "%{wks.location}/VegaEngine2/VegaEngine2"
	IncludeDir["Workspace"]		= "%{wks.location}/Workspace/Workspace"

	-- Library Path
	LibraryDir = {}
	LibraryDir["VegaEngine2"]	= "%{wks.location}/Vendor/VegaEngine2-"..version.."/lib"
	LibraryDir["SFML"]			= "%{wks.location}/Vendor/SFML-2.6.1/lib"

	-- DLL Working Directories
	WorkingDir = {}
	WorkingDir["SFML"]			= "%{wks.location}/Vendor/SFML-2.6.1/bin"

	group "Dependencies"
		include "Vendor/premake5"
	group ""

include "VegaEngine2"
include "Workspace"

