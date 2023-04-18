#include "DoorbellModule.h"
#include "doorbell.h"
#include "hardware.h"
#include <Arduino.h>
#include <cstdint>
#include <knx.h>

DoorbellModule::DoorbellModule()
{
  channels[0] = new DoorbellChannel("Door", KoDoorbellDoorCall, DOORBELL_DOOR_RINGING_PIN);
  channels[1] = new DoorbellChannel("Storey", KoDoorbellStoreyCall, DOORBELL_STOREY_RINGING_PIN);
}

const std::string DoorbellModule::name() { return "Doorbell"; }

const std::string DoorbellModule::version() { return DOORBELL_VERSION; }

void DoorbellModule::setup()
{
  for (int i = 0; i < DOORBELL_CHANNEL_COUNT; i++)
  {
    channels[i]->setup();
  }
}

void DoorbellModule::loop()
{
  for (int i = 0; i < DOORBELL_CHANNEL_COUNT; i++)
  {
    channels[i]->loop();
  }
}
