#pragma once
#include"ComponentBase.h"
#include"glm/glm.hpp"
namespace EulerEngine {
	struct TagComponent : public ComponentBase {
		std::string Tag;
		TagComponent() = default;
		TagComponent(const TagComponent& other) = default;
		TagComponent(const std::string& tag)
			:Tag(tag) {
		}
	};
}
