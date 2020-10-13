#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 4

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature temp_sensor(&oneWire);

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 1 line display

void setup() {
    lcd.init();                      // initialize the lcd
    // Print a message to the LCD.
    lcd.backlight();

    temp_sensor.begin();

    Serial.begin(9600);
}

void loop() {
    temp_sensor.requestTemperatures(); // Send the command to get temperatures

    lcd.clear();
    lcd.setCursor(0,0); // positionne le curseur à la colonne 1 et à la ligne 2
    float current_temperature{temp_sensor.getTempCByIndex(0)};

    lcd.print("T: 25.2/28.0" "\xDF" "C");
    Serial.println("Hello World!");
    Serial.println(current_temperature);
    delay(1000);
}
