#include "enginemsg_utils.h"
#include <cstring>

namespace nitroapi
{
    PEngineMsg FindEngineMsgByName(PEngineMsg enigne_msg_start, const char *msg_name)
    {
        PEngineMsg cur_msg = enigne_msg_start;

        while (strcmp(cur_msg->name, OFF_SVC_MESSAGES_P) != 0)
        {
            if (strcmp(cur_msg->name, msg_name) == 0)
                return cur_msg;

            cur_msg++;
        }

        return nullptr;
    }
}