#include "SearchConfig.h"

#include <utility>
#include <iostream>

namespace nitroapi
{
    SearchConfig::SearchConfig(std::string search_string, SearchType search_type) :
        search_string(std::move(search_string)),
        search_type(search_type),
        offset(0)
    { }

    SearchConfig::SearchConfig(uint32_t offset) :
        search_string(),
        search_type(SearchType::Offset),
        offset(offset)
    { }

    SearchConfig::SearchConfig(std::string search_string, uint32_t offset, SearchType search_type) :
        search_string(std::move(search_string)),
        offset(offset),
        search_type(search_type)
    { }

    uint32_t SearchConfig::FindAddress(MemScanner& mem_scanner) const
    {
        switch (search_type)
        {
            case SearchType::PatternEx:
                return (uint32_t)mem_scanner.FindPattern2(search_string);

            case SearchType::ExportFunc:
                return (uint32_t)nitro_utils::GetProcAddress(mem_scanner.Module(), search_string.c_str());

            case SearchType::Offset:
                return (uint32_t)(mem_scanner.ModuleStart() + offset);

            case SearchType::PatternAndOffset:
                return (uint32_t)mem_scanner.FindPattern(search_string.c_str()) + offset;

            case SearchType::PatternExAndOffset:
                return (uint32_t)mem_scanner.FindPattern2(search_string) + offset;

            case SearchType::NotPresent:
                return 0;

            default:
            case SearchType::Pattern:
                return (uint32_t)mem_scanner.FindPattern(search_string.c_str());
        }
    }
}