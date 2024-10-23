project "Workspace"
	location "Workspace"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"
	systemversion "latest"

pchheader "stdafx.h"
pchsource "%{prj.name}/stdafx.cpp"

-- 작업 디렉토리 설정 (상대 경로 설정)
-- debugdir
targetdir("../Build/Bin/"..outputDir.."/%{prj.name}")
objdir("../Build/Bin-int/"..outputDir.."/%{prj.name}")

files
{
	"%{prj.name}/**.cpp",
	"%{prj.name}/**.h",
}

includedirs
{
	"%{prj.name}",
	"%{IncludeDir.VEGAENGINE}/include/VegaEngine/",
	"%{IncludeDir.IMGUI}/",
	"%{wks.location}/Vendor/SFML-2.6.1/include/",
}

libdirs
{
	"%{IncludeDir.SFML}/lib/",
	"%{IncludeDir.SFML}/lib/%{cfg.buildcfg}/",
	"%{IncludeDir.IMGUI}/lib/%{cfg.buildcfg}/",
	"%{IncludeDir.VEGAENGINE}/lib/%{cfg.buildcfg}/",
}

links
{
	"VegaEngine",
	"flac.lib",
	"freetype.lib",
	"ogg.lib",
	"vorbis.lib",
	"vorbisenc.lib",
	"vorbisfile.lib",
	"openal32.lib",
	"sfml-audio.lib",
	"sfml-graphics.lib",
	"sfml-main.lib",
	"sfml-network.lib",
	"sfml-system.lib",
	"sfml-window.lib",
	"opengl32.lib",
	"VegaEngine.lib",
}

prebuildcommands 
{ 
    "mkdir \"%{wks.location}\\Vendor\\VegaEngine-"..version.."\\include\\VegaEngine\"",
	"{COPYFILE} %[%{wks.location}/Vendor/SFML-2.6.1/bin/**.dll] %[%{wks.location}/Build/Bin/"..outputDir.."/%{prj.name}]",
}

filter "system:Windows"
defines
{
	"DEF_PLATFORM_WINDOWS",
}

filter "configurations:Debug"
	defines "DEF_DEBUG"
	runtime "Debug"
	symbols "On"

filter "configurations:Release"
	defines "DEF_RELEASE"
	runtime "Release"
	optimize "On"
