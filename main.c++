#include <BluetoothSerial.h>
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run make menuconfig to and enable it
#endif
BluetoothSerial SerialBT;
int valorRecebido;

// Definir pinos
const int led1 = 15;
const int led2 = 2;
const int led3 = 4;
const int sensorMovimento = 16;
const int sensorUmidade = 34;
const int bomba = 17;
const int buzzer = 5;
char comando = '0';

void setup() {
  Serial.begin(9600);
  SerialBT.begin("Casa automática");
  Serial.println("O dispositivo já pode ser pareado!");
  
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(sensorMovimento, INPUT);
  pinMode(sensorUmidade, INPUT);
  pinMode(bomba, OUTPUT);
  pinMode(buzzer, OUTPUT);


  // Buzzer apita ao ligar o sistema
  digitalWrite(buzzer, HIGH);  
  delay(500);                  
  digitalWrite(buzzer, LOW); 
}

void loop() {

  //Realiza leitura do Bluetooth
  if (Serial.available() > 0) {
   comando = Serial.read();
  
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


  if (comando == 'A') {
      //Controle Leds
      digitalWrite(led1, HIGH); // Liga LED1
    } else if (comando == 'a') {
      digitalWrite(led1, LOW);  // Desliga LED1
    } else if (comando == 'B') {
      digitalWrite(led2, HIGH); // Liga LED2
    } else if (comando == 'b') {
      digitalWrite(led2, LOW);  // Desliga LED2
    } else if (comando == 'C') {
      digitalWrite(led3, HIGH); // Liga LED3
    } else if (comando == 'c') {
      digitalWrite(led3, LOW);  // Desliga LED3
    }
      //Controle buzzer
      else if (comando == 'P') {
      digitalWrite(buzzer, HIGH); // Liga o buzzer
    } else if (comando == 'p') {
      digitalWrite(buzzer, LOW);  // Desliga o buzzer
    }

      // Controle da Bomba
      else if (comando == 'L') {
      digitalWrite(bomba, HIGH); // Liga a bomba
    } else if (comando == 'D') {
      digitalWrite(bomba, LOW);  // Desliga a bomba
    }

  }
}


