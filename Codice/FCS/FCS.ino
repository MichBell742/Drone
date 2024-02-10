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
int inserisci=0;
//OUTPUT che andranno ai motori va da 124 a 250
int motore1=0;
int motore2=0;
int motore3=0;
int motore4=0;

long tempoPassato=millis();

#define CE_PIN 7
#define CSN_PIN 8
// instantiate an object for the nRF24L01 transceiver
RF24 radio(CE_PIN, CSN_PIN);

uint8_t address[6] = {"1Node"}; //frequenza di comunicazione

float messaggio[4]={0, 0, 0, 0}; //valori da 0 a 1023 che vengono inviati dal Joystick

void setup() {
  Serial.begin(115200);

  pinMode(pinMotore1, OUTPUT);
  pinMode(pinMotore2, OUTPUT);
  pinMode(pinMotore3, OUTPUT);
  pinMode(pinMotore4, OUTPUT);

  if (!radio.begin()) {
    while (true) {Serial.println(F("radio hardware is not responding!!"));}  // hold in infinite loop
  }

  radio.setPALevel(RF24_PA_LOW);

  radio.openReadingPipe(1, address[0]);

  radio.startListening();
}

void loop() {
  uint8_t pipe;
  if (radio.available(&pipe)) {          // is there a payload? get the pipe number that recieved it
    uint8_t bytes = radio.getPayloadSize();  // get the size of the payload
    radio.read(messaggio, sizeof(messaggio));
  }

  if(inserisci <= val){
    if(millis()-tempoPassato>10){ //aumentiamo di uno ogni 10 millis cosicché si diminuisce il rischio di blocco del motore
      tempoPassato=millis(); 
      inserisci++;
    }
  }else if(inserisci >= val){
    inserisci--;
  }
  val = messaggio[0];
  val = map(val, 0, 1023, 124, 250);
  scriviIn(9, inserisci);
  scriviIn(10, inserisci);
  Serial.println(inserisci);
}