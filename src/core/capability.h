#ifndef CAPABILITY_H_
#define CAPABILITY_H_

#include <cstdint>
#include <functional>
#include <string>
#include <variant>

namespace BB::Core::Capability {


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


struct Failure {
	FailureSemantic kind;
	std::string message;
};

template <typename T>
class Result {
public:
  static Result Ok(T value)
  {
      return Result(std::move(value));
  }

  static Result Fail(Failure f)
  {
      return Result(std::move(f));
  }

  bool IsOk() const
  {
      return std::holds_alternative<T>(data_);
  }

  const T &Value() const
  {
      return std::get<T>(data_);
  }
  const Failure &Error() const
  {
      return std::get<Failure>(data_);
  }

private:
  std::variant<T, Failure> data_;
  explicit Result(T v) : data_(std::move(v)) {}
  explicit Result(Failure f) : data_(std::move(f)) {}
};


namespace AppLaunch {
struct Input {
    std::string name;
};
struct Output {
    int pid;
};
}

namespace FsMove {
struct Input {
	std::string source;
	std::string destination;
};
struct Output {};
}


}

#endif // CAPABILITY_H_
