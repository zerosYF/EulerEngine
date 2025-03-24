#pragma once
#include"Core/Global/EulerUUID.h"
namespace EulerEngine{
	struct IDCom {
		EulerUUID ID;
		IDCom() = default;
		IDCom(const IDCom& com) = default;
	};
}