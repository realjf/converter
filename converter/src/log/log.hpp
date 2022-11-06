#pragma once
#include "core/core.hpp"

#define SPDLOG_HEADER_ONLY
#include <spdlog/spdlog.h>
#define FMT_HEADER_ONLY
#include <spdlog/fmt/ostr.h>

namespace Converter {
    class Log {
       public:
        static void Init();

        static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
        static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

       private:
        static Ref<spdlog::logger> s_CoreLogger;
        static Ref<spdlog::logger> s_ClientLogger;
    };

}  // namespace Converter

// Core Log Macros
#define C_CORE_ERROR(...) ::Converter::Log::GetCoreLogger()->error(__VA_ARGS__)
#define C_CORE_WARN(...) ::Converter::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define C_CORE_INFO(...) ::Converter::Log::GetCoreLogger()->info(__VA_ARGS__)
#define C_CORE_TRACE(...) ::Converter::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define C_CORE_CRITICAL(...) ::Converter::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client Log Macros
#define C_ERROR(...) ::Converter::Log::GetClientLogger()->error(__VA_ARGS__)
#define C_WARN(...) ::Converter::Log::GetClientLogger()->warn(__VA_ARGS__)
#define C_INFO(...) ::Converter::Log::GetClientLogger()->info(__VA_ARGS__)
#define C_TRACE(...) ::Converter::Log::GetClientLogger()->trace(__VA_ARGS__)
#define C_CRITICAL(...) ::Converter::Log::GetClientLogger()->critical(__VA_ARGS__)
