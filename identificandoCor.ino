#include <Wire.h>
#include <SensorRoxoOBR.h>

SensorRoxoOBR sensorEsquerdo(0x70, 0, 50, 4);
SensorRoxoOBR sensorDireito(0x70, 3, 50, 4);

void setup()
{
    Serial.begin(9600);
    Wire.begin();

    if(!sensorEsquerdo.inicializar()) Serial.println("Sensor esquerdo NAO encontrado!");
    if(!sensorDireito.inicializar()) Serial.println("Sensor direito NAO encontrado!");

    sensorEsquerdo.calibrar(4000, 800, 0.50, 0.43, 0.40);
    sensorDireito.calibrar(4000, 800, 0.50, 0.43, 0.40);
}

void loop()
{
    String cor_esquerda = sensorEsquerdo.cor();
    String cor_direita = sensorDireito.cor();

    Serial.print("Sensor esquerdo: "); Serial.print(cor_esquerda);
    Serial.print(" || Sensor direito: "); Serial.println(cor_direita);
}