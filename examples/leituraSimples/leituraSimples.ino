#include <SensorRoxoOBR.h>

SensorRoxoOBR sensor0(0x70, 0, 50, 4);
SensorRoxoOBR sensor3(0x70, 3, 50, 4);

void setup()
{
    Serial.begin(9600);
    Wire.begin();

    if(!sensor0.inicializar()) Serial.println("Sensor 0 NAO encontrado!");
    if(!sensor3.inicializar()) Serial.println("Sensor 3 NAO encontrado!");
}

void loop()
{
    String coleta0 = sensor0.coletar();
    String coleta3 = sensor3.coletar();

    Serial.print("Valores para calibrar sensor esquerdo: ") Serial.print(coleta0);
    Serial.print(" || Valores para calibrar sensor direito: ") Serial.println(coleta3);
}
