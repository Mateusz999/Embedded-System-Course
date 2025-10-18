import dht11
import RPi.GPIO as GPIO
import time
from luma.core.interface.serial import i2c
from luma.oled.device import sh1106
from luma.core.render import canvas
from PIL import ImageFont

# Inicjalizacja OLED
serial = i2c(port=1, address=0x3C)
device = sh1106(serial)

# GPIO
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)
GPIO.cleanup()

# Czujnik DHT11 na GPIO21
instance = dht11.DHT11(pin=21)

try:
    while True:
        result = instance.read()
        if result.is_valid():
            temp = result.temperature
            hum = result.humidity
            print(f"Temperatura: {temp}°C  Wilgotność: {hum}%")
        # TWORZENIE OBIEKTU, NA KTÓRYM MOŻNA RYSOWAĆ
            with canvas(device) as draw:

        # RYSOWANIE OBRAMOWANIA DOOKOŁA
                draw.rectangle(device.bounding_box, outline="white", fill="black")
        # USTAWIANIE OFFSETU, NAPISU ORAZ KOLORU JAKIM ZOSTANIE WYPEŁNIONY NAPIS
                draw.text((27, 17), f"Temp: {temp}°C", fill="white")
                draw.text((27, 17 + 15), f"Wilg: {hum}%", fill="white")


      
        time.sleep(0.1)
except KeyboardInterrupt:
    GPIO.cleanup()
