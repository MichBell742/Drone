#include <RF24.h>
#include <RF24_config.h>
#include <nRF24L01.h>
#include <printf.h>

#define pinAnalogicoUnoAsseX A0
#define pinAnalogicoUnoAsseY A1
#define pinAnalogicoDueAsseX A2
#define pinAnalogicoDueAsseY A3

#define CE_PIN 7
#define CSN_PIN 8
// instantiate an object for the nRF24L01 transceiver
RF24 radio(CE_PIN, CSN_PIN);


uint8_t address[6] = {"1Node"};

float messaggio[4];
int convertito=0;


void setup() {
  Serial.begin(115200);
  

  if (!radio.begin()) {
    Serial.println(F("radio hardware is not responding!!"));
    while (true) {}  // hold in infinite loop
  }

  radio.setPALevel(RF24_PA_LOW);

  radio.openWritingPipe(address[0]);

  radio.stopListening();

}


void loop() {
  
  messaggio[0]=converti(analogRead(pinAnalogicoUnoAsseX));
  messaggio[1]=analogRead(pinAnalogicoUnoAsseY);
  messaggio[2]=converti(analogRead(pinAnalogicoDueAsseX));
  messaggio[3]=converti(analogRead(pinAnalogicoDueAsseY));

  for(int i=0; i< 4; i++){
    Serial.println(messaggio[i]);
  }

  bool report = radio.write(messaggio, sizeof(messaggio));

  if(report){
    Serial.println("------Trasmissione riuscita");
  }else {
    Serial.println("!!!!!!Trasmissione non riuscita");
  }
  delay(50);
}
int converti(int analogico){
  convertito=map(analogico, 0, 1023, 124, 250);
  return convertito;
}