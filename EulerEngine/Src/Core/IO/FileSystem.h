#pragma once
#include"Core/Memory/EulerBuffer.h"
#include<filesystem>
namespace EulerEngine{
	class FileSystem {
	public:
		static Buffer ReadFileBinary(const std::filesystem::path& filePath);
		static std::string ReadFileText(const std::filesystem::path& filePath);
		static const std::string GetFileName(const std::string& path);
	};

}