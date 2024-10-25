project "Workspace"
	location "Workspace"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"
	systemversion "latest"

-- pchheader "etc/pch.h"
-- pchsource "%{wks.location}/%{prj.name}/etc/pch.cpp"

targetdir(binDir)
objdir(binIntDir)

files
{
	"%{prj.name}/**.cpp",
	"%{prj.name}/**.hpp",
	"%{prj.name}/**.h",
}

includedirs
{
	"%{IncludeDir.Workspace}/",
	"%{IncludeDir.VegaEngine2}/Source/",
}

libdirs
{
	
}

links
{
	"VegaEngine2",
}

prebuildcommands 
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
