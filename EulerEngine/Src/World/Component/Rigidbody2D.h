#pragma once
#include"box2d/base.h"
#include"box2d/box2d.h"
namespace EulerEngine {
	struct Rigidbody2D {
		enum class BodyType { Static = 0, Dynamic = 1, Kinematic = 2 };
		BodyType Type = BodyType::Static;
		bool FixedRotation = false;
		float Mass = 1.0f;
		float LinearDamping = 0.0f;
		float AngularDamping = 0.0f;
		b2BodyId RuntimeBody;
		Rigidbody2D() = default;
		Rigidbody2D(const Rigidbody2D&) = default;

	};
}
