//
// File: temp_and_hubidity_printed_to_LCD.ino
// Description:  Combines previous LCD code and temp/humidity code into one package.  Prints to the
// LCD and not serial out.

#include <dht11.h>
//#include <math.h>
#include <LiquidCrystal.h>

dht11 DHT11;
#define DHT11_PIN 7
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

double Fahrenheit(double celsius)
{
  return 1.8 * celsius + 32;
}

void setup() {
  lcd.begin(16, 2);
  delay(500);//Delay to let system boot
  
}

void loop() {
  int chk = DHT11.read(DHT11_PIN);
  lcd.setCursor(0,0);
  
  // first line
  float theTemp = Fahrenheit(DHT11.temperature);
  lcd.print("Temp: ");
  lcd.print(theTemp, 1);
  lcd.print("F");
  
  // We could do the following fancy and combersom conversions to get it only to print one digit.  It works
  // but it gives the same result as above in practicle appliction and we will use the higher precision value to 
  // controll temps later in the project any way.
  /*
  int integer_part = theTemp;// convert to an integer to get only the first part
  lcd.print((int)integer_part);// print the interger side
  // This next part uses integer math, multiplication and division to producte the fractional part as a resulting int.
  int fractional_part = ((int)round(theTemp * 10)) - (( ((int)round(theTemp * 10)) / 10)*10);
  lcd.print(("."));// print the decimal point
  lcd.print(fractional_part);//print the fractional side to one place
  lcd.print("F");
  */
  // second line
  lcd.setCursor(0,1);
  lcd.print("Humidity: ");
  lcd.print(DHT11.humidity);
  lcd.print("%");
  delay(2000);

}
