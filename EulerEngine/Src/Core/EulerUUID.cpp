#include"gkpch.h"
#include"EulerUUID.h"
#include<random>
#include<unordered_map>

namespace EulerEngine {
	static std::random_device s_Rd;
	static std::mt19937_64 s_Gen(s_Rd());
	static std::uniform_int_distribution<uint64_t> s_Dis;

	EulerUUID::EulerUUID(): m_UUID(s_Dis(s_Gen))
	{

	}
	EulerUUID::EulerUUID(uint64_t uuid): m_UUID(uuid)
	{

	}
}