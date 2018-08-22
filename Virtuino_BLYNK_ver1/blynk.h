const char* ssid = "xxxxxx";
const char* password = "yyyyyyyyy";

/*
  v0 LED kontrolny
  v1 terminal do wyswietlania co dzieje sie wewnatrz
  v6 term on/off
*/
#define _RED        "#FF0000"
#define _GREEN      "#00FF00"
#define _MAGENTA    "#FF00FF"
#define _YELLOW     "#FFFF00"
#define _BLACK      "#000000"
#define _WHITE      "#FFFFFF"
#define _WBLUE      "#00FFFF"
#define _PINK       "#FFB3B3"
#define _OLIVE      "#808000"
#define _BRAU       "#FF8000"
#define _karmin     "#FF0080"
#define _SEE        "#00FF80"
#define _fiolet     "#8000FF"
#define _BLUE       "#0080FF"

char auth[] = "8c6b48c053784dc5a0ab889cf69b4c71";

#define ESP01 1
#define D1MINI 2
int procesor = D1MINI;
#define led_wew   2

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define treconnect 60 // czas miedzy kolejnymi testami łaczności z serwerem BLYNK w sek
int liczreconnect = 10; // licnik czasu testów łącznosci
int printon = 0; // flaga wysyłania danych na monitor
int terminalon = 0; // flaga wysyłania danych na terminal BLYNK

WidgetLED led1(V0); // led w aplikacji wskazujący na połacenie mikroprocesor - aplikacja
WidgetTerminal terminal(V1);

void testconnect() // test łączności z serwerem BLYNK bez blokowania programu głównego GS
{
  if (Blynk.connected()) {
    digitalWrite(led_wew, HIGH); //wskaźnik łączności z serwerem stan wysoki- wyłączenie LEDa
    akcja.updateInterval(2, 2000);
    if (procesor == D1MINI)  Serial.println("connection OK");
    liczreconnect = treconnect;
  } else {
    akcja.updateInterval(2, 0);
    digitalWrite(led_wew, LOW);
    liczreconnect--;
    if (procesor == D1MINI)  Serial.println("connection DOWN");
    if (liczreconnect == 0) {
      Blynk.connect();
      liczreconnect = treconnect;
    }
  }
}

//  digitalWrite(16, !digitalRead(16));
int flaga_led = 1;
void led_timer()
{
  flaga_led = !flaga_led;
  digitalWrite(2, flaga_led);
}

int wskrunAr = 0;
void vLED_timer()//miganie vLED dla kontroli połączenia
{
  wskrunAr = !wskrunAr ;
  if (wskrunAr == 0)led1.off(); else led1.on();
}

void blynk_timer() { //różne rzeczy wykonywane cyklicznie
  testconnect(); // test łączności z serwerem
  vLED_timer();
}

void blynksetup() //nie blokująca procedura połączenia z BLYNK
{
  akcja.attach(0, 3000, blynk_timer); //
  akcja.attach(2, 2000, led_timer);
  
  pinMode(led_wew, OUTPUT); //LED na module
  digitalWrite(led_wew, LOW);
  //stały IP
  Serial.println(""); Serial.println("Connecting to " + String(ssid));
  IPAddress ip(192, 168, 2, 177); IPAddress gateway(192, 168, 2, 1);  IPAddress subnet(255, 255, 255, 0);
  WiFi.config(ip, gateway, subnet);

  WiFi.mode(WIFI_STA);                       // Config module as station only.
  WiFi.begin(ssid, password);

  Blynk.config(auth, IPAddress(192, 168, 2, 111), 8080);
  Blynk.connect();
  if (Blynk.connected()) Blynk.run();  else  Blynk.connect();

  Blynk.setProperty(V0, "color", _BRAU);
  Blynk.virtualWrite(V5, 0);
  Blynk.virtualWrite(V6, 0);
}

void blynkakcja()
{
  if (Blynk.connected()) Blynk.run();
}



BLYNK_WRITE(V6) {
  terminalon = param.asInt();
}
