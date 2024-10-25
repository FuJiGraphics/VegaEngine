project "ImGui"
    kind "StaticLib"
    language "C++"

    targetdir ("lib/%{cfg.buildcfg}")
	objdir ("lib/%{cfg.buildcfg}/bin-int")

    files
	{
		"imgui.cpp",
        "imgui_widgets.cpp",
        "imgui_draw.cpp",
        "imgui_tables.cpp",
        "imgui-sfml/imgui-SFML.cpp",
	}

    includedirs
    {
        "%{IncludeDir.IMGUI}/",
        "%{IncludeDir.SFML}/include/",
        "%{IncludeDir.IMGUI}/include/",
    }

	libdirs 
	{
        "%{IncludeDir.SFML}/lib/%{cfg.buildcfg}/",
	    "%{IncludeDir.SFML}/lib/",
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
        "opengl32.lib",
	}

	filter "system:windows"
		systemversion "latest"
		cppdialect "C++17"
		staticruntime "off"

	filter "system:linux"
		pic "On"
		systemversion "latest"
		cppdialect "C++17"
		staticruntime "off"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
