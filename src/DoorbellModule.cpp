#include "DoorbellModule.h"
#include "doorbell.h"
#include "hardware.h"
#include <Arduino.h>
#include <cstdint>
#include <knx.h>

const std::string DoorbellModule::name() { return "Elcom-1+n-Doorbell"; }

const std::string DoorbellModule::version() { return DOORBELL_VERSION; }

void DoorbellModule::setup() {
  lastPolledAt = 0;

  ringDetected = false;
  ringDetectedAt = 0;

  pinMode(DOORBELL_RINGING_PIN, INPUT_PULLUP);
}

void DoorbellModule::loop() {
  uint32_t now = millis();

  if (lastPolledAt + DOORBELL_POLLING_INTERVAL > now)
    return;

  processGpioInput();

  lastPolledAt = now;
}

void DoorbellModule::processGpioInput() {
  if (doorbellRingingStateChanged()) {
    DEBUG_LOG("Doorbell ring detected, publishing telegram...");

    KoDoorbellRinging.value(ringDetected, DPT_State);
  }
}

bool DoorbellModule::doorbellRingingStateChanged() {
  bool state = doorbellRingingRawState();
  uint32_t now = millis();
  bool stateChanged = false;

  if (ringDetectedAt != -1) {
    if (ringDetected != state &&
        (ringDetectedAt + DOORBELL_DEBOUNCE_INTERVAL) > now) {
      ringDetected = state;
      ringDetectedAt = now;
      return true;
    }
  } else {
    ringDetected = state;
    ringDetectedAt = now;
    return true;
  }

  return false;
}

bool DoorbellModule::doorbellRingingRawState() {
  int state = digitalRead(DOORBELL_RINGING_PIN);
  return state == LOW;
}
