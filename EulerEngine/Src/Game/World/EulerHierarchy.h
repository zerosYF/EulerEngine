#pragma once
#include<string>
#include<unordered_map>
#include<memory>
#include"../EulerObject.h"
namespace EulerEngine {
	/*class Hierarchy {
		using GameObjects = std::unordered_map<GameObjectID, std::shared_ptr<GameObject>>;
	public:
		void clear();
		void load();
		bool unload();
		bool save();
		void update(float deltaTime);
		const std::string& getResUrl() const { return m_resUrl; }
		const GameObjects& getGameObjects() const { return m_objects; }
		const std::weak_ptr<GameObject> getGameObjectByID(GameObjectID id) const;
	protected:
		bool m_isLoaded{ false };
		std::string m_resUrl;
		GameObjects m_objects;
	};*/
}