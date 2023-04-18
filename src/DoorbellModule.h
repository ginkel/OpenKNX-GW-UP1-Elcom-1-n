#include "OpenKNX.h"
#include "DoorbellChannel.h"
#include "hardware.h"
#include <cstdint>

class DoorbellModule : public OpenKNX::Module
{
public:
  DoorbellModule();

  void loop() override;
  void setup() override;

  const std::string name() override;
  const std::string version() override;

private:
  DoorbellChannel *channels[DOORBELL_CHANNEL_COUNT];
};
