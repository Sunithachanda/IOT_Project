#define BLYNK_TEMPLATE_ID "TMPL26V4fGv5q"
#define BLYNK_TEMPLATE_NAME "Test"
#define BLYNK_AUTH_TOKEN "XEHxNF_Ur1Nt2p7wB5B20dNI1ZUwj34P"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

int duration1 = 0;
int distance1 = 0;
int duration2 = 0;
int distance2 = 0;
int dis1 = 0;
int dis2 = 0;
int dis_new1 = 0;
int dis_new2 = 0;
int entered = 0;
int left = 0;
int inside = 0;
#define LED 2
#define PIN_TRIG1 15
#define PIN_ECHO1 14
#define PIN_TRIG2 13
#define PIN_ECHO2 12
BlynkTimer timer;

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Wokwi-GUEST";   // your network SSID (name)
char pass[] = "";
#define BLYNK_PRINT Serial

long get_distance1() {
  // Start a new measurement:
  digitalWrite(PIN_TRIG1, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG1, LOW);

  // Read the result:
  duration1 = pulseIn(PIN_ECHO1, HIGH);
  distance1 = duration1 / 58;
  return distance1;
}

long get_distance2() {
  // Start a new measurement:
  digitalWrite(PIN_TRIG2, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG2, LOW);

  // Read the result:
  duration2 = pulseIn(PIN_ECHO2, HIGH);
  distance2 = duration2 / 58;
  return distance2;
}

void myTimer() {
  Serial.println("100");
  dis_new1 = get_distance1();
  dis_new2 = get_distance2();
  if (dis1 != dis_new1 || dis2 != dis_new2){
    Serial.println("200");
    if (dis1 < dis2){
      Serial.println("Enter loop");
      entered = entered + 1;
      inside = inside + 1;
      digitalWrite(LED, HIGH);
      Blynk.virtualWrite(V0, entered);
      Blynk.virtualWrite(V2, inside);
      dis1 = dis_new1;
      delay(1000);
      digitalWrite(LED, LOW);
    }
    if (dis1 > dis2){
      Serial.println("Leave loop");
      left = left + 1;
      inside = inside - 1;
      Blynk.virtualWrite(V1, left);
      Blynk.virtualWrite(V2, inside);
      dis2 = dis_new2;
      delay(1000);
    }

  }
 
  
}

 void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  pinMode(PIN_TRIG1, OUTPUT);
  pinMode(PIN_ECHO1, INPUT);
  pinMode(PIN_TRIG2, OUTPUT);
  pinMode(PIN_ECHO2, INPUT);
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 8080);
  timer.setInterval(1000L, myTimer);

}

void loop() {
  Blynk.run();
  timer.run();
}