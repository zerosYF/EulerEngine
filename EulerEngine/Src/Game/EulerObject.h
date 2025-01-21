#pragma once
#include<tchar.h>
#include<vector>
#include<memory>
#include<atomic>
#include<iostream>
#include"Component/ComponentBase.h"
namespace EulerEngine {
	//using GameObjectID = size_t;
	//const GameObjectID k_invalidID = 1000;
	//class ObjectIDAllocator {
	//public:
	//	static GameObjectID allocate() {
	//		atomic<GameObjectID> newID = m_nextID.load();
	//		m_nextID++;
	//		if (m_nextID > k_invalidID) {
	//			std::cout << "����ID overflow" << endl;
	//			return 0;
	//		}
	//		return newID;
	//	}
	//private:
	//	static  atomic<GameObjectID> m_nextID;
	//};
	//class GameObject:public enable_shared_from_this<GameObject>{
	//	//����thisָ���ȡʹ��shared_ptr
	//public:
	// 	virtual ~GameObject() = 0;
	//	GameObject(GameObjectID id) :m_id(id) {}
	//	virtual void update(double deltaTime);
	//	bool load();
	//	void save();
	//	GameObjectID getID() const { return m_id; }
	//	bool hasComponent(std::string componentName) const;

	//private:
	//	GameObjectID m_id{k_invalidID};
	//	std::string m_name;
	//	std::string m_infoUrl;
	//	std::vector<ComponentBase*> m_components;
	//};
}