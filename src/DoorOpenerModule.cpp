#include "DoorOpenerModule.h"
#include "doorbell.h"
#include "hardware.h"
#include <Arduino.h>
#include <knx.h>

const std::string DoorOpenerModule::name() { return "Elcom-1+n-DoorOpener"; }

const std::string DoorOpenerModule::version() { return DOORBELL_VERSION; }

void DoorOpenerModule::setup() {
  doorOpenerActive = false;
  doorOpenerEngagedAt = -1;

  pinMode(ACTIVATE_DOOR_OPENER_PIN, OUTPUT);
}

void DoorOpenerModule::loop() { maybeDisengageDoorOpener(); }

void DoorOpenerModule::processInputKo(GroupObject &iKo) {
  if (iKo.asap() == KoActivateDoorOpener &&
      ((bool)iKo.value(DPT_Trigger)) == true) {

    triggerDoorOpener();
  }
}

void DoorOpenerModule::triggerDoorOpener() {
  DEBUG_LOG("Triggering door opener...");

  digitalWrite(ACTIVATE_DOOR_OPENER_PIN, HIGH);
  doorOpenerActive = true;
  doorOpenerEngagedAt = millis();
}

void DoorOpenerModule::maybeDisengageDoorOpener() {
  if (doorOpenerActive &&
      doorOpenerEngagedAt + DOOR_OPENER_DURATION < millis()) {
    DEBUG_LOG("Disengaging door opener...");

    digitalWrite(ACTIVATE_DOOR_OPENER_PIN, LOW);
    doorOpenerActive = false;
  }
}
