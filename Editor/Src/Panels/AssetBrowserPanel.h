#pragma once
#include<filesystem>
namespace EulerEngine {
	class AssetBrowserPanel {
	public:
		AssetBrowserPanel();
		void OnImGuiRender();
	private:
		std::filesystem::path m_CurrentDirectory;
	};
}