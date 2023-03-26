#include "DoorOpenerModule.h"
#include "DoorbellModule.h"
#include "OpenKNX.h"
#include "doorbell.h"
#include <Arduino.h>

void setup() {
#ifdef DEBUG
  Serial.begin(115200);
#endif
  DEBUG_LOG("GW-UP1-Elcom-1+n starting...");

  const uint8_t firmwareRevision = 0;
  openknx.init(firmwareRevision);
  openknx.addModule(1, new DoorbellModule());
  openknx.addModule(2, new DoorOpenerModule());
  openknx.setup();
}

void loop() { openknx.loop(); }
