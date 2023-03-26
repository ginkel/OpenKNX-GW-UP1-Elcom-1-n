#pragma once
#ifdef DEBUG
#define DEBUG_LOG(x) Serial.println(x)
#else
#define DEBUG_LOG(x) ((void)0)
#endif

#define DOORBELL_VERSION "0.1"
