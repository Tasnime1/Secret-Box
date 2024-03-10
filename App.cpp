/************************************************************************************************
*            FILE: APP.CPP
*          DRIVER: APP
*     DESCRIPTION: Source file for all APPLICATION-related functions declarations
*          Author: Tasneem Mansour.
*         Version: v1
*            Date: 9.3.2024
*
************************************************************************************************/


/*- INCLUDES
************************************************************************************************/
#include "Arduino.h"
#include "HardwareSerial.h"
#include "App.h"

#define BuilInLed 2
#define tiltAngle 30
#define boxDepth 20

/*- FUNCTIONS' DECLARATION
************************************************************************************************/
void App_init(void) {
  mpu_setup();
  Ultrasonic_init();
  pinMode(BuilInLed, OUTPUT);
}

/**************************************
/*- DRIVER FUNCTION FOR WHOLE PROGRAM
***************************************/
void App_start(void) {
  
  //frequently update MPU readings
  mpu_update();

  //getting latest inclination angles and distance from sensors
  float yaw = return_yaw();
  float pitch = return_pitch();
  float roll = return_roll();
  float distance = ultrasonic_calc_distance();

  //Calculating battery voltage and percentage
  float batteryVoltage = Battery_getBatteryVoltage();
  float batteryPercentage = Battery_getBatteryPercentage(); 


  /*DEBUGGING FOR BATTERY*/
  Serial.print("Battery Voltage: ");
  Serial.println(batteryVoltage);

  Serial.print("Battery Percentage: ");
  Serial.print(batteryPercentage);
  Serial.println("%");

  /*DEBUGGING FOR ULTRASONIC SENSOR*/
  /*Printing distance to screen*/
  /**
  Serial.print("Distance: ");
  Serial.println(distance);**/

  
  /*Checking box has been opened*/
  if(distance>boxDepth)
  {
    Serial.println("BOX HAS BEEN OPENED!!");
    digitalWrite(BuilInLed, HIGH);
    delay(100);
    digitalWrite(BuilInLed, LOW);
    delay(100);
  }

  /*DEBUGGING FOR IMU SENSOR*/
  /**
  Serial.print("YPR:  ");
  Serial.print(yaw);
  Serial.print("\t");
  Serial.println(pitch);
  Serial.print("\t");
  Serial.println(roll);
  **/

  /*Checking box has falled*/
  if( ( abs(pitch)>tiltAngle ) || ( abs(roll)>tiltAngle ) )
  {
    Serial.println("Box has fallen down");
    digitalWrite(BuilInLed, HIGH);
    delay(500);
    digitalWrite(BuilInLed, LOW);
    delay(500);
  }
}



