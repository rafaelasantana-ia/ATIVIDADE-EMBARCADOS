# Temperatura e umidade com ESP32-S3 e DHT22

Atividade em C usando ESP-IDF e simulacao Wokwi no VS Code.

## Verificacao realizada

- Compilacao concluida em 22/09/2026 com ESP-IDF 6.1.0, alvo ESP32-S3.
- Firmware gerado: `build/temperatura_dht22.bin` (176800 bytes).
- Saida real da compilacao salva em `evidencias/compilacao.txt`.
- Licenca Wokwi ativada e simulacao executada no VS Code em 22/09/2026.
- Monitor serial validado com leituras sucessivas de 25.0 C e 60.0% de umidade.
  Captura real do circuito, licenca ativa e monitor: `evidencias/04-leituras.png`.

## Circuito

| DHT22 | ESP32-S3 |
| --- | --- |
| VCC | 3V3 |
| GND | GND |
| SDA (dados, nao e I2C) | GPIO 4 |
| NC | Sem conexao |

Resistor de 10 kohms entre SDA e 3V3. O circuito esta em `diagram.json`.
O sensor inicia com 25 C e 60% de umidade no simulador.

## Codigo e inicializacao

`main/main.c` configura GPIO 4 com pull-up, aguarda 2,5 segundos para
estabilizacao e chama `dht_read_float_data(DHT_TYPE_AM2301, ...)`.
Este e o tipo usado pela biblioteca `esp-idf-lib/dht` para o DHT22.
A biblioteca faz o protocolo de inicializacao de cada leitura e verifica
o checksum. O intervalo entre leituras e de 2,5 segundos. Falhas sao
mostradas no monitor, sem imprimir medidas invalidas.

A dependencia esta fixada em 1.2.0 em `main/idf_component.yml`; o gerenciador
de componentes do ESP-IDF faz o download durante a primeira compilacao.

## Compilar no VS Code

1. Abra esta pasta (`C:\Projetos\Embarcados`) no VS Code.
2. Use `ESP-IDF: Select Current ESP-IDF Version` e escolha a instalacao 6.1.
3. Abra `ESP-IDF: Open ESP-IDF Terminal` pela paleta (Ctrl + Shift + P).
4. Execute `idf.py build`. O alvo ESP32-S3 esta em `sdkconfig.defaults`.
5. Aguarde `Project build complete`.

Os arquivos gerados ficam em `build/`. O Wokwi usa `build/flasher_args.json`
para carregar firmware, bootloader e tabela de particoes.

## Conta Wokwi e simulacao

1. Com a extensao Wokwi instalada, use `Wokwi: Request a New License`.
2. No navegador, entre ou crie sua conta e clique em `GET YOUR LICENSE`.
3. Autorize o retorno ao VS Code e confira a mensagem de ativacao.
   A modalidade e validade da licenca sao informadas pelo Wokwi.
4. Depois da compilacao, use `Wokwi: Start Simulator`.
5. Aguarde o inicio do firmware e as leituras no monitor serial do Wokwi.
6. Clique no DHT22 durante a simulacao e altere temperatura/umidade.
   Confira se as proximas leituras acompanham os valores selecionados.

Exemplo de formato esperado (nao e uma captura de execucao):

```text
Leitura 1 | Temperatura: 25.0 C | Umidade: 60.0 %
```

Nao e necessario conectar uma placa fisica ou selecionar uma porta COM
para simular. Use o monitor do Wokwi.

## Referencias

- Sensor Wokwi: https://docs.wokwi.com/parts/wokwi-dht22
- Biblioteca C e API: https://esp-idf-lib.github.io/dht/
- Componente: https://components.espressif.com/components/esp-idf-lib/dht/versions/1.2.0/readme
- Licenca e extensao: https://docs.wokwi.com/vscode/getting-started
- Firmware ESP-IDF no Wokwi: https://docs.wokwi.com/vscode/project-config
