#pragma once
#include<vector>
#include"EulerObject.h"
using namespace std;
namespace EulerEngine {
	class Serialize {
		enum {
			SAVE,
			LOAD,
			LINK,
			REGISTER,
			SIZE,
			POSTLOAD,
		};
		unsigned int streamFlag;
		vector<GameObject*> objs;
		bool RegisterObj(GameObject* obj);
		bool RegisterObjs(GameObject* obj);
	};
}