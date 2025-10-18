#include <Arduino.h>
#include <lib/config.h>
#include <lib/oled.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>

// Inicjalizacja instancji naszego wyświetlacza 1.3' OLED
Adafruit_SH1106 display(OLED_DATA_PIN,OLED_CLOCK_PIN);

// Funkcja inicjalizacyjna naszego wyświetlacza 
void initOLED(){
    display.begin(SH1106_SWITCHCAPVCC,OLED_ADDR);
}


/*

    Funkcje wyświetlająca podane parametry na wyświetlaczu 
    Dwa parametry String wyświetlane w sposób String(nazwa_zmienne,2) 
    oznacza, że wyświelane są jako ciąg bitów

*/ 

void updateDisplay( float temperature, int inkrementor, 
                    String binary_representation, String grey_representations,
                    float humidity)
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