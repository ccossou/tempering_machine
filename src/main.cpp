#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 1 line display

void setup() {
    lcd.init();                      // initialize the lcd
    // Print a message to the LCD.
    lcd.backlight();
    Serial.begin(9600);
}

void loop() {
    lcd.clear();
    lcd.setCursor(0,0); // positionne le curseur à la colonne 1 et à la ligne 2
    lcd.print("T: 25.2/28.0" "\xDF" "C");
    Serial.println("Hello World!");
    delay(1000);
}
