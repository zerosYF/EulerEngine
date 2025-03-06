#pragma once
#include"Core/EulerUUID.h"
namespace EulerEngine{
	struct IDCom {
		EulerUUID ID;
		IDCom() = default;
		IDCom(const IDCom& com) = default;
	};
}