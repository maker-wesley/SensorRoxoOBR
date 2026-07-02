#ifndef _SENSORROXOOBR_H
#define _SENSORROXOOBR_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_BusIO.h>
#include <Adafruit_TCS34725.h>

class SensorRoxoOBR {
    private:
        int _enderecoMultiplexador;
        int _canalMultiplexador;
        float _lbr, _lpr, _lr, _lg, _lb;
        uint16_t _r, _g, _b, _c;
        Adafruit_TCS34725 _sensorTcs;

    public:
        SensorRoxoOBR();
        void selecionarCanal();
        bool inicializar();
        String cor();
        String coletar();
        void calibrar(float limiar_branco, float limiar_preto, float limiar_vermelho, float limiar_verde, float limiar_azul)
}

#endif