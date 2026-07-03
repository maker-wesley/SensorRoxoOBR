#include <SensorRoxoOBR.h>

SensorRoxoOBR sensorEsquerdo(0x70, 0, 50, 4);
SensorROxoOBR sensorDireito(0x70, 3, 50, 4);

void setup()
{
    Serial.begin(9600);
    Wire.begin();

    if(!sensorEsquerdo.inicializar()) Serial.println("Sensor esquerdo NAO encontrado!");
    if(!sensorDireito.inicializar()) Serial.println("Sensor direito NAO encontrado!");
}

void loop()
{
    String coleta_esquerdo = sensorEsquerdo.coletar();
    String coleta_direito = sensorDireito.coletar();

    Serial.print("Valores para calibrar sensor esquerdo: ") Serial.print(coleta_esquerdo);
    Serial.print(" || Valores para calibrar sensor direito: ") Serial.println(coleta_direito);
}
