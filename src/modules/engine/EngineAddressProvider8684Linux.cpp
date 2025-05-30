#include "EngineAddressProvider8684Linux.h"

namespace nitroapi
{
    const std::unordered_map<StaticHookId, SearchConfig> EngineAddressProvider8684Linux::addresses_hook_id_
    {
        { StaticHookId::CL_QueueHTTPDownload,       SearchConfig("CL_QueueHTTPDownload", SearchType::ExportFunc) },
        { StaticHookId::CL_HTTPUpdate,              SearchConfig("CL_HTTPUpdate", SearchType::ExportFunc) },
        { StaticHookId::CL_CanUseHTTPDownload,      SearchConfig("CL_CanUseHTTPDownload", SearchType::ExportFunc) },
        { StaticHookId::CL_GetDownloadQueueSize,    SearchConfig("CL_GetDownloadQueueSize", SearchType::ExportFunc) },
        { StaticHookId::CL_Connect_f,               SearchConfig("CL_Connect_f", SearchType::ExportFunc) },
        { StaticHookId::CL_HTTPStop_f,              SearchConfig("CL_HTTPStop_f", SearchType::ExportFunc) },
        { StaticHookId::CL_HTTPCancel_f,            SearchConfig("CL_HTTPCancel_f", SearchType::ExportFunc) },
        { StaticHookId::CL_Disconnect,              SearchConfig("CL_Disconnect", SearchType::ExportFunc) },
        { StaticHookId::CL_SendConsistencyInfo,     SearchConfig("CL_SendConsistencyInfo", SearchType::ExportFunc) },
        { StaticHookId::CL_CheckFile,               SearchConfig("CL_CheckFile", SearchType::ExportFunc) },
        { StaticHookId::CL_Init,                    SearchConfig("CL_Init", SearchType::ExportFunc) },
        { StaticHookId::CL_SendConnectPacket,       SearchConfig("CL_SendConnectPacket", SearchType::ExportFunc) },
        { StaticHookId::CL_ParseResourceList,       SearchConfig("CL_ParseResourceList", SearchType::ExportFunc) },
        { StaticHookId::CL_PrecacheResources,       SearchConfig("CL_PrecacheResources", SearchType::ExportFunc) },
        { StaticHookId::CL_StartResourceDownloading,SearchConfig("CL_StartResourceDownloading", SearchType::ExportFunc) },
        { StaticHookId::CL_ParseServerMessage,      SearchConfig("CL_ParseServerMessage", SearchType::ExportFunc) },
        { StaticHookId::CL_ReadPackets,             SearchConfig("CL_ReadPackets", SearchType::ExportFunc) },
        { StaticHookId::Cvar_Set,                   SearchConfig("Cvar_Set", SearchType::ExportFunc) },
        { StaticHookId::Cvar_Command,               SearchConfig("Cvar_Command", SearchType::ExportFunc) },
        { StaticHookId::CL_RegisterResources,       SearchConfig("CL_RegisterResources", SearchType::ExportFunc) },
        { StaticHookId::CL_MarkMapAsUsingHTTPDownload,SearchConfig("CL_MarkMapAsUsingHTTPDownload", SearchType::ExportFunc) },
        { StaticHookId::CL_SetSolidEntities,        SearchConfig("CL_SetSolidEntities", SearchType::ExportFunc) },
        { StaticHookId::CL_ConnectionlessPacket,    SearchConfig("CL_ConnectionlessPacket", SearchType::ExportFunc) },
        { StaticHookId::CL_ProcessFile_0,           SearchConfig("CL_ProcessFile", SearchType::ExportFunc) }, // CL_ProcessFile on linux
        { StaticHookId::CL_RequestMissingResources, SearchConfig("CL_RequestMissingResources", SearchType::ExportFunc) },
        { StaticHookId::CL_InitSpectator,           SearchConfig("CL_InitSpectator", SearchType::ExportFunc) },
        { StaticHookId::CL_ReallocateDynamicData,   SearchConfig("CL_ReallocateDynamicData", SearchType::ExportFunc) },
        { StaticHookId::SCR_UpdateScreen,           SearchConfig("SCR_UpdateScreen", SearchType::ExportFunc) },
        { StaticHookId::BuildSurfaceDisplayList,    SearchConfig("BuildSurfaceDisplayList", SearchType::ExportFunc) },
        { StaticHookId::COM_InitArgv,               SearchConfig("COM_InitArgv", SearchType::ExportFunc) },
        { StaticHookId::COM_CreateCustomization,    SearchConfig("COM_CreateCustomization", SearchType::ExportFunc) },
        { StaticHookId::Draw_DecalSetName,          SearchConfig("Draw_DecalSetName", SearchType::ExportFunc) },
        { StaticHookId::SetCareerAudioState,        SearchConfig("SetCareerAudioState", SearchType::ExportFunc) },
        { StaticHookId::Cmd_TokenizeString,         SearchConfig("Cmd_TokenizeString", SearchType::ExportFunc) },
        { StaticHookId::Info_IsKeyImportant,        SearchConfig("Info_IsKeyImportant", SearchType::ExportFunc) },
        { StaticHookId::Cbuf_AddText,               SearchConfig("Cbuf_AddText", SearchType::ExportFunc) },
        { StaticHookId::Con_Printf,                 SearchConfig("Con_Printf", SearchType::ExportFunc) },
        { StaticHookId::Con_DPrintf,                SearchConfig("Con_DPrintf", SearchType::ExportFunc) },
        { StaticHookId::Mem_Free,                   SearchConfig("Mem_Free", SearchType::ExportFunc) },
        { StaticHookId::Mem_Malloc,                 SearchConfig("Mem_Malloc", SearchType::ExportFunc) },
        { StaticHookId::Mem_ZeroMalloc,             SearchConfig("Mem_ZeroMalloc", SearchType::ExportFunc) },
        { StaticHookId::Mem_Strdup,                 SearchConfig("Mem_Strdup", SearchType::ExportFunc) },
        { StaticHookId::SZ_Write,                   SearchConfig("SZ_Write", SearchType::ExportFunc) },
        { StaticHookId::SZ_Clear,                   SearchConfig("SZ_Clear", SearchType::ExportFunc) },
        { StaticHookId::Netchan_CopyFileFragments,  SearchConfig("Netchan_CopyFileFragments", SearchType::ExportFunc) },
        { StaticHookId::Netchan_FlushIncoming,      SearchConfig("Netchan_FlushIncoming", SearchType::ExportFunc) },
        { StaticHookId::Netchan_CreateFragments,    SearchConfig("Netchan_CreateFragments", SearchType::ExportFunc) },
        { StaticHookId::Netchan_FragSend,           SearchConfig("Netchan_FragSend", SearchType::ExportFunc) },
        { StaticHookId::Netchan_Process,            SearchConfig("Netchan_Process", SearchType::ExportFunc) },
        { StaticHookId::Netchan_CopyNormalFragments,SearchConfig("Netchan_CopyNormalFragments", SearchType::ExportFunc) },
        { StaticHookId::Netchan_UpdateProgress,     SearchConfig("Netchan_UpdateProgress", SearchType::ExportFunc) },
        { StaticHookId::Netchan_Setup,              SearchConfig("Netchan_Setup", SearchType::ExportFunc) },
        { StaticHookId::CreateVoiceRecord_DSound,   SearchConfig() },
        { StaticHookId::CreateVoiceRecord_WaveIn,   SearchConfig() },
        { StaticHookId::MSG_BeginReading,           SearchConfig("MSG_BeginReading", SearchType::ExportFunc) },
        { StaticHookId::MSG_StartBitReading,        SearchConfig("MSG_StartBitReading", SearchType::ExportFunc) },
        { StaticHookId::MSG_EndBitReading,          SearchConfig("MSG_EndBitReading", SearchType::ExportFunc) },
        { StaticHookId::MSG_ReadBits,               SearchConfig("MSG_ReadBits", SearchType::ExportFunc) },
        { StaticHookId::MSG_ReadBitString,          SearchConfig("MSG_ReadBitString", SearchType::ExportFunc) },
        { StaticHookId::MSG_ReadBitData,            SearchConfig("MSG_ReadBitData", SearchType::ExportFunc) },
        { StaticHookId::MSG_ReadByte,               SearchConfig("MSG_ReadByte", SearchType::ExportFunc) },
        { StaticHookId::MSG_ReadString,             SearchConfig("MSG_ReadString", SearchType::ExportFunc) },
        { StaticHookId::MSG_ReadLong,               SearchConfig("MSG_ReadLong", SearchType::ExportFunc) },
        { StaticHookId::MSG_ReadFloat,              SearchConfig("MSG_ReadFloat", SearchType::ExportFunc) },
        { StaticHookId::MSG_ReadStringLine,         SearchConfig("MSG_ReadStringLine", SearchType::ExportFunc) },
        { StaticHookId::MSG_WriteByte,              SearchConfig("MSG_WriteByte", SearchType::ExportFunc) },
        { StaticHookId::MSG_WriteString,            SearchConfig("MSG_WriteString", SearchType::ExportFunc) },
        { StaticHookId::NET_SendPacket,             SearchConfig("NET_SendPacket", SearchType::ExportFunc) },
        { StaticHookId::NET_GetPacket,              SearchConfig("NET_GetPacket", SearchType::ExportFunc) },
        { StaticHookId::NET_GetPacket_0,            SearchConfig() },
        { StaticHookId::Net_APICheckTimeouts,       SearchConfig("Net_APICheckTimeouts", SearchType::ExportFunc) },
        { StaticHookId::Sys_InitGame,               SearchConfig() },
        { StaticHookId::Sys_Error,                  SearchConfig("Sys_Error", SearchType::ExportFunc) },
        { StaticHookId::Sys_Printf,                 SearchConfig("Sys_Printf", SearchType::ExportFunc) },
        { StaticHookId::Host_WriteConfiguration,    SearchConfig("Host_WriteConfiguration", SearchType::ExportFunc) },
        { StaticHookId::Host_Frame,                 SearchConfig("Host_Frame", SearchType::ExportFunc) },
        { StaticHookId::Host_FrameInternal,         SearchConfig() },
        { StaticHookId::Host_FilterTime,            SearchConfig("Host_FilterTime", SearchType::ExportFunc) },
        { StaticHookId::Host_Map_f,                 SearchConfig("Host_Map_f", SearchType::ExportFunc) },
        { StaticHookId::Host_Map,                   SearchConfig("Host_Map", SearchType::ExportFunc) },
        { StaticHookId::Con_MessageMode_f,          SearchConfig("Con_MessageMode_f", SearchType::ExportFunc) },
        { StaticHookId::Con_MessageMode2_f,         SearchConfig("Con_MessageMode2_f", SearchType::ExportFunc) },
        { StaticHookId::Key_Message,                SearchConfig("Key_Message", SearchType::ExportFunc) },
        { StaticHookId::Host_InitializeGameDLL,     SearchConfig("Host_InitializeGameDLL", SearchType::ExportFunc) },
        { StaticHookId::ForceReloadProfile,         SearchConfig("ForceReloadProfile", SearchType::ExportFunc) },
        { StaticHookId::VGuiWrap2_ConPrintf,             SearchConfig("VGuiWrap2_ConPrintf", SearchType::ExportFunc) },
        { StaticHookId::SystemWrapper_RunFrame,          SearchConfig("SystemWrapper_RunFrame", SearchType::ExportFunc) },
        { StaticHookId::ClientDLL_Frame,                 SearchConfig("ClientDLL_Frame", SearchType::ExportFunc) },
        { StaticHookId::ClientDLL_Init,                  SearchConfig("ClientDLL_Init", SearchType::ExportFunc) },
        { StaticHookId::AddStartupTiming,                SearchConfig("AddStartupTiming", SearchType::ExportFunc) },
        { StaticHookId::HPAK_GetDataPointer,             SearchConfig("HPAK_GetDataPointer", SearchType::ExportFunc) },
        { StaticHookId::HPAK_AddLump,                    SearchConfig("HPAK_AddLump", SearchType::ExportFunc) },
        { StaticHookId::NotifyDedicatedServerUI,         SearchConfig("NotifyDedicatedServerUI", SearchType::ExportFunc) },
        { StaticHookId::StartLoadingProgressBar,         SearchConfig("StartLoadingProgressBar", SearchType::ExportFunc) },
        { StaticHookId::SetLoadingProgressBarStatusText, SearchConfig("SetLoadingProgressBarStatusText", SearchType::ExportFunc) },
        { StaticHookId::Mod_ClearAll,                    SearchConfig("Mod_ClearAll", SearchType::ExportFunc) },
        { StaticHookId::Mod_FindName,                    SearchConfig("Mod_FindName", SearchType::ExportFunc) },
        { StaticHookId::Mod_LoadModel,                   SearchConfig("Mod_LoadModel", SearchType::ExportFunc) },
        { StaticHookId::Mod_Print,                       SearchConfig("Mod_Print", SearchType::ExportFunc) },
        { StaticHookId::Mod_ValidateCRC,                 SearchConfig("Mod_ValidateCRC", SearchType::ExportFunc) },
        { StaticHookId::Mod_NeedCRC,                     SearchConfig("Mod_NeedCRC", SearchType::ExportFunc) },
        { StaticHookId::Mod_LoadAliasModel,              SearchConfig("Mod_LoadAliasModel", SearchType::ExportFunc) },
        { StaticHookId::Mod_LoadSpriteModel,             SearchConfig("Mod_LoadSpriteModel", SearchType::ExportFunc) },
        { StaticHookId::Mod_LoadStudioModel,             SearchConfig("Mod_LoadStudioModel", SearchType::ExportFunc) },
        { StaticHookId::Mod_LoadBrushModel,              SearchConfig("Mod_LoadBrushModel", SearchType::ExportFunc) },
        { StaticHookId::S_PrecacheSound,                 SearchConfig("S_PrecacheSound", SearchType::ExportFunc) },
        { StaticHookId::SPR_Shutdown,               SearchConfig("SPR_Shutdown", SearchType::ExportFunc) },
        { StaticHookId::SPR_Init,                   SearchConfig("SPR_Init", SearchType::ExportFunc) },
        { StaticHookId::R_StudioReloadSkin,         SearchConfig("R_StudioReloadSkin", SearchType::ExportFunc) },
        { StaticHookId::R_NewMap,                   SearchConfig("R_NewMap", SearchType::ExportFunc) },
        { StaticHookId::DT_LoadDetailMapFile,       SearchConfig("DT_LoadDetailMapFile", SearchType::ExportFunc) },
        { StaticHookId::Cache_Alloc,                SearchConfig("Cache_Alloc", SearchType::ExportFunc) },
        { StaticHookId::Cache_Check,                SearchConfig("Cache_Check", SearchType::ExportFunc) },
        { StaticHookId::Cache_Free,                 SearchConfig("Cache_Free", SearchType::ExportFunc) },
        { StaticHookId::Z_Malloc,                   SearchConfig("Z_Malloc", SearchType::ExportFunc) },
        { StaticHookId::Hunk_AllocName,             SearchConfig("Hunk_AllocName", SearchType::ExportFunc) },
        { StaticHookId::Hunk_TempAlloc,             SearchConfig("Hunk_TempAlloc", SearchType::ExportFunc) },
        { StaticHookId::Hunk_Check,                 SearchConfig("Hunk_Check", SearchType::ExportFunc) },
        //{ StaticHookId::ClientDLL_Shutdown,           SearchConfig() },
        { StaticHookId::GL_SetMode,                 SearchConfig("GL_SetMode", SearchType::ExportFunc) },
        { StaticHookId::CL_WriteDemoStartup,        SearchConfig("CL_WriteDemoStartup", SearchType::ExportFunc) },
        { StaticHookId::CL_WriteDemoMessage,        SearchConfig("CL_WriteDemoMessage", SearchType::ExportFunc) },
        { StaticHookId::CL_Record_f,                SearchConfig("CL_Record_f", SearchType::ExportFunc) },
        { StaticHookId::S_LoadSound,                SearchConfig("S_LoadSound", SearchType::ExportFunc) },
        { StaticHookId::VoiceSE_GetSFXCache,        SearchConfig("VoiceSE_GetSFXCache", SearchType::ExportFunc) },
        { StaticHookId::Sys_FloatTime,              SearchConfig("Sys_FloatTime", SearchType::ExportFunc) },
        { StaticHookId::SPR_Load,                   SearchConfig("SPR_Load", SearchType::ExportFunc) },
        { StaticHookId::GL_UnloadTexture,           SearchConfig("GL_UnloadTexture", SearchType::ExportFunc) },
        { StaticHookId::CL_GetModelByIndex,         SearchConfig("CL_GetModelByIndex", SearchType::ExportFunc) },
        { StaticHookId::GL_Init,                    SearchConfig("GL_Init", SearchType::ExportFunc) },
        { StaticHookId::DT_Initialize,              SearchConfig("DT_Initialize", SearchType::ExportFunc) },
        { StaticHookId::GL_BuildLightmaps,          SearchConfig("GL_BuildLightmaps", SearchType::ExportFunc) },
        { StaticHookId::Cvar_DirectSet,             SearchConfig("Cvar_DirectSet", SearchType::ExportFunc) },
        { StaticHookId::V_Init,                     SearchConfig("V_Init", SearchType::ExportFunc) },
        { StaticHookId::R_Init,                     SearchConfig("R_Init", SearchType::ExportFunc) },
        { StaticHookId::R_RenderView,               SearchConfig("R_RenderView", SearchType::ExportFunc) },
        { StaticHookId::SPR_Draw,                   SearchConfig("SPR_Draw", SearchType::ExportFunc) },
        { StaticHookId::SPR_DrawAdditive,           SearchConfig("SPR_DrawAdditive", SearchType::ExportFunc) },
        { StaticHookId::SPR_DrawHoles,              SearchConfig("SPR_DrawHoles", SearchType::ExportFunc) },
        { StaticHookId::SPR_DrawGeneric,            SearchConfig("SPR_DrawGeneric", SearchType::ExportFunc) },
        { StaticHookId::SPR_EnableScissor,          SearchConfig("SPR_EnableScissor", SearchType::ExportFunc) },
        { StaticHookId::SPR_DisableScissor,         SearchConfig("SPR_DisableScissor", SearchType::ExportFunc) },
        { StaticHookId::GL_SelectTexture,           SearchConfig("GL_SelectTexture", SearchType::ExportFunc) },
        { StaticHookId::GL_LoadTexture,             SearchConfig("GL_LoadTexture", SearchType::ExportFunc) },
        { StaticHookId::GL_Bind,                    SearchConfig("GL_Bind", SearchType::ExportFunc) },
        { StaticHookId::VGUI2_ResetCurrentTexture,  SearchConfig("VGUI2_ResetCurrentTexture", SearchType::ExportFunc) },
        { StaticHookId::SetCrosshair,               SearchConfig("SetCrosshair", SearchType::ExportFunc) },
        { StaticHookId::DrawCrosshair,              SearchConfig("DrawCrosshair", SearchType::ExportFunc) },
        { StaticHookId::R_DrawTEntitiesOnList,      SearchConfig("R_DrawTEntitiesOnList", SearchType::ExportFunc) },
        { StaticHookId::CL_FxBlend,                 SearchConfig("CL_FxBlend", SearchType::ExportFunc) },
        { StaticHookId::R_GetAttachmentPoint,       SearchConfig("R_GetAttachmentPoint", SearchType::ExportFunc) },
        { StaticHookId::GlowBlend,                  SearchConfig("GlowBlend", SearchType::ExportFunc) },
        { StaticHookId::R_DrawSpriteModel,          SearchConfig("R_DrawSpriteModel", SearchType::ExportFunc) },
        { StaticHookId::R_DrawBrushModel,           SearchConfig("R_DrawBrushModel", SearchType::ExportFunc) },
        { StaticHookId::R_DrawAliasModel,           SearchConfig("R_DrawAliasModel", SearchType::ExportFunc) },
        { StaticHookId::ClientDLL_DrawTransparentTriangles, SearchConfig("ClientDLL_DrawTransparentTriangles", SearchType::ExportFunc) },
        { StaticHookId::CL_IsDevOverviewMode,       SearchConfig("CL_IsDevOverviewMode", SearchType::ExportFunc) },
        { StaticHookId::CL_SetDevOverView,          SearchConfig("CL_SetDevOverView", SearchType::ExportFunc) },
        { StaticHookId::R_SetupFrame,               SearchConfig("R_SetupFrame", SearchType::ExportFunc) },
        { StaticHookId::R_SetFrustum,               SearchConfig("R_SetFrustum", SearchType::ExportFunc) },
        { StaticHookId::R_SetupGL,                  SearchConfig("R_SetupGL", SearchType::ExportFunc) },
        { StaticHookId::R_MarkLeaves,               SearchConfig("R_MarkLeaves", SearchType::ExportFunc) },
        { StaticHookId::R_DrawWorld,                SearchConfig("R_DrawWorld", SearchType::ExportFunc) },
        { StaticHookId::S_ExtraUpdate,              SearchConfig("S_ExtraUpdate", SearchType::ExportFunc) },
        { StaticHookId::R_RenderFinalFog,           SearchConfig("R_RenderFinalFog", SearchType::ExportFunc) },
        { StaticHookId::ClientDLL_DrawNormalTriangles, SearchConfig("ClientDLL_DrawNormalTriangles", SearchType::ExportFunc) },
        { StaticHookId::R_RenderDlights,            SearchConfig("R_RenderDlights", SearchType::ExportFunc) },
        { StaticHookId::R_DrawParticles,            SearchConfig("R_DrawParticles", SearchType::ExportFunc) },
        { StaticHookId::R_DrawViewModel,            SearchConfig("R_DrawViewModel", SearchType::ExportFunc) },
        { StaticHookId::R_PolyBlend,                SearchConfig("R_PolyBlend", SearchType::ExportFunc) },
        { StaticHookId::AddTEntity,                 SearchConfig("AddTEntity", SearchType::ExportFunc) },
        { StaticHookId::AppendTEntity,              SearchConfig("AppendTEntity", SearchType::ExportFunc) },
        { StaticHookId::R_PreDrawViewModel,         SearchConfig("R_PreDrawViewModel", SearchType::ExportFunc) },
        { StaticHookId::R_Clear,                    SearchConfig("R_Clear", SearchType::ExportFunc) },
        { StaticHookId::MSG_WriteShort,             SearchConfig("MSG_WriteShort", SearchType::ExportFunc) },
        { StaticHookId::SNDDMA_Init,                SearchConfig("SNDDMA_Init", SearchType::ExportFunc) },
        { StaticHookId::S_Init,                     SearchConfig("S_Init", SearchType::ExportFunc) },
        { StaticHookId::S_Shutdown,                 SearchConfig("S_Shutdown", SearchType::ExportFunc) },
        { StaticHookId::S_FindName,                 SearchConfig("S_FindName", SearchType::ExportFunc) },
        { StaticHookId::S_StartDynamicSound,        SearchConfig("S_StartDynamicSound", SearchType::ExportFunc) },
        { StaticHookId::S_StartStaticSound,         SearchConfig("S_StartStaticSound", SearchType::ExportFunc) },
        { StaticHookId::S_StopSound,                SearchConfig("S_StopSound", SearchType::ExportFunc) },
        { StaticHookId::S_StopAllSounds,            SearchConfig("S_StopAllSounds", SearchType::ExportFunc) },
        { StaticHookId::S_Update,                   SearchConfig("S_Update", SearchType::ExportFunc) },
        { StaticHookId::VoiceSE_NotifyFreeChannel,  SearchConfig("VoiceSE_NotifyFreeChannel", SearchType::ExportFunc) },
        { StaticHookId::SequenceGetSentenceByIndex, SearchConfig("SequenceGetSentenceByIndex", SearchType::ExportFunc) },
        { StaticHookId::CL_ConnectClient,           SearchConfig("CL_ConnectClient", SearchType::ExportFunc) },
        { StaticHookId::CL_GetFragmentSize,         SearchConfig("CL_GetFragmentSize", SearchType::ExportFunc) },
        { StaticHookId::NET_ClearLagData,           SearchConfig("NET_ClearLagData", SearchType::ExportFunc) },
        { StaticHookId::SZ_GetSpace,                SearchConfig("SZ_GetSpace", SearchType::ExportFunc) },
        { StaticHookId::Host_Shutdown,              SearchConfig("Host_Shutdown", SearchType::ExportFunc) },
        { StaticHookId::Host_Quit_f,                SearchConfig("Host_Quit_f", SearchType::ExportFunc) },
        { StaticHookId::CL_ClearClientState,        SearchConfig("CL_ClearClientState", SearchType::ExportFunc) },
        { StaticHookId::MD5_Hash_File,              SearchConfig("MD5_Hash_File", SearchType::ExportFunc) },
        { StaticHookId::COM_ClearCustomizationList, SearchConfig("COM_ClearCustomizationList", SearchType::ExportFunc) },
        { StaticHookId::HPAK_FlushHostQueue,        SearchConfig("HPAK_FlushHostQueue", SearchType::ExportFunc) },
        { StaticHookId::ClientDLL_HudInit,          SearchConfig("ClientDLL_HudInit", SearchType::ExportFunc) },
    };

    const std::unordered_map<std::string, SearchConfig> EngineAddressProvider8684Linux::addresses_str_
    {
        { "server",                                 SearchConfig("sv", SearchType::ExportFunc) },
        { "server_static",                          SearchConfig("svs", SearchType::ExportFunc) },
        { "client_static",                          SearchConfig() },
        { "client_state",                           SearchConfig() },
        { "cl_enginefunc",                          SearchConfig("cl_enginefuncs", SearchType::ExportFunc) },
        { "enginefuncs",                            SearchConfig() },
        { "cldll_func",                             SearchConfig("cl_funcs", SearchType::ExportFunc) },
        { "modfuncs",                               SearchConfig("g_modfuncs", SearchType::ExportFunc) },
        { "eng",                                    SearchConfig("eng", SearchType::ExportFunc) },
        { "net_message",                            SearchConfig("net_message", SearchType::ExportFunc) },
        { "net_from",                               SearchConfig("net_from", SearchType::ExportFunc) },
        { "msg_readcount",                          SearchConfig("msg_readcount", SearchType::ExportFunc) },
        { "host_framecount",                        SearchConfig("host_framecount", SearchType::ExportFunc) },
        { "host_frametime",                         SearchConfig("host_frametime", SearchType::ExportFunc) },
        { "realtime",                               SearchConfig("realtime", SearchType::ExportFunc) },
        { "EngineMsgBase",                          SearchConfig(0x27D200) },
        { "SampleRate",                             SearchConfig() },
        { "gDownloadFile",                          SearchConfig("gDownloadFile", SearchType::ExportFunc) },
        { "gfExtendedError",                        SearchConfig("gfExtendedError", SearchType::ExportFunc) },
        { "gszDisconnectReason",                    SearchConfig("gszDisconnectReason", SearchType::ExportFunc) },
        { "scr_downloading",                        SearchConfig("scr_downloading", SearchType::ExportFunc) },
        { "cmd_source",                             SearchConfig("cmd_source", SearchType::ExportFunc) },
        { "bMajorMapChange",                        SearchConfig() },
        { "careerState",                            SearchConfig() },
        { "loadmodel",                              SearchConfig("loadmodel", SearchType::ExportFunc) },
        { "cl_playerindex",                         SearchConfig("cl_playerindex", SearchType::ExportFunc) },
        { "com_argc",                               SearchConfig("com_argc", SearchType::ExportFunc) },
        { "com_argv",                               SearchConfig("com_argv", SearchType::ExportFunc) },
        { "loadcache",                              SearchConfig("loadcache", SearchType::ExportFunc) },
        { "loadbuf",                                SearchConfig("loadbuf", SearchType::ExportFunc) },
        { "loadsize",                               SearchConfig("loadsize", SearchType::ExportFunc) },
        { "known_sfx",                              SearchConfig("known_sfx", SearchType::ExportFunc) },
        { "num_sfx",                                SearchConfig("num_sfx", SearchType::ExportFunc) },
        { "cl_entities",                            SearchConfig("cl_entities", SearchType::ExportFunc) },
        { "noclip_anglehack",                       SearchConfig("noclip_anglehack", SearchType::ExportFunc) },
        { "currentmodel",                           SearchConfig("currentmodel", SearchType::ExportFunc) },
        { "r_pcurrentvertbase",                     SearchConfig("r_pcurrentvertbase", SearchType::ExportFunc) },
        { "sys_timescale",                          SearchConfig("sys_timescale", SearchType::ExportFunc) },
        { "shm",                                    SearchConfig("shm", SearchType::ExportFunc) },
        { "wavstreams",                             SearchConfig("wavstreams", SearchType::ExportFunc) },
        { "channels",                               SearchConfig("channels", SearchType::ExportFunc) },
        { "host_initialized",                       SearchConfig("host_initialized", SearchType::ExportFunc) },
        { "g_engdstAddrs",                          SearchConfig("g_engdstAddrs", SearchType::ExportFunc) },
        { "vid",                                    SearchConfig("vid", SearchType::ExportFunc) },
        { "gl_mtexable",                            SearchConfig("gl_mtexable", SearchType::ExportFunc) },
        { "r_framecount",                           SearchConfig("r_framecount", SearchType::ExportFunc) },
        { "gVShake",                                SearchConfig("gVShake", SearchType::ExportFunc) },
        { "gHostSpawnCount",                        SearchConfig("gHostSpawnCount", SearchType::ExportFunc) },
        { "gGLPalette",                             SearchConfig("gGLPalette", SearchType::ExportFunc) },
        { "r_refdef",                               SearchConfig("r_refdef", SearchType::ExportFunc) },
        { "currenttexture",                         SearchConfig("currenttexture", SearchType::ExportFunc) },
        { "currententity",                          SearchConfig("currententity", SearchType::ExportFunc) },
        { "r_blend",                                SearchConfig("r_blend", SearchType::ExportFunc) },
        { "r_entorigin",                            SearchConfig("r_entorigin", SearchType::ExportFunc) },
        { "g_bUserFogOn",                           SearchConfig("g_bUserFogOn", SearchType::ExportFunc) },
        { "numTransObjs",                           SearchConfig("numTransObjs", SearchType::ExportFunc) },
        { "transObjects",                           SearchConfig("transObjects", SearchType::ExportFunc) },
        { "mtexenabled",                            SearchConfig("mtexenabled", SearchType::ExportFunc) },
        { "r_worldentity",                          SearchConfig("r_worldentity", SearchType::ExportFunc) },
        { "mirror",                                 SearchConfig("mirror", SearchType::ExportFunc) },
        { "c_brush_polys",                          SearchConfig("c_brush_polys", SearchType::ExportFunc) },
        { "c_alias_polys",                          SearchConfig("c_alias_polys", SearchType::ExportFunc) },
        { "cl_numvisedicts",                        SearchConfig("cl_numvisedicts", SearchType::ExportFunc) },
        { "cl_visedicts",                           SearchConfig("cl_visedicts", SearchType::ExportFunc) },
        { "isFogEnabled",                           SearchConfig("isFogEnabled", SearchType::ExportFunc) },
        { "scr_fov_value",                          SearchConfig("scr_fov_value", SearchType::ExportFunc) },
        { "g_SND_VoiceOverdrive",                   SearchConfig("g_SND_VoiceOverdrive", SearchType::ExportFunc) },
        { "cszrawsentences",                        SearchConfig("cszrawsentences", SearchType::ExportFunc) },
        { "rgpszrawsentence",                       SearchConfig("rgpszrawsentence", SearchType::ExportFunc) },
        { "scr_con_current",                        SearchConfig("scr_con_current", SearchType::ExportFunc) },
        { "developer",                              SearchConfig("developer", SearchType::ExportFunc) },
        { "cmd_argc",                               SearchConfig("cmd_argc", SearchType::ExportFunc) },
        { "cmd_argv",                               SearchConfig("cmd_argv", SearchType::ExportFunc) },
        { "cvar_vars",                              SearchConfig("cvar_vars", SearchType::ExportFunc) },
        { "key_dest",                               SearchConfig("key_dest", SearchType::ExportFunc) },
        { "engine_studio_api",                      SearchConfig("engine_studio_api", SearchType::ExportFunc) },
    };
}