#define BLYNK_TEMPLATE_ID "TMPL29IO9xEIK"
#define BLYNK_TEMPLATE_NAME "Domótica Hogar Prueba"
#define BLYNK_AUTH_TOKEN "pSQg5qM_izTycYxLnpdVCWwiF07PdCYJ"

// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "DylanEsp32";
char pass[] = "Dylanesp32";

BlynkTimer timer;

#define button1_pin 5
#define button2_pin 18
#define button3_pin 4
#define button4_pin 16
#define button5_pin 13
#define button6_pin 2
#define button7_pin 17
#define button8_pin 15

#define relay1_pin 33
#define relay2_pin 27
#define relay3_pin 26
#define relay4_pin 25
#define relay5_pin 32
#define relay6_pin 34
#define relay7_pin 34
#define relay8_pin 19

int relay1_state = 0;
int relay2_state = 0;
int relay3_state = 0;
int relay4_state = 0;
int relay5_state = 0;
int relay6_state = 0;
int relay7_state = 0;
int relay8_state = 0;

//Change the virtual pins according to the rooms
#define button1_vpin    V1
#define button2_vpin    V2
#define button3_vpin    V3 
#define button4_vpin    V4
#define button5_vpin    V5
#define button6_vpin    V6
#define button7_vpin    V7 
#define button8_vpin    V8

//------------------------------------------------------------------------------
// Parte agregada para que el relay 8 cuando se encienda dure 1 minuto encendido
// y luego se apague
unsigned long relay7StartTime = 0;
const unsigned long relay7Duration = 60000;

const int buzzer = 21;
const int motionSensor = 22;

#define timeSeconds 10  // Declaración de timeSeconds

// Timer: Auxiliary variables
unsigned long now = millis();
unsigned long lastTrigger = 0;
unsigned long relay5StartTime = 0;
const unsigned long relay5Duration = 60000;
boolean startTimer = false;
boolean motion = false;

void detectsMovement() {
  //Blynk.notify("¡Movimiento detectado!"); // Envía una notificación a la aplicación Blynk
  digitalWrite(led, HIGH);
  startTimer = true;
  lastTrigger = millis();
  Serial.println("yes");
  
}
//------------------------------------------------------------------------------
// This function is called every time the device is connected to the Blynk.Cloud
// Request the latest state from the server
BLYNK_CONNECTED() {
  Blynk.syncVirtual(button1_vpin);
  Blynk.syncVirtual(button2_vpin);
  Blynk.syncVirtual(button3_vpin);
  Blynk.syncVirtual(button4_vpin);
  Blynk.syncVirtual(button5_vpin);
  Blynk.syncVirtual(button6_vpin);
  Blynk.syncVirtual(button7_vpin);
  Blynk.syncVirtual(button8_vpin);
}

//--------------------------------------------------------------------------
// This function is called every time the Virtual Pin state change
//i.e when web push switch from Blynk App or Web Dashboard
BLYNK_WRITE(button1_vpin) {
  relay1_state = param.asInt();
  digitalWrite(relay1_pin, relay1_state);
}
//--------------------------------------------------------------------------
BLYNK_WRITE(button2_vpin) {
  relay2_state = param.asInt();
  digitalWrite(relay2_pin, relay2_state);
}
//--------------------------------------------------------------------------
BLYNK_WRITE(button3_vpin) {
  relay3_state = param.asInt();
  digitalWrite(relay3_pin, relay3_state);
}
//--------------------------------------------------------------------------
BLYNK_WRITE(button4_vpin) {
  relay4_state = param.asInt();
  digitalWrite(relay4_pin, relay4_state);
}
//--------------------------------------------------------------------------
BLYNK_WRITE(button5_vpin) {
  relay5_state = param.asInt();
  digitalWrite(relay5_pin, relay5_state);
}
//--------------------------------------------------------------------------
BLYNK_WRITE(button6_vpin) {
  relay6_state = param.asInt();
  digitalWrite(relay6_pin, relay6_state);
}
//--------------------------------------------------------------------------
BLYNK_WRITE(button7_vpin) {
  relay7_state = param.asInt();
  digitalWrite(relay7_pin, relay7_state);
}
//--------------------------------------------------------------------------
BLYNK_WRITE(button8_vpin) {
  relay8_state = param.asInt();
  digitalWrite(relay8_pin, relay8_state);
}
//--------------------------------------------------------------------------

void setup()
{
  // Debug console
  Serial.begin(115200);
  
  
  pinMode(button1_pin, INPUT_PULLUP);
  pinMode(button2_pin, INPUT_PULLUP);
  pinMode(button3_pin, INPUT_PULLUP);
  pinMode(button4_pin, INPUT_PULLUP);
  pinMode(button5_pin, INPUT_PULLUP);
  pinMode(button6_pin, INPUT_PULLUP);
  pinMode(button7_pin, INPUT_PULLUP);
  pinMode(button8_pin, INPUT_PULLUP);
  
  pinMode(relay1_pin, OUTPUT);
  pinMode(relay2_pin, OUTPUT);
  pinMode(relay3_pin, OUTPUT);
  pinMode(relay4_pin, OUTPUT);
  pinMode(relay5_pin, OUTPUT);
  pinMode(relay6_pin, OUTPUT);
  pinMode(relay7_pin, OUTPUT);
  pinMode(relay8_pin, OUTPUT);
  
 
  digitalWrite(relay1_pin, HIGH);
  digitalWrite(relay2_pin, HIGH);
  digitalWrite(relay3_pin, HIGH);
  digitalWrite(relay4_pin, HIGH);
  digitalWrite(relay5_pin, HIGH);
  digitalWrite(relay6_pin, HIGH);
  digitalWrite(relay7_pin, HIGH);
  digitalWrite(relay8_pin, HIGH);
  relay5StartTime = 0; 
  
  pinMode(motionSensor, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(motionSensor), detectsMovement, RISING);
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  Blynk.begin(auth, ssid, pass);
}

void loop() {

  if (digitalRead(motionSensor) == LOW) {
    if (!motion) {
      Serial.println("MOTION DETECTED!!!");
      motion = true;
      digitalWrite(buzzer, HIGH); 
      startTimer = true;
      lastTrigger = millis();
    }
  } else {
    // No hay movimiento
    motion = false;
  }
  
 
  Blynk.run();
  timer.run();
  
  listen_push_buttons();
}


void listen_push_buttons(){
  if(digitalRead(button1_pin) == LOW){
    delay(200);
    control_relay(1);
    Blynk.virtualWrite(button1_vpin, relay1_state); 
  }
  else if (digitalRead(button2_pin) == LOW){
    delay(200);
    control_relay(2);
    Blynk.virtualWrite(button2_vpin, relay2_state); 
  }
  else if (digitalRead(button3_pin) == LOW){
    delay(200);
    control_relay(3);
    Blynk.virtualWrite(button3_vpin, relay3_state);
  }
  else if (digitalRead(button4_pin) == LOW){
    delay(200);
    control_relay(4);
    Blynk.virtualWrite(button4_vpin, relay4_state); 
  }
  else if (digitalRead(button5_pin) == LOW){
    delay(200);
    control_relay(5);
    Blynk.virtualWrite(button5_vpin, relay5_state); 
  }
  else if (digitalRead(button6_pin) == LOW){
    delay(200);
    control_relay(6);
    Blynk.virtualWrite(button6_vpin, relay6_state); 
  else if (digitalRead(button7_pin) == LOW){
    delay(200);
    control_relay(7);
    Blynk.virtualWrite(button7_vpin, relay7_state); 
  }
  else if (digitalRead(button8_pin) == LOW){
    delay(200);
    control_relay(8);
    Blynk.virtualWrite(button8_vpin, relay8_state); 
  }
}

void control_relay(int relay){
  if(relay == 1){
    relay1_state = !relay1_state;
    digitalWrite(relay1_pin, relay1_state);
    Serial.print("Relay1 State = ");
    Serial.println(relay1_state);
    delay(50);
  }
  else if(relay == 2){
    relay2_state = !relay2_state;
    digitalWrite(relay2_pin, relay2_state);
    delay(50);
  }
  else if(relay == 3){
    relay3_state = !relay3_state;
    digitalWrite(relay3_pin, relay3_state);
    delay(50);
  }
  else if(relay == 4){
    relay4_state = !relay4_state;
    digitalWrite(relay4_pin, relay4_state);
    delay(50);
  }
  else if(relay == 5){
    relay5_state = !relay5_state;
    if (relay5StartTime > 0) {
    unsigned long currentTime = millis();
    if (currentTime - relay5StartTime >= relay5Duration) {
    // Ha pasado el tiempo establecido, apaga el relé 5 y reinicia el temporizador
    digitalWrite(relay5_pin, HIGH);  // Apaga el relé 5
    relay5StartTime = 0;  // Reinicia el temporizador
  }
}
    digitalWrite(relay5_pin, relay5_state);
    delay(50);
  }
  else if(relay == 6){
    relay6_state = !relay6_state;
    digitalWrite(relay6_pin, relay6_state);
    delay(50);
  }
  else if(relay == 7){
    relay7_state = !relay7_state;
    digitalWrite(relay7_pin, relay7_state);
    delay(50);
  }
  else if(relay == 8){
    relay8_state = !relay8_state;
    digitalWrite(relay8_pin, relay8_state);
    delay(50);
  }
}
