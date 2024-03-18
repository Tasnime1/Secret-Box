/************************************************************************************************
*            FILE: MPU6050.H
*          DRIVER: MPU6050
*     DESCRIPTION: HEADER file for all MPU6050-related functions prototypes and constants
*          Author: Tasneem Mansour.
*         Version: v1
*            Date: 9.3.2024
*
************************************************************************************************/

#ifndef MPU6050_H
#define MPU6050_H


/*- INCLUDES
************************************************************************************************/
#include <Arduino.h>
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include "Wire.h"
#endif


/*- CONSTANTS
************************************************************************************************/
#define EXTERNAL_INTERRUPT15 15  // used for MPU6050 interrupt signal; attached to GPIO18 on ESP32

/*- ISR attached to pin2|ExInt0
************************************************************************************************/

void dmpDataReady();


/*- FUNCTIONS PROTOTYPES
************************************************************************************************/

//Settung up DMP of MPU6050; Digital Motion Processor, provides accurate readings of accelerations, angles...etc
void mpu_setup();
//Function to constantly update mpu readings from DMP
void mpu_update();
void mpu_clearBuffer();

//Returning required angles to be input for PID
float return_yaw();   //around Z
float return_pitch(); //around Y
float return_roll(); //around X


#endif /* MPU6050_H */