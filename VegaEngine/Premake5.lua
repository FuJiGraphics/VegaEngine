project "VegaEngine"
	location "VegaEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"
	systemversion "latest"

pchheader "Core/stdafx.h"
pchsource "%{prj.name}/Core/stdafx.cpp"

-- 작업 디렉토리 설정 (상대 경로 설정)
-- debugdir
targetdir("%{wks.location}/Vendor/%{prj.name}-"..version.."/lib/%{cfg.buildcfg}/")
objdir("%{wks.location}/Vendor/%{prj.name}-"..version.."/bin-int/%{cfg.buildcfg}/")

files
{
	"%{prj.name}/**.cpp",
	"%{prj.name}/**.hpp",
	"%{prj.name}/**.h",
}

includedirs
{
	"%{prj.name}",
	"%{wks.location}/Vendor/SFML-2.6.1/include/",
	"%{IncludeDir.IMGUI}/",
}

libdirs
{
	"%{IncludeDir.SFML}/lib/%{cfg.buildcfg}/",
	"%{IncludeDir.SFML}/lib/",
	"%{IncludeDir.IMGUI}/lib/%{cfg.buildcfg}/",
}

prebuildcommands 
{
    "mkdir \"%{wks.location}\\Vendor\\VegaEngine-"..version.."\\include\\VegaEngine\"",
    -- ENGINE 헤더 파일 재귀적 복사
     "xcopy /Y /S \"%{IncludeDir.ENGINE}*.h\" \"%{wks.location}Vendor\\%{prj.name}-"..version.."\\include\\%{prj.name}\"",
     "xcopy /Y /S \"%{IncludeDir.ENGINE}*.hpp\" \"%{wks.location}Vendor\\%{prj.name}-"..version.."\\include\\%{prj.name}\""
}

links
{
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
	"ImGui.lib",
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
