#pragma once

#include <memory>
#include <spdlog/spdlog.h>

namespace Acroy
{
    class Log
    {
    public:
        static void Init();

        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };
}

// Core Logger Macros
#define ACROY_CORE_TRACE(...) ::Acroy::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define ACROY_CORE_INFO(...)  ::Acroy::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ACROY_CORE_WARN(...)  ::Acroy::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ACROY_CORE_ERROR(...) ::Acroy::Log::GetCoreLogger()->error(__VA_ARGS__)
#define ACROY_CORE_FATAL(...) ::Acroy::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client Logger Macros
#define ACROY_TRACE(...)      ::Acroy::Log::GetClientLogger()->trace(__VA_ARGS__)
#define ACROY_INFO(...)       ::Acroy::Log::GetClientLogger()->info(__VA_ARGS__)
#define ACROY_WARN(...)       ::Acroy::Log::GetClientLogger()->warn(__VA_ARGS__)
#define ACROY_ERROR(...)      ::Acroy::Log::GetClientLogger()->error(__VA_ARGS__)
#define ACROY_FATAL(...)      ::Acroy::Log::GetClientLogger()->critical(__VA_ARGS__)

#define ACROY_ASSERT(x, ...) { if(!(x)) { ACROY_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __builtin_trap(); } }
#define ACROY_CORE_ASSERT(x, ...) { if(!(x)) { ACROY_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __builtin_trap(); } }
