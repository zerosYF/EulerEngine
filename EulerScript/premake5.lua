project "EulerScript"
	kind "SharedLib"
	language "C#"
	dotnetframework "4.8"

	targetdir ("%{wks.location}/Editor/Scripts")
	objdir ("%{wks.location}/Editor/Scripts/Indermediates")

	files{
		"Source/**.cs",
		"Properties/**.cs",
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