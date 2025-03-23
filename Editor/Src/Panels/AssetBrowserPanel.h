#pragma once
#include<filesystem>
#include"GutKink.h"
namespace EulerEngine {
	class AssetBrowserPanel {
	public:
		AssetBrowserPanel();
		void OnImGuiRender();
	private:
		std::filesystem::path m_BasePath;
		std::filesystem::path m_CurrentDirectory;
		Ref<Texture2D> m_DirectoryIcon;
		Ref<Texture2D> m_FileIcon;
	};
}