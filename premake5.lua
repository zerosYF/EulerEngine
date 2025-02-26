workspace "EulerEngine"
	architecture "x64"
	configurations{
		"Debug",
		"Release",
		"Dist"
	}
	toolset "v143"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["Glad"] = "EulerEngine/Vendor/Glad/include"
IncludeDir["ImGui"] = "EulerEngine/Vendor/ImGui"
IncludeDir["Entt"] = "EulerEngine/Vendor/Entt/include"
IncludeDir["Yaml_cpp"] = "EulerEngine/Vendor/Yaml-cpp/include"
IncludeDir["ImGuizmo"] = "EulerEngine/Vendor/ImGuizmo"
include "EulerEngine/Vendor/Glad"
include "EulerEngine/Vendor/ImGui"
include "EulerEngine/Vendor/Yaml-cpp"

project "EulerEngine"
	location "EulerEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"
	characterset "Unicode"
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-interm/" .. outputdir .. "/%{prj.name}")

	defines { "YAML_CPP_STATIC_DEFINE" }

	files{
		"%{prj.name}/Src/**.h",
		"%{prj.name}/Src/**.cpp",
		"%{prj.name}/External/include/glm/**.hpp",
		"%{prj.name}/External/include/glm/**.inl",
		"%{prj.name}/External/include/stb_image/**.cpp",
		"%{prj.name}/External/include/stb_image/**.h",
		"%{prj.name}/Vendor/ImGuizmo/ImGuizmo.h",
		"%{prj.name}/Vendor/ImGuizmo/ImGuizmo.cpp",
	}
	includedirs{
		"%{prj.name}/Src",
		"%{prj.name}/Vendor/spdlog/include",
		"%{prj.name}/External/include",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.Entt}",
		"%{IncludeDir.Yaml_cpp}",
		"%{IncludeDir.ImGuizmo}",
	}
	libdirs{
		"%{prj.name}/External/libs"
	}
	links{
		"glfw3",
		"Glad",
		"ImGui",
		"Yaml-cpp",
		"opengl32"
	}

	filter "system:windows"
		--systemversion "latest" 
		buildoptions { "/utf-8" } 
		defines{
			"KINK_PLATFORM_WINDOWS",
			"KINK_BUILD_DLL",
			"_WINDLL",
			"KINK_ENABLE_ASSERTS"
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
	--must be at the end of the file
	pchheader "gkpch.h"
	pchsource "%{prj.name}/Src/gkpch.cpp"
	filter "files:%{prj.name}/Vendor/ImGuizmo/**.cpp"
		flags {"NoPCH"}

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"
	characterset "Unicode"
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-interm/" .. outputdir .. "/%{prj.name}")
	defines { "YAML_CPP_STATIC_DEFINE" }
	files{
		"%{prj.name}/Src/**.h",
		"%{prj.name}/Src/**.cpp"
	}
	includedirs{
		"EulerEngine/Vendor/spdlog/include",
		"EulerEngine/Src",
		"EulerEngine/External/include",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.Entt}",
		"%{IncludeDir.Yaml_cpp}",
		"%{IncludeDir.ImGuizmo}",
	}
	links{
		"EulerEngine"
	}


	filter "system:windows"
		--systemversion "latest"
		buildoptions { "/utf-8" } 
		defines{
			"KINK_PLATFORM_WINDOWS",	
		}
	filter "configurations:Debug"
		defines "KINK_DEBUG"
		runtime "Debug"
		symbols "On"
	filter "configurations:Release"
		defines "KINK_RELEASE"
		runtime "Release"
		symbols "On"
	filter "configurations:Dist"
		defines "KINK_DIST"
		runtime "Release"
		symbols "On"

project "Editor"
	location "Editor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"
	characterset "Unicode"
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-interm/" .. outputdir .. "/%{prj.name}")
	defines { "YAML_CPP_STATIC_DEFINE" }
	files{
		"%{prj.name}/Src/**.h",
		"%{prj.name}/Src/**.cpp"
	}
	includedirs{
		"EulerEngine/Vendor/spdlog/include",
		"EulerEngine/Src",
		"EulerEngine/External/include",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.Entt}",
		"%{IncludeDir.Yaml_cpp}",
		"%{IncludeDir.ImGuizmo}",
	}
	links{
		"EulerEngine"
	}


	filter "system:windows"
		--systemversion "latest"
		buildoptions { "/utf-8" } 
		defines{
			"KINK_PLATFORM_WINDOWS",	
		}
	filter "configurations:Debug"
		defines "KINK_DEBUG"
		runtime "Debug"
		symbols "On"
	filter "configurations:Release"
		defines "KINK_RELEASE"
		runtime "Release"
		symbols "On"
	filter "configurations:Dist"
		defines "KINK_DIST"
		runtime "Release"
		symbols "On"