workspace "SandBox"
	architecture "x86_64"
	configurations{
		"Debug",
		"Release",
		"Dist"
	}
	startproject "Sandbox"
	--toolset "v143"
project "Sandbox"
	kind "SharedLib"
	language "C#"
	dotnetframework "4.8"

	targetdir ("Binaries")
	objdir ("Intermediates")

	files{
		"Source/**.cs",
		"Properties/**.cs",
	}
	links{
		"EulerScript",
	}

	filter "configurations:Debug"
		optimize "Off"
		symbols "Default"
	filter "configurations:Release"
		optimize "On"
		symbols "Default"
	filter "configurations:Dist"
		optimize "Full"
		symbols "Off"

group"EulerEngine"
	include"../../../../EulerScript"
group""