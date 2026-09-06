#pragma once

#include <string>
#include <cstdint>

#include "capabilities.h"

namespace Navi::Core::Capability {

enum class CapabilityLevel: std::uint8_t {
	READ_ONLY,
	LOW_RISK_WRITE,
	USER_CONFIRMATION_REQUIRED,
	PRIVILEGED,
	EXTERNAL_NETWORK_EFFECT,
	DESTRUCTIVE,
};

enum class FailureSemantic : std::uint8_t {
	UNAVAILABLE,
	INVALID_INPUT,
	PRECONDITION_FAILED,
	EXECUTION_FAILED,
	AMBIGIOUS,
	UNSUPPORTED_RESULT,
};

enum class PermissionModel : std::uint8_t {
	NONE,
	LOCAL,
	SUDO,
};

enum class Health : std::uint8_t {

	READY,
	NOT_READY,
	STATE_CHANGE_REQUIRED,
};


using input_t = struct {
	std::string name;
	std::string path;
};

using output_t = struct {
	int pid;
};

using capabilities_t = struct {
	std::string family;
	std::string description;
	input_t inputs;
	output_t outputs;
	CapabilityLevel side_effect;
	PermissionModel permission;
	int timeout_ms;
	bool cancellable;
    Health health;
};

} // namespace Navi::Core::Capability
