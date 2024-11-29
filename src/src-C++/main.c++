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

void setup() {
  Serial.begin(115200);
  SerialBT.begin("Casa Inteligente");
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

    int sensorState = digitalRead(sensorMovimento);
    if (sensorState == 1) {
        SerialBT.println("1");
    } else {
        SerialBT.println("0");
    }
    delay(500);




  /*

  // Leitura dos sensores
  int movimento = digitalRead(sensorMovimento);
  int umidade = analogRead(sensorUmidade);


  
  digitalWrite(bomba, LOW);  // Começa com a bomba desligada

  teste para sensor de umidade
  if (umidade < 1000) {
    digitalWrite(bomba, HIGH);  // Liga a bomba se a umidade estiver baixa
  } else {
    digitalWrite(bomba, LOW);
  }
*/


  //Realiza leitura do Bluetooth
  if (SerialBT.available() > 0) {
  valorRecebido = (int)SerialBT.read();
  
  if (valorRecebido == 1) {
      //Controle Leds
      digitalWrite(led1, HIGH); // Liga LED1
    } else if (valorRecebido == 0) {
      digitalWrite(led1, LOW);  // Desliga LED1
    } else if (valorRecebido == 2) {
      digitalWrite(led2, HIGH); // Liga LED2
    } else if (valorRecebido == 3) {
      digitalWrite(led2, LOW);  // Desliga LED2
    } else if (valorRecebido == 4) {
      digitalWrite(led3, HIGH); // Liga LED3
    } else if (valorRecebido == 5) {
      digitalWrite(led3, LOW);  // Desliga LED3
    }
      //Controle buzzer
      else if (valorRecebido == 8) {
      digitalWrite(buzzer, HIGH); // Liga o buzzer
    } else if (valorRecebido == 9) {
      digitalWrite(buzzer, LOW);  // Desliga o buzzer
    }

      // Controle da Bomba
      else if (valorRecebido == 6) {
      digitalWrite(bomba, HIGH); // Liga a bomba
    } else if (valorRecebido == 7) {
      digitalWrite(bomba, LOW);  // Desliga a bomba
    }

      // Controle sensor de presença
      else if (valorRecebido == 10) {
      digitalWrite(bomba, HIGH); // Liga a bomba
    } else if (valorRecebido == 11) {
      digitalWrite(bomba, LOW);  // Desliga a bomba
    }

  }
}
