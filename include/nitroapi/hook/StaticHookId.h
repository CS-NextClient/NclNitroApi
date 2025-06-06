#pragma once

#include <magic_enum/magic_enum.hpp>

namespace nitroapi
{
    enum class StaticHookId
    {
        LoadLibraryA,
        LoadLibraryW,
        FreeLibrary,
        SetCursor,

        // hw.dll
        Cbuf_AddText = 500,
        CL_QueueHTTPDownload,
        CL_HTTPUpdate,
        CL_CanUseHTTPDownload,
        CL_GetDownloadQueueSize,
        CL_Connect_f,
        CL_HTTPStop_f,
        CL_HTTPCancel_f,
        CL_Disconnect,
        CL_SendConsistencyInfo,
        CL_Init,
        CL_CheckFile,
        CL_SendConnectPacket,
        CL_ParseResourceList,
        CL_StartResourceDownloading,
        Cvar_Set,
        Cvar_Command,
        SCR_UpdateScreen,
        BuildSurfaceDisplayList,
        COM_InitArgv,
        COM_CreateCustomization,
        SetCareerAudioState,
        Draw_DecalSetName,
        Cmd_TokenizeString,
        Info_IsKeyImportant,
        Netchan_CopyFileFragments,
        SVC_Nop,
        SVC_Disconnect,
        SVC_Event,
        SVC_Version,
        SVC_SetView,
        SVC_Sound,
        SVC_Time,
        SVC_Print,
        SVC_StuffText,
        SVC_SetAngle,
        SVC_ResourceList,
        SVC_ResourceLocation,
        SVC_Director,
        SVC_SignOnNum,
        SVC_NewUserMsg,
        SVC_SendCvarValue,
        SVC_UpdateUserInfo,
        SVC_TimeScale,
        NET_SendPacket,
        NET_GetPacket,
        NET_GetPacket_0,
        Net_APICheckTimeouts,
        Sys_InitGame,
        Host_WriteConfiguration,
        Host_Frame,
        Host_FrameInternal,
        Host_FilterTime,
        Host_Map_f,
        Host_Map,
        Con_MessageMode_f,
        Con_MessageMode2_f,
        Key_Message,
        Host_InitializeGameDLL,
        ForceReloadProfile,
        VGuiWrap2_ConPrintf,
        SystemWrapper_RunFrame,
        ClientDLL_Frame,
        ClientDLL_Init,
        GL_SetMode,
        Con_Printf,
        Con_DPrintf,
        SZ_Write,
        SZ_Clear,
        Netchan_FlushIncoming,
        CreateVoiceRecord_DSound,
        CreateVoiceRecord_WaveIn,
        MSG_BeginReading,
        MSG_StartBitReading,
        MSG_EndBitReading,
        MSG_ReadBits,
        MSG_ReadBitString,
        MSG_ReadBitData,
        MSG_ReadByte,
        MSG_ReadString,
        MSG_ReadLong,
        MSG_ReadFloat,
        MSG_ReadStringLine,
        MSG_WriteByte,
        MSG_WriteString,
        Mem_Free,
        Mem_Malloc,
        Mem_ZeroMalloc,
        Mem_Strdup,
        CL_ParseServerMessage,
        CL_RegisterResources,
        CL_ReadPackets,
        CL_PrecacheResources,
        Sys_Error,
        Sys_Printf,
        AddStartupTiming,
        HPAK_GetDataPointer,
        HPAK_AddLump,
        Netchan_CreateFragments,
        Netchan_FragSend,
        Netchan_Process,
        Netchan_CopyNormalFragments,
        Netchan_UpdateProgress,
        Netchan_Setup,
        NotifyDedicatedServerUI,
        StartLoadingProgressBar,
        SetLoadingProgressBarStatusText,
        Mod_ClearAll,
        Mod_FindName,
        Mod_LoadModel,
        Mod_Print,
        Mod_ValidateCRC,
        Mod_NeedCRC,
        Mod_LoadAliasModel,
        Mod_LoadSpriteModel,
        Mod_LoadStudioModel,
        Mod_LoadBrushModel,
        S_PrecacheSound,
        SPR_Shutdown,
        SPR_Init,
        SPR_Load,
        R_StudioReloadSkin,
        R_NewMap,
        DT_LoadDetailMapFile,
        Cache_Alloc,
        Cache_Check,
        Cache_Free,
        Z_Malloc,
        Hunk_AllocName,
        Hunk_TempAlloc,
        Hunk_Check,
        CL_MarkMapAsUsingHTTPDownload,
        CL_SetSolidEntities,
        CL_ConnectionlessPacket,
        CL_ProcessFile_0,
        CL_RequestMissingResources,
        CL_InitSpectator,
        CL_ReallocateDynamicData,
        CL_WriteDemoStartup,
        CL_WriteDemoMessage,
        CL_Record_f,
        S_LoadSound,
        VoiceSE_GetSFXCache,
        Sys_FloatTime,
        GL_UnloadTexture,
        SPR_Set,
        SPR_Width,
        SPR_Height,
        SPR_Frames,
        SPR_GetModelPointer,
        SPR_Shutdown_NoModelFree,
        CL_GetModelByIndex,
        GL_Init,
        DT_Initialize,
        GL_BuildLightmaps,
        Cvar_DirectSet,
        V_Init,
        R_Init,
        R_RenderView,
        SPR_Draw,
        SPR_DrawAdditive,
        SPR_DrawHoles,
        SPR_DrawGeneric,
        SPR_EnableScissor,
        SPR_DisableScissor,
        GL_SelectTexture,
        GL_LoadTexture,
        GL_Bind,
        VGUI2_ResetCurrentTexture,
        SetCrosshair,
        DrawCrosshair,
        R_DrawTEntitiesOnList,
        CL_FxBlend,
        R_GetAttachmentPoint,
        GlowBlend,
        R_DrawSpriteModel,
        R_DrawBrushModel,
        R_DrawAliasModel,
        ClientDLL_DrawTransparentTriangles,
        CL_IsDevOverviewMode,
        CL_SetDevOverView,
        R_SetupFrame,
        R_SetFrustum,
        R_SetupGL,
        R_MarkLeaves,
        R_DrawWorld,
        S_ExtraUpdate,
        R_RenderFinalFog,
        AllowFog,
        ClientDLL_DrawNormalTriangles,
        R_RenderDlights,
        R_DrawParticles,
        R_DrawViewModel,
        R_PolyBlend,
        AddTEntity,
        AppendTEntity,
        R_PreDrawViewModel,
        R_Clear,
        MSG_WriteShort,
        SNDDMA_Init,
        S_Init,
        S_Shutdown,
        S_FindName,
        S_StartDynamicSound,
        S_StartStaticSound,
        S_StopSound,
        S_StopAllSounds,
        S_Update,
        VoiceSE_NotifyFreeChannel,
        SequenceGetSentenceByIndex,
        CL_ConnectClient,
        CL_GetFragmentSize,
        NET_ClearLagData,
        SZ_GetSpace,
        Host_Shutdown,
        Host_Quit_f,
        CL_ClearClientState,
        MD5_Hash_File,
        COM_ClearCustomizationList,
        HPAK_FlushHostQueue,
        ClientDLL_HudInit,

        // client.dll
        UserMsg_MOTD = 1000,
        UserMsg_AmmoX,

        CLDLL_Initialize,
        HUD_Init,
        HUD_VidInit,
        HUD_Redraw,
        HUD_UpdateClientData,
        HUD_Reset,
        HUD_PlayerMove,
        HUD_PlayerMoveInit,
        HUD_PlayerMoveTexture,
        IN_ActivateMouse,
        IN_DeactivateMouse,
        IN_MouseEvent,
        IN_ClearStates,
        IN_Accumulate,
        CL_CreateMove,
        CL_IsThirdPerson,
        CL_CameraOffset,
        KB_Find,
        CAM_Think,
        V_CalcRefdef,
        HUD_AddEntity,
        HUD_CreateEntities,
        HUD_DrawNormalTriangles,
        HUD_DrawTransparentTriangles,
        HUD_StudioEvent,
        HUD_PostRunCmd,
        HUD_Shutdown,
        HUD_TxferLocalOverrides,
        HUD_ProcessPlayerState,
        HUD_TxferPredictionData,
        Demo_ReadBuffer,
        HUD_ConnectionlessPacket,
        HUD_GetHullBounds,
        HUD_Frame,
        HUD_Key_Event,
        HUD_TempEntUpdate,
        HUD_GetUserEntity,
        HUD_VoiceStatus,
        HUD_DirectorMessage,
        HUD_GetStudioModelInterface,

        CHudAmmo__DrawCrosshair,
        CHudHealth__Draw,
        CHudHealth__DrawRadar,
        CHudHealth__GetAllPlayersInfo,
        CHudDeathNotice__Draw,

        UserMsg_SetFOV,
        UserMsg_CurWeapon,
        UserMsg_InitHUD,
        UserMsg_DeathMsg,
        UserMsg_TextMsg,

        // SDL2.dll
        SDL_DestroyWindow = 1500,
        SDL_CreateWindow,
        SDL_GetError,
        SDL_GL_GetProcAddress,

        LAST_ITEM
    };
}

template <>
struct magic_enum::customize::enum_range<nitroapi::StaticHookId> {
    static constexpr int min = 0;
    static constexpr int max = (int)nitroapi::StaticHookId::LAST_ITEM;
};
