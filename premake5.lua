workspace "EulerEngine"
	architecture "x64"
	configurations{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "EulerEngine"
	location "EulerEngine"
	kind "SharedLib"
	language "C++"
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-interm/" .. outputdir .. "/%{prj.name}")
	files{
		"%{prj.name}/Src/**.h",
		"%{prj.name}/Src/**.cpp"
	}
	includedirs{
		"%{prj.name}/Vendor/spdlog/include"
	}


	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		defines{
			"KINK_PLATFORM_WINDOWS",
			"KINK_BUILD_DLL",
			"_WINDLL"	
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
		symbols "On"
	filter "configurations:Release"
		defines "KINK_RELEASE"
		symbols "On"
	filter "configurations:Dist"
		defines "KINK_DIST"
		symbols "On"