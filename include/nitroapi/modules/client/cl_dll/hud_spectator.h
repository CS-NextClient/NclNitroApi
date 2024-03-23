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

#include "interpolation.h"

#define INSET_OFF				0
#define	INSET_CHASE_FREE		1
#define	INSET_IN_EYE			2
#define	INSET_MAP_FREE			3
#define	INSET_MAP_CHASE			4

#define OVERVIEW_TILE_SIZE		256		// don't change this
#define OVERVIEW_MAX_LAYERS		1

// Handles the drawing of the spectator stuff (camera & top-down map and all the things on it)
typedef struct overviewInfo_s
{
    char		map[64];	// cl.levelname or empty
    vec3_t		origin;		// center of map
    float		zoom;		// zoom of map images
    int			layers;		// how may layers do we have
    float		layersHeights[OVERVIEW_MAX_LAYERS];
    char		layersImages[OVERVIEW_MAX_LAYERS][255];
    qboolean	rotated;	// are map images rotated (90 degrees) ?

    int			insetWindowX;
    int			insetWindowY;
    int			insetWindowHeight;
    int			insetWindowWidth;
} overviewInfo_t;

typedef struct overviewEntity_s
{
    HSPRITE_t hSprite;
    struct cl_entity_s *entity;
    double killTime;
} overviewEntity_t;

typedef struct cameraWayPoint_s
{
    float time;
    vec3_t position;
    vec3_t angle;
    float fov;
    int flags;
} cameraWayPoint_t;

constexpr auto MAX_SPEC_HUD_MESSAGES = 8;
constexpr auto MAX_CAM_WAYPOINTS     = 32;
constexpr auto MAX_OVERVIEW_ENTITIES = 128;

class CHudSpectator: public CHudBase
{
public:
    ~CHudSpectator() {}

    virtual void Reset();
    int ToggleInset(bool allowOff);
    void ToggleInsetVisibility();
    void CheckSettings();
    virtual void InitHUDData();
    bool AddOverviewEntityToList(HSPRITE_t sprite, cl_entity_t *ent, double killTime);
    void DeathMessage(int victim);
    bool AddOverviewEntity(int type, struct cl_entity_s *ent, const char *modelname);
    void CheckOverviewEntities();
    void DrawOverview();
    void DrawOverviewEntities();
    void GetMapPosition(float *returnvec);
    void DrawOverviewLayer();
    void LoadMapSprites();
    bool ParseOverviewFile();
    bool IsActivePlayer(cl_entity_t *ent);
    void SetModes(int iMainMode, int iInsetMode);
    void HandleButtonsDown(int ButtonPressed);
    void HandleButtonsUp(int ButtonPressed);
    void FindNextPlayer(bool bReverse);
    void FindPlayer(const char *name);
    void DirectorMessage(int iSize, void *pbuf);
    void SetSpectatorStartPosition();
    virtual int Init();
    virtual int VidInit();
    virtual int Draw(float flTime);

    void AddWaypoint(float time, Vector pos, Vector angle, float fov, int flags);
    void SetCameraView(Vector pos, Vector angle, float fov);
    float GetFOV();
    bool GetDirectorCamera(Vector &position, Vector &angle);
    void SetWayInterpolation(cameraWayPoint_t *prev, cameraWayPoint_t *start, cameraWayPoint_t *end, cameraWayPoint_t *next);

public:
    int m_iDrawCycle;
    client_textmessage_t m_HUDMessages[MAX_SPEC_HUD_MESSAGES];
    char m_HUDMessageText[MAX_SPEC_HUD_MESSAGES][128];
    int m_lastHudMessage;
    overviewInfo_t m_OverviewData;
    overviewEntity_t m_OverviewEntities[MAX_OVERVIEW_ENTITIES];
    int m_iObserverFlags;
    int m_iSpectatorNumber;

    float m_mapZoom;		// zoom the user currently uses
    vec3_t m_mapOrigin;		// origin where user rotates around
    cvar_t *m_drawnames;
    cvar_t *m_drawcone;
    cvar_t *m_drawstatus;
    cvar_t *m_autoDirector;
    cvar_t *m_pip;
    cvar_t *m_scoreboard;
    cvar_t *m_mode;

    qboolean m_chatEnabled;
    qboolean m_IsInterpolating;

    int m_ChaseEntity;						// if != 0, follow this entity with viewangles
    int m_WayPoint;							// current waypoint 1
    int m_NumWayPoints;						// current number of waypoints
    vec3_t m_cameraOrigin;					// a help camera
    vec3_t m_cameraAngles;					// and it's angles
    CInterpolation m_WayInterpolation;

    vec3_t m_vPlayerPos[64];
    HSPRITE_t m_hsprPlayerBlue;
    HSPRITE_t m_hsprPlayerRed;
    HSPRITE_t m_hsprPlayer;
    HSPRITE_t m_hsprPlayerVIP;
    HSPRITE_t m_hsprPlayerC4;
    HSPRITE_t m_hsprCamera;
    HSPRITE_t m_hsprPlayerDead;
    HSPRITE_t m_hsprViewcone;
    HSPRITE_t m_hsprUnkownMap;
    HSPRITE_t m_hsprBeam;
    HSPRITE_t m_hsprBomb;
    HSPRITE_t m_hsprHostage;
    HSPRITE_t m_hsprBackpack;
    struct model_s *m_MapSprite;	// each layer image is saved in one sprite, where each tile is a sprite frame
    float m_flNextObserverInput;
    float m_FOV;
    float m_zoomDelta;
    float m_moveDelta;
    int m_lastPrimaryObject;
    int m_lastSecondaryObject;
    float m_lastAutoDirector;
    cameraWayPoint_t m_CamPath[MAX_CAM_WAYPOINTS];
};

void ToggleScores();
const char *GetSpectatorLabel(int iMode);