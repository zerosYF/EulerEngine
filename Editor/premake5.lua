project "Editor" 
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "Off"
	characterset "Unicode"
	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-interm/" .. outputdir .. "/%{prj.name}")
	defines { "YAML_CPP_STATIC_DEFINE" }

	files{
		"Src/**.h",
		"Src/**.cpp",
	}
	includedirs{
		"%{wks.location}/EulerEngine/Src",
		"%{wks.location}/EulerEngine/External/include",
		"%{wks.location}/EulerEngine/External/include/glad",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.Yaml_cpp}",
		"%{IncludeDir.ImGuizmo}",
		"%{IncludeDir.Box2d}",
		"%{IncludeDir.Box2d_src}",
		"%{IncludeDir.Jolt}",
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
		symbols "On"
	filter "configurations:Release"
		defines "KINK_RELEASE"
		symbols "On"
	filter "configurations:Dist"
		defines "KINK_DIST"
		symbols "On"