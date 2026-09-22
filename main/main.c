#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_err.h"
#include "dht.h"

#define DHT_GPIO GPIO_NUM_4
#define INTERVALO_MS 2500

void app_main(void)
{
    // DHT22 usa DHT_TYPE_AM2301 nesta biblioteca. Nao utiliza I2C.
    // A biblioteca inicia a comunicacao e verifica o checksum em cada leitura.
    ESP_ERROR_CHECK(gpio_reset_pin(DHT_GPIO));
    ESP_ERROR_CHECK(gpio_set_direction(DHT_GPIO, GPIO_MODE_INPUT));
    ESP_ERROR_CHECK(gpio_set_pull_mode(DHT_GPIO, GPIO_PULLUP_ONLY));

    printf("\nESP32-S3 | Sensor DHT22 | Dados no GPIO 4\n");
    printf("Aguardando estabilizacao do sensor...\n");
    vTaskDelay(pdMS_TO_TICKS(INTERVALO_MS));

    unsigned int leitura = 0;
    while (1) {
        float temperatura = 0;
        float umidade = 0;
        esp_err_t resultado = dht_read_float_data(
            DHT_TYPE_AM2301, DHT_GPIO, &umidade, &temperatura);

        if (resultado == ESP_OK) {
            printf("Leitura %u | Temperatura: %.1f C | Umidade: %.1f %%\n",
                   ++leitura, temperatura, umidade);
        } else {
            printf("Falha na leitura: %s. Verifique VCC, GND e GPIO 4.\n",
                   esp_err_to_name(resultado));
        }
        // DHT22 requer pelo menos 2 segundos entre as leituras.
        vTaskDelay(pdMS_TO_TICKS(INTERVALO_MS));
    }
}
