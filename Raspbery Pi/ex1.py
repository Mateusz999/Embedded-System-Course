import RPi.GPIO as GPIO
import time
# -- WYBOR TRYBY NUMERACJI PINOW
GPIO.setmode(GPIO.BCM)

# -- KONFIGURACJA PINOW 
GPIO.setup(26, GPIO.OUT)
GPIO.setup(19, GPIO.OUT)
GPIO.setup(13, GPIO.OUT)
GPIO.setup(6, GPIO.OUT)
GPIO.setup(21, GPIO.IN, pull_up_down=GPIO.PUD_UP)


# - INICJALIZACJA TABLICY PINOUT
LED_PINOUT = [6, 13, 19, 26]

# - STAN PRZYCISKU ( ZMIENNA POMOCNICZA )
TACT_STATE = GPIO.HIGH

# ZMIENNA INKREMENTOWANA
inkrementor = 0

# TABLICA STATUSOW DLA DANEGO PINOUT
LED_STATE = [False, False, False, False]

try:
    while True:
        # - POBRANIE AKTUALNEGO STANU PINU 21 - PRZYCISK

        CURRENT_TACT_STATE = GPIO.input(21)

        # - JEZELI AKTUALNY STAN PRZYCISKU JEST LOW I STAN Z POPRZEDNIEJ INTERACJI WHILE
        # JEST HIGH WYKONUJE SIE INSTRUKCJA WARUNKOWA INKREMENTACJI LUB ZEROWANIA

        if CURRENT_TACT_STATE == GPIO.LOW and TACT_STATE == GPIO.HIGH:
            if inkrementor < 15:
                inkrementor += 1
            else:
                inkrementor = 0

        # - PRZELICZENIE LICZBY DECYMALNEJ NA KOD GRAYA

    
            gray_rep = inkrementor ^ (inkrementor >> 1)

        # - UCIECIE PIERWSZYCH DWOCH ZNAKOW ORAZ DOPELNIENIE DO 4 JESLI JEST KROTSZA

            bin_gray = bin(gray_rep)[2:].zfill(4)  

        # - KONTROLNE WYPISANIE NA EKRAN BINARNEJ REPREZENTACJI KODU GRAYA

            print(bin_gray)
        # - NADPISANIE STANU W TABLICY LED_STATE W ZALEZNOSCI OD WARTOSCI KODU GRAY
        # 1 - TRUE 
        # 0 - FALSE
            for i in range(4):
                LED_STATE[i] = bin_gray[i] == '1'
        # NADPISANIE ZMIENNEJ POMOCNICZEJ AKTUALNA WARTOSCIA STANU PRZYCISKU
        TACT_STATE = CURRENT_TACT_STATE
        time.sleep(0.2)

        # PRZECHODZIMY PRZEZ KAZDY INDEKS I ODPOWIADAJACY STAN LED
        for i, stan in enumerate(LED_STATE):
            if stan:
        # GDY TRUE - WLACZ DIODE
                GPIO.output(LED_PINOUT[i], GPIO.HIGH)
            else:
        # GDY FALSE - WYLACZ DIODE

                GPIO.output(LED_PINOUT[i], GPIO.LOW)
        # OBSLUGA PRZERWANIA GDY WPISZEMY NP CTRL + C W TERMINALU
        # RESETUJEMY WSZYSTKIE GPIO
except KeyboardInterrupt:
    GPIO.cleanup()
