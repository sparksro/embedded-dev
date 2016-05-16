//
// File: basic_lcd_hello_world
// Description:  print hello world to the arduino 16 x 2 lcd screen 
// pinout and wirring diagram found here: https://www.arduino.cc/en/Tutorial/LiquidCrystalDisplay
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
void setup() {
  lcd.begin(16, 2);
  lcd.print("hello, world!");
}

void loop() {
  // put your main code here, to run repeatedly:

}
