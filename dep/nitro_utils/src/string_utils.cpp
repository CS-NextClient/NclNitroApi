#include <string>
#include <vector>

#ifdef _WIN32
#include <Windows.h>
#endif

namespace nitro_utils
{
    void split(const std::string& str, const std::string& splitBy, std::vector<std::string>& tokens)
    {
        tokens.push_back(str);

        size_t splitAt;
        size_t splitLen = splitBy.size();
        std::string frag;

        while(true)
        {
            frag = tokens.back();
            splitAt = frag.find(splitBy);
            if (splitAt == std::string::npos)
                break;

            tokens.back() = frag.substr(0, splitAt);
            tokens.push_back(frag.substr(splitAt+splitLen, frag.size()-(splitAt+splitLen)));
        }
    }

    size_t split_in_args(const std::string& str, std::vector<std::string>& args, size_t maxArgs)
    {
        size_t argsNum = 0;
        size_t len = str.length();
        bool qot = false, sqot = false;
        int argLen;

        for (int i = 0; i < len; i++)
        {
            int start = i;
            if (str[i] == '\"')
                qot = true;
            else if(str[i] == '\'')
                sqot = true;

            if (qot)
            {
                i++;
                start++;
                while (i < len && str[i] != '\"')
                    i++;
                if (i < len)
                    qot = false;
                argLen = i - start;
                i++;
            }
            else if(sqot)
            {
                i++;
                while (i < len && str[i] != '\'')
                    i++;
                if (i < len)
                    sqot = false;
                argLen = i - start;
                i++;
            }
            else
            {
                while(i < len && str[i] != ' ')
                    i++;
                argLen = i - start;
            }
            args.push_back(str.substr(start, argLen));
            if (++argsNum >= maxArgs)
                return argsNum;
        }
        return argsNum;
    }

#ifdef _WIN32
    std::string ConvertCurrentCodepageToUtf8(const std::string_view& str)
    {
        int size = MultiByteToWideChar(CP_ACP, MB_COMPOSITE, str.data(), str.length(), nullptr, 0);

        std::wstring utf16_str(size, '\0');
        MultiByteToWideChar(CP_ACP, MB_COMPOSITE, str.data(), str.length(), &utf16_str[0], size);

        int utf8_size = WideCharToMultiByte(CP_UTF8, 0, utf16_str.c_str(), str.length(), nullptr, 0, nullptr, nullptr);
        std::string utf8_str(utf8_size, '\0');
        WideCharToMultiByte(CP_UTF8, 0, utf16_str.c_str(), str.length(), &utf8_str[0], utf8_size, nullptr, nullptr);

        return utf8_str;
    }
#endif
}