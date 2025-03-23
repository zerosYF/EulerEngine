#pragma once
#include"Core/EulerBuffer.h"
#include<filesystem>
namespace EulerEngine{
	class FileSystem {
	public:
		static Buffer ReadFileBinary(const std::filesystem::path& filePath);
	};

}