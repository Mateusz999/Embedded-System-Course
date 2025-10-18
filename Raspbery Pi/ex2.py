import dht11
import RPi.GPIO as GPIO
import time

# Ustawienie GPIO
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)

GPIO.cleanup()

# Inicjalizacja czujnika na GPIO21
instance = dht11.DHT11(pin=21)
GPIO.setup(26, GPIO.OUT)
try:
    while True:
        # odczyt informacji z czujnika
        result = instance.read()
        if result.is_valid():
            # jezeli dane sa poprawne to wypisujemy je w consoli
            print(f"Temperatura: {result.temperature}°C  Wilgotność: {result.humidity}%")
            # jezeli temperatura jest powyzej 27.5 stopni to zapala sie dioda
            if(result.temperature > 27.5):
                GPIO.output(26,GPIO.HIGH)

            # jezeli temperatura jest ponizej 27.5 stopni to dioda gasnie
            elif(result.temperature < 27.5):
                GPIO.output(26,GPIO.LOW)

        time.sleep(1)
except KeyboardInterrupt:
    GPIO.cleanup()
