#pragma once

#include "../../chain/HandlersChainInterface.h"
#include "../../NitroFunction.h"

#ifdef _WINDOWS
#include <Windows.h>
#endif

namespace nitroapi
{
    struct WindowsData
    {
#ifdef _WINDOWS
        NitroFunction<HMODULE, LPCSTR>  LoadLibraryAFunc;
        NitroFunction<HMODULE, LPCWSTR> LoadLibraryWFunc;
        NitroFunction<BOOL, HMODULE>    FreeLibraryFunc;
        NitroFunction<HCURSOR, HCURSOR> SetCursorFunc;
#endif
    };
}
