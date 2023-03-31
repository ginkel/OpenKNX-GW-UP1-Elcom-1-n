#pragma once

// Parameter with single occurrence
#define Enabled                    0      // 1 Bit, Bit 7
#define     EnabledMask 0x80
#define     EnabledShift 7

// Communication objects with single occurrence
#define KoDoorbellRinging 1
#define KoActivateDoorOpener 2

#define MAIN_OpenKnxId 0xAF
#define MAIN_ApplicationNumber 0
#define MAIN_ApplicationVersion 1
#define MAIN_OrderNumber "0"
