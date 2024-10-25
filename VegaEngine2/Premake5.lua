project "VegaEngine2"
	location "VegaEngine2"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"
	systemversion "latest"

pchheader "pch.h"
pchsource "%{IncludeDir.VegaEngine2}/src/pch.cpp"

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
	"%{IncludeDir.VegaEngine2}/src/",
}

libdirs
{

}

prebuildcommands 
{
    "mkdir \"%{wks.location}\\Vendor\\%{prj.name}-"..version.."\\include\\%{prj.name}\"",
    "xcopy /Y /S \"%{IncludeDir.VegaEngine2}\\*.h\" \"%{wks.location}Vendor\\%{prj.name}-"..version.."\\include\\%{prj.name}\"",
    "xcopy /Y /S \"%{IncludeDir.VegaEngine2}\\*.hpp\" \"%{wks.location}Vendor\\%{prj.name}-"..version.."\\include\\%{prj.name}\""
}

links
{

}

filter "system:Windows"

defines
{
	"VG_PLATFORM_WINDOWS",
}

filter "configurations:Debug"
	defines "VG_DEBUG"
	runtime "Debug"
	symbols "On"

filter "configurations:Release"
	defines "VG_RELEASE"
	runtime "Release"
	optimize "On"
