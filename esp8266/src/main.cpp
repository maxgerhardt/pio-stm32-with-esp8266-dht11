#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <settings.h>
#include <ThingSpeak.h>

char ssid[] = SECRET_SSID;   // your network SSID (name)
char pass[] = SECRET_PASS;   // your network password
WiFiClient client;

unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

/* holds the current serial line */
String currentLine;

int lastTemp, lastHumidity;
unsigned long lastSendTime = 0;
//send every 30 seconds (rate limit by ThingSpeak, 15 seconds per field)
const long sendInterval = 30 * 1000;

void read_serial_packet();
void send_to_thingsspeak();
void connect_to_wifi();

void setup() {
	//debug serial (TX) and data receive serial (RX)
	//when programming the ESP8266, remove the connection
	//from the STM32 to the ESP8266's RX pin!
	//can also be handled with .swap() so that RX and TX pins
	//get swapped to 2 different pins, but this way we can't
	//get the debug output from a NodeMCU
	Serial.begin(115200);
	//wait at max 1 second for a string on the serial
	Serial.setTimeout(1000);
	Serial.println("Firwmare start!");

	//set WiFi mode to STATION
	WiFi.mode(WIFI_STA);
	ThingSpeak.begin(client); // Initialize ThingSpeak
	connect_to_wifi();
}

void loop() {
	read_serial_packet();

	//check if enough time has expired to send the data to us.
	if (millis() - lastSendTime >= sendInterval) {
		lastSendTime = millis();
		send_to_thingsspeak();
	}
}

void read_serial_packet() {
	if (Serial.available()) {
		currentLine = Serial.readStringUntil('\n');

		//Serial.println("GOT LINE");
		//Serial.println(currentLine);

		int commaSplitIndex = currentLine.indexOf(',');
		if (commaSplitIndex > 0) {
			String tempStr = currentLine.substring(0, commaSplitIndex);
			String humString = currentLine.substring(commaSplitIndex + 1);

			Serial.println("[Update] Temp: " + tempStr + " Hum: " + humString);

			lastTemp = tempStr.toInt();
			lastHumidity = humString.toInt();
		}
	}
}

void connect_to_wifi() {
	// Connect or reconnect to WiFi
	if (WiFi.status() != WL_CONNECTED) {
		Serial.print("Attempting to connect to SSID: ");
		Serial.println(SECRET_SSID);
		while (WiFi.status() != WL_CONNECTED) {
			WiFi.begin(ssid, pass); // Connect to WPA/WPA2 network. Change this line if using open or WEP network
			Serial.print(".");
			delay(5000);
		}
		Serial.println("\nConnected.");
	}
}

void send_to_thingsspeak() {
	//update field 1 (temperature) and 2 (humidity)
	ThingSpeak.setField(1, lastTemp);
	ThingSpeak.setField(2, lastHumidity);
	//send update via HTTPS REST call
	int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
	if (x == 200) {
		Serial.println("Channel update successful.");
	} else {
		Serial.println(
				"Problem updating channel. HTTP error code " + String(x));
	}
}
