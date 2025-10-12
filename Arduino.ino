#include <lib/config.h>
#include <lib/button.h>
#include <DHT.h>
#include "lib/oled.h"

float temperature;
float humidity;
int grey_representations = 0;
int inkrementor = 0;
bool led_array[4] = {0, 0, 0, 0};
int LED_PINOUT[4] = {2, 4, 5, 23};

DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
    initConfiguration();
    initOLED();
    dht.begin();

    for (int i = 0; i < 4; i++) {
        pinMode(LED_PINOUT[i], OUTPUT);
    }
}

void loop() {
    static bool lastButtonState = HIGH;
    bool currentButtonState = digitalRead(INCREMENTOR);

    if (lastButtonState == HIGH && currentButtonState == LOW) {
        inkrementor++;
        if (inkrementor > 15) inkrementor = 0;
    }
    lastButtonState = currentButtonState;

    temperature = dht.readTemperature();
    humidity = dht.readHumidity();
    grey_representations = inkrementor ^ (inkrementor >> 1);


     digitalWrite(TEMPERATURE_PIN,temperature > 22.8 ? HIGH : LOW); 

    int temp = grey_representations;
    for (int i = 3; i >= 0; i--) {
        led_array[i] = temp % 2;
        temp /= 2;
    }

    for (int i = 0; i < 4; i++) {
        digitalWrite(LED_PINOUT[i], led_array[i] ? HIGH : LOW);
    }

    updateDisplay(temperature, inkrementor, String(inkrementor, BIN), String(grey_representations,BIN),humidity);

    delay(50);
}
