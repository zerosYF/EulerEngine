#pragma once
namespace EulerEngine {

	class EulerContext {
	public:
		virtual void Initialize() = 0;
		virtual void SwapBuffers() = 0;
	};
}