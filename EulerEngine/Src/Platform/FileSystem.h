#pragma once
#include<vector>
#include<filesystem>
namespace EulerEngine {
	class FileSystem {
	public:
		std::vector<std::filesystem::path> getFiles(const std::filesystem::path& directory) {
			std::vector<std::filesystem::path> files;
			for (const auto&directory_entry : std::filesystem::recursive_directory_iterator{directory}) {
				if (directory_entry.is_regular_file()) files.push_back(directory_entry);
			}
			return files;
		}
	};
}