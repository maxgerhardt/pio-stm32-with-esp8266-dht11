#include <esp8266_communication.h>
#include <stdint.h>
#include "stm32f1xx_hal.h"

/* UART2 object from main.c */
extern UART_HandleTypeDef huart2;

static void esp8266_write_bytes(void* data, size_t len) {
	HAL_UART_Transmit(&huart2, (uint8_t*) data, (uint16_t) len, 1000);
}

static void esp8266_send_packet(uint8_t tag, uint8_t* data, size_t len) {
	esp8266_write_bytes(&tag, 1);
	uint16_t packetLen = (uint16_t) len;
	esp8266_write_bytes(&packetLen, 2);
	esp8266_write_bytes(data, len);
}

void esp8266_send_value(uint8_t temp, uint8_t hum) {
	char line[10];
	snprintf(line, sizeof(line), "%d,%d\n", temp, hum);
	esp8266_write_bytes(line, strlen(line));
	//uint8_t data[2] = { temp, hum };
	//esp8266_send_packet(ESP8266_COM_TAG_TEMP_SENSOR, data, sizeof(data));
}
