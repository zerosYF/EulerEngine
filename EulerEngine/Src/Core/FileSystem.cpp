#include"gkpch.h"
#include"FileSystem.h"
namespace EulerEngine {
	Buffer FileSystem::ReadFileBinary(const std::filesystem::path& filepath)
	{
		std::ifstream stream(filepath, std::ios::binary | std::ios::ate);
		if (!stream) {
			return {};
		}
		std::streampos end = stream.tellg();
		stream.seekg(0, std::ios::beg);
		unsigned int size = end - stream.tellg();
		if (size == 0) {
			return {};
		}
		Buffer buffer(size);
		stream.read(buffer.As<char>(), size);
		return buffer;
	}
}