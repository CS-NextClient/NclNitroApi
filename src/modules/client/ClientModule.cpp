#include "ClientModule.h"
#include <utility>

namespace nitroapi
{
    ClientModule::ClientModule(std::shared_ptr<HookStorage> hook_storage,
                               std::shared_ptr<AddressProviderBase> addr_provider) :
        ModuleBase(std::move(hook_storage), std::move(addr_provider))
    {
        client_data_ = std::make_shared<ClientData>();
        client_data_->gHUD = new gamehud_t();
        memset(client_data_->gHUD, 0, sizeof(gamehud_t));

        RegisterVar(&client_data_->g_iShotsFired, "g_iShotsFired");
        RegisterVar(&client_data_->g_PlayerExtraInfo, "g_PlayerExtraInfo");

        RegisterFuncCdecl<StaticHookId::UserMsg_MOTD>(&client_data_->UserMsg_MOTD);
        RegisterFuncCdecl<StaticHookId::UserMsg_AmmoX>(&client_data_->UserMsg_AmmoX);
        RegisterFuncCdecl<StaticHookId::UserMsg_SetFOV>(&client_data_->UserMsg_SetFOV);
        RegisterFuncCdecl<StaticHookId::UserMsg_CurWeapon>(&client_data_->UserMsg_CurWeapon);
        RegisterFuncCdecl<StaticHookId::UserMsg_InitHUD>(&client_data_->UserMsg_InitHUD);
        RegisterFuncCdecl<StaticHookId::UserMsg_DeathMsg>(&client_data_->UserMsg_DeathMsg);

        RegisterFuncCdecl<StaticHookId::CLDLL_Initialize>(&client_data_->CLDLL_Initialize);
        RegisterFuncCdecl<StaticHookId::HUD_Init>(&client_data_->HUD_Init);
        RegisterFuncCdecl<StaticHookId::HUD_VidInit>(&client_data_->HUD_VidInit);
        RegisterFuncCdecl<StaticHookId::HUD_Redraw>(&client_data_->HUD_Redraw);
        RegisterFuncCdecl<StaticHookId::HUD_UpdateClientData>(&client_data_->HUD_UpdateClientData);
        RegisterFuncCdecl<StaticHookId::HUD_Reset>(&client_data_->HUD_Reset);
        RegisterFuncCdecl<StaticHookId::HUD_PlayerMove>(&client_data_->HUD_PlayerMove);
        RegisterFuncCdecl<StaticHookId::HUD_PlayerMoveInit>(&client_data_->HUD_PlayerMoveInit);
        RegisterFuncCdecl<StaticHookId::HUD_PlayerMoveTexture>(&client_data_->HUD_PlayerMoveTexture);
        RegisterFuncCdecl<StaticHookId::IN_ActivateMouse>(&client_data_->IN_ActivateMouse);
        RegisterFuncCdecl<StaticHookId::IN_DeactivateMouse>(&client_data_->IN_DeactivateMouse);
        RegisterFuncCdecl<StaticHookId::IN_MouseEvent>(&client_data_->IN_MouseEvent);
        RegisterFuncCdecl<StaticHookId::IN_ClearStates>(&client_data_->IN_ClearStates);
        RegisterFuncCdecl<StaticHookId::IN_Accumulate>(&client_data_->IN_Accumulate);
        RegisterFuncCdecl<StaticHookId::CL_CreateMove>(&client_data_->CL_CreateMove);
        RegisterFuncCdecl<StaticHookId::CL_IsThirdPerson>(&client_data_->CL_IsThirdPerson);
        RegisterFuncCdecl<StaticHookId::CL_CameraOffset>(&client_data_->CL_CameraOffset);
        RegisterFuncCdecl<StaticHookId::KB_Find>(&client_data_->KB_Find);
        RegisterFuncCdecl<StaticHookId::CAM_Think>(&client_data_->CAM_Think);
        RegisterFuncCdecl<StaticHookId::V_CalcRefdef>(&client_data_->V_CalcRefdef);
        RegisterFuncCdecl<StaticHookId::HUD_AddEntity>(&client_data_->HUD_AddEntity);
        RegisterFuncCdecl<StaticHookId::HUD_CreateEntities>(&client_data_->HUD_CreateEntities);
        RegisterFuncCdecl<StaticHookId::HUD_DrawNormalTriangles>(&client_data_->HUD_DrawNormalTriangles);
        RegisterFuncCdecl<StaticHookId::HUD_DrawTransparentTriangles>(&client_data_->HUD_DrawTransparentTriangles);
        RegisterFuncCdecl<StaticHookId::HUD_StudioEvent>(&client_data_->HUD_StudioEvent);
        RegisterFuncCdecl<StaticHookId::HUD_PostRunCmd>(&client_data_->HUD_PostRunCmd);
        RegisterFuncCdecl<StaticHookId::HUD_Shutdown>(&client_data_->HUD_Shutdown);
        RegisterFuncCdecl<StaticHookId::HUD_TxferLocalOverrides>(&client_data_->HUD_TxferLocalOverrides);
        RegisterFuncCdecl<StaticHookId::HUD_ProcessPlayerState>(&client_data_->HUD_ProcessPlayerState);
        RegisterFuncCdecl<StaticHookId::HUD_TxferPredictionData>(&client_data_->HUD_TxferPredictionData);
        RegisterFuncCdecl<StaticHookId::Demo_ReadBuffer>(&client_data_->Demo_ReadBuffer);
        RegisterFuncCdecl<StaticHookId::HUD_ConnectionlessPacket>(&client_data_->HUD_ConnectionlessPacket);
        RegisterFuncCdecl<StaticHookId::HUD_GetHullBounds>(&client_data_->HUD_GetHullBounds);
        RegisterFuncCdecl<StaticHookId::HUD_Frame>(&client_data_->HUD_Frame);
        RegisterFuncCdecl<StaticHookId::HUD_Key_Event>(&client_data_->HUD_Key_Event);
        RegisterFuncCdecl<StaticHookId::HUD_TempEntUpdate>(&client_data_->HUD_TempEntUpdate);
        RegisterFuncCdecl<StaticHookId::HUD_GetUserEntity>(&client_data_->HUD_GetUserEntity);
        RegisterFuncCdecl<StaticHookId::HUD_VoiceStatus>(&client_data_->HUD_VoiceStatus);
        RegisterFuncCdecl<StaticHookId::HUD_DirectorMessage>(&client_data_->HUD_DirectorMessage);
        RegisterFuncCdecl<StaticHookId::HUD_GetStudioModelInterface>(&client_data_->HUD_GetStudioModelInterface);

        if (IsWindows()) {
            RegisterFuncThiscall<StaticHookId::CHudAmmo__DrawCrosshair>(&client_data_->CHudAmmo__DrawCrosshair);
            RegisterFuncThiscall<StaticHookId::CHudHealth__Draw>(&client_data_->CHudHealth__Draw);
            RegisterFuncThiscall<StaticHookId::CHudHealth__DrawRadar>(&client_data_->CHudHealth__DrawRadar);
            RegisterFuncThiscall<StaticHookId::CHudHealth__GetAllPlayersInfo>(&client_data_->CHudHealth__GetAllPlayersInfo);
            RegisterFuncThiscall<StaticHookId::CHudDeathNotice__Draw>(&client_data_->CHudDeathNotice__Draw);
        }
        else {
            RegisterFuncCdecl<StaticHookId::CHudAmmo__DrawCrosshair>(&client_data_->CHudAmmo__DrawCrosshair);
            RegisterFuncCdecl<StaticHookId::CHudHealth__Draw>(&client_data_->CHudHealth__Draw);
            RegisterFuncCdecl<StaticHookId::CHudHealth__DrawRadar>(&client_data_->CHudHealth__DrawRadar);
            RegisterFuncCdecl<StaticHookId::CHudHealth__GetAllPlayersInfo>(&client_data_->CHudHealth__GetAllPlayersInfo);
            RegisterFuncCdecl<StaticHookId::CHudDeathNotice__Draw>(&client_data_->CHudDeathNotice__Draw);
        }
    }

    ClientModule::~ClientModule()
    {
        for (const auto& unsub : unsubscribers_)
            unsub->Unsubscribe();
    }

    void ClientModule::OnLibraryLoaded(nitro_utils::SysModule hModule)
    {
        ModuleBase::OnLibraryLoaded(hModule);

        uint32 hud = addr_provider_->FindAddress(hModule, "gHUD");
        uint32 hud_fields = hud + 0x4; // skip vtable? idno

        client_data_->gHUD->m_pHudList = reinterpret_cast<HUDLIST**>(hud_fields - 0x4);
        client_data_->gHUD->m_pSpriteList = reinterpret_cast<client_sprite_t**>(hud_fields + 0xC - 0x4);
        client_data_->gHUD->m_iSpriteCount = (int*)(hud_fields + 0x10);
        client_data_->gHUD->m_iSpriteCountAllRes = (int*)(hud_fields + 0x14);
        client_data_->gHUD->m_flMouseSensitivity = (float*)(hud_fields + 0x18);
        client_data_->gHUD->m_flTime = (float*)(hud_fields + 0x24);
        client_data_->gHUD->m_fOldTime = (float*)(hud_fields + 0x28);
        client_data_->gHUD->m_flTimeDelta = (double*)(hud_fields + 0x2C);
        client_data_->gHUD->m_vecOrigin = (Vector*)(hud_fields + 0x34);
        client_data_->gHUD->m_vecAngles = (Vector*)(hud_fields + 0x40);
        client_data_->gHUD->m_iKeyBits = (int*)(hud_fields + 0x4C);
        client_data_->gHUD->m_iHideHUDDisplay = (int*)(hud_fields + 0x50);
        client_data_->gHUD->m_iFOV = (int*)(hud_fields + 0x54);
        client_data_->gHUD->m_Teamplay = (int*)(hud_fields + 0x58);
        client_data_->gHUD->m_iRes = (int*)(hud_fields + 0x5C);
        client_data_->gHUD->m_pPlayerFOV = reinterpret_cast<int(*)[64]>(hud_fields + 0x68);
        client_data_->gHUD->m_iFontHeight = (int*)(hud_fields + 0x168);
        client_data_->gHUD->m_iFontEngineHeight = (int*)(hud_fields + 0x16C);
        client_data_->gHUD->m_rghSprites = reinterpret_cast<HSPRITE_t**>(hud_fields + 0x174);
        client_data_->gHUD->m_rgrcRects = reinterpret_cast<wrect_t**>(hud_fields + 0x178);

        client_data_->gHUD->m_rgszSpriteNames = reinterpret_cast<char**>(hud_fields + 0x17C);
        client_data_->gHUD->m_iWeaponBits = (int*)(hud + 0x4748);
        client_data_->gHUD->m_fPlayerDead = (bool*)(hud + 0x474C);
//        client_data_->gHUD->m_iIntermission = (int*)(hud_fields + 0x6B48);
        client_data_->gHUD->m_HUD_number_0 = (int*)(hud + 0x4754);
//        client_data_->gHUD->m_flCheatCheckTime = (float*)(hud_fields + 0x6B50);
//        client_data_->gHUD->m_flExpensiveCheckTime = (float*)(hud_fields + 0x6B54);
//        client_data_->gHUD->m_bRenderGunSmoke = (bool*)(hud_fields + 0x6B58);
//        client_data_->gHUD->m_fGLTEXSORT = (float*)(hud_fields + 0x6B5C);
//        client_data_->gHUD->m_flGLZMAX = (float*)(hud_fields + 0x6B60);
//        client_data_->gHUD->m_bSoftwaremode = (bool*)(hud_fields + 0x6B64);
//        client_data_->gHUD->m_bShowTimer = (bool*)(hud_fields + 0x6B65);
//        client_data_->gHUD->m_autoBuyStringSent = (bool*)(hud_fields + 0x6B66);
//        client_data_->gHUD->m_rebuyStringSent = (bool*)(hud_fields + 0x6B68);
        client_data_->gHUD->m_Ammo = (CHudAmmo*)(hud_fields + 0x180);
        client_data_->gHUD->m_Health = (CHudHealth*)(hud_fields + 0x1F0);
        client_data_->gHUD->m_Spectator = (CHudSpectator*)(hud_fields + 0x354);
//        client_data_->gHUD->m_Geiger = (CHudGeiger*)(hud_fields + 0x1AB8);
//        client_data_->gHUD->m_Battery = (CHudBattery*)(hud_fields + 0x1AD0);
//        client_data_->gHUD->m_Train = (CHudTrain*)(hud_fields + 0x1B00);
//        client_data_->gHUD->m_Flash = (CHudFlashlight*)(hud_fields + 0x1B1C);
//        client_data_->gHUD->m_Message = (CHudMessage*)(hud_fields + 0x1B5C);
//        client_data_->gHUD->m_StatusBar = (CHudStatusBar*)(hud_fields + 0x5CC4);
//        client_data_->gHUD->m_DeathNotice = (CHudDeathNotice*)(hud_fields + 0x5E00);
//        client_data_->gHUD->m_SayText = (CHudSayText*)(hud_fields + 0x5E28);
//        client_data_->gHUD->m_Menu = (CHudMenu*)(hud_fields + 0x5E44);
//        client_data_->gHUD->m_AmmoSecondary = (CHudAmmoSecondary*)(hud_fields + 0x5E68);
//        client_data_->gHUD->m_TextMessage = (CHudTextMessage*)(hud_fields + 0x5E94);
//        client_data_->gHUD->m_StatusIcons = (CHudStatusIcons*)(hud_fields + 0x5EA8);
//        client_data_->gHUD->m_accountBalance = (CHudAccountBalance*)(hud + 0x3FA0);
//        client_data_->gHUD->m_roundTimer = (CHudRoundTimer*)(hud_fields + 0x3FDC);
//        client_data_->gHUD->m_progressBar = (CHudProgressBar*)(hud_fields + 0x6004);
        client_data_->gHUD->m_NightVision = (CHudNightVision*)(hud + 0x4048);
//        client_data_->gHUD->m_careerTaskTimer = (CHudCareerTaskTimer*)(hud_fields + 0x6060);
//        client_data_->gHUD->m_scenarioStatus = (CHudScenarioStatus*)(hud_fields + 0x609C);
//        client_data_->gHUD->m_sniperScope = (CHudSniperScope*)(hud_fields + 0x60D4);
//        client_data_->gHUD->m_VGUI2Print = (CHudVGUI2Print*)(hud_fields + 0x60FC);
//        client_data_->gHUD->m_scrinfo = (SCREENINFO*)(hud_fields + 0x692C);
    }

    void ClientModule::OnLibraryUnload()
    {
        delete client_data_->gHUD;
        client_data_->gHUD = nullptr;

        ModuleBase::OnLibraryUnload();
    }
}
