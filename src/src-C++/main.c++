#include <BluetoothSerial.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run make menuconfig to and enable it
#endif

BluetoothSerial SerialBT;

// Variáveis globais
int valorRecebido;              // Armazena o comando recebido via Bluetooth
bool sensorMovimentoAtivo = false; // Controle do estado do sensor de movimento
int valorUmidade;               // Valor analógico lido do sensor de umidade
int umidadePercentual;          // Valor de umidade em porcentagem

// Definir pinos
const int led1 = 15;
const int led2 = 2;
const int led3 = 4;
const int sensorMovimento = 16;
const int sensorUmidade = 34;
const int bomba = 17;
const int buzzer = 5;

void setup() {
  // Inicializações
  Serial.begin(115200);
  SerialBT.begin("Casa Inteligente");
  Serial.println("O dispositivo já pode ser pareado!");

  // Configuração dos pinos
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(sensorMovimento, INPUT);
  pinMode(sensorUmidade, INPUT);
  pinMode(bomba, OUTPUT);
  pinMode(buzzer, OUTPUT);


  //bomba inicia desligada
  digitalWrite(bomba, LOW);

  // Buzzer apita ao iniciar
  digitalWrite(buzzer, HIGH);
  delay(500);
  digitalWrite(buzzer, LOW);
}

void loop() {
  // Comunicação com o Bluetooth
  if (SerialBT.available() > 0) {
    valorRecebido = (int)SerialBT.read();

    // Controle dos LEDs
    if (valorRecebido == 1) {
      digitalWrite(led1, HIGH);
    } else if (valorRecebido == 0) {
      digitalWrite(led1, LOW);
    } else if (valorRecebido == 2) {
      digitalWrite(led2, HIGH);
    } else if (valorRecebido == 3) {
      digitalWrite(led2, LOW);
    } else if (valorRecebido == 4) {
      digitalWrite(led3, HIGH);
    } else if (valorRecebido == 5) {
      digitalWrite(led3, LOW);
    }

    // Controle do sensor de movimento
    else if (valorRecebido == 10) {
      sensorMovimentoAtivo = true;
    } else if (valorRecebido == 11) {
      sensorMovimentoAtivo = false;
    }

    // Controle da bomba
    else if (valorRecebido == 6) {
      digitalWrite(bomba, HIGH); // Liga a bomba
    } else if (valorRecebido == 7) {
      digitalWrite(bomba, LOW);  // Desliga a bomba
    }
  }

  // Envia o estado do sensor de movimento via Bluetooth
  int sensorState = digitalRead(sensorMovimento);
  if (sensorState == 1) {
    SerialBT.println("Não Detectado");
    delay(250);
  } else {
    SerialBT.println("Detectado");
    delay(250);
  }

  // Lógica do sensor de movimento e buzzer
  if (sensorMovimentoAtivo && sensorState == LOW) { // Movimento detectado e sensor ativo
    for (int i = 0; i < 10; i++) {
      digitalWrite(buzzer, HIGH); // Liga o buzzer
      delay(500);                 // Mantém ligado por 0,5 segundos
      digitalWrite(buzzer, LOW);  // Desliga o buzzer
      delay(500);                 // Mantém desligado por 0,5 segundos
    }
  } else {
    digitalWrite(buzzer, LOW); // Garante que o buzzer está desligado se o sensor estiver inativo ou sem detecção
  }

  int valorUmidade = analogRead(sensorUmidade); // Leitura analógica do sensor

  // Converter valor lido para porcentagem (supondo que 0 a 4095 equivale a 0% a 100%)
  int porcentagemUmidade = map(valorUmidade, 0, 4095, 0, 100);

  if (porcentagemUmidade < 40) {
    SerialBT.println("12"); // Envia 12 se estiver abaixo de 40%
  } else {
    SerialBT.println("13"); // Envia 13 se estiver 40% ou acima
  }

  delay(1000); // Intervalo de envio

}
