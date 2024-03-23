#pragma once

#define DEFAULT_SOUND_PACKET_VOLUME			255
#define DEFAULT_SOUND_PACKET_ATTENUATION	1.0f
#define DEFAULT_SOUND_PACKET_PITCH			100

// Sound flags
#define SND_FL_VOLUME			BIT(0)	// send volume
#define SND_FL_ATTENUATION		BIT(1)	// send attenuation
#define SND_FL_LARGE_INDEX		BIT(2)	// send sound number as short instead of byte
#define SND_FL_PITCH			BIT(3)	// send pitch
#define SND_FL_SENTENCE			BIT(4)	// set if sound num is actually a sentence num
#define SND_FL_STOP				BIT(5)	// stop the sound
#define SND_FL_CHANGE_VOL		BIT(6)	// change sound vol
#define SND_FL_CHANGE_PITCH		BIT(7)	// change sound pitch
#define SND_FL_SPAWNING			BIT(8)	// we're spawning, used in some cases for ambients (not sent across network)

// director command types:
#define DRC_CMD_NONE				0	// NULL director command
#define DRC_CMD_START				1	// start director mode
#define DRC_CMD_EVENT				2	// informs about director command
#define DRC_CMD_MODE				3	// switches camera modes
#define DRC_CMD_CAMERA				4	// set fixed camera
#define DRC_CMD_TIMESCALE			5	// sets time scale
#define DRC_CMD_MESSAGE				6	// send HUD centerprint
#define DRC_CMD_SOUND				7	// plays a particular sound
#define DRC_CMD_STATUS				8	// HLTV broadcast status
#define DRC_CMD_BANNER				9	// set GUI banner
#define DRC_CMD_STUFFTEXT			10	// like the normal svc_stufftext but as director command
#define DRC_CMD_CHASE				11	// chase a certain player
#define DRC_CMD_INEYE				12	// view player through own eyes
#define DRC_CMD_MAP					13	// show overview map
#define DRC_CMD_CAMPATH				14	// define camera waypoint
#define DRC_CMD_WAYPOINTS			15	// start moving camera, inetranl message
#define DRC_CMD_LAST				15