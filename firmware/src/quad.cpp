#include "radio.h"
#include "imu.h"
#include "motors.h"
#include "pid_handler.h"

void setup()
{
  Serial.begin(115200);
  delay(3000);
  Serial.println("Setup started");
  setupRadio();
  Serial.println("Radio set");
  setupImu();
  Serial.println("Imu set");
  setupMotors();
  Serial.println("Motors set");
  setupPID();
  Serial.println("PID set");
  Serial.println("Setup done");
}

void loop()
{
  listenAndReply();
  PosData pos = getImuData();
  Serial.print("ro");
  Serial.print(pos.roll);
  Serial.print(" pi");
  Serial.print(pos.pitch);
  Serial.print(" ya");
  Serial.println(pos.yaw);
  updateImu();
  updatePID();
  updateMotors();
}

int main()
{
	setup();
	while(1)
		loop();
	return 0;
}
