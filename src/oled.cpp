#include <Arduino.h>
#include <lib/config.h>
#include <lib/oled.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>


Adafruit_SH1106 display(OLED_DATA_PIN,OLED_CLOCK_PIN);

void initOLED(){
    display.begin(SH1106_SWITCHCAPVCC,OLED_ADDR);
}

void updateDisplay(float temperature, int inkrementor, String binary_representation, String grey_representations,float humidity)
{
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.setCursor(0,0);
    display.println("Humidity: " + String(humidity) +" %");
    display.println("Temperature: "  + String(temperature) + "°C");
    display.setCursor(0,20);
    display.println("VALUE:"  + String(inkrementor));
    display.println("BIN: " + String(inkrementor,2));
    display.println("GRAY: " + String(grey_representations));
    display.display();
}