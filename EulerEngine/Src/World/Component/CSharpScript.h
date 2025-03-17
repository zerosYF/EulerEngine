#pragma once
#include<string>
namespace EulerEngine {
	struct CSharpScript {
		std::string Name;
		CSharpScript() = default;
		CSharpScript(const CSharpScript& other) = default;
	};
}