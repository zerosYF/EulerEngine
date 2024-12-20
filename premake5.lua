workspace "EulerEngine"
	architecture "x64"
	configurations{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["Glad"] = "EulerEngine/Vendor/Glad/include"
IncludeDir["ImGui"] = "EulerEngine/Vendor/ImGui"
include "EulerEngine/Vendor/Glad"
include "EulerEngine/Vendor/ImGui"

project "EulerEngine"
	location "EulerEngine"
	kind "SharedLib"
	language "C++"
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-interm/" .. outputdir .. "/%{prj.name}")

	pchheader "gkpch.h"
	pchsource "%{prj.name}/Src/gkpch.cpp"

	files{
		"%{prj.name}/Src/**.h",
		"%{prj.name}/Src/**.cpp"
	}
	includedirs{
		"%{prj.name}/Src",
		"%{prj.name}/Vendor/spdlog/include",
		"%{prj.name}/External/include",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}
	libdirs{
		"%{prj.name}/External/libs"
	}
	links{
		"glfw3",
		"Glad",
		"ImGui",
		"opengl32"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines{
			"KINK_PLATFORM_WINDOWS",
			"KINK_BUILD_DLL",
			"_WINDLL",
			"KINK_ENABLE_ASSERTS"
		}
		postbuildcommands{
			("{MKDIR} ../bin/" .. outputdir .. "/Sandbox"),
			("{COPYFILE} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox/")
		}
	filter "configurations:Debug"
		defines "KINK_DEBUG"
		symbols "On"
	filter "configurations:Release"
		defines "KINK_RELEASE"
		symbols "On"
	filter "configurations:Dist"
		defines "KINK_DIST"
		symbols "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-interm/" .. outputdir .. "/%{prj.name}")
	files{
		"%{prj.name}/Src/**.h",
		"%{prj.name}/Src/**.cpp"
	}
	includedirs{
		"EulerEngine/Vendor/spdlog/include",
		"EulerEngine/Src"
	}
	links{
		"EulerEngine"
	}


	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		defines{
			"KINK_PLATFORM_WINDOWS",	
		}
	filter "configurations:Debug"
		defines "KINK_DEBUG"
		buildoptions "/MDd"
		symbols "On"
	filter "configurations:Release"
		defines "KINK_RELEASE"
		buildoptions "/MD"
		symbols "On"
	filter "configurations:Dist"
		defines "KINK_DIST"
		buildoptions "/MD"
		symbols "On"