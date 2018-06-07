import RPi.GPIO as GPIO
import time

class LDR:
    def __init__(self, pin = 3):
        GPIO.setmode(GPIO.BCM)
        GPIO.setwarnings(False)
        self.__PinLDR__ = pin


    def GetLDRCount(Self):
        count = 0

        GPIO.setup(self.__PinLDR__, GPIO.OUT)
        GPIO.output(self.__PinLDR__, GPIO.LOW)

        time.sleep(0.1)
        GPIO.setup(self.__PinLDR__, GPIO.IN)

        while (GPIO.input(self.__PinLDR__) == GPIO.LOW):
            count += 1

        return count

l = LDR()

for x in range(0, 10)
    print (l.GetLDRCount())