import RPi.GPIO as GPIO
import time

class LED:
    __pinled = 14
    __durationtime = 1
    def __init__(self):
        GPIO.setmode(GPIO.BCM)
        GPIO.setwarnings(False)
        GPIO.setup(self.__pinled,GPIO.OUT)

    def setpinled(self, pin):
        self.__pinled = pin
        GPIO.setup(self.__pinled,GPIO.OUT)

    def setdurationtime(self, time):
        self.__durationtime = time
    
    def sendsignalled(self, typeofsignal):
        if typeofsignal == "on":
            GPIO.output(self.__pinled,GPIO.HIGH) # Liga o led
            time.sleep(self.__durationtime)
            GPIO.output(self.__pinled,GPIO.LOW)

        elif typeofsignal == "off":
            time.sleep(self.__durationtime)

        elif typeofsignal == "blink":
            blinktime = __durationtime/5

            for i in range(0, 5):
                GPIO.output(self.__pinled,GPIO.HIGH) # Liga o led
                time.sleep(self.blinktime)
                GPIO.output(self.__pinled,GPIO.LOW)


l = LED()
l.setdurationtime(2)
l.sendsignalled("on")
l.sendsignalled("off")
l.sendsignalled("blink")