project "Sandbox"
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