#include <SensorRoxoOBR.h>

uint8_t traduzirTempo(uint16_t tempo) {
    if (tempo == 24)  return TCS34725_INTEGRATIONTIME_24MS;
    else if (tempo == 50) return TCS34725_INTEGRATIONTIME_50MS;
    else if (tempo == 101) return TCS34725_INTEGRATIONTIME_101MS;
    else if (tempo == 154) return TCS34725_INTEGRATIONTIME_154MS;
    else if (tempo == 700) return TCS34725_INTEGRATIONTIME_600MS;
}

tcs34725Gain_t traduzirGanho(uint8_t ganho) {
    if (ganho == 1) return TCS34725_GAIN_1X;
    else if (ganho == 4) return TCS34725_GAIN_4X;
    else if (ganho == 16) return TCS34725_GAIN_16X;
    else if (ganho == 60) return TCS34725_GAIN_60X;
}

SensorRoxoOBR::SensorRoxoOBR(uint8_t enderecoMultiplexador, uint8_t canalMultiplexador, uint16_t tempo_ms, uint8_t ganho)
    : _sensorTcs(traduzirTempo(tempo_ms), traduzirGanho(ganho)) 
{
    _enderecoMultiplexador = enderecoMultiplexador;
    _canalMultiplexador = canalMultiplexador;
}

bool SensorRoxoOBR::inicializar()
{
    selecionarCanal();
    return _sensorTcs.begin();
}

void SensorRoxoOBR::selecionarCanal()
{
    Wire.beginTransmission(_enderecoMultiplexador);
    Wire.write(1 << _canalMultiplexador);
    Wire.endTransmission();
}

String SensorRoxoOBR::cor()
{
    selecionarCanal();
    _sensorTcs.getRawData(&_r, &_g, &_b, &_c);

    float rn = (float) _r/_c;
    float gn = (float) _g/_c;
    float bn = (float) _b/_c;

    if (_c == 0) return "erro na leitura do sensor, verifique.";
    else if (_c > _lbr) return "branco";
    else if (_c < _lpr) return "preto";
    else if (rn > _lr && rn > gn && rn > bn) return "vermelho";
    else if (gn > _lg && gn > rn && gn > bn) return "verde";
    else if (bn > _lb && bn > rn && bn > gn) return "azul";
    else return "cor desconhecida ou não calibrada";
}

void SensorRoxoOBR::calibrar(float limiar_branco, float limiar_preto, float limiar_vermelho, float limiar_verde, float limiar_azul)
{
    _lbr = limiar_branco;
    _lpr = limiar_preto;
    _lr = limiar_vermelho;
    _lg = limiar_verde;
    _lb = limiar_azul;
}

String SensorRoxoOBR::coletar()
{
    selecionarCanal();
    _sensorTcs.getRawData(&_r, &_g, &_b, &_c);

    float rn = (float) _r/_c;
    float gn = (float) _g/_c;
    float bn = (float) _b/_c;

    String coleta = String(rn) + ", " + String(gn) + ", " + String(bn) + ", " + String(_c);
    return coleta;
}
