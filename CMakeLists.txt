set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")
set(VCPKG_TARGET_TRIPLET "x86-windows-static" CACHE STRING "Vcpkg triplet")

cmake_minimum_required(VERSION 3.21)
project(nitro_api LANGUAGES CXX)
set(OUTPUT_NAME "nitro_api2")

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
set(CMAKE_CXX_STANDARD 23)

set(BUILD_SHARED_LIBS OFF)

if (MSVC)
    if (DEFINED NITRO_API_MSVC_RUNTIME_LIBRARY)
        set(CMAKE_MSVC_RUNTIME_LIBRARY ${NITRO_API_MSVC_RUNTIME_LIBRARY})
    else()
        set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    endif()
endif ()

if (UNIX)
    add_compile_options(-m32 -march=pentium4 -Wno-narrowing)
    add_link_options(-m32 -static-libstdc++ -static-libgcc)
    set(CMAKE_LIBRARY_ARCHITECTURE i386-linux-gnu)
endif()

# funchook options
set(FUNCHOOK_BUILD_SHARED OFF)
set(FUNCHOOK_BUILD_TESTS OFF)
set(FUNCHOOK_INSTALL OFF)
set(FUNCHOOK_CPU "x86")

# explicit dependencies
find_package(OpenGL REQUIRED)
find_package(magic_enum CONFIG REQUIRED)
find_package(xbyak CONFIG REQUIRED)

add_subdirectory(dep/ncl-hl1-source-sdk)
add_subdirectory(dep/nitro_utils)
add_subdirectory(dep/funchook) # while funchook is not in vcpkg, add it as add_subdirectory (PS do NOT make it a sub-module).

add_library(nitro_api SHARED
        dep/easyloggingpp/src/easylogging++.cc
        dep/easyloggingpp/src/easylogging++.h
        src/chain/HandlersChain.h
        src/modules/engine/enginemsg_utils.cpp
        src/modules/engine/enginemsg_utils.h
        src/hook/GenericHookJit.h
        src/hook/GenericHookStatic.h
        src/hook/GenericHookVaformatStatic.h
        src/NitroApi.cpp
        src/NitroApi.h
        src/HookStorage.h
        src/modules/windows/WindowsModule.cpp
        src/modules/windows/WindowsModule.h
        src/ChainExtensions.cpp
        src/LibraryHookListener.h
        include/nitroapi/NitroFunction.h
        src/modules/client/ClientModule.cpp
        src/modules/client/ClientModule.h
        src/modules/engine/EngineModule.cpp
        src/modules/engine/EngineModule.h
        src/modules/engine/EngineAddressProvider8684Windows.cpp
        src/modules/engine/EngineAddressProvider8684Windows.h
        src/AddressProviderBase.h
        src/modules/ModuleBase.cpp
        src/modules/ModuleBase.h
        include/nitroapi/Concepts.h
        src/modules/client/ClientAddressProvider8684Windows.cpp
        src/modules/client/ClientAddressProvider8684Windows.h
        src/SearchConfig.cpp
        src/SearchConfig.h
        include/nitroapi/BuildVersion.h
        include/nitroapi/modules/client/ClientData.h
        include/nitroapi/modules/client/cl_dll/interpolation.h
        include/nitroapi/modules/client/cl_dll/hud.h
        include/nitroapi/modules/client/cl_dll/hud_spectator.h
        include/nitroapi/modules/client/cl_dll/ammo.h
        include/nitroapi/modules/client/cl_dll/health.h
        src/modules/sdl2/SDL2Module.cpp
        src/modules/sdl2/SDL2Module.h
        include/nitroapi/modules/sdl2/SDL2Data.h
        src/modules/sdl2/SDL2AddressProvider.cpp
        src/modules/sdl2/SDL2AddressProvider.h
        include/nitroapi/modules/engine/IEngine.h
        src/profiler.h
        src/seh_platform.h
        src/AddressProviderBase.cpp
        src/modules/client/ClientAddressProvider8684Linux.cpp
        src/modules/client/ClientAddressProvider8684Linux.h
        src/modules/engine/EngineAddressProvider8684Linux.cpp
        src/modules/engine/EngineAddressProvider8684Linux.h
)

target_include_directories(nitro_api PRIVATE
        ${OPENGL_INCLUDE_DIR}
        dep/easyloggingpp/src
        dep/nitro_utils/include
        dep/funchook/include
        include
)

if (USE_PROFILER)
    target_include_directories(nitro_api PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/dep/optic/include)
endif()

target_link_libraries(nitro_api PRIVATE
        hl1_source_sdk::hl1_source_sdk
        OpenGL::GL
        magic_enum::magic_enum
        xbyak::xbyak
        funchook-static
        nitro_utils
)

if (WIN32)
    target_link_libraries(nitro_api PRIVATE
            psapi.lib
            ntdll.lib)
endif ()

if (USE_PROFILER)
    target_link_libraries(nitro_api PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/dep/optic/lib/OptickCore.lib)
endif()

if (MSVC)
    target_compile_options(nitro_api PRIVATE
            /bigobj # increases the max number of sections in obj files. Due to template methods, obj module files (EngineModule, ClientModule) get huge sizes
            /WX     # treat all warnings as error
            /EHsc   # NEVER catch SEH exceptions; c functions cannot throw exceptions
    )

    if (CMAKE_BUILD_TYPE MATCHES Release)
        target_compile_options(nitro_api PRIVATE /Zi /O2)

        set_target_properties(nitro_api PROPERTIES
                LINK_FLAGS "/INCREMENTAL:NO /DEBUG /OPT:REF /OPT:ICF")

        # Set file name & location
        set_target_properties(nitro_api PROPERTIES
                COMPILE_PDB_NAME nitro_api
                COMPILE_PDB_OUTPUT_DIR ${CMAKE_BINARY_DIR})
    endif ()
else ()
    if (CMAKE_BUILD_TYPE MATCHES Debug)
        target_compile_options(nitro_api PRIVATE -g -rdynamic)
    endif ()
endif ()

target_compile_definitions(nitro_api PRIVATE
        NITRO_API_EASYLOGGING
        #easyloggingpp options
        ELPP_WINSOCK2
        ELPP_THREAD_SAFE
        ELPP_DISABLE_VERBOSE_LOGS
        ELPP_DISABLE_TRACE_LOGS
        ELPP_DISABLE_DEBUG_LOGS
        ELPP_DISABLE_DEFAULT_CRASH_HANDLING
        ELPP_FRESH_LOG_FILE
        ELPP_DEFAULT_LOGGER="nitro_api"
        ELPP_DEFAULT_PERFORMANCE_LOGGER="nitro_api"
        ELPP_DEFAULT_LOG_FILE="nitro_api.log"
)

if (WIN32)
    target_compile_definitions(${PROJECT_NAME} PUBLIC
            _WIN32
            WIN32
            _WIN32_WINNT=0x0600
            WINVER=0x0600
            NOMINMAX
            _UNICODE
            WIN32_LEAN_AND_MEAN
    )
endif()

if (USE_PROFILER)
    target_compile_definitions(nitro_api PRIVATE -DUSE_OPTICK -DNITROAPI_USE_PROFILER)
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES
        PREFIX ""
        OUTPUT_NAME ${OUTPUT_NAME}
        SUFFIX ".dll"
        PDB_NAME ${OUTPUT_NAME}
)

#-----------------------------------------------------------------
# Export library
#-----------------------------------------------------------------
add_library(nitro_api_export STATIC
        src/ChainExtensions.cpp
)
add_library(nitro_api::nitro_api ALIAS nitro_api_export)

target_include_directories(nitro_api_export PUBLIC
        include
)

target_link_libraries(nitro_api_export INTERFACE
        nitro_utils::nitro_utils
        hl1_source_sdk::hl1_source_sdk
)

target_compile_definitions(nitro_api_export INTERFACE
        NITRO_API_INCLUDED
)
