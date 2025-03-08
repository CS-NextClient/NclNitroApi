#pragma once

#include <algorithm>
#include <functional>
#include <ranges>
#include <cctype>
#include <locale>
#include <vector>
#include <sstream>

namespace nitro_utils
{
    enum class CompareOptions
    {
        None = 0,
        RegisterIndependent = 1
    };

    static int _fast_to_lower(char c)
    {
        int i = (unsigned char)c;
        if (i < 0x80)
        {
            // Brutally fast branchless ASCII tolower():
            i += (((('A' - 1) - i) & (i - ('Z' + 1))) >> 26) & 0x20;
        }
        else
        {
            i += isupper(i) ? 0x20 : 0;
        }
        return i;
    }

    //
    //  REGISTER FUNCTIONS
    //

    inline void to_lower(std::string& s)
    {
        std::ranges::for_each(s, [](char& c)
        {
            c = _fast_to_lower(c);
        });
    }

    [[nodiscard]] inline std::string to_lower_copy(const std::string& s)
    {
        std::string result = s;

        std::ranges::for_each(result, [](char& c)
        {
            c = _fast_to_lower(c);
        });

        return result;
    }

    inline void to_upper(std::string& s)
    {
        std::ranges::for_each(s, [](char& c)
        {
            c = ::toupper(c);
        });
    }

    [[nodiscard]] inline std::string to_upper_copy(const std::string& s)
    {
        std::string result = s;

        std::ranges::for_each(result, [](char& c)
        {
            c = ::toupper(c);
        });

        return result;
    }

    //
    //  TRIM FUNCTIONS
    //

    constexpr void ltrim(std::string& s, const std::function<bool(unsigned char)>& condition)
    {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), condition));
    }

    constexpr void ltrim(std::string& s)
    {
        ltrim(s, [](unsigned char ch) { return !std::isspace(ch); });
    }

    constexpr void ltrim(std::string& s, char trim_char)
    {
        ltrim(s, [trim_char](unsigned char ch) { return !trim_char; });
    }


    constexpr void rtrim(std::string& s, const std::function<bool(unsigned char)>& condition)
    {
        s.erase(std::find_if(s.rbegin(), s.rend(), condition).base(), s.end());
    }

    constexpr void rtrim(std::string& s)
    {
        rtrim(s, [](unsigned char ch) { return !std::isspace(ch); });
    }

    constexpr void rtrim(std::string& s, char trim_char)
    {
        rtrim(s, [trim_char](unsigned char ch) { return !trim_char; });
    }

    constexpr void trim(std::string& s)
    {
        ltrim(s);
        rtrim(s);
    }

    constexpr void trim(std::string& s, char trim_char)
    {
        ltrim(s, trim_char);
        rtrim(s, trim_char);
    }

    constexpr void trim(std::string& s, const std::function<bool(unsigned char)>& condition)
    {
        ltrim(s, condition);
        rtrim(s, condition);
    }

    constexpr std::string trim_copy(const std::string& s)
    {
        std::string copy = s;
        trim(copy);
        return copy;
    }

    //
    //  REPLACE FUNCTIONS
    //

    // from https://en.cppreference.com/w/cpp/string/basic_string/replace
    constexpr std::size_t replace_all(std::string& inout, const std::string& what, const std::string& with)
    {
        std::size_t count{};
        for (std::string::size_type pos{};
             std::string::npos != (pos = inout.find(what.data(), pos, what.length()));
             pos += with.length(), ++count)
        {
            inout.replace(pos, what.length(), with.data(), with.length());
        }
        return count;
    }

    [[nodiscard]] constexpr std::string replace_all_copy(const std::string& str, const std::string& what, const std::string& with)
    {
        std::string result(str);

        replace_all(result, what, with);

        return result;
    }

    constexpr void replace_nth(std::string& inout, const std::string& what, int nth, const std::string& with)
    {
        size_t start_pos = 0;
        int i = 0;
        while ((start_pos = inout.find(what, start_pos)) != std::string::npos)
        {
            if (i == nth)
            {
                inout.replace(start_pos, what.length(), with);
                break;
            }

            start_pos += what.size();
            i++;
        }
    }

    [[nodiscard]] constexpr std::string replace_nth_copy(const std::string& str, const std::string& what, int nth, const std::string& with)
    {
        std::string result(str);

        replace_nth(result, what, nth, with);

        return result;
    }

    //
    //  SPLIT FUNCTIONS
    //

    void split(const std::string& str, const std::string& splitBy, std::vector<std::string>& tokens);
    size_t split_in_args(const std::string& str, std::vector<std::string>& args, size_t maxArgs);

    //
    //  CODEPAGE CONVERT FUNCTIONS
    //

#ifdef _WIN32
    [[nodiscard]] std::string ConvertCurrentCodepageToUtf8(const std::string_view& str);
#endif

    //
    // VARIOUS FUNCTIONS
    //

    [[nodiscard]] constexpr bool contains(const std::string& str, const std::string& sub, CompareOptions compare_options = CompareOptions::None)
    {
        if (compare_options == CompareOptions::RegisterIndependent)
        {
            auto found = std::ranges::search(str, sub, [](char a, char b) { return _fast_to_lower(a) == _fast_to_lower(b); });
            return !found.empty();
        }

        return str.find(sub) != std::string::npos;
    }

    [[nodiscard]] constexpr bool equals(const std::string& a, const std::string& b, CompareOptions compare_options = CompareOptions::None)
    {
        if (compare_options == CompareOptions::RegisterIndependent)
        {
            return std::ranges::equal(a, b, [](char a, char b) { return _fast_to_lower(a) == _fast_to_lower(b); });
        }

        return a == b;
    }

    [[nodiscard]] constexpr bool start_with(const std::string& str, const std::string& sub, CompareOptions compare_options = CompareOptions::None)
    {
        if (compare_options == CompareOptions::RegisterIndependent)
        {
            auto it = std::ranges::mismatch(str, sub, [](char a, char b) { return _fast_to_lower(a) == _fast_to_lower(b); });
            return it.in2 == sub.end();
        }

        return str.starts_with(sub);
    }

    template <class Iterator>
    [[nodiscard]] std::string join(const Iterator begin, const Iterator end, const std::string& delimiter)
    {
        std::stringstream ss;
        for (Iterator it = begin; it != end; it++)
        {
            ss << *it;

            if (std::next(it) != end)
                ss.write(delimiter.data(), delimiter.size());
        }
        return ss.str();
    }
}
