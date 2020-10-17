#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 4

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature temp_sensor(&oneWire);

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 1 line display

char current_temp_str[5];  // 4 chars and the null after. This doesn't work with Serial.println if the null is not here
float requested_temperature{55};
char requested_temp_str[5];

void setup() {
    lcd.init();                      // initialize the lcd
    // Print a message to the LCD.
    lcd.backlight();

    temp_sensor.begin();

    Serial.begin(9600);


}

/** Update temperature display, both on lcd and serial
 *
 * @param[in] current_t Current temperature measured by the sensor
 * @param[in] requested_t Requested temperature by the user
 */
void update_display(float current_t, float requested_t) {
    dtostrf(current_t, 4, 1, current_temp_str);
    dtostrf(requested_t, 4, 1, requested_temp_str);

    lcd.setCursor(0,0); // positionne le curseur at (col, row)
    lcd.print("T: 25.2/28.0" "\xDF" "C");  // Temperatures here are fake because overwritten by the real one later on

    lcd.setCursor(3, 0);
    lcd.print(current_temp_str);

    lcd.setCursor(8, 0);
    lcd.print(requested_temp_str);

    // Print temp to serial monitor
    Serial.print("Current temperature: ");
    Serial.print(current_temp_str);
    Serial.print(char(176));
    Serial.println("C");
}

void loop() {
    temp_sensor.requestTemperatures(); // Send the command to get temperatures

    lcd.clear();

    float current_temperature{temp_sensor.getTempCByIndex(0)};

    update_display(current_temperature, requested_temperature);


    delay(1000);
}
