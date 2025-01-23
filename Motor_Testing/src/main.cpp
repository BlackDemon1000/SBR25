#include <Arduino.h>
#include <DynamixelShield.h>

#if defined(ARDUINO_AVR_UNO) || defined(ARDUINO_AVR_MEGA2560)
#include <SoftwareSerial.h>
SoftwareSerial soft_serial(7, 8); 
#define DEBUG_SERIAL soft_serial
#elif defined(ARDUINO_SAM_DUE) || defined(ARDUINO_SAM_ZERO)
#define DEBUG_SERIAL SerialUSB
#else
#define DEBUG_SERIAL Serial
#endif

const uint8_t DXL_ID_1 = 1;
const uint8_t DXL_ID_2 = 2;
const float DXL_PROTOCOL_VERSION = 1.0;

DynamixelShield dxl;
using namespace ControlTableItem;

void setup() {
  // Initialize serial communication
  DEBUG_SERIAL.begin(115200);
  DEBUG_SERIAL.println("Dynamixel Shield Initializing...");

  // Initialize Dynamixel Shield
  dxl.begin(1000000);
  dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);

  // Ping and check motors
  DEBUG_SERIAL.println("Pinging Dynamixel Motors...");
  if(dxl.ping(DXL_ID_1) == true) {
    DEBUG_SERIAL.print("Motor 1 (ID: ");
    DEBUG_SERIAL.print(DXL_ID_1);
    DEBUG_SERIAL.println(") connected successfully.");
  } else {
    DEBUG_SERIAL.print("Failed to connect to Motor 1 (ID: ");
    DEBUG_SERIAL.print(DXL_ID_1);
    DEBUG_SERIAL.println(")");
  }

  if(dxl.ping(DXL_ID_2) == true) {
    DEBUG_SERIAL.print("Motor 2 (ID: ");
    DEBUG_SERIAL.print(DXL_ID_2);
    DEBUG_SERIAL.println(") connected successfully.");
  } else {
    DEBUG_SERIAL.print("Failed to connect to Motor 2 (ID: ");
    DEBUG_SERIAL.print(DXL_ID_2);
    DEBUG_SERIAL.println(")");
  }

  // Configure motors
  DEBUG_SERIAL.println("Configuring Motors...");
  dxl.torqueOff(DXL_ID_1);
  dxl.torqueOff(DXL_ID_2);

  dxl.setOperatingMode(DXL_ID_1, OP_VELOCITY);
  dxl.setOperatingMode(DXL_ID_2, OP_VELOCITY);

  dxl.torqueOn(DXL_ID_1);
  dxl.torqueOn(DXL_ID_2);

  DEBUG_SERIAL.println("Motor Configuration Complete.");
}

void loop() {
  DEBUG_SERIAL.println("Setting First Velocity Sequence...");
  
  // First velocity sequence
  dxl.setGoalVelocity(DXL_ID_1, 1.2, UNIT_PERCENT);
  dxl.setGoalVelocity(DXL_ID_2, 1.1, UNIT_PERCENT);

  DEBUG_SERIAL.print("Motor 1 Velocity: ");
  DEBUG_SERIAL.print(dxl.getPresentVelocity(DXL_ID_1, UNIT_PERCENT));
  DEBUG_SERIAL.println(" %");

  DEBUG_SERIAL.print("Motor 2 Velocity: ");
  DEBUG_SERIAL.print(dxl.getPresentVelocity(DXL_ID_2, UNIT_PERCENT));
  DEBUG_SERIAL.println(" %");

  delay(1000);

  DEBUG_SERIAL.println("Setting Second Velocity Sequence...");
  
  // Second velocity sequence
  dxl.setGoalVelocity(DXL_ID_1, -80.2, UNIT_PERCENT);
  dxl.setGoalVelocity(DXL_ID_2, 20.2, UNIT_PERCENT);

  DEBUG_SERIAL.print("Motor 1 Velocity: ");
  DEBUG_SERIAL.print(dxl.getPresentVelocity(DXL_ID_1, UNIT_PERCENT));
  DEBUG_SERIAL.println(" %");

  DEBUG_SERIAL.print("Motor 2 Velocity: ");
  DEBUG_SERIAL.print(dxl.getPresentVelocity(DXL_ID_2, UNIT_PERCENT));
  DEBUG_SERIAL.println(" %");

  delay(1000);
}