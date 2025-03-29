#include"gkpch.h"
#include"AssetBrowserPanel.h"
#include<../ImGui/imgui.h>
#include"GutKink/Core.h"
namespace EulerEngine {
	AssetBrowserPanel::AssetBrowserPanel():m_BasePath(Project::GetActiveProjectDir() / Project::GetAssetDir()), m_CurrentDirectory(m_BasePath) {
		m_DirectoryIcon = ResourceLibrary::LoadTexture2DInner("Icons/DirectoryIcon.png");
		m_FileIcon = ResourceLibrary::LoadTexture2DInner("Icons/FileIcon.png");
	}

	void AssetBrowserPanel::OnImGuiRender()
	{
		ImGui::Begin("Asset Browser");
		if (m_CurrentDirectory != std::filesystem::path(m_BasePath)) {
			if (ImGui::Button("..")) {
				m_CurrentDirectory = m_CurrentDirectory.parent_path();
			}
		}

		static float padding = 16.0f;
		static float thumbnailSize = 64.0f;
		float cellSize = thumbnailSize + padding;

		float panelWidth = ImGui::GetContentRegionAvail().x;
		int columnColunt = (int)(panelWidth / cellSize);
		if (columnColunt < 1) {
			columnColunt = 1;
		}

		ImGui::Columns(columnColunt, 0, false);
		for (auto& p: std::filesystem::directory_iterator(m_CurrentDirectory)) {
			const auto& path = p.path();
			std::string filenameString = path.filename().string();

			Ref<Texture2D> icon = p.is_directory()? m_DirectoryIcon : m_FileIcon;
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));\
			ImGui::PushID(filenameString.c_str());
			ImGui::ImageButton("", (ImTextureID)icon->GetRendererID(), {thumbnailSize, thumbnailSize}, {0, 1}, {1, 0});
			ImGui::PopID();
			if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID)) {

				std::filesystem::path relativePath(path);
				const wchar_t* itemPath = relativePath.c_str();
				//std::cout << relativePath << std::endl;
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