#include "OpenKNX.h"

class DoorOpenerModule : public OpenKNX::Module {
public:
  void loop() override;
  void setup() override;
  void processInputKo(GroupObject &ko) override;

  const std::string name() override;
  const std::string version() override;

private:
  bool doorOpenerActive;
  long doorOpenerEngagedAt;

  void triggerDoorOpener();
  void maybeDisengageDoorOpener();
};
