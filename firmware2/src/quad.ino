#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "radio.h"

#include <Wire.h>
#include "I2Cdev.h"
#include "RTIMUSettings.h"
#include "RTIMU.h"
#include "RTFusionRTQF.h" 
#include "CalLib.h"
#include <EEPROM.h>
#include "imu.h"

#include <Servo.h>
#include "motors.h"

#include <PID.h>
#include "pid_handler.h"

void setup(void)
{
  delay(3000);
  Serial.begin(115200);
  Serial.println("Setup started");
  setupRadio();
  setupImu();
  setupMotors();
  setupPID();
  Serial.println("Setup done");
}

void loop(void)
{
  listenAndReply();
  updateImu();
  updatePID();
  updateMotors();
}

int main(void)
{
	setup();
	while(1)
		loop();
	return 0;
}
