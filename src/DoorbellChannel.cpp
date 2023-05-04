#include "DoorbellChannel.h"

const std::string DoorbellChannel::name() { return channelName; }

DoorbellChannel::DoorbellChannel(std::string name, uint16_t ringingCommObject, uint8_t gpioPin)
{
    this->channelName = name;
    this->channelRingingCommObject = ringingCommObject;
    this->channelGpioPin = gpioPin;
}

void DoorbellChannel::setup()
{
    lastPolledAt = 0;

    ringDetected = false;
    ringDetectedAt = 0;

    pinMode(channelGpioPin, INPUT);
}

void DoorbellChannel::loop()
{
    uint32_t now = millis();

    if (lastPolledAt + DOORBELL_POLLING_INTERVAL > now)
        return;

    processGpioInput();

    lastPolledAt = now;
}

void DoorbellChannel::processGpioInput()
{
    if (doorbellRingingStateChanged())
    {
        logInfoP("Doorbell ring detected, publishing telegram...");

        knx.getGroupObject(channelRingingCommObject).value(ringDetected, DPT_State);
    }
}

bool DoorbellChannel::doorbellRingingStateChanged()
{
    bool state = doorbellRingingRawState();

    logDebugP("Doorbell is currently %sringing", state ? "" : "NOT ");

    uint32_t now = millis();

    if (ringDetectedAt != -1)
    {
        if (ringDetected != state &&
            (ringDetectedAt + DOORBELL_DEBOUNCE_INTERVAL) < now)
        {
            logDebugP("Detected doorbell state: %d", state);

            ringDetected = state;
            ringDetectedAt = now;
            return true;
        }
    }
    else
    {
        logDebugP("Obtained an (initial) doorbell state: %d", state);

        ringDetected = state;
        ringDetectedAt = now;
        return true;
    }

    return false;
}

bool DoorbellChannel::doorbellRingingRawState()
{
    logDebugP("Polling doorbell state...");
    int state = digitalRead(channelGpioPin);
    logDebugP("Doorbell raw state = %d", state);
    return state == LOW;
}

const std::string DoorbellChannel::logPrefix()
{
    return name();
}
