#pragma once
#include<memory>
#include"../../Render/System/EulerRender.h"
#include"../../Core/EulerTimer.h"
#include"../World/EulerWorld.h"
#include"../../Resource/SourceManager.h"
namespace EulerEngine {
	class InputSystem;
	class WindowSystem;
	class RenderSystem;
	class TimerSystem;
	class WorldManager;
	class SourceManager;

	class RuntimeGlobalContext {
	public:
		void startSystems();
		void initObject();
		void shutdownSystems();
	public:
		std::shared_ptr<InputSystem> m_input_system;
		std::shared_ptr<WindowSystem> m_window_system;
		std::shared_ptr<RenderSystem> m_render_system;
		std::shared_ptr<TimerSystem> m_timer_system;

		std::shared_ptr<WorldManager> m_world_mgr;
		std::shared_ptr<SourceManager> m_source_mgr;
	};
	extern RuntimeGlobalContext g_global_context;
}