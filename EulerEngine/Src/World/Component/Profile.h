#pragma once
#include"glm/glm.hpp"
namespace EulerEngine {
	struct Profile{
		std::string Tag;
		Profile() = default;
		Profile(const Profile& other) = default;
		Profile(const std::string& tag)
			:Tag(tag) {
		}
	};
}
