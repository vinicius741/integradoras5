import sys
from ConnetionUDP import ConnetionUDP
from LDR import LDR
from LED import LED
from OrderScale import OrderScale
from USC import USC

ddress = "192.168.1.2"

myled = LED()

myldr = LDR()

rbscale = USC(5,100,OrderScale.DESCENDING)

nmcuscale = USC(0,100, OrderScale.ASCENDING)

conn = ConnetionUDP(555)

while True:
    print (sys.stderr, '\n Esperando mensagem ...')

    nodeldrvalue = nmcuscale.GetValueUniversalScale(float(conn.ReciveData()))

    raspberryldrvalue = nmcuscale.GetValueUniversalScale(myldr.GetLDRCount())

    if (abs( nodeldrvalue - raspberryldrvalue ) < 4):
        myled.sendsignalled("blink")
        
    elif (nodeldrvalue > raspberryldrvalue):
        myled.sendsignalled("off")

    elif (nodeldrvalue < raspberryldrvalue):
        myled.sendsignalled("on")
