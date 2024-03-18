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
#include "App.h"


/*- DEFINES
************************************************************************************************/
#define BuilInLed 2
#define tiltAngle 30
#define boxDepth 20

/*- GLOBAL VARIABLES
************************************************************************************************/
float yaw;
float pitch;
float roll;
float distance;

float batteryVoltage;
float batteryPercentage;

struct tm timeinfo;
String timestamp = "";

/*- WI-FI AND NTP SERVER CREDENTIALS
************************************************************************************************/
const char* ssid       = "RAMADAN";
const char* password   = "10102020";

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;

/*- Firebase
************************************************************************************************/
#define REFERENCE_URL "https://thesecretbox-a6d98-default-rtdb.firebaseio.com/"  // Your Firebase project reference url
Firebase firebase(REFERENCE_URL);

//ESP32Time rtc;
ESP32Time rtc(0);  // offset in seconds


/*- FUNCTIONS' DECLARATION
************************************************************************************************/
void App_init(void) {
  /*Initialize MPU6050 sensor*/
  mpu_setup();
  
  /*Initialize Ultrasonic sensor*/
  Ultrasonic_init();

  /*Initialize Built-In LED for debugging purposes*/
  pinMode(BuilInLed, OUTPUT);

  /*Conenct to WI-FI*/
  APP_connectWIFI();

  //APP_disconnectWIFI();
}

/**************************************
/*- DRIVER FUNCTION FOR WHOLE PROGRAM
***************************************/
void App_start(void) {
  /*Getting MPU6050 readings*/
  APP_getMPUreadings();

  /*Checking box has fallen from yaw and pitch readings*/
  APP_checkBoxHasFallen();

  /*Getting Ultrasonic readings*/
  APP_getUltrasonicReading();

  /*Checking box has been opened if distance has changed*/
  APP_checkBoxHasBeenOpened();
  
  /*Checking battery volt and percentage*/
  APP_getBatteryReadings();

}

void APP_getMPUreadings(void)
{
  //frequently update MPU readings
  mpu_update();

  //getting latest inclination angles and distance from sensors
  yaw = return_yaw();
  pitch = return_pitch();
  roll = return_roll();

  /*DEBUGGING FOR IMU SENSOR*/
  Serial.print("YPR:  ");
  Serial.print(yaw);
  Serial.print("\t");
  Serial.println(pitch);
  Serial.print("\t");
  Serial.println(roll);
}

void APP_getUltrasonicReading()
{
  distance = ultrasonic_calc_distance();
  
  /*DEBUGGING FOR ULTRASONIC SENSOR*/
  /*Printing distance to screen*/
  Serial.print("Distance: ");
  Serial.println(distance);
}

void APP_getBatteryReadings(void)
{
  //Calculating battery voltage and percentage
  batteryVoltage = Battery_getBatteryVoltage();
  batteryPercentage = Battery_getBatteryPercentage();
  firebase.setFloat("Battery/Battery Voltage", batteryVoltage);
  firebase.setFloat("Battery/battery Percentage", batteryPercentage);

  /*DEBUGGING FOR BATTERY*/
  /**
  Serial.print("Battery Voltage: ");
  Serial.println(batteryVoltage);

  Serial.print("Battery Percentage: ");
  Serial.print(batteryPercentage);
  Serial.println("%");
  **/

}

void APP_checkBoxHasFallen(void)
{
  /*Checking box has falled*/
  if( ( abs(pitch)>tiltAngle ) || ( abs(roll)>tiltAngle ) )
  {
    Serial.println("Box has fallen down");
    /*Fetch current date and time from NTP*/
    APP_fetchCurrentDateAndTime();
    firebase.pushString("box Fallen", timestamp);

    digitalWrite(BuilInLed, HIGH);
    delay(100);
    digitalWrite(BuilInLed, LOW);
    delay(100);
  }
}

void APP_checkBoxHasBeenOpened()
{
  /*Checking box has been opened*/
  if(distance>boxDepth)
  {
    Serial.println("Box has been opened");
    /*Fetch current date and time from NTP*/
    APP_fetchCurrentDateAndTime();
    firebase.pushString("box opened", timestamp);

    digitalWrite(BuilInLed, HIGH);
    delay(100);
    digitalWrite(BuilInLed, LOW);
    delay(100);
  }
}

/*API to connect to Wifi*/
void APP_connectWIFI()
{
  //Connect to WiFi to retrieve current data and time from NTP
  //Network Time Protocol
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  Serial.println(" CONNECTED");
  
}

/*API to disconnect from Wifi*/
void APP_disconnectWIFI()
{
  //Disconnect WiFi as it's no longer needed
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
}

/*Fetch current date and time from NTP*/
void APP_fetchCurrentDateAndTime()
{
  //Init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  
  if (getLocalTime(&timeinfo))
  {
    rtc.setTimeStruct(timeinfo); 
  }
  /*Getting timestamp*/
  timestamp = rtc.getDateTime(true);
  //Serial.println(timestamp);
}




