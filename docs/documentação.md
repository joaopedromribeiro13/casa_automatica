#Portas arduino:

- LEDS
15 - led 1
02 - led 2
04 - led 3

- Bomba de água
17 - bomba
34 - sensorUmidade

- Sensor de Presença
16 - sensorMovimento

- Som de bipe   
5 - Buzzer


#Comunicação Entre ESP32 e App inventor:

Foi definodo para que o App Inventor enviasse 1 byte de sinal bluetooth em decimal para o arduino receber,
então no script (../src/src-C++/main.c++) vai receber números inteiros apartir da condição SerialBT.read().

- LED1 (pino 15):
Ligar: 1
Desligar: 0

- LED2 (pino 2):
Ligar: 2
Desligar: 3

- LED3 (pino 4):
Ligar: 4
Desligar: 5

- Bomba Hidráulica (pino 17):
Ligar: 6
Desligar: 7

- Buzzer (pino 5):
Ligar: 8
Desligar: 9

- Sensor alarme (pino 16):
Ligar: 10
Deligar:11

