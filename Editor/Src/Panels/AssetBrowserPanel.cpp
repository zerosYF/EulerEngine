#include"gkpch.h"
#include"AssetBrowserPanel.h"
#include<../ImGui/imgui.h>
#include"GutKink/Core.h"
namespace EulerEngine {
	extern const std::filesystem::path s_AssetsPath = "Assets";
	AssetBrowserPanel::AssetBrowserPanel():m_CurrentDirectory(s_AssetsPath) {
		m_DirectoryIcon = Texture2D::Create("Assets/mytextures/bricks2.jpg");
		m_FileIcon = Texture2D::Create("Assets/mytextures/grass.png");
	}

	void AssetBrowserPanel::OnImGuiRender()
	{
		ImGui::Begin("Asset Browser");
		if (m_CurrentDirectory != std::filesystem::path(s_AssetsPath)) {
			if (ImGui::Button("..")) {
				m_CurrentDirectory = m_CurrentDirectory.parent_path();
			}
		}

		static float padding = 16.0f;
		static float thumbnailSize = 128.0f;
		float cellSize = thumbnailSize + padding;

		float panelWidth = ImGui::GetContentRegionAvail().x;
		int columnColunt = (int)(panelWidth / cellSize);
		if (columnColunt < 1) {
			columnColunt = 1;
		}

		ImGui::Columns(columnColunt, 0, false);
		unsigned int i = 0;
		for (auto& p: std::filesystem::directory_iterator(m_CurrentDirectory)) {
			const auto& path = p.path();
			auto relativePath = std::filesystem::relative(path, s_AssetsPath);
			std::string filenameString = relativePath.filename().string();

			Ref<Texture2D> icon = p.is_directory()? m_DirectoryIcon : m_FileIcon;
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));\
			ImGui::PushID(i++);
			ImGui::ImageButton("", (ImTextureID)icon->GetRendererID(), {thumbnailSize, thumbnailSize}, {0, 1}, {1, 0});
			ImGui::PopID();
			if (ImGui::BeginDragDropSource()) {

				const wchar_t* itemPath = relativePath.c_str();
				ImGui::SetDragDropPayload("AssetBrowserItem", itemPath, (wcslen(itemPath) + 1) * sizeof(wchar_t)); 
				ImGui::EndDragDropSource();
			}

			ImGui::PopStyleColor();
			if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left)) {
				if (p.is_directory()) {
					m_CurrentDirectory /= p.path().filename();
				}
			}
			ImGui::TextWrapped(filenameString.c_str());
			ImGui::NextColumn();
		}
		ImGui::End();
	}
}