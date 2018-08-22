#define BLYNK_MSG_LIMIT 0

#include <Timers.h> //  my favorite timer 
Timers <7> akcja; //


#include "virtuino.h"
#include "blynk.h" //obsługa BLYNKa
#include "test.h"


void setup() {

  Serial.begin(115200);  delay(10);

  blynksetup(); // setup biblioteki BLYNK
  virtuino_setup();
  test_setup();

  digitalWrite(2, 1);
}

void loop() {

  akcja.process(); // timer
  virtuino_akcja();
  blynkakcja();    //BLYNK
  test_run();

}



