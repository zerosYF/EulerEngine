#include"gkpch.h"
#include"FileSystem.h"
#include"Core/Logs/EulerLog.h"
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
	std::string FileSystem::ReadFileText(const std::filesystem::path& filePath)
	{
		std::ifstream stream;
		stream.exceptions(std::ifstream::badbit | std::ifstream::failbit);
		try {
			stream.open(filePath);
			std::stringstream StringStream;
			StringStream << stream.rdbuf();
			std::string shaderSource = StringStream.str();
			return shaderSource;
		}
		catch (std::ifstream::failure e) {
			KINK_CORE_ERROR("read file error: {0}", std::string(e.what()));
		}
		return std::string();
	}
	const std::string FileSystem::GetFileName(const std::string& path)
	{
		auto lastSlash = path.find_last_of("/\\");
		lastSlash = lastSlash == path.npos ? 0 : lastSlash + 1;
		auto lastDot = path.rfind('.');
		auto count = lastDot == path.npos ? path.size() - lastSlash : lastDot - lastSlash;
		return path.substr(lastSlash, count);
	}
}