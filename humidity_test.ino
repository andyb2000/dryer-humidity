#include <dht11.h>
#include <rgb.h>

dht11 DHT11;
RGB led;

#define DHT11PIN A0

void setup() {
  Serial.begin(9600);
  led.init(5, 6, 7);
  led.fadeToColor(BLUE, GREEN, 5);
}

void loop() {
  Serial.println("\n");

  int chk = DHT11.read(DHT11PIN);

  Serial.print("S: ");
  switch (chk)
  {
    case DHTLIB_OK: 
		Serial.println("OK"); 
                led.setColor(MAGENTA);
                  Serial.print("H: ");
                  Serial.println((float)DHT11.humidity, 2);
                  Serial.print("T: ");
                  Serial.println((float)DHT11.temperature, 2);
                  Serial.print("D: ");
                  Serial.println(dewPoint(DHT11.temperature, DHT11.humidity));
                  if (DHT11.humidity > 70) {
                    Serial.println("Dryer wet");
                    led.fadeToColor(BLUE, CYAN, 5);
                  } else {
                    led.fadeToColor(MAGENTA, GREEN, 3);
                  };
		break;
    case DHTLIB_ERROR_CHECKSUM: 
		Serial.println("Checksum error"); 
                led.setColor(RED);
		break;
    case DHTLIB_ERROR_TIMEOUT: 
		Serial.println("Time out error"); 
                led.setColor(RED);
		break;
    default: 
		Serial.println("Unknown error"); 
                led.setColor(RED);
		break;
  }

  Serial.println("E: 1");
  delay(2000);
}
