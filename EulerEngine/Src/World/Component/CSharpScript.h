#pragma once
#include<string>
namespace EulerEngine {
	struct CSharpScript {
		std::string Name; //32bytes;
		CSharpScript() = default;
		CSharpScript(const CSharpScript& other) = default;
	};
}