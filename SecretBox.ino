/************************************************************************************************
*            FILE: LILO
*          DRIVER: ARDUINO
*     DESCRIPTION: Main (.ino) file where all the program starts.
*          Author: Tasneem Mansour.
*         Version: v1
*            Date: 9.3.2024
*
************************************************************************************************/


/*- INCLUDES
************************************************************************************************/
#include "App.h"

void setup() {
  Serial.begin(115200);
  App_init();
}

void loop() {
  //Driver Function where all program logic runs
  App_start();
}
