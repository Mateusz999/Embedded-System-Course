#include <lib/config.h>
#include <lib/button.h>
#include <DHT.h>
#include "lib/oled.h"


float temperature;
float humidity;
int grey_representations = 0;
int inkrementor = 0;

/*
    led_array - jest to tablica określająca stan logiczny 
    dla danej diody 
    0 - LOW ( dioda zgaszona ) 
    1 - HIGH ( dioda zapalona )
    LED_PINOUT - jest to tablica, \
    która zawiera w sobie w odpowiedniej kolejności zadeklarowane piny
     odpowiedzialne za zadaną diodę
*/
bool led_array[4] = {0, 0, 0, 0};
int LED_PINOUT[4] = {FIRST, SECOND, THIRD, FOURTH};

// inicjalizujemy instancje naszego czujnika DHT11
DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
    initConfiguration();
    initOLED();
    dht.begin();

}

void loop() {
    static bool lastButtonState = HIGH;
    bool currentButtonState = digitalRead(INCREMENTOR);

    /*
    Instrukcja warunkowa, która wykona się tylko raz 
    po wciśnięciu przycisku typu tact switch - gdy w poprzedniej petli loop
    przycisk był w stanie HIGH

    W przypadku gdy wartość naszego inkrementora 
    będzie większa od 15 to zostanie ona wyzerowana
    */
    if (lastButtonState == HIGH && currentButtonState == LOW) {
        inkrementor++;
        if (inkrementor > 15) inkrementor = 0;
    }
    lastButtonState = currentButtonState;
    // odczyt temperatury oraz wilgotności z czujnika DHT11

    temperature = dht.readTemperature();
    digitalWrite(TEMPERATURE_PIN,temperature > 22.8 ? HIGH : LOW); 

    humidity = dht.readHumidity();

    // Operacja konwersji liczby na reprezentacje kodu Gray'a

    grey_representations = inkrementor ^ (inkrementor >> 1);

    // Operacja wykonana za pomocą operatora trójargumentowanego, 
    // który ustawia stan wysoki lub niski w zależności od temperatury


    /*
        Algorytm poniżej rozkłada nam liczbę wyrazoną w reprezentacji 
        Kodu Gray'a poprzez przypisanie do odpowiednich elementów 
        tablicy wartości 0 lub 1 za pomocą operacji modulo oraz dzielenia
    */

    int temp = grey_representations;
    for (int i = 3; i >= 0; i--) {
        led_array[i] = temp % 2;
        temp /= 2;
    }
    // Podanie na pin stanu wysokiego bądź niskiego
    // w zależności od danego elementu tablicy

    for (int i = 0; i < 4; i++) {
        digitalWrite(LED_PINOUT[i], led_array[i] ? HIGH : LOW);
    }


    // odswieżanie wyświetlacza z częstotliowścia 20 Hz
    updateDisplay(  temperature, inkrementor, 
                    String(inkrementor, BIN), 
                    String(grey_representations,BIN),humidity);
    delay(50);
}
