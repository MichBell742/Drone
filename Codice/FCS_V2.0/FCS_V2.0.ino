#include <RF24.h>
#include <RF24_config.h>
#include <nRF24L01.h>
#include <printf.h>

//pin dei motori tutti devono essere PWM
#define pinMotore1 5
#define pinMotore2 6
#define pinMotore3 9
#define pinMotore4 10

int val;
int inserisci = 0;

long tempoPassato = millis();

#define CE_PIN 7
#define CSN_PIN 8
// instantiate an object for the nRF24L01 transceiver
RF24 radio(CE_PIN, CSN_PIN);

uint8_t address[6] = { "1Node" };  //frequenza di comunicazione

int messaggio[4] = {0, 0, 0, 0};  //Attenzione è stato modificato in int - valori da 0 a 1023 che vengono inviati dal Joystick

void setup() {
  Serial.begin(115200);

  pinMode(pinMotore1, OUTPUT);
  pinMode(pinMotore2, OUTPUT);
  pinMode(pinMotore3, OUTPUT);
  pinMode(pinMotore4, OUTPUT);

  if (!radio.begin()) {
    while (true) { Serial.println(F("radio hardware is not responding!!")); }  // hold in infinite loop
  }

  radio.setPALevel(RF24_PA_LOW);

  radio.openReadingPipe(1, address[0]);

  radio.startListening();

  start(185); //attiva le eliche del drone
}

void start(int motori) {
  int assegna = 124;
  analogWrite(pinMotore1, assegna);
  analogWrite(pinMotore2, assegna);
  analogWrite(pinMotore3, assegna);
  analogWrite(pinMotore4, assegna);
  delay(2000);
  for (assegna; assegna < motori; assegna++) {
    analogWrite(pinMotore1, assegna);
    analogWrite(pinMotore2, assegna);
    analogWrite(pinMotore3, assegna);
    analogWrite(pinMotore4, assegna);
    delay(30);
  }
}

void loop() {
  if (radio.available()) {
    radio.read(messaggio, sizeof(messaggio));
  }
  //movimento su asse Z
  //messaggio[0] corrisponde alla X del primo joystick
  if(messaggio[0]>185 && messaggio[0]<250){
    movimentiAsseZ(messaggio[0],messaggio[0],messaggio[0],messaggio[0]);
  }
  //messaggio[1] corrisponde alla Y del primo joystick
  if(messaggio[1]<505){ //diamo uno spazio di 7 cosicche da evitare problemi
    rotazioneAsseX();
  }else if(messaggio[1]<519){
    rotazioneAsseX();
  }
}

void movimentiAsseZ(int motore1, int motore2, int motore3, int motore4) {
  analogWrite(pinMotore1, motore1);
  analogWrite(pinMotore2, motore2);
  analogWrite(pinMotore3, motore3);
  analogWrite(pinMotore4, motore4);
}

void rotazioneAsseX(String verso){
  //codice per ruotare il drone
}