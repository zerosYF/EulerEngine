#pragma once
#include"glm/glm.hpp"
namespace EulerEngine {
	struct TagComponent{
		std::string Tag;
		TagComponent() = default;
		TagComponent(const TagComponent& other) = default;
		TagComponent(const std::string& tag)
			:Tag(tag) {
		}
	};
}
