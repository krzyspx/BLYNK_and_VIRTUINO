
#define przyc1 4
#define przyc2 5

#define led_bialy 12 //  led jak odbiornik 1
#define led_blue  14  //  odbiornik 2

BLYNK_WRITE(V10) {
  int x = param.asInt();
  virtuino.vDigitalMemoryWrite(10, x);
}
BLYNK_WRITE(V12) {
  String s = param.asStr();
  virtuino.sendText(0, s);
}
BLYNK_WRITE(V13) {
  int x = param.asInt();
  virtuino.vMemoryWrite(13, x);
}

int     counter;
void v1_timer() {
  long x =  random(100);
  virtuino.vMemoryWrite(2, x);   //----  Write  to virtual pin 2
  Blynk.virtualWrite(V14, x);
  long y =  50 + random(50);
  virtuino.vMemoryWrite(3, y);   //----  Write  to virtual pin 3
  long t = millis();      // read the time
  counter++;
  if (counter > 20) counter = 0;
  virtuino.vMemoryWrite(4, counter);     // write counter to virtual pin V4
  // Serial.println (".............................licznik" + String(counter) + " v10 " + String(v10) + " stv10 " + String(stv10));


  String s = ("Hello " + String(x));
  // virtuino.sendText(0, s);

}

int v10 = 0;
int stv10 = 0;
int v13 = 0;
int stv13 = 0;

void read_vD10() {
  v10 = virtuino.vDigitalMemoryRead(10);            // Read virtual memory 10 from Virtuino app
  if (v10 == stv10) ; else {
    Serial.println("-------Virtual pin v10 is changed to=" + String(v10));
    if (v10 == 1) digitalWrite(12, 0); else digitalWrite(12, 1);
    if (v10 == 1) Blynk.virtualWrite(V10, 1); else  Blynk.virtualWrite(V10, 0);
    stv10 = v10;
  }
}
void read_v13() {
  v13 = virtuino.vMemoryRead(13);
  if (v13 == stv13) ; else {
    Blynk.virtualWrite(V13, v13);
    stv13 = v13;
  }
}

void read_ch1() {
  if (virtuino.textAvailable()) {         // check for a new received TEXT Command from Virtuino app
    int y = virtuino.textAvailable();
    int z = getTextID();
    String text = virtuino.getText(z);    // Read the text command from the  text Channel ID = z
    Serial.println("Text of ID " + String(z) + "  " + text ); // Print the command on serial display
 
    Blynk.virtualWrite(V11, text);
    virtuino.clearTextBuffer();           // Clear all Text Commands from buffer
  }
}

//-----------------------------------------------setup run
void test_setup() {

  akcja.attach(3, 3000, v1_timer);

  pinMode(led_bialy, OUTPUT); // port jako wyj do odbiornika
  digitalWrite(led_bialy, 1); // wyłączenie odbiornika - wyłącza wysoki stan
  pinMode(led_blue, OUTPUT); //
  digitalWrite(led_blue, 1);

  pinMode(przyc1, INPUT_PULLUP); // port jako wejście z przyciku
  pinMode(przyc2, INPUT_PULLUP);
}


void test_run() {
  read_vD10();
  read_v13();
  read_ch1();
}



