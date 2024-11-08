// Definir pinos
const int led1 = 15;
const int led2 = 2;
const int led3 = 4;
const int sensorMovimento = 16;
const int sensorUmidade = 34;
const int bomba = 17;

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(sensorMovimento, INPUT);
  pinMode(sensorUmidade, INPUT);
  pinMode(bomba, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Leitura dos sensores
  int movimento = digitalRead(sensorMovimento);
  int umidade = analogRead(sensorUmidade);

  pinMode(bombaPin, OUTPUT);
  digitalWrite(bombaPin, LOW);  // Começa com a bomba desligada


  //teste para sensor de umidade
  if (umidade < 1000) {
    digitalWrite(bomba, HIGH);  // Liga a bomba se a umidade estiver baixa
  } else {
    digitalWrite(bomba, LOW);
  }




  if (Serial.available()) {
    char comando = Serial.read();  // Lê o comando do Bluetooth
    if (comando == 'L') {
      digitalWrite(bomba, HIGH); // Liga a bomba
    } else if (comando == 'D') {
      digitalWrite(bomba, LOW);  // Desliga a bomba
    }
  }
}


