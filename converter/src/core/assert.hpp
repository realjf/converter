#pragma once

#include "core/core.hpp"

#ifdef C_ENABLE_ASSERTS

// Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
#define C_INTERNAL_ASSERT_IMPL(type, check, msg, ...) \
    {                                                 \
        if (!(check)) {                               \
            C##type##ERROR(msg, __VA_ARGS__);         \
            C_DEBUGBREAK();                           \
        }                                             \
    }
#define C_INTERNAL_ASSERT_WITH_MSG(type, check, ...) C_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
#define C_INTERNAL_ASSERT_NO_MSG(type, check) C_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", C_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

#define C_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
#define C_INTERNAL_ASSERT_GET_MACRO(...) C_EXPAND_MACRO(C_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, C_INTERNAL_ASSERT_WITH_MSG, C_INTERNAL_ASSERT_NO_MSG))

// Currently accepts at least the condition and one additional parameter (the message) being optional
#define C_ASSERT(...) C_EXPAND_MACRO(C_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__))
#define C_CORE_ASSERT(...) C_EXPAND_MACRO(C_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__))
#else
#define C_ASSERT(...)
#define C_CORE_ASSERT(...)
#endif
