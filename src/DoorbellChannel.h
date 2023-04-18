#include "OpenKNX.h"
#include "hardware.h"
#include <cstdint>

class DoorbellChannel : public OpenKNX::Channel
{
public:
    DoorbellChannel(std::string name, uint16_t ringingCommObject, uint8_t gpioPin);

    void loop() override;
    void setup() override;

    const std::string name() override;

private:
    std::string channelName;
    uint16_t channelRingingCommObject;
    uint8_t channelGpioPin;
    uint32_t lastPolledAt;
    bool ringDetected;
    uint32_t ringDetectedAt;

    void processGpioInput();

    bool doorbellRingingStateChanged();
    bool doorbellRingingRawState();
};
