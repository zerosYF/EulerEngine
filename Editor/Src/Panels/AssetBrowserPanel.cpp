#include"gkpch.h"
#include"AssetBrowserPanel.h"
#include<../ImGui/imgui.h>
namespace EulerEngine {
	static const std::filesystem::path s_AssetsPath = "Assets";
	AssetBrowserPanel::AssetBrowserPanel() {
		m_CurrentDirectory = s_AssetsPath;
	}

	void AssetBrowserPanel::OnImGuiRender()
	{
		ImGui::Begin("Asset Browser");
		if (m_CurrentDirectory != std::filesystem::path(s_AssetsPath)) {
			if (ImGui::Button("..")) {
				m_CurrentDirectory = m_CurrentDirectory.parent_path();
			}
		}

		for (auto& p: std::filesystem::directory_iterator(m_CurrentDirectory)) {
			const auto& path = p.path();
			auto relativePath = std::filesystem::relative(p.path(), s_AssetsPath);
			std::string filenameString = relativePath.filename().string();
			if (p.is_directory()) {
				if (ImGui::Button(filenameString.c_str())) {
					m_CurrentDirectory /= p.path().filename();
				}
			}
			else {
				ImGui::Text(filenameString.c_str());
			}
		}

		ImGui::End();
	}
}