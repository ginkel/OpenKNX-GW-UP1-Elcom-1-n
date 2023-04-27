#include "DoorOpenerModule.h"
#include "DoorbellModule.h"
#include "OpenKNX.h"
#include "UpdateModule.h"
#include "doorbell.h"
#include <Arduino.h>

void setup() {
#ifdef DEBUG
  Serial.begin(115200);
#endif
  openknx.logger.log("GW-UP1-Elcom-1+n starting...");

  const uint8_t firmwareRevision = 0;
  openknx.init(firmwareRevision);
  openknx.addModule(1, new DoorbellModule());
  openknx.addModule(2, new DoorOpenerModule());
  openknx.addModule(3, new UpdateModule());
  openknx.setup();
}

void loop() { openknx.loop(); }
