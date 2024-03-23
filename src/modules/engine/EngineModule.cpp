#include "EngineModule.h"
#include "enginemsg_utils.h"
#include <utility>

namespace nitroapi
{
    EngineModule::EngineModule(std::shared_ptr<HookStorage> hook_storage,
                               std::shared_ptr<AddressProviderBase> addr_provider,
                               NitroApiInterface* nitro_api,
                               ICommandLine* command_line,
                               IFileSystem* file_system,
                               IRegistry* registry) :
        ModuleBase(std::move(hook_storage), std::move(addr_provider)),
        nitro_api_(nitro_api),
        command_line_(command_line),
        file_system_(file_system),
        registry_(registry)
    {
        engine_data_ = std::make_shared<EngineData>();

        RegisterVar(&engine_data_->EngineMsgBase, "EngineMsgBase");
        RegisterVar(&engine_data_->msg_readcount, "msg_readcount");
        RegisterVar(&engine_data_->host_framecount, "host_framecount");
        RegisterVar(&engine_data_->realtime, "realtime");
        RegisterVar(&engine_data_->host_frametime, "host_frametime");
        RegisterVar(&engine_data_->SampleRate, "SampleRate");
        RegisterVar(&engine_data_->gDownloadFile, "gDownloadFile");
        RegisterVar(&engine_data_->gfExtendedError, "gfExtendedError");
        RegisterVar(&engine_data_->gszDisconnectReason, "gszDisconnectReason");
        RegisterVar(&engine_data_->client_static, "client_static");
        RegisterVar(&engine_data_->server_static, "server_static");
        RegisterVar(&engine_data_->server, "server");
        RegisterVar(&engine_data_->client_state, "client_state");
        RegisterVar(&engine_data_->cl_enginefunc, "cl_enginefunc");
        RegisterVar(&engine_data_->enginefuncs, "enginefuncs");
        RegisterVar(&engine_data_->net_message, "net_message");
        RegisterVar(&engine_data_->net_from, "net_from");
        RegisterVar(&engine_data_->cldll_func, "cldll_func");
        RegisterVar(&engine_data_->modfuncs, "modfuncs");
        RegisterVar(&engine_data_->eng, "eng");
        RegisterVar(&engine_data_->scr_downloading, "scr_downloading");
        RegisterVar(&engine_data_->cmd_source, "cmd_source");
        RegisterVar(&engine_data_->bMajorMapChange, "bMajorMapChange");
        RegisterVar(&engine_data_->careerState, "careerState");
        RegisterVar(&engine_data_->loadmodel, "loadmodel");
        RegisterVar(&engine_data_->cl_playerindex, "cl_playerindex");
        RegisterVar(&engine_data_->com_argc, "com_argc");
        RegisterVar(&engine_data_->com_argv, "com_argv");
        RegisterVar(&engine_data_->loadcache, "loadcache");
        RegisterVar(&engine_data_->loadbuf, "loadbuf");
        RegisterVar(&engine_data_->loadsize, "loadsize");
        RegisterVar(&engine_data_->known_sfx, "known_sfx");
        RegisterVar(&engine_data_->num_sfx, "num_sfx");
        RegisterVar(&engine_data_->cl_entities, "cl_entities");
        RegisterVar(&engine_data_->noclip_anglehack, "noclip_anglehack");
        RegisterVar(&engine_data_->currentmodel, "currentmodel");
        RegisterVar(&engine_data_->r_pcurrentvertbase, "r_pcurrentvertbase");
        RegisterVar(&engine_data_->sys_timescale, "sys_timescale");
        RegisterVar(&engine_data_->shm, "shm");
        RegisterVar(&engine_data_->wavstreams, "wavstreams");
        RegisterVar(&engine_data_->channels, "channels");
        RegisterVar(&engine_data_->host_initialized, "host_initialized");
        RegisterVar(&engine_data_->g_engdstAddrs, "g_engdstAddrs");
        RegisterVar(&engine_data_->vid, "vid");
        RegisterVar(&engine_data_->gl_mtexable, "gl_mtexable");
        RegisterVar(&engine_data_->r_framecount, "r_framecount");
        RegisterVar(&engine_data_->gVShake, "gVShake");
        RegisterVar(&engine_data_->gHostSpawnCount, "gHostSpawnCount");
        RegisterVar(&engine_data_->gGLPalette, "gGLPalette");
        RegisterVar(&engine_data_->r_refdef, "r_refdef");
        RegisterVar(&engine_data_->currenttexture, "currenttexture");
        RegisterVar(&engine_data_->currententity, "currententity");
        RegisterVar(&engine_data_->r_blend, "r_blend");
        RegisterVar(&engine_data_->r_entorigin, "r_entorigin");
        RegisterVar(&engine_data_->g_bUserFogOn, "g_bUserFogOn");
        RegisterVar(&engine_data_->numTransObjs, "numTransObjs");
        RegisterVar(&engine_data_->transObjects, "transObjects");
        RegisterVar(&engine_data_->mtexenabled, "mtexenabled");
        RegisterVar(&engine_data_->r_worldentity, "r_worldentity");
        RegisterVar(&engine_data_->mirror, "mirror");
        RegisterVar(&engine_data_->c_brush_polys, "c_brush_polys");
        RegisterVar(&engine_data_->c_alias_polys, "c_alias_polys");
        RegisterVar(&engine_data_->cl_numvisedicts, "cl_numvisedicts");
        RegisterVar(&engine_data_->cl_visedicts, "cl_visedicts");
        RegisterVar(&engine_data_->isFogEnabled, "isFogEnabled");
        RegisterVar(&engine_data_->scr_fov_value, "scr_fov_value");
        RegisterVar(&engine_data_->g_SND_VoiceOverdrive, "g_SND_VoiceOverdrive");
        RegisterVar(&engine_data_->cszrawsentences, "cszrawsentences");
        RegisterVar(&engine_data_->rgpszrawsentence, "rgpszrawsentence");

        RegisterFuncCdecl<StaticHookId::Cbuf_AddText>(&engine_data_->Cbuf_AddText);
        RegisterFuncCdecl<StaticHookId::CL_QueueHTTPDownload>(&engine_data_->CL_QueueHTTPDownload);
        RegisterFuncCdecl<StaticHookId::CL_HTTPUpdate>(&engine_data_->CL_HTTPUpdate);
        RegisterFuncCdecl<StaticHookId::CL_CanUseHTTPDownload>(&engine_data_->CL_CanUseHTTPDownload);
        RegisterFuncCdecl<StaticHookId::CL_GetDownloadQueueSize>(&engine_data_->CL_GetDownloadQueueSize);
        RegisterFuncCdecl<StaticHookId::CL_Connect_f>(&engine_data_->CL_Connect_f);
        RegisterFuncCdecl<StaticHookId::CL_HTTPStop_f>(&engine_data_->CL_HTTPStop_f);
        RegisterFuncCdecl<StaticHookId::CL_HTTPCancel_f>(&engine_data_->CL_HTTPCancel_f);
        RegisterFuncCdecl<StaticHookId::CL_Disconnect>(&engine_data_->CL_Disconnect);
        RegisterFuncCdecl<StaticHookId::CL_SendConsistencyInfo>(&engine_data_->CL_SendConsistencyInfo);
        RegisterFuncCdecl<StaticHookId::CL_Init>(&engine_data_->CL_Init);
        RegisterFuncCdecl<StaticHookId::CL_CheckFile>(&engine_data_->CL_CheckFile);
        RegisterFuncCdecl<StaticHookId::CL_SendConnectPacket>(&engine_data_->CL_SendConnectPacket);
        RegisterFuncCdecl<StaticHookId::CL_ParseResourceList>(&engine_data_->CL_ParseResourceList);
        RegisterFuncCdecl<StaticHookId::CL_StartResourceDownloading>(&engine_data_->CL_StartResourceDownloading);
        RegisterFuncCdecl<StaticHookId::CL_ParseServerMessage>(&engine_data_->CL_ParseServerMessage);
        RegisterFuncCdecl<StaticHookId::CL_RegisterResources>(&engine_data_->CL_RegisterResources);
        RegisterFuncCdecl<StaticHookId::CL_PrecacheResources>(&engine_data_->CL_PrecacheResources);
        RegisterFuncCdecl<StaticHookId::CL_ReadPackets>(&engine_data_->CL_ReadPackets);
        RegisterFuncCdecl<StaticHookId::CL_MarkMapAsUsingHTTPDownload>(&engine_data_->CL_MarkMapAsUsingHTTPDownload);
        RegisterFuncCdecl<StaticHookId::CL_SetSolidEntities>(&engine_data_->CL_SetSolidEntities);
        RegisterFuncCdecl<StaticHookId::CL_ConnectionlessPacket>(&engine_data_->CL_ConnectionlessPacket);
        RegisterFuncCdecl<StaticHookId::CL_ProcessFile_0>(&engine_data_->CL_ProcessFile_0);
        RegisterFuncCdecl<StaticHookId::CL_RequestMissingResources>(&engine_data_->CL_RequestMissingResources);
        RegisterFuncCdecl<StaticHookId::CL_InitSpectator>(&engine_data_->CL_InitSpectator);
        RegisterFuncCdecl<StaticHookId::CL_ReallocateDynamicData>(&engine_data_->CL_ReallocateDynamicData);
        RegisterFuncCdecl<StaticHookId::Cvar_Set>(&engine_data_->Cvar_Set);
        RegisterFuncCdecl<StaticHookId::Cvar_Command>(&engine_data_->Cvar_Command);
        RegisterFuncCdecl<StaticHookId::SCR_UpdateScreen>(&engine_data_->SCR_UpdateScreen);
        RegisterFuncCdecl<StaticHookId::BuildSurfaceDisplayList>(&engine_data_->BuildSurfaceDisplayList);
        RegisterFuncCdecl<StaticHookId::COM_InitArgv>(&engine_data_->COM_InitArgv);
        RegisterFuncCdecl<StaticHookId::COM_CreateCustomization>(&engine_data_->COM_CreateCustomization);
        RegisterFuncCdecl<StaticHookId::SetCareerAudioState>(&engine_data_->SetCareerAudioState);
        RegisterFuncCdecl<StaticHookId::Cmd_TokenizeString>(&engine_data_->Cmd_TokenizeString);
        RegisterFuncCdecl<StaticHookId::Draw_DecalSetName>(&engine_data_->Draw_DecalSetName);
        RegisterFuncCdecl<StaticHookId::Info_IsKeyImportant>(&engine_data_->Info_IsKeyImportant);
        RegisterFuncCdecl<StaticHookId::Netchan_CopyFileFragments>(&engine_data_->Netchan_CopyFileFragments);
        RegisterFuncCdecl<StaticHookId::Netchan_FlushIncoming>(&engine_data_->Netchan_FlushIncoming);
        RegisterFuncCdecl<StaticHookId::Netchan_Process>(&engine_data_->Netchan_Process);
        RegisterFuncCdecl<StaticHookId::Netchan_CopyNormalFragments>(&engine_data_->Netchan_CopyNormalFragments);
        RegisterFuncCdecl<StaticHookId::Netchan_CreateFragments>(&engine_data_->Netchan_CreateFragments);
        RegisterFuncCdecl<StaticHookId::Netchan_FragSend>(&engine_data_->Netchan_FragSend);
        RegisterFuncCdecl<StaticHookId::Netchan_UpdateProgress>(&engine_data_->Netchan_UpdateProgress);
        RegisterFuncCdecl<StaticHookId::Netchan_Setup>(&engine_data_->Netchan_Setup);
        RegisterFuncCdecl<StaticHookId::NET_SendPacket>(&engine_data_->NET_SendPacket);
        RegisterFuncCdecl<StaticHookId::NET_GetPacket>(&engine_data_->NET_GetPacket);
        RegisterFuncCdecl<StaticHookId::NET_GetPacket_0>(&engine_data_->NET_GetPacket_0);
        RegisterFuncCdecl<StaticHookId::Net_APICheckTimeouts>(&engine_data_->Net_APICheckTimeouts);
        RegisterFuncCdecl<StaticHookId::Sys_InitGame>(&engine_data_->Sys_InitGame);
        RegisterFuncVaformat<StaticHookId::Sys_Error>(&engine_data_->Sys_Error);
        RegisterFuncVaformat<StaticHookId::Sys_Printf>(&engine_data_->Sys_Printf);
        RegisterFuncCdecl<StaticHookId::Host_WriteConfiguration>(&engine_data_->Host_WriteConfiguration);
        RegisterFuncCdecl<StaticHookId::Host_Frame>(&engine_data_->Host_Frame);
        RegisterFuncCdecl<StaticHookId::Host_FrameInternal>(&engine_data_->Host_FrameInternal);
        RegisterFuncCdecl<StaticHookId::Host_FilterTime>(&engine_data_->Host_FilterTime);
        RegisterFuncCdecl<StaticHookId::Host_Map_f>(&engine_data_->Host_Map_f);
        RegisterFuncCdecl<StaticHookId::Host_Map>(&engine_data_->Host_Map);
        RegisterFuncCdecl<StaticHookId::Host_InitializeGameDLL>(&engine_data_->Host_InitializeGameDLL);
        RegisterFuncCdecl<StaticHookId::ForceReloadProfile>(&engine_data_->ForceReloadProfile);
        RegisterFuncCdecl<StaticHookId::VGuiWrap2_ConPrintf>(&engine_data_->VGuiWrap2_ConPrintf);
        RegisterFuncCdecl<StaticHookId::SystemWrapper_RunFrame>(&engine_data_->SystemWrapper_RunFrame);
        RegisterFuncCdecl<StaticHookId::GL_SetMode>(&engine_data_->GL_SetMode);
        RegisterFuncCdecl<StaticHookId::NotifyDedicatedServerUI>(&engine_data_->NotifyDedicatedServerUI);
        RegisterFuncCdecl<StaticHookId::StartLoadingProgressBar>(&engine_data_->StartLoadingProgressBar);
        RegisterFuncCdecl<StaticHookId::SetLoadingProgressBarStatusText>(&engine_data_->SetLoadingProgressBarStatusText);
        RegisterFuncCdecl<StaticHookId::Mod_ClearAll>(&engine_data_->Mod_ClearAll);
        RegisterFuncCdecl<StaticHookId::Mod_FindName>(&engine_data_->Mod_FindName);
        RegisterFuncCdecl<StaticHookId::Mod_LoadModel>(&engine_data_->Mod_LoadModel);
        RegisterFuncCdecl<StaticHookId::Mod_Print>(&engine_data_->Mod_Print);
        RegisterFuncCdecl<StaticHookId::Mod_ValidateCRC>(&engine_data_->Mod_ValidateCRC);
        RegisterFuncCdecl<StaticHookId::Mod_NeedCRC>(&engine_data_->Mod_NeedCRC);
        RegisterFuncCdecl<StaticHookId::Mod_LoadAliasModel>(&engine_data_->Mod_LoadAliasModel);
        RegisterFuncCdecl<StaticHookId::Mod_LoadSpriteModel>(&engine_data_->Mod_LoadSpriteModel);
        RegisterFuncCdecl<StaticHookId::Mod_LoadStudioModel>(&engine_data_->Mod_LoadStudioModel);
        RegisterFuncCdecl<StaticHookId::Mod_LoadBrushModel>(&engine_data_->Mod_LoadBrushModel);
        RegisterFuncCdecl<StaticHookId::S_PrecacheSound>(&engine_data_->S_PrecacheSound);
        RegisterFuncCdecl<StaticHookId::SPR_Shutdown>(&engine_data_->SPR_Shutdown);
        RegisterFuncCdecl<StaticHookId::SPR_Init>(&engine_data_->SPR_Init);
        RegisterFuncCdecl<StaticHookId::SPR_Load>(&engine_data_->SPR_Load);
        RegisterFuncCdecl<StaticHookId::R_StudioReloadSkin>(&engine_data_->R_StudioReloadSkin);
        RegisterFuncCdecl<StaticHookId::R_NewMap>(&engine_data_->R_NewMap);
        RegisterFuncCdecl<StaticHookId::DT_LoadDetailMapFile>(&engine_data_->DT_LoadDetailMapFile);
        RegisterFuncCdecl<StaticHookId::Cache_Alloc>(&engine_data_->Cache_Alloc);
        RegisterFuncCdecl<StaticHookId::Cache_Check>(&engine_data_->Cache_Check);
        RegisterFuncCdecl<StaticHookId::Cache_Free>(&engine_data_->Cache_Free);
        RegisterFuncCdecl<StaticHookId::Z_Malloc>(&engine_data_->Z_Malloc);
        RegisterFuncCdecl<StaticHookId::Hunk_AllocName>(&engine_data_->Hunk_AllocName);
        RegisterFuncCdecl<StaticHookId::Hunk_TempAlloc>(&engine_data_->Hunk_TempAlloc);
        RegisterFuncCdecl<StaticHookId::Hunk_Check>(&engine_data_->Hunk_Check);
        RegisterFuncCdecl<StaticHookId::ClientDLL_Frame>(&engine_data_->ClientDLL_Frame);
        RegisterFuncCdecl<StaticHookId::ClientDLL_Init>(&engine_data_->ClientDLL_Init);
        RegisterFuncCdecl<StaticHookId::AddStartupTiming>(&engine_data_->AddStartupTiming);
        RegisterFuncCdecl<StaticHookId::HPAK_GetDataPointer>(&engine_data_->HPAK_GetDataPointer);
        RegisterFuncCdecl<StaticHookId::HPAK_AddLump>(&engine_data_->HPAK_AddLump);
        RegisterFuncVaformat<StaticHookId::Con_Printf>(&engine_data_->Con_Printf);
        RegisterFuncVaformat<StaticHookId::Con_DPrintf>(&engine_data_->Con_DPrintf);
        RegisterFuncCdecl<StaticHookId::Mem_Free>(&engine_data_->Mem_Free);
        RegisterFuncCdecl<StaticHookId::Mem_Malloc>(&engine_data_->Mem_Malloc);
        RegisterFuncCdecl<StaticHookId::Mem_ZeroMalloc>(&engine_data_->Mem_ZeroMalloc);
        RegisterFuncCdecl<StaticHookId::Mem_Strdup>(&engine_data_->Mem_Strdup);
        RegisterFuncCdecl<StaticHookId::SZ_Write>(&engine_data_->SZ_Write);
        RegisterFuncCdecl<StaticHookId::SZ_Clear>(&engine_data_->SZ_Clear);
        RegisterFuncCdecl<StaticHookId::CreateVoiceRecord_DSound>(&engine_data_->CreateVoiceRecord_DSound);
        RegisterFuncCdecl<StaticHookId::CreateVoiceRecord_WaveIn>(&engine_data_->CreateVoiceRecord_WaveIn);
        RegisterFuncCdecl<StaticHookId::MSG_BeginReading>(&engine_data_->MSG_BeginReading);
        RegisterFuncCdecl<StaticHookId::MSG_StartBitReading>(&engine_data_->MSG_StartBitReading);
        RegisterFuncCdecl<StaticHookId::MSG_EndBitReading>(&engine_data_->MSG_EndBitReading);
        RegisterFuncCdecl<StaticHookId::MSG_ReadBits>(&engine_data_->MSG_ReadBits);
        RegisterFuncCdecl<StaticHookId::MSG_ReadBitString>(&engine_data_->MSG_ReadBitString);
        RegisterFuncCdecl<StaticHookId::MSG_ReadBitData>(&engine_data_->MSG_ReadBitData);
        RegisterFuncCdecl<StaticHookId::MSG_ReadByte>(&engine_data_->MSG_ReadByte);
        RegisterFuncCdecl<StaticHookId::MSG_ReadString>(&engine_data_->MSG_ReadString);
        RegisterFuncCdecl<StaticHookId::MSG_ReadLong>(&engine_data_->MSG_ReadLong);
        RegisterFuncCdecl<StaticHookId::MSG_ReadFloat>(&engine_data_->MSG_ReadFloat);
        RegisterFuncCdecl<StaticHookId::MSG_ReadStringLine>(&engine_data_->MSG_ReadStringLine);
        RegisterFuncCdecl<StaticHookId::MSG_WriteByte>(&engine_data_->MSG_WriteByte);
        RegisterFuncCdecl<StaticHookId::MSG_WriteString>(&engine_data_->MSG_WriteString);
        RegisterFuncCdecl<StaticHookId::CL_WriteDemoStartup>(&engine_data_->CL_WriteDemoStartup);
        RegisterFuncCdecl<StaticHookId::CL_WriteDemoMessage>(&engine_data_->CL_WriteDemoMessage);
        RegisterFuncCdecl<StaticHookId::CL_Record_f>(&engine_data_->CL_Record_f);
        RegisterFuncCdecl<StaticHookId::S_LoadSound>(&engine_data_->S_LoadSound);
        RegisterFuncCdecl<StaticHookId::VoiceSE_GetSFXCache>(&engine_data_->VoiceSE_GetSFXCache);
        RegisterFuncCdecl<StaticHookId::Sys_FloatTime>(&engine_data_->Sys_FloatTime);
        RegisterFuncCdecl<StaticHookId::GL_UnloadTexture>(&engine_data_->GL_UnloadTexture);
        RegisterFuncCdecl<StaticHookId::SPR_Set>(&engine_data_->SPR_Set);
        RegisterFuncCdecl<StaticHookId::SPR_Width>(&engine_data_->SPR_Width);
        RegisterFuncCdecl<StaticHookId::SPR_Height>(&engine_data_->SPR_Height);
        RegisterFuncCdecl<StaticHookId::SPR_Frames>(&engine_data_->SPR_Frames);
        RegisterFuncCdecl<StaticHookId::SPR_GetModelPointer>(&engine_data_->SPR_GetModelPointer);
        RegisterFuncCdecl<StaticHookId::SPR_Shutdown_NoModelFree>(&engine_data_->SPR_Shutdown_NoModelFree);
        RegisterFuncCdecl<StaticHookId::SPR_Draw>(&engine_data_->SPR_Draw);
        RegisterFuncCdecl<StaticHookId::SPR_DrawAdditive>(&engine_data_->SPR_DrawAdditive);
        RegisterFuncCdecl<StaticHookId::SPR_DrawHoles>(&engine_data_->SPR_DrawHoles);
        RegisterFuncCdecl<StaticHookId::SPR_DrawGeneric>(&engine_data_->SPR_DrawGeneric);
        RegisterFuncCdecl<StaticHookId::SPR_EnableScissor>(&engine_data_->SPR_EnableScissor);
        RegisterFuncCdecl<StaticHookId::SPR_DisableScissor>(&engine_data_->SPR_DisableScissor);
        RegisterFuncCdecl<StaticHookId::CL_GetModelByIndex>(&engine_data_->CL_GetModelByIndex);
        RegisterFuncCdecl<StaticHookId::GL_Init>(&engine_data_->GL_Init);
        RegisterFuncCdecl<StaticHookId::DT_Initialize>(&engine_data_->DT_Initialize);
        RegisterFuncCdecl<StaticHookId::GL_BuildLightmaps>(&engine_data_->GL_BuildLightmaps);
        RegisterFuncCdecl<StaticHookId::Cvar_DirectSet>(&engine_data_->Cvar_DirectSet);
        RegisterFuncCdecl<StaticHookId::V_Init>(&engine_data_->V_Init);
        RegisterFuncCdecl<StaticHookId::R_Init>(&engine_data_->R_Init);
        RegisterFuncCdecl<StaticHookId::R_RenderView>(&engine_data_->R_RenderView);
        RegisterFuncCdecl<StaticHookId::GL_SelectTexture>(&engine_data_->GL_SelectTexture);
        RegisterFuncCdecl<StaticHookId::GL_LoadTexture>(&engine_data_->GL_LoadTexture);
        RegisterFuncCdecl<StaticHookId::GL_Bind>(&engine_data_->GL_Bind);
        RegisterFuncCdecl<StaticHookId::VGUI2_ResetCurrentTexture>(&engine_data_->VGUI2_ResetCurrentTexture);
        RegisterFuncCdecl<StaticHookId::SetCrosshair>(&engine_data_->SetCrosshair);
        RegisterFuncCdecl<StaticHookId::DrawCrosshair>(&engine_data_->DrawCrosshair);
        RegisterFuncCdecl<StaticHookId::R_DrawTEntitiesOnList>(&engine_data_->R_DrawTEntitiesOnList);
        RegisterFuncCdecl<StaticHookId::CL_FxBlend>(&engine_data_->CL_FxBlend);
        RegisterFuncCdecl<StaticHookId::R_GetAttachmentPoint>(&engine_data_->R_GetAttachmentPoint);
        RegisterFuncCdecl<StaticHookId::GlowBlend>(&engine_data_->GlowBlend);
        RegisterFuncCdecl<StaticHookId::R_DrawSpriteModel>(&engine_data_->R_DrawSpriteModel);
        RegisterFuncCdecl<StaticHookId::R_DrawBrushModel>(&engine_data_->R_DrawBrushModel);
        RegisterFuncCdecl<StaticHookId::R_DrawAliasModel>(&engine_data_->R_DrawAliasModel);
        RegisterFuncCdecl<StaticHookId::ClientDLL_DrawTransparentTriangles>(&engine_data_->ClientDLL_DrawTransparentTriangles);
        RegisterFuncCdecl<StaticHookId::CL_IsDevOverviewMode>(&engine_data_->CL_IsDevOverviewMode);
        RegisterFuncCdecl<StaticHookId::CL_SetDevOverView>(&engine_data_->CL_SetDevOverView);
        RegisterFuncCdecl<StaticHookId::R_SetupFrame>(&engine_data_->R_SetupFrame);
        RegisterFuncCdecl<StaticHookId::R_SetFrustum>(&engine_data_->R_SetFrustum);
        RegisterFuncCdecl<StaticHookId::R_SetupGL>(&engine_data_->R_SetupGL);
        RegisterFuncCdecl<StaticHookId::R_MarkLeaves>(&engine_data_->R_MarkLeaves);
        RegisterFuncCdecl<StaticHookId::R_DrawWorld>(&engine_data_->R_DrawWorld);
        RegisterFuncCdecl<StaticHookId::S_ExtraUpdate>(&engine_data_->S_ExtraUpdate);
        RegisterFuncCdecl<StaticHookId::R_RenderFinalFog>(&engine_data_->R_RenderFinalFog);
        RegisterFuncCdecl<StaticHookId::ClientDLL_DrawNormalTriangles>(&engine_data_->ClientDLL_DrawNormalTriangles);
        RegisterFuncCdecl<StaticHookId::R_RenderDlights>(&engine_data_->R_RenderDlights);
        RegisterFuncCdecl<StaticHookId::R_DrawParticles>(&engine_data_->R_DrawParticles);
        RegisterFuncCdecl<StaticHookId::R_DrawViewModel>(&engine_data_->R_DrawViewModel);
        RegisterFuncCdecl<StaticHookId::R_PolyBlend>(&engine_data_->R_PolyBlend);
        RegisterFuncCdecl<StaticHookId::AddTEntity>(&engine_data_->AddTEntity);
        RegisterFuncCdecl<StaticHookId::AppendTEntity>(&engine_data_->AppendTEntity);
        RegisterFuncCdecl<StaticHookId::R_PreDrawViewModel>(&engine_data_->R_PreDrawViewModel);
        RegisterFuncCdecl<StaticHookId::R_Clear>(&engine_data_->R_Clear);
        RegisterFuncCdecl<StaticHookId::MSG_WriteShort>(&engine_data_->MSG_WriteShort);
        RegisterFuncCdecl<StaticHookId::SNDDMA_Init>(&engine_data_->SNDDMA_Init);
        RegisterFuncCdecl<StaticHookId::S_Init>(&engine_data_->S_Init);
        RegisterFuncCdecl<StaticHookId::S_Shutdown>(&engine_data_->S_Shutdown);
        RegisterFuncCdecl<StaticHookId::S_FindName>(&engine_data_->S_FindName);
        RegisterFuncCdecl<StaticHookId::S_StartDynamicSound>(&engine_data_->S_StartDynamicSound);
        RegisterFuncCdecl<StaticHookId::S_StartStaticSound>(&engine_data_->S_StartStaticSound);
        RegisterFuncCdecl<StaticHookId::S_StopSound>(&engine_data_->S_StopSound);
        RegisterFuncCdecl<StaticHookId::S_StopAllSounds>(&engine_data_->S_StopAllSounds);
        RegisterFuncCdecl<StaticHookId::S_Update>(&engine_data_->S_Update);
        RegisterFuncCdecl<StaticHookId::VoiceSE_NotifyFreeChannel>(&engine_data_->VoiceSE_NotifyFreeChannel);
        RegisterFuncCdecl<StaticHookId::SequenceGetSentenceByIndex>(&engine_data_->SequenceGetSentenceByIndex);

        RegisterFuncCdecl<StaticHookId::SVC_Nop>(&engine_data_->SVC_Nop, [this](nitro_utils::SysModule hModule){return (uint32_t)FindEngineMsgByName(engine_data_->EngineMsgBase, "svc_nop")->pfn;});
        RegisterFuncCdecl<StaticHookId::SVC_Disconnect>(&engine_data_->SVC_Disconnect, [this](nitro_utils::SysModule hModule){return (uint32_t)FindEngineMsgByName(engine_data_->EngineMsgBase, "svc_disconnect")->pfn;});
        RegisterFuncCdecl<StaticHookId::SVC_Event>(&engine_data_->SVC_Event, [this](nitro_utils::SysModule hModule){return (uint32_t)FindEngineMsgByName(engine_data_->EngineMsgBase, "svc_event")->pfn;});
        RegisterFuncCdecl<StaticHookId::SVC_Version>(&engine_data_->SVC_Version, [this](nitro_utils::SysModule hModule){return (uint32_t)FindEngineMsgByName(engine_data_->EngineMsgBase, "svc_version")->pfn;});
        RegisterFuncCdecl<StaticHookId::SVC_SetView>(&engine_data_->SVC_SetView, [this](nitro_utils::SysModule hModule){return (uint32_t)FindEngineMsgByName(engine_data_->EngineMsgBase, "svc_setview")->pfn;});
        RegisterFuncCdecl<StaticHookId::SVC_Sound>(&engine_data_->SVC_Sound, [this](nitro_utils::SysModule hModule){return (uint32_t)FindEngineMsgByName(engine_data_->EngineMsgBase, "svc_sound")->pfn;});
        RegisterFuncCdecl<StaticHookId::SVC_Time>(&engine_data_->SVC_Time, [this](nitro_utils::SysModule hModule){return (uint32_t)FindEngineMsgByName(engine_data_->EngineMsgBase, "svc_time")->pfn;});
        RegisterFuncCdecl<StaticHookId::SVC_Print>(&engine_data_->SVC_Print, [this](nitro_utils::SysModule hModule){return (uint32_t)FindEngineMsgByName(engine_data_->EngineMsgBase, "svc_print")->pfn;});
        RegisterFuncCdecl<StaticHookId::SVC_StuffText>(&engine_data_->SVC_StuffText, [this](nitro_utils::SysModule hModule){return (uint32_t)FindEngineMsgByName(engine_data_->EngineMsgBase, "svc_stufftext")->pfn;});
        RegisterFuncCdecl<StaticHookId::SVC_SetAngle>(&engine_data_->SVC_SetAngle, [this](nitro_utils::SysModule hModule){return (uint32_t)FindEngineMsgByName(engine_data_->EngineMsgBase, "svc_setangle")->pfn;});
        RegisterFuncCdecl<StaticHookId::SVC_ResourceList>(&engine_data_->SVC_ResourceList, [this](nitro_utils::SysModule hModule){return (uint32_t)FindEngineMsgByName(engine_data_->EngineMsgBase,"svc_resourcelist")->pfn;});
        RegisterFuncCdecl<StaticHookId::SVC_ResourceLocation>(&engine_data_->SVC_ResourceLocation, [this](nitro_utils::SysModule hModule){return (uint32_t)FindEngineMsgByName(engine_data_->EngineMsgBase,"svc_resourcelocation")->pfn;});
        RegisterFuncCdecl<StaticHookId::SVC_Director>(&engine_data_->SVC_Director, [this](nitro_utils::SysModule hModule){return (uint32_t)FindEngineMsgByName(engine_data_->EngineMsgBase, "svc_director")->pfn;});
        RegisterFuncCdecl<StaticHookId::SVC_SignOnNum>(&engine_data_->SVC_SignOnNum, [this](nitro_utils::SysModule hModule){return (uint32_t)FindEngineMsgByName(engine_data_->EngineMsgBase, "svc_signonnum")->pfn;});
        RegisterFuncCdecl<StaticHookId::SVC_NewUserMsg>(&engine_data_->SVC_NewUserMsg, [this](nitro_utils::SysModule hModule){return (uint32_t)FindEngineMsgByName(engine_data_->EngineMsgBase, "svc_newusermsg")->pfn;});
        RegisterFuncCdecl<StaticHookId::SVC_SendCvarValue>(&engine_data_->SVC_SendCvarValue, [this](nitro_utils::SysModule hModule){return (uint32_t)FindEngineMsgByName(engine_data_->EngineMsgBase, "svc_sendcvarvalue")->pfn;});
        RegisterFuncCdecl<StaticHookId::SVC_UpdateUserInfo>(&engine_data_->SVC_UpdateUserInfo, [this](nitro_utils::SysModule hModule){return (uint32_t)FindEngineMsgByName(engine_data_->EngineMsgBase, "svc_updateuserinfo")->pfn;});
        RegisterFuncCdecl<StaticHookId::SVC_TimeScale>(&engine_data_->SVC_TimeScale, [this](nitro_utils::SysModule hModule){return (uint32_t)FindEngineMsgByName(engine_data_->EngineMsgBase, "svc_timescale")->pfn;});
    }
}