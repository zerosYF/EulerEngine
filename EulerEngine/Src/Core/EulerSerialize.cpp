#include"EulerSerialize.h"
using namespace EulerEngine;
bool Serialize::RegisterObj(GameObject* obj) {
	if (!obj) {
		return 0;
	}
	for (unsigned int i = 0; i < objs.size();i++) {
		if (objs[i] == obj) {
			return 0;
		}
	}
	objs.push_back(obj);
	return 1;
}
bool Serialize::RegisterObjs(GameObject* obj) {
	return true;
}