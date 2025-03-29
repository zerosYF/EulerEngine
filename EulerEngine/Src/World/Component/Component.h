#pragma once
#include"IDCom.h"
#include"Transform.h"
#include"Profile.h"
#include"Camera.h"

#include"NativeScript.h"
#include"CSharpScript.h"

#include"MeshFilter.h"
#include"MeshRenderer.h"
#include"SpriteRenderer.h"

#include"Rigidbody2D.h"
#include"BoxCollider2D.h"
#include"CircleCollider2D.h"
namespace EulerEngine {
	template<typename... Component>
	struct ComponentGroup {

	};
	using AllComponents = ComponentGroup<
		IDCom, Transform, Profile,Camera, 
		NativeScript,CSharpScript, 
		MeshFilter, MeshRenderer, SpriteRenderer,
		Rigidbody2D, BoxCollider2D, CircleCollider2D
		>;
}