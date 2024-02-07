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
}
