#pragma once
#include <functional>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>

namespace nitro_utils
{
    struct transparent_string_hash
    {
        using is_transparent = void;

        size_t operator()(std::string_view value) const noexcept
        {
            return std::hash<std::string_view>{}(value);
        }

        size_t operator()(const std::string& value) const noexcept
        {
            return std::hash<std::string_view>{}(value);
        }

        size_t operator()(const char* value) const noexcept
        {
            return std::hash<std::string_view>{}(value);
        }
    };

    struct transparent_string_equal
    {
        using is_transparent = void;

        bool operator()(std::string_view lhs, std::string_view rhs) const noexcept
        {
            return lhs == rhs;
        }
    };

    template <typename TValue>
    using transparent_string_map = std::unordered_map<std::string, TValue, transparent_string_hash, transparent_string_equal>;

    using transparent_string_set = std::unordered_set<std::string, transparent_string_hash, transparent_string_equal>;
} // namespace nitro_utils
