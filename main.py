import sys
from ConnetionUDP import ConnetionUDP
from LDR import LDR
from LED import LED
from Universal import Universal
from OrderScale import OrderScale

ddress = "192.168.1.2"

myled = LED()
myled.setdurationtime(1)

nodeLED = LED()

nodeLED.setpinled(15)
nodeLED.setdurationtime(1)

myldr = LDR()

rbscale = Universal(100,10, OrderScale.DESCENDING)

nmcuscale = Universal(0,100, OrderScale.ASCENDING)

conn = ConnetionUDP(555)

while True:
    temp = conn.ReciveData()

    nodeldrvalue = nmcuscale.GetValueUniversalScale(float(temp))

    raspberryldrvalue = rbscale.GetValueUniversalScale(myldr.GetLDRCount())
   
    if (abs( nodeldrvalue - raspberryldrvalue ) < 20):
        myled.sendsignalled("blink")
        nodeLED.sendsignalled("blink")
        
    elif (nodeldrvalue > raspberryldrvalue):
        myled.sendsignalled("off")
        nodeLED.sendsignalled("on")

    elif (nodeldrvalue < raspberryldrvalue):
        myled.sendsignalled("on")
        nodeLED.sendsignalled("off")

