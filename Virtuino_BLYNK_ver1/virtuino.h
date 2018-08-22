#include "Virtuino_ESP_WifiServer.h"

WiFiServer server(8000);
Virtuino_ESP_WifiServer virtuino(&server);

int flaga_led1 = 1;
void virtuino_timer() {
  flaga_led1 = !flaga_led1;
  virtuino.vDigitalMemoryWrite(0, flaga_led1);
}

void virtuino_setup() {
  akcja.attach(1, 2000, virtuino_timer);

  virtuino.DEBUG = true;  virtuino.DEBUG1 = false;

  virtuino.password = "1234";                  // Use only numbers or text characters
  server.begin();   Serial.println("VIRTUINO Server started");
}

void virtuino_akcja() {
  virtuino.run();
}

int getTextID(){
  if (virtuino.textReceivedCommandBuffer.length()>5) {
    char c= virtuino.textReceivedCommandBuffer.charAt(3);
    return ((uint8_t) c)-48; 
  }
  return -1;
}





/* Virtuino WeMos ESP8266 web server and WiFi access point example No1  Created by Ilias Lamprou
  Open the Virtuino library file: VirtuinoESP.h,  enable the line #define WEMOS_D1_MINI_PRO and disable the other boards
*/
/*========= VirtuinoBluetooth Class methods
   vPinMode(int pin, int state)                                  set pin as digital OUTPUT or digital INPUT.  (Insteed default pinMode method

  ========= Virtuino General methods  do sprawdzenia
   void vDigitalMemoryWrite(int digitalMemoryIndex, int value)   write a value to a Virtuino digital memory   (digitalMemoryIndex=0..31, value range = 0 or 1)
   int  vDigitalMemoryRead(int digitalMemoryIndex)               read  the value of a Virtuino digital memory (digitalMemoryIndex=0..31, returned value range = 0 or 1)
   void vMemoryWrite(int analogMemoryIndex, float value)         write a value to Virtuino float memory       (memoryIndex=0..31, value range as float value)
   float vMemoryRead(int analogMemoryIndex)                      read the value of  Virtuino analog memory    (analogMemoryIndex=0..31, returned value range = 0..1023)
   run()                                                         neccesary command to communicate with Virtuino android app  (on start of void loop)
   int getPinValue(int pin)                                      read the value of a Pin. Usefull for PWM pins
   void vDelay(long milliseconds);                               Pauses the program (without block communication) for the amount of time (in miliseconds) specified as parameter
   void clearTextBuffer();                                       Clear the text received text buffer
   int textAvailable();                                          Check if there is text in the received buffer
   String getText(byte ID);                                      Read the text from Virtuino app
   void sendText(byte ID, String text);                          Send text to Virtuino app
*/
/*========= Virtuino General methods

   void vDigitalMemoryWrite(int digitalMemoryIndex, int value)       write a value to a Virtuino digital memory   (digitalMemoryIndex=0..31, value range = 0 or 1)
   int  vDigitalMemoryRead(int digitalMemoryIndex)                   read  the value of a Virtuino digital memory (digitalMemoryIndex=0..31, returned value range = 0 or 1)
   void vMemoryWrite(int memoryIndex, float value);                  write a value to Virtuino memory             (memoryIndex=0..31, value range as float value)
   float vMemoryRead(int memoryIndex);                               read a value of  Virtuino memory             (memoryIndex=0..31, returned a float value
   run();                                                            neccesary command to communicate with Virtuino android app  (on start of void loop)
   int getPinValue(int pin);                                         read the value of a Pin. Usefull to read the value of a PWM pin
   long lastCommunicationTime;                                       Stores the last communication with Virtuino time
*/

/*
  //------ avoid to use delay() function in your code
  virtuino.vDelay(5000);        // wait 5 seconds

  porty nie są automatycznie ustawiane przez aplikację
  pinMode(D4,OUTPUT);             // On Virtuino panel add a switch to pin D4 to enable or disable the board led
  pinMode(D5,INPUT);            // connect a switch.  On Virtuino panel add a Led to pin D5


     //----- example 1 how to read a Text Command from virtuino
   if (virtuino.textAvailable()){          // check for a new received TEXT Command from Virtuino app
     String text= virtuino.getText(0);     // Read the text command from the  text Channel ID = 0
     //String text2= virtuino.getText(2);  // Read the text command from the  Channel ID ID = 2
     Serial.println("Text of ID 0="+text); // Print the command on serial display
     virtuino.clearTextBuffer();           // Clear all Text Commands from buffer

     if (text.equals("0")) {
        digitalWrite(D4,0);                                // do something
     }
     else
       if (text.equals("1")){
          digitalWrite(D4,1);                            // do something
          virtuino.sendText(1,"Hello Virtuino the pin is 1");   // On Virtuino app add a terminal display to Text Channel 1 to get this message
       }
   }


      //----- example 2 how to send a Text Command to virtuino

   byte pinState=digitalRead(D5);       // read Pin 6 state
   if (pinState!=storedPinState) {     // check if pin value has changed
     delay(100);                       // wait 100 millis
      if (digitalRead(D5)==1) virtuino.sendText(1,"Hello Virtuino the pin D5 is 1");
      else virtuino.sendText(1,"Now the pin D5 is 0");
      storedPinState=pinState;
   }


  // Use virtuino.vPinMode instead default pinMode method for digital input or digital output pins.
  //pinMode(13,OUTPUT);
    virtuino.vPinMode(13,OUTPUT);                               // Don't use vPinMode for PWM pins, or pins that their values change many times per second
                                                                // Every time the value of a vPinMode  pin is changed the virtuino library sends a message and inform virtuino about the pin value.
                                                                // If an PWM pin is declared as vPinMode pin the arduino will continuously try  to send data to android device because the value of a pwm pin changes constantly
  // Use virtuino.vPinMode instead default pinMode method for digital input or digital output pins.
  virtuino.vPinMode(12,OUTPUT);    // Connect a LED to pin 12 as digital output
  virtuino.vPinMode(5,INPUT);      // Connect a switch or button to pin as digtial input

                                   // Don't use vPinMode for PWM pins, or pins that their values change many times per second
                                   // Every time the value of a vPinMode  pin is changed the virtuino library sends a message and inform virtuino about the pin value.
                                   // If an PWM pin is declared as vPinMode pin the arduino will continuously try  to send data to android device because the value of a pwm pin changes constantly
  pinMode(10,OUTPUT);              // Connect a LED to pin 10 as analog output.

                                   // Connect a potentiometer to analog pin A0

     if (value == HIGH) {
        virtuino.vDigitalMemoryWrite(1,LOW);            // disable the virtual memory value DV1.
    }
    else {
      virtuino.vDigitalMemoryWrite(1,HIGH);             // enable the virtual memory value DV1
    }

       //----- example 1 how to read a Text Command from virtuino
   if (virtuino.textAvailable()){          // check if exist a TEXT Command from Virtuino app
     String text= virtuino.getText(0);     // Read the command by Channel ID
     //String text2= virtuino.getText(2);  // Read the command by Channel ID
     Serial.println("Text of ID 0="+text); // Print the command to serial display
     virtuino.clearTextBuffer();           // Clear all Text Commands from buffer

     if (text.equals("0")) {
        digitalWrite(13,0);                                // do something
     }
     else
       if (text.equals("1")){
          digitalWrite(13,1);                            // do something
           virtuino.sendText(1,"Hello Virtuino the pin is 1");        // Write text to text channel 1
       }
   }


   //--------------------------------------------------------
   //----- example 2 how to send a Text Command to virtuino
   byte pinState=digitalRead(6);       // read Pin 6 state
   if (pinState!=storedPinState) {     // check if pin value has changed
      virtuino.vDelay(100);                       // wait 100 millis
      if (digitalRead(6)==1) virtuino.sendText(1,"Hello Virtuino the pin is 1");
      else virtuino.sendText(1,"Now the pin is 0");
      storedPinState=pinState;
   }





*/
