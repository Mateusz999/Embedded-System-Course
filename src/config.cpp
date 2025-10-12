#include "lib/config.h"
#include <Arduino.h>

// Funkcja inicjalizująca dla określenia roli danego pinu
void initConfiguration(){

    pinMode(INCREMENTOR,INPUT_PULLUP);
    pinMode(FIRST,OUTPUT);
    pinMode(SECOND,OUTPUT);
    pinMode(THIRD,OUTPUT);
    pinMode(FOURTH,OUTPUT);
    pinMode(TEMPERATURE_PIN,OUTPUT);

}