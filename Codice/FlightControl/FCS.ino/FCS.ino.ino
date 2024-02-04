#include <RF24.h>
#include <RF24_config.h>
#include <nRF24L01.h>
#include <printf.h>

int val;

#define CE_PIN 7
#define CSN_PIN 8
// instantiate an object for the nRF24L01 transceiver
RF24 radio(CE_PIN, CSN_PIN);

uint8_t address[][6] = { "1Node", "2Node" };

float messaggio[4];

void setup() {
  Serial.begin(115200);

  pinMode(9, OUTPUT);

  if (!radio.begin()) {
    Serial.println(F("radio hardware is not responding!!"));
    while (true) {}  // hold in infinite loop
  }else{
    Serial.println("pronto");
  }
  radio.setPALevel(RF24_PA_MAX);

  radio.setPayloadSize(sizeof(messaggio));

  radio.openWritingPipe(address[1]);

  radio.openReadingPipe(1, address[0]);

  radio.startListening();
}

void loop() {
  uint8_t pipe;
  if (radio.available(&pipe)) {              // is there a payload? get the pipe number that recieved it
    uint8_t bytes = radio.getPayloadSize();  // get the size of the payload
    radio.read(&messaggio, bytes);
    val = messaggio[0];// fetch payload from FIFO
    val = map(val, 0, 1023, 124, 250);
    Serial.println(val);   /*          
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
  
  analogWrite(9, val);
}
