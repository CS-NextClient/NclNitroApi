#pragma once

#include <cstdint>
#include <quakedef.h>
#include <extdll.h>
#include <pm_defs.h>
#include <client.h>

namespace nitroapi
{
    typedef void( *pfnEngineMessage )();

    typedef struct UserMsg
    {
        int number;
        int size;
        char name[16];
        struct UserMsg *next;
        pfnUserMsgHook pfn;
    } *PUserMsg;

    typedef struct EngineMsg
    {
        int number;
        char *name;
        pfnEngineMessage pfn;
    } *PEngineMsg;

    #define	SVC_BAD                   0
    #define	SVC_NOP                   1
    #define	SVC_DISCONNECT            2
    #define	SVC_EVENT                 3
    #define	SVC_VERSION               4
    #define	SVC_SETVIEW               5
    #define	SVC_SOUND                 6
    #define	SVC_TIME                  7
    #define	SVC_PRINT                 8
    #define	SVC_STUFFTEXT             9
    #define	SVC_SETANGLE              10
    #define	SVC_SERVERINFO            11
    #define	SVC_LIGHTSTYLE            12
    #define	SVC_UPDATEUSERINFO        13
    #define	SVC_DELTADESCRIPTION      14
    #define	SVC_CLIENTDATA            15
    #define	SVC_STOPSOUND             16
    #define	SVC_PINGS                 17
    #define	SVC_PARTICLE              18
    #define	SVC_DAMAGE                19
    #define	SVC_SPAWNSTATIC           20
    #define	SVC_EVENT_RELIABLE        21
    #define	SVC_SPAWNBASELINE         22
    #define	SVC_TEMPENTITY            23
    #define	SVC_SETPAUSE              24
    #define	SVC_SIGNONNUM             25
    #define	SVC_CENTERPRINT           26
    #define	SVC_KILLEDMONSTER         27
    #define	SVC_FOUNDSECRET           28
    #define	SVC_SPAWNSTATICSOUND      29
    #define	SVC_INTERMISSION          30
    #define	SVC_FINALE                31
    #define	SVC_CDTRACK               32
    #define	SVC_RESTORE               33
    #define	SVC_CUTSCENE              34
    #define	SVC_WEAPONANIM            35
    #define	SVC_DECALNAME             36
    #define	SVC_ROOMTYPE              37
    #define	SVC_ADDANGLE              38
    #define	SVC_NEWUSERMSG            39
    #define	SVC_PACKETENTITIES        40
    #define	SVC_DELTAPACKETENTITIES   41
    #define	SVC_CHOKE                 42
    #define	SVC_RESOURCELIST          43
    #define	SVC_NEWMOVEVARS           44
    #define	SVC_RESOURCEREQUEST       45
    #define	SVC_CUSTOMIZATION         46
    #define	SVC_CROSSHAIRANGLE        47
    #define	SVC_SOUNDFADE             48
    #define	SVC_FILETXFERFAILED       49
    #define	SVC_HLTV                  50
    #define	SVC_DIRECTOR              51
    #define	SVC_VOICEINIT             52
    #define	SVC_VOICEDATA             53
    #define	SVC_SENDEXTRAINFO         54
    #define	SVC_TIMESCALE             55
    #define	SVC_RESOURCELOCATION      56
    #define	SVC_SENDCVARVALUE         57
    #define	SVC_SENDCVARVALUE2        58
    #define OFF_SVC_MESSAGES_P "End of List"

    enum VidTypes : int
    {
        VT_None     = 0,
        VT_Software = 1,
        VT_OpenGL   = 2,
        VT_Direct3D = 3
    };

    typedef struct viddef_s
    {
        uint8_t* buffer;                // invisible buffer
        uint8_t* colormap;              // 256 * VID_GRADES size
        unsigned short* colormap16;     // 256 * VID_GRADES size
        int fullbright;                 // index of first fullbright color
        int bits;
        int is15bit;
        unsigned int rowbytes;          // may be > width if displayed in a window
        unsigned int width;
        unsigned int height;
        float aspect;                   // width / height -- < 0 is taller than wide
        int numpages;
        int recalc_refdef;              // if true, recalc vid-based stuff
        uint8_t* conbuffer;
        int conrowbytes;
        unsigned int conwidth;
        unsigned int conheight;
        int maxwarpwidth;
        int maxwarpheight;
        uint8_t* direct;                // direct drawing to framebuffer, if not NULL
        VidTypes vidtype;
    } viddef_t;

    struct transObjRef
    {
        cl_entity_t* pEnt;
        float distance;
    };
}