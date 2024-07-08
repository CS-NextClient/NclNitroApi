#pragma once

#include "../../chain/HandlersChainInterface.h"
#include "../../NitroFunction.h"
#include "cl_dll/hud.h"

#if NO_HLSDK_ARCHTYPES
#include <steam/steamtypes.h>
#endif

#include <extdll.h>
#include <vmodes.h>
#include <pm_defs.h>
#include <client.h>
#include <r_efx.h>
#include <ref_params.h>
#include <APIProxy.h>
#include <r_studioint.h>
#include <cdll_int.h>

namespace nitroapi
{
    struct ClientData
    {
        gamehud_t* gHUD = nullptr;
        int* g_iShotsFired = nullptr;

        // int UserMsg_MOTD(const char* name, int size, void* data)
        NitroFunction<int, const char*, int, void*>                 UserMsg_MOTD;
        // int UserMsg_AmmoX(const char* name, int size, void* data)
        NitroFunction<int, const char*, int, void*>                 UserMsg_AmmoX;
        // int UserMsg_SetFOV(const char* name, int size, void* data)
        NitroFunction<int, const char*, int, void*>                 UserMsg_SetFOV;

        // int CHudAmmo::DrawCrosshair(CHudAmmo *const this, float flTime, int weaponid)
        NitroFunction<int, CHudAmmo* const, float, int>             CHudAmmo__DrawCrosshair;

        // int Initialize(cl_enginefunc_t *pEnginefuncs, int iVersion)
        NitroFunction<int, cl_enginefuncs_s*, int>                  CLDLL_Initialize;
        // void HUD_Init()
        NitroFunctionVoid<>                                         HUD_Init;
        // int HUD_VidInit()
        NitroFunction<int>                                          HUD_VidInit;
        // int HUD_Redraw(float flTime, int iIntermission)
        NitroFunction<int, float, int>                              HUD_Redraw;
        // int HUD_UpdateClientData(client_data_t *cdata, float flTime)
        NitroFunction<int, client_data_t*, float>                   HUD_UpdateClientData;
        // void HUD_Reset()
        NitroFunctionVoid<>                                         HUD_Reset;
        // void HUD_PlayerMove(struct playermove_t *ppmove, int server)
        NitroFunctionVoid<playermove_t*, int>                       HUD_PlayerMove;
        // void HUD_PlayerMoveInit(struct playermove_t *ppmove)
        NitroFunctionVoid<playermove_t*>                            HUD_PlayerMoveInit;
        // char HUD_PlayerMoveTexture(char *name)
        NitroFunction<char, char*>                                  HUD_PlayerMoveTexture;
        // void IN_ActivateMouse()
        NitroFunctionVoid<>                                         IN_ActivateMouse;
        // void IN_DeactivateMouse()
        NitroFunctionVoid<>                                         IN_DeactivateMouse;
        // void IN_MouseEvent(int mstate)
        NitroFunctionVoid<int>                                      IN_MouseEvent;
        // void IN_ClearStates()
        NitroFunctionVoid<>                                         IN_ClearStates;
        // void IN_Accumulate()
        NitroFunctionVoid<>                                         IN_Accumulate;
        // void CL_CreateMove(float frametime, struct usercmd_s *cmd, int active)
        NitroFunctionVoid<float, usercmd_s*, int>                   CL_CreateMove;
        // int CL_IsThirdPerson()
        NitroFunction<int>                                          CL_IsThirdPerson;
        // void CL_CameraOffset(float *ofs)
        NitroFunctionVoid<float*>                                   CL_CameraOffset;
        // struct kbutton_s *KB_Find(const char *name)
        NitroFunction<kbutton_s*, const char*>                      KB_Find;
        // void CAM_Think()
        NitroFunctionVoid<>                                         CAM_Think;
        // void V_CalcRefdef(struct ref_params_s* pparams)
        NitroFunctionVoid<ref_params_s*>                            V_CalcRefdef;
        // int HUD_AddEntity(int type, struct cl_entity_s *ent, const char *modelname)
        NitroFunction<int, int, cl_entity_s*, const char*>          HUD_AddEntity;
        // void HUD_CreateEntities()
        NitroFunctionVoid<>                                         HUD_CreateEntities;
        // void HUD_DrawNormalTriangles()
        NitroFunctionVoid<>                                         HUD_DrawNormalTriangles;
        // void HUD_DrawTransparentTriangles()
        NitroFunctionVoid<>                                         HUD_DrawTransparentTriangles;
        // void HUD_StudioEvent(const struct mstudioevent_s *event, const struct cl_entity_s *entity)
        NitroFunctionVoid<const mstudioevent_s*, const cl_entity_s*> HUD_StudioEvent;
        // void HUD_PostRunCmd(struct local_state_s *from, struct local_state_s *to, struct usercmd_s *cmd, int runfuncs, double time, unsigned int random_seed)
        NitroFunctionVoid<local_state_s*, local_state_s*, usercmd_s*, int, double, unsigned int> HUD_PostRunCmd;
        // void HUD_Shutdown()
        NitroFunctionVoid<>                                         HUD_Shutdown;
        // void HUD_TxferLocalOverrides(struct entity_state_s *state, const struct clientdata_s *client)
        NitroFunctionVoid<entity_state_s*, const clientdata_s*>     HUD_TxferLocalOverrides;
        // void HUD_ProcessPlayerState(struct entity_state_s *dst, const struct entity_state_s *src)
        NitroFunctionVoid<entity_state_s*, const entity_state_s*>   HUD_ProcessPlayerState;
        // void HUD_TxferPredictionData(struct entity_state_s *ps, const struct entity_state_s *pps, struct clientdata_s *pcd, const struct clientdata_s *ppcd, struct weapon_data_s *wd, const struct weapon_data_s *pwd)
        NitroFunctionVoid<entity_state_s*, const entity_state_s*, clientdata_s*, const clientdata_s*, weapon_data_s*, const weapon_data_s*> HUD_TxferPredictionData;
        // void Demo_ReadBuffer(int size, unsigned char *buffer)
        NitroFunctionVoid<int, unsigned char*>                      Demo_ReadBuffer;
        // int HUD_ConnectionlessPacket(const netadr_s *net_from, const char *args, char *response_buffer, int *response_buffer_size)
        NitroFunction<int, const netadr_s*, const char*, char*, int*> HUD_ConnectionlessPacket;
        // int HUD_GetHullBounds(int hullnumber, float *mins, float *maxs)
        NitroFunction<int, int, float*, float*>                     HUD_GetHullBounds;
        // void HUD_Frame(double time)
        NitroFunctionVoid<double>                                   HUD_Frame;
        // int HUD_Key_Event(int eventcode, int keynum, const char *pszCurrentBinding)
        NitroFunction<int, int, int, const char*>                   HUD_Key_Event;
        // void HUD_TempEntUpdate(double frametime,double client_time, double cl_gravity, TEMPENTITY **ppTempEntFree, TEMPENTITY **ppTempEntActive, int ( *Callback_AddVisibleEntity )( cl_entity_t *pEntity ), void ( *Callback_TempEntPlaySound )( TEMPENTITY *pTemp, float damp ))
        NitroFunctionVoid<double, double, double, TEMPENTITY**, TEMPENTITY**, int (*)( cl_entity_t *pEntity ), void (*)( TEMPENTITY *pTemp, float damp )> HUD_TempEntUpdate;
        // struct cl_entity_s *HUD_GetUserEntity(int index)
        NitroFunction<cl_entity_s*, int>                            HUD_GetUserEntity;
        // int HUD_VoiceStatus(int entindex, qboolean bTalking)
        NitroFunction<int, int, qboolean>                           HUD_VoiceStatus;
        // void HUD_DirectorMessage(int iSize, void *pbuf)
        NitroFunctionVoid<int, void*>                               HUD_DirectorMessage;
        // int HUD_GetStudioModelInterface(int version, struct r_studio_interface_s **ppinterface, struct engine_studio_api_s *pstudio)
        NitroFunction<int, int, r_studio_interface_s**, engine_studio_api_s*> HUD_GetStudioModelInterface;

        // int UserMsg_CurWeapon(const char* name, int size, void* data)
        NitroFunction<int, const char*, int, void*>                 UserMsg_CurWeapon;
        // int UserMsg_InitHUD(const char* name, int size, void* data)
        NitroFunction<int, const char*, int, void*>                 UserMsg_InitHUD;
        // int UserMsg_TextMsg(const char* name, int size, void* data)
        NitroFunction<int, const char*, int, void*>                 UserMsg_TextMsg;

        // int CHudHealth::Draw(CHudHealth *const this, float flTime)
        NitroFunction<int, CHudHealth* const, float>                CHudHealth__Draw;
        // void CHudHealth::DrawRadar(CHudHealth *const this, float flTime)
        NitroFunctionVoid<CHudHealth* const, float>                 CHudHealth__DrawRadar;
        // void CHudHealth::GetAllPlayersInfo(CHudHealth *const this)
        NitroFunctionVoid<CHudHealth* const>                        CHudHealth__GetAllPlayersInfo;
        // int CHudDeathNotice::Draw(CHudDeathNotice *const this, float flTime)
        NitroFunction<int, CHudDeathNotice* const, float>           CHudDeathNotice__Draw;

        // void UserMsg_DeathMsg(const char* name, int size, void* data)
        NitroFunctionVoid<const char*, int, void*>                 UserMsg_DeathMsg;

        extra_player_info_t* g_PlayerExtraInfo;
    };
}