// 
//   FILE:  dht11_temp_humidity.ino
//   PURPOSE: Read temp and humidity and return in F and % to serial out.
//   The pin out and attaching the dht-11 to the arduino is easy.  The 
//   bread board lines are +,_ and data <pin assigned>. The vcc attaches 
//   to arduino 5 volt and ground goes to ground.  A good diagram can be 
//   found here: https://brainy-bits.com/tutorials/dht11-tutorial/
//   THe plain sensor adds a 5 k pull up resistor to the data line as 
//   pictured here: http://learning.grobotronics.com/2013/07/measuring-humidity-with-dht11-sensor/
//
#include <dht11.h>

dht11 DHT11;
#define DHT11_PIN 7
int correction = 2;// correction for my specific dht11 so it matches another thermometer 
// in the house. This probably will not be necessary in your case.

// **** Functions **** 
//Celsius to Fahrenheit conversion
double Fahrenheit(double celsius)
{
	return 1.8 * celsius + 32 + correction;
}

double dewPointFast(double celsius, double humidity)// converted to F
{
	double a = 17.271;
	double b = 237.7;
	double temp = (a * celsius) / (b + celsius) + log(humidity*0.01);
	double Td = (b * temp) / (a - temp);
  return 1.8 * Td + 32 + correction;
}


void setup()
{
  Serial.begin(9600);
  delay(500);//Delay to let system boot
  Serial.println("DHT11 TEST PROGRAM ");
  Serial.print("LIBRARY VERSION: ");
  Serial.println(DHT11LIB_VERSION);
  Serial.println();
}

void loop()
{
  Serial.println("\n");

  int chk = DHT11.read(DHT11_PIN);
  
  Serial.print("Temperature (F): ");
  Serial.println(Fahrenheit(DHT11.temperature), DHT11_PIN);
  
  Serial.print("Humidity (%): ");
  Serial.println((float)DHT11.humidity, DHT11_PIN);

  Serial.print("Dew Point (F): ");//fast version
  Serial.println(dewPointFast(DHT11.temperature, DHT11.humidity));

  delay(3000);
}

// END OF FILE

