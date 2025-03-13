workspace "EulerEngine"
	architecture "x86_64"
	configurations{
		"Debug",
		"Release",
		"Dist"
	}
	startproject "Editor"
	--toolset "v143"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["ImGui"] = "%{wks.location}/EulerEngine/Vendor/ImGui"
IncludeDir["Yaml_cpp"] = "%{wks.location}/EulerEngine/Vendor/Yaml-cpp/include"
IncludeDir["ImGuizmo"] = "%{wks.location}/EulerEngine/Vendor/ImGuizmo"
IncludeDir["Box2d"] = "%{wks.location}/EulerEngine/Vendor/Box2d/include"
IncludeDir["Box2d_src"] = "%{wks.location}/EulerEngine/Vendor/Box2d/src"

Library = {}
Library["WinSock"] = "Ws2_32.lib"
Library["WinMM"] = "Winmm.lib"
Library["WinVersion"] = "Version.lib"
Library["BCrypt"] = "Bcrypt.lib"

group "Dependences"
	include"EulerEngine/Vendor/ImGui"
	include"EulerEngine/Vendor/Yaml-cpp"
	include"EulerEngine/Vendor/Box2d"
group ""

group "Core"
	include"EulerEngine"
	include"EulerScript"
group ""

group "Tools"
	include"Editor"
	include"Sandbox"
group ""