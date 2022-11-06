#pragma once

#include "platform_detecction.hpp"

#ifdef C_PLATFORM_WINDOWS
#ifndef NOMINMAX
// See github.com/skypjack/entt/wiki/Frequently-Asked-Questions#warning-c4003-the-min-the-max-and-the-macro
#define NOMINMAX
#endif
#endif

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <array>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <filesystem>
#include <map>

namespace Converter {

    template <typename T>
    using Scope = std::unique_ptr<T>;
    template <typename T, typename... Args>
    constexpr Scope<T> CreateScope(Args&&... args) {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template <typename T>
    using Ref = std::shared_ptr<T>;
    template <typename T, typename... Args>
    constexpr Ref<T> CreateRef(Args&&... args) {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

}  // namespace Converter

#ifdef C_DEBUG
#if defined(C_PLATFORM_WINDOWS)
#define C_DEBUGBREAK() __debugbreak()
#elif defined(C_PLATFORM_LINUX)
#include <signal.h>
#define C_DEBUGBREAK() raise(SIGTRAP)
#else
#error "Platform doesn't support debugbreak yet!"
#endif
#define C_ENABLE_ASSERTS
#else
#define C_DEBUGBREAK()
#endif

#include "log/log.hpp"
#include "core/assert.hpp"
