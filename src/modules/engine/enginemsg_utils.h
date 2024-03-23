#pragma once

#include <nitroapi/modules/engine/structs.h>

namespace nitroapi
{
    PEngineMsg FindEngineMsgByName(PEngineMsg enigne_msg_start, const char* msg_name);
}