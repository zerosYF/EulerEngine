#pragma once
#include"Core.h"
#include"../Core/Events/Event.h"
namespace EulerEngine {
	class KINK_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
	};

	Application* CreateApplication();
}

