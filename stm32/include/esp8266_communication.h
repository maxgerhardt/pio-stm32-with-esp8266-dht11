#ifndef INCLUDE_ESP8266_COMMUNICATION_H_
#define INCLUDE_ESP8266_COMMUNICATION_H_

#include <stdint.h>
#include <stddef.h>

/**
 * Uses tag-length-value format
 *
 *    1       2      <length>   Bytes
 * +--------------------------+
 * | Tag  | Length | Value    |
 * +--------------------------+
 */

/**
 *
 */
#define ESP8266_COM_TAG_TEMP_SENSOR 0x01

/**
 * Sends a temperature and humidity value to the ESP8266
 */
void esp8266_send_value(uint8_t temp, uint8_t hum);

#endif /* INCLUDE_ESP8266_COMMUNICATION_H_ */
