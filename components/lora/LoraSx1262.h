/*License: Creative Commons 4.0 - Attribution, NonCommercial
 * https://creativecommons.org/licenses/by-nc/4.0/
 * Author: Mitch Davis (2023). github.com/thekakester
 *
 * You are free to:
 *    Share — copy and redistribute the material in any medium or format
 *    Adapt — remix, transform, and build upon the material
 * Under the following terms:
 *    Attribution — You must give appropriate credit, provide a link to the license, and indicate if changes were made.
 *                  You may do so in any reasonable manner, but not in any way that suggests the licensor endorses you or your use.
 *    NonCommercial — You may not use the material for commercial purposes.
 *
 * No warranties are given. The license may not give you all of the permissions necessary for your intended use.
 * For example, other rights such as publicity, privacy, or moral rights may limit how you use the material
 */

#ifndef __LORA1262__
#define __LORA1262__

#include <driver/gpio.h>
#include <driver/spi_master.h>
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bsp.h"

/* Wiring requirements (for default shield pinout)
# +-----------------+-------------+------------+
# | Description     | Arduino Pin | Sx1262 Pin |
# +-----------------+-------------+------------+
# | Power (3v3)     | 3v3         | 3v3        |
# | GND             | GND         | GND        |
# | Radio Reset     | A0          | SX_NRESET  |
# | Busy (optional) | D3          | BUSY       |
# | Radio Interrupt | D5          | DIO1       |
# | SPI SCK         | 13          | SCK        |
# | SPI MOSI        | D11         | MOSI       |
# | SPI MISO        | D12         | MISO       |
# | SPI CS          | D7          | NSS        |
# +-----------------+----------+------------+
*/

// Pin configurations (for Arduino UNO)
#define SX1262_NSS CONFIG_LORA_NSS_GPIO
#define SX126x_BUSY CONFIG_BUSY_GPIO
#define SX126x_TXEN CONFIG_TXEN_GPIO
#define SX126x_RXEN CONFIG_RXEN_GPIO
#define SX1262_RESET CONFIG_RST_GPIO
#define SX1262_DIO1 CONFIG_LORA_D1_GPIO

// Presets. These help make radio config easier
#define PRESET_DEFAULT 0
#define PRESET_LONGRANGE 1
#define PRESET_FAST 2

typedef struct {
  // These variables show signal quality, and are updated automatically whenever a packet is received
  int rssi;
  int snr;
  int signalRssi;
} lora_t;

typedef uint8_t byte;

// public
bool lora_init();
bool sanityCheck(); /*Returns true if we have an active SPI communication with the radio*/
void transmit(byte* data, int dataLen);
int lora_receive_async(byte* buff, int buffMaxLen); /*Checks to see if a lora packet was received yet, returns the packet if available*/
int lora_receive_blocking(byte* buff, int buffMaxLen, uint32_t timeout); /*Waits until a packet is received, with an optional timeout*/

// Radio configuration (optional)
bool configSetPreset(int preset);
bool configSetFrequency(long frequencyInHz);
bool configSetBandwidth(int bandwidth);
bool configSetCodingRate(int codingRate);
bool configSetSpreadingFactor(int spreadingFactor);

uint32_t frequencyToPLL(long freqInHz);

// private
bool spi_write_byte(uint8_t* Dataout, size_t DataLength);
bool spi_read_byte(uint8_t* Datain, uint8_t* Dataout, size_t DataLength);
uint8_t spi_transfer(uint8_t address);

void setModeReceive();  // Puts the radio in receive mode, allowing it to receive packets
void setModeStandby();  // Put radio into standby mode.  Switching from Rx to Tx directly is slow
void configureRadioEssentials();
bool waitForRadioCommandCompletion(uint32_t timeout);
void updateRadioFrequency();
void updateModulationParameters();

#endif