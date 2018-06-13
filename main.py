import sys
from ConnetionUDP import ConnetionUDP
from LDR import LDR
from LED import LED
from UniversalScaleConversion import UniversalScaleConversion
from OrderScale import OrderScale

ddress = "192.168.x.x"

myled = LED()
myled.setdurationtime(4)

myldr = LDR()

rbscale = Universal(100,10, OrderScale.DESCENDING)

nmcuscale = Universal(0,100, OrderScale.ASCENDING)

conn = ConnetionUDP(555)

while True:
    temp = conn.ReciveData()

    nodeldrvalue = nmcuscale.GetValueUniversalScale(float(temp))

    raspberryldrvalue = rbscale.GetValueUniversalScale(myldr.GetLDRCount())
   
    if (abs( nodeldrvalue - raspberryldrvalue ) < 10):
        myled.sendsignalled("blink")
        conn.SendData("2", ddress)
        
    elif (nodeldrvalue > raspberryldrvalue):
        myled.sendsignalled("off")
        conn.SendData("0", ddress)

    elif (nodeldrvalue < raspberryldrvalue):
        myled.sendsignalled("on")
        conn.SendData("1", ddress)

