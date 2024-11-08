const int bombaPin = 16;  // Escolha o pino que controla o relé da bomba
const int led1 = 15;
const int led2 = 2;
const int lde3 = 4;







void setup() {
  Serial.begin(9600);   // Configura a taxa de transmissão do Bluetooth
  pinMode(bombaPin, OUTPUT);
  digitalWrite(bombaPin, LOW);  // Começa com a bomba desligada
}

void loop() {
  if (Serial.available()) {
    char comando = Serial.read();  // Lê o comando do Bluetooth
    if (comando == 'L') {
      digitalWrite(bombaPin, HIGH); // Liga a bomba
    } else if (comando == 'D') {
      digitalWrite(bombaPin, LOW);  // Desliga a bomba
    }
  }
}
