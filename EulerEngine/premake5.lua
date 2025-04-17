project "EulerEngine"
	kind "StaticLib"
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
		"External/include/glm/**.hpp",
		"External/include/glm/**.inl",
		"External/include/stb_image/**.cpp",
		"External/include/stb_image/**.h",
		"External/include/glad/**.c",
		"External/include/glad/glad/**.h",
		"External/include/glad/KHR/**.h",
		"External/include/entt/**.hpp",
		"External/include/filewatch/**.h",
		"Vendor/ImGuizmo/ImGuizmo.h",
		"Vendor/ImGuizmo/ImGuizmo.cpp", 
		"Vendor/Jolt/Jolt/**.h",
		"Vendor/Jolt/Jolt/**.cpp",
	}
	includedirs{
		"Src",
		"External/include",
		"External/include/glad",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.Yaml_cpp}",
		"%{IncludeDir.ImGuizmo}",
		"%{IncludeDir.Box2d}",
		"%{IncludeDir.Box2d_src}",
		"%{IncludeDir.Jolt}",
	}
	libdirs{
		"External/libs",
	}
	links{
		"glfw3",
		"Box2d",
		"ImGui",
		"Yaml-cpp",
		"opengl32",
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
		links{
			"%{Library.WinSock}",
			"%{Library.WinMM}",
			"%{Library.WinVersion}",
			"%{Library.BCrypt}",
		}
	filter "configurations:Debug"
		defines "KINK_DEBUG"
		links{
			"/mono/Deb/libmono-static-sgen",
		}
		runtime "Debug"
		symbols "On"
	filter "configurations:Release"
		defines "KINK_RELEASE"
		links{
			"/mono/Rel/libmono-static-sgen",
		}
		runtime "Release"
		optimize "On"
	filter "configurations:Dist"
		defines "KINK_DIST"
		symbols "On"
	--must be at the end of the file
	pchheader "gkpch.h"
	pchsource "%{prj.name}/Src/gkpch.cpp"

	filter "files:%{prj.name}/Vendor/ImGuizmo/**.cpp"
		flags {"NoPCH"}