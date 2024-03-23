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

#define DMG_IMAGE_LIFE			2	// seconds that image is up

#define DMG_IMAGE_POISON		0
#define DMG_IMAGE_ACID			1
#define DMG_IMAGE_COLD			2
#define DMG_IMAGE_DROWN			3
#define DMG_IMAGE_BURN			4
#define DMG_IMAGE_NERVE			5
#define DMG_IMAGE_RAD			6
#define DMG_IMAGE_SHOCK			7

#define DMG_IMAGE_CALTROP		8
#define DMG_IMAGE_TRANQ			9
#define DMG_IMAGE_CONCUSS		10
#define DMG_IMAGE_HALLUC		11
#define NUM_DMG_TYPES			12

// instant damage
#define DMG_GENERIC				0		// generic damage was done
#define DMG_CRUSH				(1<<0)	// crushed by falling or moving object
#define DMG_BULLET				(1<<1)	// shot
#define DMG_SLASH				(1<<2)	// cut, clawed, stabbed
#define DMG_BURN				(1<<3)	// heat burned
#define DMG_FREEZE				(1<<4)	// frozen
#define DMG_FALL				(1<<5)	// fell too far
#define DMG_BLAST				(1<<6)	// explosive blast damage
#define DMG_CLUB				(1<<7)	// crowbar, punch, headbutt
#define DMG_SHOCK				(1<<8)	// electric shock
#define DMG_SONIC				(1<<9)	// sound pulse shockwave
#define DMG_ENERGYBEAM			(1<<10)	// laser or other high energy beam
#define DMG_NEVERGIB			(1<<12)	// with this bit OR'd in, no damage type will be able to gib victims upon death
#define DMG_ALWAYSGIB			(1<<13)	// with this bit OR'd in, any damage type can be made to gib victims upon death.

// time-based damage
//mask off TF-specific stuff too
#define DMG_TIMEBASED			(~(0xff003fff))	// mask for time-based damage

#define DMG_DROWN				(1<<14)	// Drowning
#define DMG_FIRSTTIMEBASED		DMG_DROWN

#define DMG_PARALYZE			(1<<15)	// slows affected creature down
#define DMG_NERVEGAS			(1<<16)	// nerve toxins, very bad
#define DMG_POISON				(1<<17)	// blood poisioning
#define DMG_RADIATION			(1<<18)	// radiation exposure
#define DMG_DROWNRECOVER		(1<<19)	// drowning recovery
#define DMG_ACID				(1<<20)	// toxic chemicals or acid burns
#define DMG_SLOWBURN			(1<<21)	// in an oven
#define DMG_SLOWFREEZE			(1<<22)	// in a subzero freezer
#define DMG_MORTAR				(1<<23)	// Hit by air raid (done to distinguish grenade from mortar)

// ADDITIONS
#define DMG_IGNITE				(1<<24)	// Players hit by this begin to burn
#define DMG_RADIUS_MAX			(1<<25)	// Radius damage with this flag doesn't decrease over distance
#define DMG_RADIUS_QUAKE		(1<<26)	// Radius damage is done like Quake. 1/2 damage at 1/2 radius.
#define DMG_IGNOREARMOR			(1<<27)	// Damage ignores target's armor
#define DMG_AIMED				(1<<28)	// Does Hit location damage
#define DMG_WALLPIERCING		(1<<29)	// Blast Damages ents through walls

#define DMG_CALTROP				(1<<30)
#define DMG_HALLUC				(1<<31)

// Healing Additions for TakeHealth
#define DMG_IGNORE_MAXHEALTH	DMG_IGNITE

// Redefines since we never use the originals
#define DMG_NAIL				DMG_SLASH
#define DMG_NOT_SELF			DMG_FREEZE

#define DMG_TRANQ				DMG_MORTAR
#define DMG_CONCUSS				DMG_SONIC

struct DAMAGE_IMAGE
{
    float fExpire;
    float fBaseline;
    int	x, y;
};

class CHudHealth: public CHudBase
{
public:
    virtual int Init();
    virtual int VidInit();
    virtual int Draw(float fTime);
    virtual void Reset();

    DECLARE_MESSAGE_FUNC(Health);
    DECLARE_MESSAGE_FUNC(Health2);
    DECLARE_MESSAGE_FUNC(Damage);
    DECLARE_MESSAGE_FUNC(Money);
    DECLARE_MESSAGE_FUNC(Radar);
    DECLARE_MESSAGE_FUNC(Account);
    DECLARE_MESSAGE_FUNC(HealthInfo);
    DECLARE_MESSAGE_FUNC(ScoreAttrib);
    DECLARE_MESSAGE_FUNC(ClCorpse);
    DECLARE_MESSAGE_FUNC(ReceiveW);

    DECLARE_USERCMD_FUNC(TrackPlayer);
    DECLARE_USERCMD_FUNC(ClearPlayers);
    DECLARE_USERCMD_FUNC(DrawRadar);
    DECLARE_USERCMD_FUNC(HideRadar);

    void DrawRadarDot(int x, int y, float z_diff, int iBaseDotSize, int flags, int r, int g, int b, int a);
    void DrawRadar(float flTime);
    void DrawPlayerLocation();
    void GetAllPlayersInfo();
    void GetPainColor(int &r, int &g, int &b);
    int DrawPain(float flTime);
    int DrawDamage(float flTime);
    void CalcDamageDirection(Vector vecFrom);
    void UpdateTiles(float flTime, long int bitsDamage);

public:
    int m_iHealth;
    int m_HUD_dmg_bio;
    int m_HUD_cross;
    float m_fFade;
    float m_fAttackFront, m_fAttackRear, m_fAttackLeft, m_fAttackRight;
    bool m_bTrackArray[MAX_PLAYERS + 1];
    int m_iPlayerLastPointedAt;
    int m_iPlayerNum;
    bool m_bDrawRadar;
    HSPRITE_t m_hSprite;
    HSPRITE_t m_hDamage;
    wrect_t *m_hrad;
    wrect_t *m_hradopaque;
    HSPRITE_t m_hRadar;
    HSPRITE_t m_hRadaropaque;
    DAMAGE_IMAGE m_dmg[NUM_DMG_TYPES];
    int	m_bitsDamage;
};

class CHudRoundTimer: public CHudBase
{
public:
    virtual int Init();
    virtual int VidInit();
    virtual int Draw(float fTime);
    virtual void Reset();

    DECLARE_MESSAGE_FUNC(RoundTime);

    int GetClosestRight() const { return m_closestRight; }

public:
    float m_flTimeEnd;
    int m_HUD_stopwatch;
    float m_fFade;
    float m_flNewPeriod;
    float m_flNextToggle;
    int m_bPanicColor;
    int m_closestRight;
};

class CHudProgressBar: public CHudBase
{
public:
    virtual int Init();
    virtual int VidInit();
    virtual int Draw(float fTime);
    virtual void Reset();

    DECLARE_MESSAGE_FUNC(BarTime);
    DECLARE_MESSAGE_FUNC(BarTime2);

public:
    float m_tmEnd;
    float m_tmStart;
    float m_tmNewPeriod;
    float m_tmNewElapsed;
    int m_width;
    int m_height;
    int m_x0;
    int m_y0;
    int m_x1;
    int m_y1;
};

class CHudCareerTaskTimer: public CHudBase
{
public:
    virtual int Init();
    virtual int VidInit();
    virtual int Draw(float fTime);
    virtual void Reset();

    DECLARE_MESSAGE_FUNC(TaskTime);

public:
    float m_flTimeEnd;
    int m_HUD_stopwatch;
    float m_fFade;
    float m_flNewPeriod;
    float m_flNextToggle;
    int m_bPanicColor;
    bool m_bTaskComplete;
    bool m_bCountdown;
    float m_flAlpha;
    float m_flFadeDelay;
    float m_flFadeStart;
};