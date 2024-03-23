#pragma once

#include <string>

namespace nitro_utils
{
    bool inet_stonp(const std::string &ip, uint32_t &nIP, uint16_t &nConnPort, bool bDnsResolve = false);
}