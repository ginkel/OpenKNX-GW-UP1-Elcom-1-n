#include "OpenKNX.h"
#include "hardware.h"
#include <cstdint>

class DoorbellModule : public OpenKNX::Module {
public:
  void loop() override;
  void setup() override;

  const std::string name() override;
  const std::string version() override;

private:
  uint32_t lastPolledAt;
  bool ringDetected;
  uint32_t ringDetectedAt;

  void processGpioInput();

  bool doorbellRinging();
  bool doorbellRingingStateChanged();
  bool doorbellRingingRawState();
};
