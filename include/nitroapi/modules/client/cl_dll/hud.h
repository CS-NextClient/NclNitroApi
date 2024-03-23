/*
*
*    Copyright (c) 1996-2002, Valve LLC. All rights reserved.
*
*    This product contains software technology licensed from Id
*    Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc.
*    All Rights Reserved.
*
*    Use, distribution, and modification of this source code and/or resulting
*    object code is restricted to non-commercial enhancements to products from
*    Valve LLC.  All other use, distribution, or modification is prohibited
*    without written permission from Valve LLC.
*
*/

#pragma once

#include <vector>

#include "extdll.h"
#include "vmodes.h"
#include "pm_defs.h"
#include "client.h"
#include "r_efx.h"
#include "ref_params.h"
#include "APIProxy.h"
#include "r_studioint.h"
#include "cdll_int.h"

#include "vgui/VGUI2.h"

#define GHUD_DECLARE_MESSAGE(x)\
	int (*MsgFunc_##x##_OrigFunc)(const char *pszName, int iSize, void *buf);\
	int __MsgFunc_##x(const char *pszName, int iSize, void *pbuf)\
	{\
		return gHUD.MsgFunc_##x(pszName, iSize, pbuf);\
	}

#define DECLARE_MESSAGE_FUNC(x)\
	int MsgFunc_##x(const char *pszName, int iSize, void *buf)

#define DECLARE_USERCMD_FUNC(x)\
	void UserCmd_##x()

#define RGB_YELLOWISH			0x00FFA000	// 255, 160, 0
#define RGB_REDISH				0x00FF1010	// 255,  16, 16
#define RGB_GREENISH			0x0000A000	// 0,   160, 0

#include "ammo.h"

#define DHN_DRAWZERO				1
#define DHN_2DIGITS					2
#define DHN_3DIGITS					4
#define DHN_PADZERO					8
#define DHN_4DIGITS					16
#define DHN_5DIGITS					32

#define MIN_ALPHA					100

#define MAX_SCORES					10
#define MAX_SCOREBOARD_TEAMS		5
#define MAX_SERVERNAME_LENGTH		64
#define MAX_TEAMNAME_SIZE			32

#define NUM_ROWS					(MAX_PLAYERS + (MAX_SCOREBOARD_TEAMS * 2))

#define HUDELEM_ACTIVE				1

#define HUD_ACTIVE					1
#define HUD_INTERMISSION			2

enum
{
	MAX_PLAYERS       = 64,
	MAX_TEAMS         = 64,
	MAX_TEAM_NAME     = 16,
	MAX_LOCATION_NAME = 32,
	MAX_HOSTAGES      = 24,
};

class CHudBase
{
public:
	//virtual ~CHudBase() {}
	virtual int Init() { return 0; }
	virtual int VidInit() { return 0; }
	virtual int Draw(float flTime) { return 0; }
	virtual void Think() {}
	virtual void Reset() {}
	virtual void InitHUDData() {}		// called every time a server is connected to

public:
	struct POSITION
	{
		int x, y;
	};

	POSITION m_pos;
	int m_type;
	int m_iFlags; // active, moving,
};

struct HUDLIST
{
	CHudBase *p;
	HUDLIST  *pNext;
};

#include "hud_spectator.h"

class CHudAmmo: public CHudBase
{
public:
	virtual int Init();
	virtual int VidInit();
	virtual int Draw(float flTime);
	virtual void Think();
	virtual void Reset();

	int DrawWList(float flTime);
	int DrawCrosshair(float flTime, int weaponid = 0);

	DECLARE_MESSAGE_FUNC(CurWeapon);
	DECLARE_MESSAGE_FUNC(WeaponList);
	DECLARE_MESSAGE_FUNC(AmmoX);
	DECLARE_MESSAGE_FUNC(AmmoPickup);
	DECLARE_MESSAGE_FUNC(WeapPickup);
	DECLARE_MESSAGE_FUNC(ItemPickup);
	DECLARE_MESSAGE_FUNC(HideWeapon);
	DECLARE_MESSAGE_FUNC(Crosshair);

	void SlotInput(int iSlot);
	DECLARE_USERCMD_FUNC(Slot1);
	DECLARE_USERCMD_FUNC(Slot2);
	DECLARE_USERCMD_FUNC(Slot3);
	DECLARE_USERCMD_FUNC(Slot4);
	DECLARE_USERCMD_FUNC(Slot5);
	DECLARE_USERCMD_FUNC(Slot6);
	DECLARE_USERCMD_FUNC(Slot7);
	DECLARE_USERCMD_FUNC(Slot8);
	DECLARE_USERCMD_FUNC(Slot9);
	DECLARE_USERCMD_FUNC(Slot10);
	DECLARE_USERCMD_FUNC(Close);
	DECLARE_USERCMD_FUNC(NextWeapon);
	DECLARE_USERCMD_FUNC(PrevWeapon);
	DECLARE_USERCMD_FUNC(Adjust_Crosshair);

	void CalculateCrosshairColor();
	void CalculateCrosshairDrawMode();
	void CalculateCrosshairSize();

public:
	float m_fFade;

	struct RGBA
	{
		unsigned char r, g, b, a;
	};

	RGBA m_rgba;
	WEAPON *m_pWeapon;
	int m_HUD_bucket0;
	int m_HUD_selection;
    HSPRITE_t m_hObserverCrosshair;
	wrect_t m_rcObserverCrosshair;
	int m_bObserverCrosshair;
	int m_iAmmoLastCheck;
	float m_flCrosshairDistance;
	int m_iAlpha;
	int m_R, m_G, m_B;
	int m_cvarR, m_cvarG, m_cvarB;
	int m_iCurrentCrosshair;
	bool m_bAdditive;
	int m_iCrosshairScaleBase;
};

class CHudAmmoSecondary: public CHudBase
{
public:
	virtual int Init();
	virtual int VidInit();
	virtual int Draw(float flTime);
	virtual void Reset();

	DECLARE_MESSAGE_FUNC(SecAmmoVal);
	DECLARE_MESSAGE_FUNC(SecAmmoIcon);

public:
	enum
	{
		MAX_SEC_AMMO_VALUES = 4
	};

	int m_HUD_ammoicon; // sprite indices
	int m_iAmmoAmounts[MAX_SEC_AMMO_VALUES];
	float m_fFade;
};

#include "health.h"

#define FADE_TIME 100.0f

class CHudGeiger: public CHudBase
{
public:
	virtual int Init();
	virtual int VidInit();
	virtual int Draw(float flTime);
	DECLARE_MESSAGE_FUNC(Geiger);

public:
	int m_iGeigerRange;
};

class CHudTrain: public CHudBase
{
public:
	virtual int Init();
	virtual int VidInit();
	virtual int Draw(float flTime);
	DECLARE_MESSAGE_FUNC(Train);

public:
    HSPRITE_t m_hSprite;
	int m_iPos;
};

class CHudStatusBar: public CHudBase
{
public:
	virtual int Init();
	virtual int VidInit();
	virtual int Draw(float flTime);
	virtual void Reset();

	void ParseStatusString(int line_num);

	DECLARE_MESSAGE_FUNC(StatusText);
	DECLARE_MESSAGE_FUNC(StatusValue);

protected:
	enum
	{
		MAX_STATUSTEXT_LENGTH = 128,
		MAX_STATUSBAR_VALUES  = 8,
		MAX_STATUSBAR_LINES   = 1,
	};

	char m_szStatusText[MAX_STATUSBAR_LINES][MAX_STATUSTEXT_LENGTH];  // a text string describing how the status bar is to be drawn
	char m_szStatusBar[MAX_STATUSBAR_LINES][MAX_STATUSTEXT_LENGTH];	// the constructed bar that is drawn
	int m_iStatusValues[MAX_STATUSBAR_VALUES];  // an array of values for use in the status bar

	int m_bReparseString; // set to TRUE whenever the m_szStatusBar needs to be recalculated

	// an array of colors...one color for each line
	float *m_pflNameColors[MAX_STATUSBAR_LINES];
};

struct extra_player_info_t
{
	short frags;
	short deaths;
	short team_id;
	qboolean has_c4;
	qboolean vip;
	vec3_t origin;
	float radarflash;
	int radarflashon;
	int radarflashes;
	short playerclass;
	short teamnumber;
	char teamname[16];
	bool dead;
	float showhealth;
	int health;
	char location[32];
	int sb_health;
	int sb_account;
	int has_defuse_kit;
};

struct hostage_info_t
{
	bool dead;
	vec3_t origin;
	int health;
	float radarflash;
	int radarflashon;
	int radarflashes;
	char teamname[MAX_TEAM_NAME];
};

extern hud_player_info_t	g_PlayerInfoList[MAX_PLAYERS + 1];	// player info from the engine
extern extra_player_info_t	g_PlayerExtraInfo[MAX_PLAYERS + 1];	// additional player info sent directly to the client dll
extern hostage_info_t		g_HostageInfo[MAX_HOSTAGES + 1];

class CHudDeathNotice: public CHudBase
{
public:
	virtual int Init();
	virtual int VidInit();
	virtual int Draw(float flTime);
	virtual void InitHUDData();

	int GetDeathNoticeY();
	DECLARE_MESSAGE_FUNC(DeathMsg);

public:
	int m_HUD_d_skull;			// sprite index of skull icon
	int m_iDeathNoticeGap;
	int m_iDeathNoticeTop;
	int m_iDeathTextGap;
	int m_iDeathNoticeGapRight;
};

class CHudMenu: public CHudBase
{
public:
	virtual int Init();
	virtual int VidInit();
	virtual int Draw(float flTime);
	virtual void Reset();
	virtual void InitHUDData();

	DECLARE_MESSAGE_FUNC(ShowMenu);
	void SelectMenuItem(int menu_item);

	int m_fMenuDisplayed;
	int m_bitsValidSlots;
	float m_flShutoffTime;
	int m_fWaitingForMore;
};

class CHudSayText: public CHudBase
{
public:
	virtual int Init();
	virtual int VidInit();
	virtual int Draw(float flTime);
	virtual void InitHUDData();

	DECLARE_MESSAGE_FUNC(SayText);

	void SayTextPrint(const char *pszBuf, int iBufSize, int clientIndex = -1, char *sstr1 = nullptr, char *sstr2 = nullptr, char *sstr3 = nullptr, char *sstr4 = nullptr);
	int GetTextPrintY();

	void EnsureTextFitsInOneLineAndWrapIfHaveTo(int line);
	void FindAudMessage(const char *pszBuf, int iBufSize, int pitch);

	DECLARE_MESSAGE_FUNC(SendAudio);

public:
	friend class CHudSpectator;
	struct cvar_s *m_HUD_saytext;
	struct cvar_s *m_HUD_saytext_time;
};

class CHudBattery: public CHudBase
{
public:
	virtual int Init();
	virtual int VidInit();
	virtual int Draw(float flTime);

	DECLARE_MESSAGE_FUNC(Battery);
	DECLARE_MESSAGE_FUNC(ArmorType);

	int GetArmorPercent() const;
	bool HasHelmet() const;

public:
	int m_HUD_suit_empty;
	int m_HUD_suit_full;
	int m_HUD_suithelmet_empty;
	int m_HUD_suithelmet_full;
	int m_iBat;
	float m_fFade;
	int m_iArmorType;
};

class CHudFlashlight: public CHudBase
{
public:
	virtual int Init();
	virtual int VidInit();
	virtual int Draw(float flTime);
	virtual void Reset();
	DECLARE_MESSAGE_FUNC(Flashlight);
	DECLARE_MESSAGE_FUNC(FlashBat);

public:
	HSPRITE_t m_hSprite1;
	HSPRITE_t m_hSprite2;
	HSPRITE_t m_hBeam;
	wrect_t *m_prc1;
	wrect_t *m_prc2;
	wrect_t *m_prcBeam;
	float m_flBat;
	int m_iBat;
	int m_fOn;
	float m_fFade;
	int m_iWidth;			// width of the battery innards
};

const int maxHUDMessages = 16;
struct message_parms_t
{
	client_textmessage_t *pMessage;
	float time;
	int x, y;
	int	totalWidth, totalHeight;
	int width;
	int lines;
	int lineLength;
	int length;
	int r, g, b;
	int text;
	int fadeBlend;
	float charTime;
	float fadeTime;
};

class CHudTextMessage: public CHudBase
{
public:
	int Init();
	static char *LocaliseTextString(const char *msg, char *dst_buffer, int buffer_size);
	static char *BufferedLocaliseTextString(const char *msg);
	char *LookupString(const char *msg_name, int *msg_dest = NULL);
	DECLARE_MESSAGE_FUNC(TextMsg);
};

class CHudMessage: public CHudBase
{
public:
	virtual int Init();
	virtual int VidInit();
	virtual int Draw(float flTime);
	virtual void Reset();

	DECLARE_MESSAGE_FUNC(HudText);
	DECLARE_MESSAGE_FUNC(HudTextPro);
	DECLARE_MESSAGE_FUNC(HudTextArgs);
	DECLARE_MESSAGE_FUNC(GameTitle);

	float FadeBlend(float fadein, float fadeout, float hold, float localTime);
	int	XPosition(float x, int width, int lineWidth);
	int YPosition(float y, int height);

	enum
	{
		MESSAGE_ARG_LEN = 64,
		MAX_MESSAGE_ARGS = 4,
	};

	struct client_message_t
	{
		client_textmessage_t *pMessage;
		vgui2::HFont font;
		wchar_t args[MESSAGE_ARG_LEN][MAX_MESSAGE_ARGS];
		int numArgs;
	};

	int  MessageAdd(const char *pName, float time, int hintMessage, vgui2::HFont font);
	void MessageAdd(client_textmessage_t *newMessage);
	void MessageDrawScan(client_message_t *pClientMessage, float time, vgui2::HFont font);
	void MessageScanStart();
	void MessageScanNextChar(vgui2::HFont font);

public:
	client_message_t		m_Messages[maxHUDMessages];
	float					m_startTime[maxHUDMessages];
	message_parms_t			m_parms;
	float					m_gameTitleTime;
	client_textmessage_t	*m_pGameTitle;

	int m_HUD_title_life;
	int m_HUD_title_half;
};

constexpr auto MAX_SPRITE_NAME_LENGTH = 24;

class CHudStatusIcons: public CHudBase
{
public:
	virtual int Init();
	virtual int VidInit();
	virtual int Draw(float flTime);
	virtual void Reset();
	DECLARE_MESSAGE_FUNC(StatusIcon);

	enum
	{
		MAX_ICONSPRITENAME_LENGTH = MAX_SPRITE_NAME_LENGTH,
		MAX_ICONSPRITES = 4,
	};

	// had to make these public so CHud could access them (to enable concussion icon)
	// could use a friend declaration instead...
	void EnableIcon(char *pszIconName, unsigned char red, unsigned char green, unsigned char blue, bool bFlash);
	void DisableIcon(char *pszIconName);
	bool InBuyZone() const;

public:
	int m_iCrossWidth;
	int m_bFlashOn;
	float m_tmNextFlash;

	struct icon_sprite_t
	{
		char szSpriteName[MAX_ICONSPRITENAME_LENGTH];
        HSPRITE_t spr;
		wrect_t rc;
		unsigned char r, g, b;
		qboolean bFlash;
	};

	icon_sprite_t m_IconList[MAX_ICONSPRITES];
};

class CHudAccountBalance: public CHudBase
{
public:
	virtual int Init();
	virtual int VidInit();
	virtual int Draw(float flTime);
	virtual void Reset();

	DECLARE_MESSAGE_FUNC(Money);
	DECLARE_MESSAGE_FUNC(BlinkAcct);

	int m_iAccount;
	int GetBalance() const;

public:
	int m_HUD_dollar;
	int m_HUD_minus;
	int m_HUD_plus;
	int m_iAccountDelta;
	float m_fFade;
	float m_fFadeFast;
	int m_bShowDelta;
	int m_iBlinkCount;
	float m_fBlinkTime;
};

class CHudNightVision: public CHudBase
{
public:
	~CHudNightVision();

	virtual int Init();
	virtual int VidInit();
	virtual int Draw(float flTime);
	virtual void Reset();

	DECLARE_MESSAGE_FUNC(NVGToggle);
	DECLARE_USERCMD_FUNC(NVGAdjustUp);
	DECLARE_USERCMD_FUNC(NVGAdjustDown);

public:
	int m_fOn;
	int m_iAlpha;
	int m_iScopeTextureID;
};

class CHudScenarioStatus: public CHudBase
{
public:
	virtual int Init();
	virtual int VidInit();
	virtual int Draw(float flTime);
	virtual void Reset();

	DECLARE_MESSAGE_FUNC(Scenario);

public:
    HSPRITE_t m_hSprite;
	wrect_t m_rect;
	int m_alpha;
	float m_nextFlash;
	float m_flashInterval;
	int m_flashAlpha;
};

// Draws the zoom screen
class CHudSniperScope: public CHudBase
{
public:
	~CHudSniperScope();

	virtual int Init();
	virtual int VidInit();
	virtual int Draw(float flTime);
	virtual void Reset();

public:
	int m_iScopeTextureID;
	int m_iScopeNWTextureID, m_iScopeNETextureID, m_iScopeSWTextureID, m_iScopeSETextureID;
};

class CHudVGUI2Print: public CHudBase
{
public:
	virtual int Init();
	virtual int VidInit();
	virtual int Draw(float flTime);

	int DrawVGUI2String(char *charMsg, int x, int y, float r, float g, float b);
	int DrawVGUI2StringReverse(char *charMsg, int x, int y, float r, float g, float b);

	int DrawVGUI2String(wchar_t *msg, int x, int y, float r, float g, float b);
	int DrawVGUI2StringReverse(wchar_t *msg, int x, int y, float r, float g, float b);

	void VGUI2HudPrintArgs(char *charMsg, char *sstr1, char *sstr2, char *sstr3, char *sstr4, int x, int y, float r, float g, float b);
	void VGUI2HudPrint(char *charMsg, int x, int y, float r, float g, float b);
	void VGUI2LocalizeArg(char *pSrc, wchar_t *pDest, int unicodeBufferSizeInBytes);

	int GetHudFontHeight();
	void GetStringSize(const wchar_t *string, int *width, int *height);

public:
	vgui2::HFont m_hudfont;
	float m_flVGUI2StringTime;
	wchar_t m_wCharBuf[512];
	float m_fR, m_fG, m_fB;
	int m_iX, m_iY;
};

#pragma pack(push, 8)
class CHud
{
public:
	CHud();
	~CHud(); // destructor, frees allocated memory

	void Init();
	void VidInit();
	void Think();
	int Redraw(float flTime, int intermission);
	int UpdateClientData(client_data_t *, float);

	bool IsGame(const char *gamename) const;
	const char *GetGameDir() const;

	void AddHudElem(CHudBase *phudelem);
	float GetSensitivity();
	void AutoBuy();
	void SendAutoBuyString();
	void Rebuy();
	void SendRebuyString();
	void RunCredits();

public:
	DECLARE_MESSAGE_FUNC(Damage);
	DECLARE_MESSAGE_FUNC(GameMode);
	DECLARE_MESSAGE_FUNC(Logo);
	DECLARE_MESSAGE_FUNC(ResetHUD);
	DECLARE_MESSAGE_FUNC(InitHUD);
	DECLARE_MESSAGE_FUNC(ViewMode);
	DECLARE_MESSAGE_FUNC(SetFOV);
	DECLARE_MESSAGE_FUNC(HLTV);
	DECLARE_MESSAGE_FUNC(SpecHealth);
	DECLARE_MESSAGE_FUNC(Concuss);
	DECLARE_MESSAGE_FUNC(ReloadSound);
	DECLARE_MESSAGE_FUNC(BombDrop);
	DECLARE_MESSAGE_FUNC(BombPickup);
	DECLARE_MESSAGE_FUNC(ADStop);
	DECLARE_MESSAGE_FUNC(HostagePos);
	DECLARE_MESSAGE_FUNC(HostageK);
	DECLARE_MESSAGE_FUNC(SpecHealth2);
	DECLARE_MESSAGE_FUNC(Brass);
	DECLARE_MESSAGE_FUNC(Fog);
	DECLARE_MESSAGE_FUNC(ShowTimer);
	DECLARE_MESSAGE_FUNC(BotVoice);

public:
	HUDLIST *m_pHudList;
    HSPRITE_t m_hsprLogo;
	int m_iLogo;
	client_sprite_t *m_pSpriteList;
	int m_iSpriteCount;
	int m_iSpriteCountAllRes;
	float m_flMouseSensitivity;
	int m_iConcussionEffect;
    HSPRITE_t m_hsprCursor;
	float m_flTime;
	float m_fOldTime;
	double m_flTimeDelta;
	Vector m_vecOrigin;
	Vector m_vecAngles;
	int m_iKeyBits;
	int m_iHideHUDDisplay;
	int m_iFOV;
	int m_Teamplay;
	int m_iRes;
	cvar_t *m_pCvarStealMouse;
	cvar_t *m_pCvarDraw;
	int m_PlayerFOV[64];
	int m_iFontHeight;
	int m_iFontEngineHeight;

	int DrawHudNumber(int x, int y, int iNumber, int r, int g, int b);
	int DrawHudNumber(int x, int y, int iFlags, int iNumber, int r, int g, int b);
	int DrawHudString(int x, int y, int iMaxX, const char *szString, int r, int g, int b);
	int DrawHudStringReverse(int xpos, int ypos, int iMinX, const char *szString, int r, int g, int b);
	int DrawHudNumberString(int xpos, int ypos, int iMinX, int iNumber, int r, int g, int b);
	int GetNumWidth(int iNumber, int iFlags);

	void VGUI2HudPrint(char *charMsg, int x, int y, int r, int g, int b);

	cvar_t *default_fov;
    HSPRITE_t *m_rghSprites;
	wrect_t *m_rgrcRects;
	char *m_rgszSpriteNames;

    HSPRITE_t GetSprite(int index)
	{
		return (index < 0) ? 0 : m_rghSprites[index];
	}

	wrect_t &GetSpriteRect(int index)
	{
		return m_rgrcRects[index];
	}

	int GetSpriteWidth(int index)
	{
		return m_rgrcRects[index].right - m_rgrcRects[index].left;
	}

	int GetSpriteHeight(int index)
	{
		return m_rgrcRects[index].bottom - m_rgrcRects[index].top;
	}

	int GetSpriteIndex(const char *SpriteName); // gets a sprite index, for use in the m_rghSprites[] array

public:
	CHudAmmo			m_Ammo;
	CHudHealth			m_Health;
	CHudSpectator		m_Spectator;
	CHudGeiger			m_Geiger;
	CHudBattery			m_Battery;
	CHudTrain			m_Train;
	CHudFlashlight		m_Flash;
	CHudMessage			m_Message;
	CHudStatusBar		m_StatusBar;
	CHudDeathNotice		m_DeathNotice;
	CHudSayText			m_SayText;
	CHudMenu			m_Menu;
	CHudAmmoSecondary	m_AmmoSecondary;
	CHudTextMessage		m_TextMessage;
	CHudStatusIcons		m_StatusIcons;
	CHudAccountBalance	m_accountBalance;
	CHudRoundTimer		m_roundTimer;
	CHudProgressBar		m_progressBar;
	CHudNightVision		m_NightVision;
	CHudCareerTaskTimer	m_careerTaskTimer;
	CHudScenarioStatus	m_scenarioStatus;
	CHudSniperScope		m_sniperScope;
	CHudVGUI2Print		m_VGUI2Print;
	SCREENINFO			m_scrinfo;

	int m_iWeaponBits;
	bool m_fPlayerDead;
	int m_iIntermission;
	int m_HUD_number_0;
	float m_flCheatCheckTime;
	float m_flExpensiveCheckTime;
	bool m_bRenderGunSmoke;
	float m_fGLTEXSORT;
	float m_flGLZMAX;
	bool m_bSoftwaremode;
	bool m_bShowTimer;
	bool m_autoBuyStringSent;
	bool m_rebuyStringSent;
	std::vector<int> m_botVoiceEntities;
};

#pragma pack(pop)

// Binding members, use this instead of CHUD,
// because CHUD isn't guarantees the consistency for members.
struct gamehud_t
{
	bool initialized;

	HUDLIST         *(*m_pHudList);
	client_sprite_t *(*m_pSpriteList);
	int              (*m_iSpriteCount);
	int              (*m_iSpriteCountAllRes);
	float            (*m_flMouseSensitivity);
	float            (*m_flTime);
	float            (*m_fOldTime);
	double           (*m_flTimeDelta);
	Vector           (*m_vecOrigin);
	Vector           (*m_vecAngles);
	int              (*m_iKeyBits);
	int              (*m_iHideHUDDisplay);
	int              (*m_iFOV);
	int              (*m_Teamplay);
	int              (*m_iRes);
	int              (*m_pPlayerFOV)[64];
	int              (*m_iFontHeight);
	int              (*m_iFontEngineHeight);
    HSPRITE_t         *(*m_rghSprites);
	wrect_t         *(*m_rgrcRects);

    HSPRITE_t GetSprite(int index) const
	{
		return (index < 0) ? 0 : (*m_rghSprites)[index];
	}

	wrect_t &GetSpriteRect(int index) const
	{
		return (*m_rgrcRects)[index];
	}

	int GetSpriteWidth(int index) const
	{
		return (*m_rgrcRects)[index].right - (*m_rgrcRects)[index].left;
	}

	int GetSpriteHeight(int index) const
	{
		return (*m_rgrcRects)[index].bottom - (*m_rgrcRects)[index].top;
	}

	inline int GetSpriteIndex(const char *SpriteName)
	{
		for(int i = 0; i < *m_iSpriteCount; i++ )
		{
			if (strnicmp(SpriteName, *m_rgszSpriteNames + (i * MAX_SPRITE_NAME_LENGTH), MAX_SPRITE_NAME_LENGTH ) == 0)
				return i;
		}

		return -1; // invalid sprite
	}

	char               *(*m_rgszSpriteNames);
	int                 (*m_iWeaponBits);
	bool                (*m_fPlayerDead);
	int                 (*m_iIntermission);
	int                 (*m_HUD_number_0);
	float               (*m_flCheatCheckTime);
	float               (*m_flExpensiveCheckTime);
	bool                (*m_bRenderGunSmoke);
	float               (*m_fGLTEXSORT);
	float               (*m_flGLZMAX);
	bool                (*m_bSoftwaremode);
	bool                (*m_bShowTimer);
	bool                (*m_autoBuyStringSent);
	bool                (*m_rebuyStringSent);
	CHudAmmo            (*m_Ammo);
	CHudHealth          (*m_Health);
	CHudSpectator       (*m_Spectator);
	CHudGeiger          (*m_Geiger);
	CHudBattery         (*m_Battery);
	CHudTrain           (*m_Train);
	CHudFlashlight      (*m_Flash);
	CHudMessage         (*m_Message);
	CHudStatusBar       (*m_StatusBar);
	CHudDeathNotice     (*m_DeathNotice);
	CHudSayText         (*m_SayText);
	CHudMenu            (*m_Menu);
	CHudAmmoSecondary   (*m_AmmoSecondary);
	CHudTextMessage     (*m_TextMessage);
	CHudStatusIcons     (*m_StatusIcons);
	CHudAccountBalance  (*m_accountBalance);
	CHudRoundTimer      (*m_roundTimer);
	CHudProgressBar     (*m_progressBar);
	CHudNightVision     (*m_NightVision);
	CHudCareerTaskTimer (*m_careerTaskTimer);
	CHudScenarioStatus  (*m_scenarioStatus);
	CHudSniperScope     (*m_sniperScope);
	CHudVGUI2Print      (*m_VGUI2Print);
	SCREENINFO          (*m_scrinfo);
};

class Element
{
public:
	Element(float Time) :
		flTimeCreated(Time)
	{
	}

	float flTimeCreated;
	Element *next;
	Element *previous;
};

class Queue
{
public:
	Queue();
	~Queue();

	bool Full() const;
	bool Add(float flTime);
	void Update(float flCurrentTime = 99999.0f);

	int count;
	int maxelements;
	float m_flDuration;
	Element *first;
	Element *last;
	Element *current;
};

inline Queue::Queue()
{
	maxelements = 60;
	count = 0;
	first = nullptr;
	last = nullptr;
	current = nullptr;
	m_flDuration = 2.0f;
}

inline Queue::~Queue()
{
	Update();
}

inline bool Queue::Full() const
{
	return (count >= maxelements);
}

inline bool Queue::Add(float flTime)
{
	if (count >= maxelements)
		return false;

	if (first)
	{
		auto elem = new Element(flTime);
		current->next = elem;
		current->next->previous = current;

		auto temp = current->next;
		current = temp;
		last = temp;
		count++;
	}
	else
	{
		auto elem = new Element(flTime);
		first = elem;
		first->next = nullptr;
		first->previous = nullptr;

		auto temp = first;
		current = temp;
		last = temp;
		count++;
	}

	return true;
}

inline void Queue::Update(float flCurrentTime)
{
	if (!last)
		return;

	auto next = last;
	while ((next->flTimeCreated + m_flDuration) < flCurrentTime)
	{
		auto temp = next->previous;
		delete next;

		last = temp;
		current = temp;
		count--;

		if (!temp)
		{
			first = nullptr;
			current = nullptr;
			break;
		}

		next = temp;
	}
}