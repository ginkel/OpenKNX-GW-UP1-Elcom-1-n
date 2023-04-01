#pragma once
#ifdef DEBUG
#define DEBUG_LOG(...) Serial.println(__VA_ARGS__)
#else
#define DEBUG_LOG(...) ((void)0)
#endif

#define DOORBELL_VERSION "0.1"
