
#define MAIN_OpenKnxId 0xA4
#define MAIN_ApplicationNumber 0x01
#define MAIN_ApplicationVersion 0x01
#define MAIN_OrderNumber "GW-UP1-Elcom-1+n"

#define KO_DOORBELL_RINGING 0
#define KO_ACTIVATE_DOOR_OPENER 1

#define KoDoorbellRinging (knx.getGroupObject(KO_DOORBELL_RINGING))
#define KoActivateDoorOpener (knx.getGroupObject(KO_ACTIVATE_DOOR_OPENER))
