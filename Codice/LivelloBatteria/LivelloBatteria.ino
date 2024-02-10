



/*
//avendo un'alimentazione esterna
//ricordarsi di creare un separatore di tensione con due resistenze messe insieme in modo
//tale che la tensione immessa in arduino non superino i 5 volt
float tMax=9000;//voltaggio massimo della batteria
float tAttuale=0.0;//voltaggio della batteria attuale

void setup() {
  pinMode(A7, INPUT);
  Serial.begin(9600); 
}

void loop() {
  tAttuale=analogRead(A7);
  tAttuale=map(tAttuale, 0, 1023, 0, tMax)/1000.0;
  Serial.println(tAttuale);
  if(tAttuale<4.5){
    accendiLed();
  }else{
    spegniLed();
  }
}*/

//avendo alimentazione interna

#include <CPUVolt.h>

float voltmV=0;
float voltPerc=0;

void setup() {
  pinMode(A7, INPUT);
  pinMode(9, OUTPUT);
  Serial.begin(9600); 
}

void loop() {
  voltmV=readVcc()/1000.00;
  Serial.println("Volt: ");
  Serial.println(voltmV, 1);
  voltPerc=readPercent(4500, 5000);
  Serial.println("Percentuale: ");
  Serial.println(voltPerc);
  if(voltmV<4.5){
    accendiLed();
  }else{
    spegniLed();
  }
  delay(100);
}
void accendiLed(){
  digitalWrite(9, HIGH);
}
void spegniLed(){
  digitalWrite(9, LOW);
}