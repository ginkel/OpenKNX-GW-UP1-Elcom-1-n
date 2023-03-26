Import("env")
import shutil

print(env.Dump())

print("Current CLI targets", COMMAND_LINE_TARGETS)
print("Current Build targets", BUILD_TARGETS)

print("Copying hardware.h")
shutil.copyfile('src/DoorbellGatewayHardware.h', 'lib/OGM-Common/include/hardware.h')
print("Copying knxprod.h")
shutil.copyfile('src/DoorbellGateway.h', 'lib/OGM-Common/include/knxprod.h')
