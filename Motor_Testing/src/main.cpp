#include <Arduino.h>
#include <DynamixelShield.h>
#if defined(ARDUINO_AVR_UNO) || defined(ARDUINO_AVR_MEGA2560)
#include <SoftwareSerial.h>
SoftwareSerial soft_serial(7, 8); // DYNAMIXELShield UART RX/TX
#define DEBUG_SERIAL soft_serial
#elif defined(ARDUINO_SAM_DUE) || defined(ARDUINO_SAM_ZERO)
#define DEBUG_SERIAL SerialUSB
#else
#define DEBUG_SERIAL Serial
#endif
const uint8_t DXL_ID = 0;
const float DXL_PROTOCOL_VERSION = 1.0;
DynamixelShield dxl;
//This namespace is required to use Control table item names
using namespace ControlTableItem;
void setup() {
// put your setup code here, to run once:
// For Uno, Nano, Mini, and Mega, use UART port of DYNAMIXEL Shield to debug.
DEBUG_SERIAL.begin(115200);
// Set Port baudrate to 1000000bps. This has to match with DYNAMIXEL baudrate.
dxl.begin(1000000);
// Set Port Protocol Version. This has to match with DYNAMIXEL protocol version.
dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);
// Get DYNAMIXEL information
dxl.ping(DXL_ID);
// Turn off torque when configuring items in EEPROM area
dxl.torqueOff(DXL_ID);
dxl.setOperatingMode(DXL_ID_1, OP_VELOCITY);
dxl.torqueOn(DXL_ID);
}
void loop() {
// put your main code here, to run repeatedly:
dxl.setGoalVelocity(DXL_ID_1, 1.2, UNIT_PERCENT);
dxl.setGoalVelocity(DXL_ID_2, 1.1, UNIT_PERCENT);
delay(1000);
dxl.setGoalVelocity(DXL_ID_1, -80.2, UNIT_PERCENT);
// Set Goal Velocity using percentage (-100.0 [%] ~ 100.0 [%])
dxl.setGoalVelocity(DXL_ID_2, 20.2, UNIT_PERCENT);
DEBUG_SERIAL.print("Present Velocity(ratio) : ");
DEBUG_SERIAL.println(dxl.getPresentVelocity(DXL_ID_2, UNIT_PERCENT));
delay(1000);
}