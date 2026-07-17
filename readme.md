# Documentação da Biblioteca `SensorRoxoOBR`

A biblioteca `SensorRoxoOBR` foi desenvolvida para simplificar a programação de robôs de linha na OBR (Olimpíada Brasileira de Robótica). Ela gerencia o sensor de cor TCS34725 integrado a um multiplexador I2C, automatizando a troca de canais, normalização de dados e a calibração para a identificação direta de cores como verde, vermelho, preto e branco.

# 1. Construtor

Para utilizar múltiplos sensores, é necessário instanciar a classe para cada sensor informando seus parâmetros de configuração.

```
SensorRoxoOBR(uint8_t enderecoMultiplexador, uint8_t canalMultiplexador, uint16_t tempo_ms, uint8_t ganho);
```

- enderecoMultiplexador: Endereço I2C do multiplexador (geralmente `0x70`).
- canalMultiplexador: A porta do multiplexador onde o sensor está conectado (ex: `0`, `3`).
- tempo_ms: Tempo de integração em milissegundos. Valores aceitos: `24`, `50`, `101`, `154`, `700`. Se for inserido um valor inválido, a biblioteca assume `50` como padrão de segurança.
- ganho: Ganho de sensibilidade do sensor. Valores aceitos: `1`, `4`, `16`, `60`. Se for inserido um valor inválido, a biblioteca assume `4` como padrão.

# 2. Métodos da Biblioteca

## `bool inicializar()`
Configura o canal do multiplexador e inicia a comunicação com o sensor TCS34725.
- Retorno: `true` se o sensor for iniciado corretamente, `false` se não for encontrado. É recomendado chamá-lo dentro do `setup()`.

## `void selecionarCanal()`
Abre a comunicação I2C e altera o canal do multiplexador para focar exclusivamente neste sensor. É acionado automaticamente por métodos como `cor()` ou `coletar()`.

## `String coletar()`
Realiza a leitura dos dados brutos do sensor (Red, Green, Blue e Clear) e calcula os valores normalizados dividindo R, G e B pelo valor de C (Clear).
- Retorno: Retorna uma String com o padrão: `C = [valor], R = [valor], G = [valor], B = [valor]`. Se o ambiente estiver num breu total (C igual a 0), retorna `0.00, 0.00, 0.00, 0` para evitar erros matemáticos de divisão por zero.

## `void calibrar(float limiar_branco, float limiar_preto, float limiar_vermelho, float limiar_verde, float limiar_azul)`
Define os pontos de corte e referências numéricas (limiares) que a biblioteca usará para classificar a cor lida.
- limiar_branco: Valor *mínimo* absoluto de Clear (C) para a leitura ser "branco".
- limiar_preto: Valor *máximo* absoluto de Clear (C) para a leitura ser "preto".
- limiar_vermelho: Valor *mínimo normalizado* de Red (R/C) para ser "vermelho".
- limiar_verde: Valor *mínimo normalizado* de Green (G/C) para ser "verde".
- limiar_azul: Valor *mínimo normalizado* de Blue (B/C) para ser "azul".

## `String cor()`
Retorna o nome da cor identificada com base nos parâmetros configurados em `calibrar()`.
- Lógica de classificação:
  1. Verifica se houve erro de leitura (C = 0).
  2. Compara primeiro a luminosidade absoluta (Clear) contra os limites de branco e preto.
  3. Compara as proporções normalizadas (R, G, B), garantindo que a cor não só supere seu limiar, mas também seja dominante sobre as outras duas.
- Retorno: `"branco"`, `"preto"`, `"vermelho"`, `"verde"`, `"azul"`, `"cor desconhecida ou não calibrada"`, ou erro de leitura.

---

# 3. Exemplos de Uso

## Exemplo 1: Coleta de Dados para Calibração
Antes de o robô identificar cores, é essencial coletar os dados sobre a iluminação local.

```
#include <SensorRoxoOBR.h>

SensorRoxoOBR sensor0(0x70, 0, 50, 4);
SensorRoxoOBR sensor3(0x70, 3, 50, 4);

void setup() {
    Serial.begin(9600);
    Wire.begin();

    if(!sensor0.inicializar()) Serial.println("Sensor 0 NAO encontrado!");
    if(!sensor3.inicializar()) Serial.println("Sensor 3 NAO encontrado!");
}

void loop() {
    String coleta0 = sensor0.coletar();
    String coleta3 = sensor3.coletar();

    Serial.print("Valores do sensor 0: "); Serial.print(coleta0);
    Serial.print(" || Valores do sensor 3: "); Serial.println(coleta3);
}
```

## Exemplo 2: Identificação de Cores em Pista
Após descobrir os valores normalizados testando o robô na pista, aplica-se no `calibrar()`.

```
#include <SensorRoxoOBR.h>

SensorRoxoOBR sensor0(0x70, 0, 50, 4);
SensorRoxoOBR sensor3(0x70, 3, 50, 4);

void setup() {
    Serial.begin(9600);
    Wire.begin();

    if(!sensor0.inicializar()) Serial.println("Sensor 0 NAO encontrado!");
    if(!sensor3.inicializar()) Serial.println("Sensor 3 NAO encontrado!");

    // Calibração: Branco(>4000), Preto(<800), Vermelho(>0.50), Verde(>0.43), Azul(>0.40)
    sensor0.calibrar(4000, 800, 0.50, 0.43, 0.40);
    sensor3.calibrar(4000, 800, 0.50, 0.43, 0.40);
}

void loop() {
    String cor0 = sensor0.cor();
    String cor3 = sensor3.cor();

    Serial.print("Sensor 0: "); Serial.print(cor0);
    Serial.print(" || Sensor 3: "); Serial.println(cor3);
}
```
