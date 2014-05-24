
//Celsius to Fahrenheit conversion
double Fahrenheit(double celsius)
{
	return 1.8 * celsius + 32;
}

// fast integer version with rounding
//int Celcius2Fahrenheit(int celcius)
//{
//  return (celsius * 18 + 5)/10 + 32;
//}


//Celsius to Kelvin conversion
double Kelvin(double celsius)
{
	return celsius + 273.15;
}

// dewPoint function NOAA
// reference (1) : http://wahiduddin.net/calc/density_algorithms.htm
// reference (2) : http://www.colorado.edu/geography/weather_station/Geog_site/about.htm
//
double dewPoint(double celsius, double humidity)
{
	// (1) Saturation Vapor Pressure = ESGG(T)
	double RATIO = 373.15 / (273.15 + celsius);
	double RHS = -7.90298 * (RATIO - 1);
	RHS += 5.02808 * log10(RATIO);
	RHS += -1.3816e-7 * (pow(10, (11.344 * (1 - 1/RATIO ))) - 1) ;
	RHS += 8.1328e-3 * (pow(10, (-3.49149 * (RATIO - 1))) - 1) ;
	RHS += log10(1013.246);

        // factor -3 is to adjust units - Vapor Pressure SVP * humidity
	double VP = pow(10, RHS - 3) * humidity;

        // (2) DEWPOINT = F(Vapor Pressure)
	double T = log(VP/0.61078);   // temp var
	return (241.88 * T) / (17.558 - T);
}

// delta max = 0.6544 wrt dewPoint()
// 6.9 x faster than dewPoint()
// reference: http://en.wikipedia.org/wiki/Dew_point
double dewPointFast(double celsius, double humidity)
{
	double a = 17.271;
	double b = 237.7;
	double temp = (a * celsius) / (b + celsius) + log(humidity*0.01);
	double Td = (b * temp) / (a - temp);
	return Td;
}


#include <dht11.h>
#include <rgb.h>
#include <rgb.h>

dht11 DHT11;
RGB led;

#define DHT11PIN A0

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
  Serial.println("DHT11 TEST PROGRAM ");
  Serial.print("LIBRARY VERSION: ");
  Serial.println(DHT11LIB_VERSION);
  Serial.println();
  led.init(5, 6, 7);
  led.fadeToColor(BLUE, GREEN, 5);
}

void loop() {
  // put your main code here, to run repeatedly:
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
