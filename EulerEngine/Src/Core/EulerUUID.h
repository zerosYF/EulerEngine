#pragma once
#include<xhash>
namespace EulerEngine {
	class EulerUUID
	{
	public:
		EulerUUID();
		EulerUUID(uint64_t uuid);
		EulerUUID(const EulerUUID& other) = default;
		operator uint64_t() const { return m_UUID; }
	private:
		uint64_t m_UUID;
	};
}
namespace std {
	template<>
	struct hash<EulerEngine::EulerUUID>
	{
		size_t operator()(const EulerEngine::EulerUUID& uuid) const
		{
			return hash<uint64_t>()((uint64_t)uuid);
		}
	};
}