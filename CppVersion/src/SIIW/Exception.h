#pragma once

#include <string>

namespace SIIW
{
	class Exception
	{
	public:
		Exception(const std::string& message) : reason(message) {};
		const std::string reason;
	};
}