#include <stdio.h>
#include <stdint.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"

#include "TMC4671.h"

// SPI Defines
// We are going to use SPI 0, and allocate it to the following GPIO pins
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define SPI_PORT spi0
#define PIN_MISO 16
#define PIN_CS   17
#define PIN_SCK  18
#define PIN_MOSI 19

#define DEFAULT_ICID 0

void tmc4671_readWriteSPI(uint16_t icID, uint8_t *data, size_t dataLength) {
    (void) icID;

    gpio_put(PIN_CS, 0);

    spi_write_read_blocking(SPI_PORT, data, data, dataLength);

    gpio_put(PIN_CS, 1);
}


int main() {
    stdio_init_all();


    // SPI initialisation. This example will use SPI at 1MHz.
    spi_init(SPI_PORT, 100 * 1000);
    gpio_set_function(PIN_MISO, GPIO_FUNC_SPI);
    gpio_set_function(PIN_CS, GPIO_FUNC_SIO);
    gpio_set_function(PIN_SCK, GPIO_FUNC_SPI);
    gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);

    // Chip select is active-low, so we'll initialise it to a driven-high state
    gpio_set_dir(PIN_CS, GPIO_OUT);
    gpio_put(PIN_CS, 1);
    // For more examples of SPI use see https://github.com/raspberrypi/pico-examples/tree/master/spi

    while (true) {
        sleep_ms(3000);

        printf("Sending SPI Request \n");

        uint32_t test = tmc4671_getTargetTorque_raw(DEFAULT_ICID);

        printf("Target Torque : %d\n", test);
    }
}
