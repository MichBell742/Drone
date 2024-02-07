#include <RF24.h>
#include <RF24_config.h>
#include <nRF24L01.h>
#include <printf.h>

int val;
int inserisci=0;
long tempoPassato=millis();

#define CE_PIN 7
#define CSN_PIN 8
// instantiate an object for the nRF24L01 transceiver
RF24 radio(CE_PIN, CSN_PIN);

uint8_t address[6] = {"1Node"};

float messaggio[4]={0, 0, 0, 0};

void setup() {
  Serial.begin(115200);
  pinMode(9, OUTPUT);

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
    /*          
    Serial.print(F("Received "));
    Serial.print(bytes);  // print the size of the payload
    Serial.print(F(" bytes on pipe "));
    Serial.print(pipe);  // print the pipe number
    Serial.print(F(": "));
    for(int i=0; i< 4; i++){
      Serial.println(messaggio[i]);
    }*/
    Serial.println(messaggio[0]);
  }
  if(inserisci <= val){
    if(millis()-tempoPassato>10){
      tempoPassato=millis(); 
      inserisci++;
    }
  }else if(inserisci >= val){
    inserisci--;
  }
  val = messaggio[0];
  val = map(val, 0, 1023, 124, 250);
  analogWrite(9, inserisci);
}
