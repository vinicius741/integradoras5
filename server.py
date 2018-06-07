import socket
import sys
from time import sleep
from OrderScale import OrderScale
from USC import USC
from LED import LED
from LDR import LDR

address = "192.168.1.2"

myled = LED()

myldr = LDR()

rbscale = USC(5,200,OrderScale.DESCENDING)

nmcuscale = USC(0,1000, OrderScale.ASCENDING)

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

sock.bind(('', 555))

while True:

    print >>sys.stderr, '\n Esperando mensagem ...'
    
    data, address = sock.recvfrom(1024)
    nodeldrvalue = nmcuscale.GetValueUniversalScale(float(data))

    raspberryldrvalue = nmcuscale.GetValueUniversalScale(myldr.GetLDRCount())
    
    if (abs( nodeldrvalue - raspberryldrvalue ) < 4):
        sock.sendto("2", address)
        myled.sendsignalled("blink")
        
    elif (nodeldrvalue > raspberryldrvalue):
        sock.sendto("1", address)
        myled.sendsignalled("off")

    elif (nodeldrvalue < raspberryldrvalue):
        sock.sendto("0", address)
        myled.sendsignalled("on")