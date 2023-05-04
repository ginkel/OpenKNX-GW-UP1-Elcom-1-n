#include "DoorbellModule.h"
#include "DoorOpenerModule.h"
#include "UpdateModule.h"
#include "doorbell.h"

void setup() {
#ifdef DEBUG
  Serial.begin(115200);
#endif
  logInfo("GW-UP1-Elcom-1+n %s starting...", DOORBELL_VERSION);

  const uint8_t firmwareRevision = 0;
  openknx.init(firmwareRevision);
  openknx.addModule(1, new DoorbellModule());
  openknx.addModule(2, new DoorOpenerModule());
  openknx.addModule(3, new UpdateModule());
  openknx.setup();
}

void loop() { openknx.loop(); }
