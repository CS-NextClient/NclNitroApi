#include "NitroApi.h"

#include <ranges>
#include <filesystem>

#ifdef _WIN32
#include <Windows.h>
#endif

#include <easylogging++.h>

#include "nitroapi/handler_helper/Handler.h"
#include "modules/windows/WindowsModule.h"
#include "modules/engine/EngineAddressProvider8684Windows.h"
#include "modules/engine/EngineAddressProvider8684Linux.h"
#include "modules/client/ClientAddressProvider8684Windows.h"
#include "modules/client/ClientAddressProvider8684Linux.h"
#include "modules/sdl2/SDL2AddressProvider.h"

#ifdef NITROAPI_USE_PROFILER
#include "profiler.h"
bool g_ProfilerInsideFrame = false;
#endif

#ifndef NITRO_API_STATIC
INITIALIZE_EASYLOGGINGPP
#endif

namespace nitroapi
{
    static nitroapi::NitroApi g_NitroApi;
    NitroApiInterface* GetNitroApi() { return &g_NitroApi; }

    static GlobalExceptionHandlerFunc g_WriteMiniDumpCallback = nullptr;

#ifndef NITRO_API_STATIC
    EXPOSE_SINGLE_INTERFACE_GLOBALVAR(NitroApi, NitroApiInterface, NITROAPI_INTERFACE_VERSION, g_NitroApi);
#endif

    NitroApi::~NitroApi()
    {
        g_WriteMiniDumpCallback = nullptr;
    }

    void NitroApi::WriteLog(const char* tag, const char* message)
    {
        el::Loggers::getLogger(tag)->info(message);
    }

    void NitroApi::SetSEHCallback(GlobalExceptionHandlerFunc callback)
    {
        g_WriteMiniDumpCallback = callback;
    }

    GlobalExceptionHandlerFunc NitroApi::GetSEHCallback()
    {
        return g_WriteMiniDumpCallback;
    }

    bool NitroApi::Initialize(ICommandLine *command_line, IFileSystem* file_system, IRegistry *registry)
    {
        if (is_initialized_)
            return true;

        LOG(INFO) << "---------- Initialize | Begin ----------";

        hook_storage_ = std::make_shared<HookStorage>();

        auto windows_module = std::make_unique<WindowsModule>(hook_storage_, nullptr);
        windows_data_ = windows_module->GetWindowsData();
        modules_.emplace_back("<exe>", std::move(windows_module));

        std::shared_ptr<AddressProviderBase> engine_provider;
        std::string engine_path;
        if (IsWindows())
        {
            engine_path = "hw.dll";
            engine_provider = std::make_shared<EngineAddressProvider8684Windows>();
        }
        else
        {
            engine_path = "hw.so";
            engine_provider = std::make_shared<EngineAddressProvider8684Linux>();
        }
        auto engine_module = std::make_unique<EngineModule>(hook_storage_, engine_provider, this, command_line, file_system, registry);
        engine_data_ = engine_module->GetEngineData();
        modules_.emplace_back(engine_path, std::move(engine_module));

        std::shared_ptr<AddressProviderBase> client_provider;
        std::string client_path;
        if (IsWindows())
        {
            client_path = "cstrike\\cl_dlls\\client.dll";
            client_provider = std::make_shared<ClientAddressProvider8684Windows>();
        }
        else
        {
            client_path = "cstrike/cl_dlls/client.so";
            client_provider = std::make_shared<ClientAddressProvider8684Linux>();
        }
        auto client_module = std::make_unique<ClientModule>(hook_storage_, client_provider);
        client_data_ = client_module->GetClientData();
        modules_.emplace_back(client_path, std::move(client_module));

        if (IsWindows())
        {
            auto sdl2_module = std::make_unique<SDL2Module>(hook_storage_, std::make_shared<SDL2AddressProvider>());
            sdl2_data_ = sdl2_module->GetSDL2Data();
            modules_.emplace_back("sdl2.dll", std::move(sdl2_module));
        }

        for (auto& [path, module]: modules_)
            InvokeLibraryLoaded(path, module);

#ifdef NITROAPI_USE_PROFILER
        SetupProfiler();
#endif

        LOG(INFO) << "---------- Initialize | End ----------";

        is_initialized_ = true;
        return true;
    }

    bool NitroApi::UnInitialize()
    {
        if (!is_initialized_)
            return true;

        is_initialized_ = false;

        LOG(INFO) << "---------- UnInitialize | Begin ----------";

        for (auto& [path, module]: modules_ | std::views::reverse)
            InvokeLibraryUnloading(path, module);

        modules_.clear();
        hook_storage_.reset();

        LOG(INFO) << "---------- UnInitialize | End ----------";

        return true;
    }

    void NitroApi::InvokeLibraryLoaded(const std::string& module_path, ModuleHookData& module_hook_data)
    {
        nitro_utils::SysModule hModule;

        if (module_path == "<exe>")
            hModule = nitro_utils::GetSysModule(nullptr);
        else
            hModule = nitro_utils::LoadSysModule(module_path.c_str());

        if (hModule == nullptr)
        {
            LOG(INFO) << "Module loading " << module_path << " failed (nitro_utils::GetSysModule/nitro_utils::LoadSysModule returns null)";
            return;
        }

        if (module_path == "hw.dll" || module_path == "hw.so")
            RetrieveBuildVersion();

        LOG(INFO) << "Module loading " << module_path << " | Begin";

        module_hook_data.module_handle = hModule;
        module_hook_data.module->OnLibraryLoaded(hModule);

        LOG(INFO) << "Module loading " << module_path << " | End";
    }

    void NitroApi::InvokeLibraryUnloading(const std::string& module_path, ModuleHookData& module_hook_data)
    {
        LOG(INFO) << "Module unloading " << module_path << " | Begin";

        module_hook_data.module->OnLibraryUnload();

        if (module_path != "<exe>")
            nitro_utils::UnloadSysModule(module_hook_data.module_handle);

        module_hook_data.module_handle = nullptr;

        LOG(INFO) << "Module unloading " << module_path << " | End";
    }

#ifdef NITROAPI_USE_PROFILER
    void NitroApi::SetupProfiler()
    {
        static bool filter_result;

        engine_data_->Host_FilterTime += [](float delta, int result) {
            filter_result = result;

            if (!filter_result)
                return;

            g_ProfilerInsideFrame = true;

            OPTICK_FRAME("Frame");
            OPTICK_TAG("Delta", std::to_string(delta * 1000).c_str());

            OPTICK_EVENT("Host_FrameInternal");
        };

        engine_data_->Host_FrameInternal += [](float delta) {
            if (!filter_result)
                return;

            g_ProfilerInsideFrame = false;

            ::Optick::EndFrame();
			::Optick::Update();
        };
    }
#endif

    void NitroApi::RetrieveBuildVersion()
    {

    }

    void NitroApi::GetVersion(char* buffer, int size)
    {
        if (buffer != nullptr)
            V_strncpy(buffer, NITROAPI_INTERFACE_VERSION ", " __DATE__ " " __TIME__, size);
    }

#ifdef _WIN32
    LONG WINAPI GlobalExceptionHandlerWin32(EXCEPTION_POINTERS* exception_pointers)
    {
        if (g_WriteMiniDumpCallback != nullptr)
        {
            g_WriteMiniDumpCallback(exception_pointers);
            return EXCEPTION_EXECUTE_HANDLER;
        }

        return EXCEPTION_CONTINUE_SEARCH;
    }
#endif
}