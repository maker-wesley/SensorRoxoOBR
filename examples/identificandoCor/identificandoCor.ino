#include <SensorRoxoOBR.h>

SensorRoxoOBR sensor0(0x70, 0, 50, 4);
SensorRoxoOBR sensor3(0x70, 3, 50, 4);

void setup()
{
    Serial.begin(9600);
    Wire.begin();

    if(!sensor0.inicializar()) Serial.println("Sensor 0 NAO encontrado!");
    if(!sensor3.inicializar()) Serial.println("Sensor 3 NAO encontrado!");

    sensor0.calibrar(4000, 800, 0.50, 0.43, 0.40);
    sensor3.calibrar(4000, 800, 0.50, 0.43, 0.40);
}

void loop()
{
    String cor0 = sensor0.cor();
    String cor3 = sensor3.cor();

    Serial.print("Sensor esquerdo: "); Serial.print(cor0);
    Serial.print(" || Sensor direito: "); Serial.println(cor3);
}
