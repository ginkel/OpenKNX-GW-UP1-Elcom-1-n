#include "DoorbellModule.h"
#include "DoorOpenerModule.h"
#include "doorbell.h"
#ifdef ARDUINO_ARCH_RP2040
#include "FileTransferModule.h"
#endif

void setup() {
#ifdef DEBUG
  Serial.begin(115200);
#endif
  logInfo("GW-UP1-Elcom-1+n %s starting...", DOORBELL_VERSION);

  const uint8_t firmwareRevision = 0;
  openknx.init(firmwareRevision);
  openknx.addModule(1, new DoorbellModule());
  openknx.addModule(2, new DoorOpenerModule());
#ifdef ARDUINO_ARCH_RP2040
  openknx.addModule(3, new FileTransferModule());
#endif
  openknx.setup();
}

void loop() { openknx.loop(); }
