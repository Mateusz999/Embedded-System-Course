#pragma once

// Konfiguracja pod wyświetlacz OLED

#define OLED_DATA_PIN 21
#define OLED_CLOCK_PIN 22
#define OLED_ADDR 0x3C

// Konfiguracja pod przycisk typu tackt switch

#define INCREMENTOR 15

// Konfiguracja pod czujnik wilgotności i temperatury

#define DHT_PIN 18
#define DHT_TYPE DHT11


// Konfiguracja pod wyświetlanie wartości na pin

#define FIRST 2
#define SECOND 4
#define THIRD 5
#define FOURTH 23

// Konfiguracja pinu pod sygnalizacje zbyt wysokie temperatury
#define TEMPERATURE_PIN 19


void initConfiguration();
