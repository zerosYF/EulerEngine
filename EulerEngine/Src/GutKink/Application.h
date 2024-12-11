#pragma once
#include"Core.h"
namespace EulerEngine {
	class KINK_API Application
	{
	public:
		Application();
		~Application();
		void Run();
	};

	Application* CreateApplication();
}

