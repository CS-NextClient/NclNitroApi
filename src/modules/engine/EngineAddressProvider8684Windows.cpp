#include "EngineAddressProvider8684Windows.h"
#include <easylogging++.h>

namespace nitroapi
{
    const std::unordered_map<StaticHookId, SearchConfig> EngineAddressProvider8684Windows::addresses_hook_id_
    {
        { StaticHookId::CL_QueueHTTPDownload,       SearchConfig(0x38940) },
        { StaticHookId::CL_HTTPUpdate,              SearchConfig(0x38900) },
        { StaticHookId::CL_CanUseHTTPDownload,      SearchConfig(0x38970) },
        { StaticHookId::CL_GetDownloadQueueSize,    SearchConfig(0x38960) },
        { StaticHookId::CL_Connect_f,               SearchConfig(0x183A0) },
        { StaticHookId::CL_HTTPStop_f,              SearchConfig(0x38910) },
        { StaticHookId::CL_HTTPCancel_f,            SearchConfig(0x38920) },
        { StaticHookId::CL_Disconnect,              SearchConfig(0x17850) },
        { StaticHookId::CL_SendConsistencyInfo,     SearchConfig(0x1B040) },
        { StaticHookId::CL_CheckFile,               SearchConfig(0x1ABE0) },
        { StaticHookId::CL_Init,                    SearchConfig(0x19DB0) },
        { StaticHookId::CL_SendConnectPacket,       SearchConfig(0x17C80) },
        { StaticHookId::CL_ParseResourceList,       SearchConfig(0x1BBB0) },
        { StaticHookId::CL_PrecacheResources,       SearchConfig(0x16C60) },
        { StaticHookId::CL_StartResourceDownloading,SearchConfig(0x1B910) },
        { StaticHookId::CL_ParseServerMessage,      SearchConfig(0x1D300) },
        { StaticHookId::CL_ReadPackets,             SearchConfig(0x17230) },
        { StaticHookId::Cvar_Set,                   SearchConfig(0x2E850) },
        { StaticHookId::Cvar_Command,               SearchConfig(0x2EB10) },
        { StaticHookId::CL_RegisterResources,       SearchConfig(0x1B370) },
        { StaticHookId::CL_MarkMapAsUsingHTTPDownload,SearchConfig(0x38A00) },
        { StaticHookId::CL_SetSolidEntities,        SearchConfig(0x144C0) },
        { StaticHookId::CL_ConnectionlessPacket,    SearchConfig(0x16640) },
        { StaticHookId::CL_ProcessFile_0,           SearchConfig(0x16FE0) },
        { StaticHookId::CL_RequestMissingResources, SearchConfig(0x1C100) },
        { StaticHookId::CL_InitSpectator,           SearchConfig(0x20B10) },
        { StaticHookId::CL_ReallocateDynamicData,   SearchConfig(0x1C190) },
        { StaticHookId::SCR_UpdateScreen,           SearchConfig(0x4C2A0) },
        { StaticHookId::BuildSurfaceDisplayList,    SearchConfig(0x497B0) },
        { StaticHookId::COM_InitArgv,               SearchConfig(0x2B370) },
        { StaticHookId::COM_CreateCustomization,    SearchConfig(0x29020) },
        //{ StaticHookId::CL_Parse_StuffText,         SearchConfig("56 E8 ? ? ? ? 8B F0 56 E8 ? ? ? ? 83 C4 04 85 C0 56 75 0F") },
        { StaticHookId::Draw_DecalSetName,          SearchConfig(0x2F750) },
        { StaticHookId::SetCareerAudioState,        SearchConfig(0x8E260) },
        { StaticHookId::Cmd_TokenizeString,         SearchConfig(0x27F30) },
        { StaticHookId::Info_IsKeyImportant,        SearchConfig(0x5E220) },
        { StaticHookId::Cbuf_AddText,               SearchConfig("55 8B EC 56 57 8B 7D 08 57 E8 ? ? ? ? 8B 75 0C 83 C4 04 8B 4E 10 03 C8 8B 46 0C 3B C8 7C 11") },
        { StaticHookId::Con_Printf,                 SearchConfig("55 8B EC B8 00 10 00 00 E8 ? ? ? ? 8B 4D 08 8D 45 0C 50 51 8D 95 00 F0 FF FF 68 00 10 00 00") },
        { StaticHookId::Con_DPrintf,                SearchConfig(0x2CC90) },
        { StaticHookId::Mem_Free,                   SearchConfig(0x63550) },
        { StaticHookId::Mem_Malloc,                 SearchConfig(0x634A0) },
        { StaticHookId::Mem_ZeroMalloc,             SearchConfig(0x634C0) },
        { StaticHookId::Mem_Strdup,                 SearchConfig(0x63530) },
        { StaticHookId::SZ_Write,                   SearchConfig("55 8B EC 56 8B 75 08 57 8B 7D 10 57 56 E8 ? ? ? ? 8A 4E 04 83 C4 08 F6 C1 02 75 0E") },
        { StaticHookId::SZ_Clear,                   SearchConfig(0x2AC50) },
        { StaticHookId::Netchan_CopyFileFragments,  SearchConfig(0x666B0) },
        { StaticHookId::Netchan_FlushIncoming,      SearchConfig(0x66500) },
        { StaticHookId::Netchan_CreateFragments,    SearchConfig(0x65EC0) },
        { StaticHookId::Netchan_FragSend,           SearchConfig(0x65BF0) },
        { StaticHookId::Netchan_Process,            SearchConfig(0x65740) },
        { StaticHookId::Netchan_CopyNormalFragments,SearchConfig(0x66570) },
        { StaticHookId::Netchan_UpdateProgress,     SearchConfig(0x66B50) },
        { StaticHookId::Netchan_Setup,              SearchConfig(0x64CC0) },
        { StaticHookId::CreateVoiceRecord_DSound,   SearchConfig("55 8B EC 56 6A 24 E8 ? ? ? ? 83 C4 04 85 C0 74 28 8B C8") },
        { StaticHookId::CreateVoiceRecord_WaveIn,   SearchConfig("55 8B EC 56 68 1C 20 00 00 E8 ? ? ? ? 83 C4 04 85 C0 74 28 8B C8 E8") },
        { StaticHookId::MSG_BeginReading,           SearchConfig(0x2A880) },
        { StaticHookId::MSG_StartBitReading,        SearchConfig(0x2a250) },
        { StaticHookId::MSG_EndBitReading,          SearchConfig(0x2a2a0) },
        { StaticHookId::MSG_ReadBits,               SearchConfig(0x2a370) },
        { StaticHookId::MSG_ReadBitString,          SearchConfig(0x2a4e0) },
        { StaticHookId::MSG_ReadBitData,            SearchConfig(0x2a520) },
        { StaticHookId::MSG_ReadByte,               SearchConfig(0x2a8d0) },
        { StaticHookId::MSG_ReadString,             SearchConfig(0x2aab0) },
        { StaticHookId::MSG_ReadLong,               SearchConfig(0x2A9B0) },
        { StaticHookId::MSG_ReadFloat,              SearchConfig(0x2AA10) },
        { StaticHookId::MSG_ReadStringLine,         SearchConfig(0x2AAF0) },
        { StaticHookId::MSG_WriteByte,              SearchConfig(0x29C20) },
        { StaticHookId::MSG_WriteString,            SearchConfig(0x29CE0) },
        { StaticHookId::NET_SendPacket,             SearchConfig(0x68840) },
        { StaticHookId::NET_GetPacket,              SearchConfig(0x68500) },
        { StaticHookId::NET_GetPacket_0,            SearchConfig(0x17200) },
        { StaticHookId::Net_APICheckTimeouts,       SearchConfig(0x63D80) },
        { StaticHookId::Sys_InitGame,               SearchConfig(0xAC480) },
        { StaticHookId::Sys_Error,                  SearchConfig(0xAA5D0) },
        { StaticHookId::Sys_Printf,                 SearchConfig(0xAA720) },
        { StaticHookId::Host_WriteConfiguration,    SearchConfig(0x56210) },
        { StaticHookId::Host_Frame,                 SearchConfig(0x577D0) },
        { StaticHookId::Host_FrameInternal,         SearchConfig(0x57610) },
        { StaticHookId::Host_FilterTime,            SearchConfig(0x56F80) },
        { StaticHookId::Host_Map_f,                 SearchConfig(0x597E0) },
        { StaticHookId::Host_Map,                   SearchConfig(0x59640) },
        { StaticHookId::Host_InitializeGameDLL,     SearchConfig(0x581C0) },
        { StaticHookId::ForceReloadProfile,         SearchConfig(0xAA9B0) },
        { StaticHookId::VGuiWrap2_ConPrintf,             SearchConfig(0x74F0) },
        { StaticHookId::SystemWrapper_RunFrame,          SearchConfig(0xB1250) },
        { StaticHookId::ClientDLL_Frame,                 SearchConfig(0xBED0) },
        { StaticHookId::ClientDLL_Init,                  SearchConfig(0xb180) },
        { StaticHookId::AddStartupTiming,                SearchConfig(0x15270) },
        { StaticHookId::HPAK_GetDataPointer,             SearchConfig(0x50E30) },
        { StaticHookId::HPAK_AddLump,                    SearchConfig(0x512E0) },
        { StaticHookId::NotifyDedicatedServerUI,         SearchConfig(0xA3A10) },
        { StaticHookId::StartLoadingProgressBar,         SearchConfig(0x7690) },
        { StaticHookId::SetLoadingProgressBarStatusText, SearchConfig(0x7720) },
        { StaticHookId::Mod_ClearAll,                    SearchConfig(0x3FDC0) },
        { StaticHookId::Mod_FindName,                    SearchConfig(0x3FE20) },
        { StaticHookId::Mod_LoadModel,                   SearchConfig(0x40030) },
        { StaticHookId::Mod_Print,                       SearchConfig(0x42BA0) },
        { StaticHookId::Mod_ValidateCRC,                 SearchConfig(0x3FF30) },
        { StaticHookId::Mod_NeedCRC,                     SearchConfig(0x3FF90) },
        { StaticHookId::Mod_LoadAliasModel,              SearchConfig(0x422A0) },
        { StaticHookId::Mod_LoadSpriteModel,             SearchConfig(0x429E0) },
        { StaticHookId::Mod_LoadStudioModel,             SearchConfig(0x61AD0) },
        { StaticHookId::Mod_LoadBrushModel,              SearchConfig(0x41BB0) },
        { StaticHookId::S_PrecacheSound,                 SearchConfig(0x8BD40) },
        { StaticHookId::SPR_Shutdown,               SearchConfig(0x117E0) },
        { StaticHookId::SPR_Init,                   SearchConfig(0x11940) },
        { StaticHookId::R_StudioReloadSkin,         SearchConfig(0x846B0) },
        { StaticHookId::R_NewMap,                   SearchConfig(0x46DB0) },
        { StaticHookId::DT_LoadDetailMapFile,       SearchConfig(0x334B0) },
        { StaticHookId::Cache_Alloc,                SearchConfig(0xC88D0) },
        { StaticHookId::Cache_Check,                SearchConfig(0xC88A0) },
        { StaticHookId::Cache_Free,                 SearchConfig(0xC8830) },
        { StaticHookId::Z_Malloc,                   SearchConfig(0xC7B50) },
        { StaticHookId::Hunk_AllocName,             SearchConfig(0xC7FE0) },
        { StaticHookId::Hunk_TempAlloc,             SearchConfig(0xC8230) },
        { StaticHookId::Hunk_Check,                 SearchConfig(0xC7D70) },
        //{ StaticHookId::ClientDLL_Shutdown,           SearchConfig() },
        { StaticHookId::GL_SetMode,                 SearchConfig(0x4DA10) },
        { StaticHookId::CL_WriteDemoStartup,        SearchConfig(0xFCAD) },
        { StaticHookId::CL_WriteDemoMessage,        SearchConfig(0xFDFD) },
        { StaticHookId::CL_Record_f,                SearchConfig(0x1010D) },
        { StaticHookId::S_LoadSound,                SearchConfig(0x8D720) },
        { StaticHookId::VoiceSE_GetSFXCache,        SearchConfig(0xC5340) },
        { StaticHookId::Sys_FloatTime,              SearchConfig(0xAA790) },
        { StaticHookId::SPR_Load,                   SearchConfig(0x116E0) },
        { StaticHookId::GL_UnloadTexture,           SearchConfig(0x3E970) },
        { StaticHookId::SPR_Set,                    SearchConfig(0x11A50) },
        { StaticHookId::SPR_Width,                  SearchConfig(0x119B0) },
        { StaticHookId::SPR_Height,                 SearchConfig(0x119F0) },
        { StaticHookId::SPR_Frames,                 SearchConfig(0x11980) },
        { StaticHookId::SPR_GetModelPointer,        SearchConfig(0x11910) },
        { StaticHookId::SPR_Shutdown_NoModelFree,   SearchConfig(0x11870) },
        { StaticHookId::CL_GetModelByIndex,         SearchConfig(0x1A3E0) },
        { StaticHookId::GL_Init,                    SearchConfig(0x4CFF0) },
        { StaticHookId::DT_Initialize,              SearchConfig(0x32FD0) },
        { StaticHookId::GL_BuildLightmaps,          SearchConfig(0x49BC0) },
        { StaticHookId::Cvar_DirectSet,             SearchConfig(0x2E530) },
        { StaticHookId::V_Init,                     SearchConfig(0xC27F0) },
        { StaticHookId::R_Init,                     SearchConfig(0x46B80) },
        { StaticHookId::R_RenderView,               SearchConfig(0x46440) },
        { StaticHookId::SPR_Draw,                   SearchConfig(0x11AF0) },
        { StaticHookId::SPR_DrawAdditive,           SearchConfig(0x11BF0) },
        { StaticHookId::SPR_DrawHoles,              SearchConfig(0x11B70) },
        { StaticHookId::SPR_DrawGeneric,            SearchConfig(0x11C70) },
        { StaticHookId::SPR_EnableScissor,          SearchConfig(0x11D10) },
        { StaticHookId::SPR_DisableScissor,         SearchConfig(0x11D50) },
        { StaticHookId::GL_SelectTexture,           SearchConfig(0x3C100) },
        { StaticHookId::GL_LoadTexture,             SearchConfig(0x3EFA0) },
        { StaticHookId::GL_Bind,                    SearchConfig(0x3C0A0) },
        { StaticHookId::VGUI2_ResetCurrentTexture,  SearchConfig(0x6A40) },
        { StaticHookId::SetCrosshair,               SearchConfig(0x11600) },
        { StaticHookId::DrawCrosshair,              SearchConfig(0x11670) },
        { StaticHookId::R_DrawTEntitiesOnList,      SearchConfig(0x88AF0) },
        { StaticHookId::CL_FxBlend,                 SearchConfig(0x267F0) },
        { StaticHookId::R_GetAttachmentPoint,       SearchConfig(0x270A0) },
        { StaticHookId::GlowBlend,                  SearchConfig(0x88670) },
        { StaticHookId::R_DrawSpriteModel,          SearchConfig(0x43D70) },
        { StaticHookId::R_DrawBrushModel,           SearchConfig(0x48D30) },
        { StaticHookId::R_DrawAliasModel,           SearchConfig(0x44410) },
        { StaticHookId::ClientDLL_DrawTransparentTriangles, SearchConfig(0xBAB0) },
        { StaticHookId::CL_IsDevOverviewMode,       SearchConfig(0x20920) },
        { StaticHookId::CL_SetDevOverView,          SearchConfig(0x20D10) },
        { StaticHookId::R_SetupFrame,               SearchConfig(0x45640) },
        { StaticHookId::R_SetFrustum,               SearchConfig(0x45270) },
        { StaticHookId::R_SetupGL,                  SearchConfig(0x458D0) },
        { StaticHookId::R_MarkLeaves,               SearchConfig(0x495C0) },
        { StaticHookId::R_DrawWorld,                SearchConfig(0x49440) },
        { StaticHookId::S_ExtraUpdate,              SearchConfig(0x8CC80) },
        { StaticHookId::R_RenderFinalFog,           SearchConfig(0x88E60) },
        { StaticHookId::ClientDLL_DrawNormalTriangles, SearchConfig(0xBA90) },
        { StaticHookId::R_RenderDlights,            SearchConfig(0x430F0) },
        { StaticHookId::R_DrawParticles,            SearchConfig(0x7CB20) },
        { StaticHookId::R_DrawViewModel,            SearchConfig(0x44AA0) },
        { StaticHookId::R_PolyBlend,                SearchConfig(0x45000) },
        { StaticHookId::AddTEntity,                 SearchConfig(0x888D0) },
        { StaticHookId::AppendTEntity,              SearchConfig(0x88A10) },
        { StaticHookId::R_PreDrawViewModel,         SearchConfig(0x44E40) },
        { StaticHookId::R_Clear,                    SearchConfig(0x45CD0) },
        { StaticHookId::MSG_WriteShort,             SearchConfig(0x29C40) },
        { StaticHookId::SNDDMA_Init,                SearchConfig(0x91B60) },
        { StaticHookId::S_Init,                     SearchConfig(0x8B870) },
        { StaticHookId::S_Shutdown,                 SearchConfig(0x8BAA0) },
        { StaticHookId::S_FindName,                 SearchConfig(0x8BAE0) },
        { StaticHookId::S_StartDynamicSound,        SearchConfig(0x8C210) },
        { StaticHookId::S_StartStaticSound,         SearchConfig(0x8C4C0) },
        { StaticHookId::S_StopSound,                SearchConfig(0x8C6A0) },
        { StaticHookId::S_StopAllSounds,            SearchConfig(0x8C6F0) },
        { StaticHookId::S_Update,                   SearchConfig(0x8CA20) },
        { StaticHookId::VoiceSE_NotifyFreeChannel,  SearchConfig(0xC53F0) },
        { StaticHookId::SequenceGetSentenceByIndex, SearchConfig(0x8A900) },
    };

    const std::unordered_map<std::string, SearchConfig> EngineAddressProvider8684Windows::addresses_str_
    {
        { "server",                                 SearchConfig(0x643E4C) },
        { "server_static",                          SearchConfig(0x807580) },
        { "client_static",                          SearchConfig(0x1059AE0) },
        { "client_state",                           SearchConfig(0x10602E0) },
        { "cl_enginefunc",                          SearchConfig(0x136260) },
        { "enginefuncs",                            SearchConfig(0x15b260) },
        { "cldll_func",                             SearchConfig(0x122ED60) },
        { "modfuncs",                               SearchConfig(0x6442b8) },
        { "eng",                                    SearchConfig(0x6C3A40) },
        { "net_message",                            SearchConfig(0xAA2720) },
        { "net_from",                               SearchConfig(0xAB2760) },
        { "msg_readcount",                          SearchConfig(0x1008228) },
        { "host_framecount",                        SearchConfig(0xAB7530) },
        { "host_frametime",                         SearchConfig(0xAB7528) },
        { "realtime",                               SearchConfig(0xAB7600) },
        { "EngineMsgBase",                          SearchConfig(0x13b3b0) },
        { "SampleRate",                             SearchConfig(0x15dfb4) },
        { "gDownloadFile",                          SearchConfig(0xAB3740) },
        { "gfExtendedError",                        SearchConfig(0x6C319C) },
        { "gszDisconnectReason",                    SearchConfig(0x7F5A20) },
        { "scr_downloading",                        SearchConfig(0x147638) },
        { "cmd_source",                             SearchConfig(0x100827C) },
        { "bMajorMapChange",                        SearchConfig(0x643F74) },
        { "careerState",                            SearchConfig(0x643F70) },
        { "loadmodel",                              SearchConfig(0xED4EE0) },
        { "cl_playerindex",                         SearchConfig(0x105DFA8) },
        { "com_argc",                               SearchConfig(0x10076CC) },
        { "com_argv",                               SearchConfig(0x10077E8) },
        { "loadcache",                              SearchConfig(0x10076C4) },
        { "loadbuf",                                SearchConfig(0x10077E4) },
        { "loadsize",                               SearchConfig(0x1008220) },
        { "known_sfx",                              SearchConfig(0xA2ED80) },
        { "num_sfx",                                SearchConfig(0xA3020C) },
        { "cl_entities",                            SearchConfig(0x16CF20) },
        { "noclip_anglehack",                       SearchConfig(0x643F6C) },
        { "currentmodel",                           SearchConfig(0xAB9084) },
        { "r_pcurrentvertbase",                     SearchConfig(0xEC8AE0) },
        { "sys_timescale",                          SearchConfig(0x149CC4) },
        { "shm",                                    SearchConfig(0x6BB1F8) },
        { "wavstreams",                             SearchConfig(0xA2EDA0) },
        { "channels",                               SearchConfig(0xA30220) },
        { "host_initialized",                       SearchConfig(0x643E44) },
        { "g_engdstAddrs",                          SearchConfig(0x14D4B0) },
        { "vid",                                    SearchConfig(0xAB7780) },
        { "gl_mtexable",                            SearchConfig(0x643444) },
        { "r_framecount",                           SearchConfig(0xEC97EC) },
        { "gVShake",                                SearchConfig(0x7EBC40) },
        { "gHostSpawnCount",                        SearchConfig(0x643F68) },
        { "gGLPalette",                             SearchConfig(0xFC3000) },
        { "r_refdef",                               SearchConfig(0xEC96E0) },
        { "currenttexture",                         SearchConfig(0x142240) },
        { "currententity",                          SearchConfig(0xEC98FC) },
        { "r_blend",                                SearchConfig(0xA32418) },
        { "r_entorigin",                            SearchConfig(0xEC98E0) },
        { "g_bUserFogOn",                           SearchConfig(0xA323E4) },
        { "numTransObjs",                           SearchConfig(0x6B78FC) },
        { "transObjects",                           SearchConfig(0x6B7904) },
        { "mtexenabled",                            SearchConfig(0x643310) },
        { "r_worldentity",                          SearchConfig(0xEC8B00) },
        { "mirror",                                 SearchConfig(0xEC97C0) },
        { "c_brush_polys",                          SearchConfig(0xEC97FC) },
        { "c_alias_polys",                          SearchConfig(0xEC99BC) },
        { "cl_numvisedicts",                        SearchConfig(0x120F950) },
        { "cl_visedicts",                           SearchConfig(0x105F0C0) },
        { "isFogEnabled",                           SearchConfig(0x625C94) },
        { "scr_fov_value",                          SearchConfig(0x147584) },
        { "g_SND_VoiceOverdrive",                   SearchConfig(0x154CF0) },
        { "cszrawsentences",                        SearchConfig(0x6BB248) },
        { "rgpszrawsentence",                       SearchConfig(0xA23400) },
        { "scr_con_current",                        SearchConfig(0xAB7BF4) },
        { "developer",                              SearchConfig(0x149E0C) },
    };
}