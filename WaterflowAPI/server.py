import socket
import sys
from time import sleep

HELLO_SERVER = "0"
HI_THERE     = "1"
WHATS_MY_ID  = "2"

Nodes = {}

# Create a TCP/IP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Bind the socket to the port
# print >>sys.stderr, 'Starting up on %s port %s' % server_address
sock.bind(('', 555))

while True:

    print >>sys.stderr, '\nWaiting to receive message ...'
    data, address = sock.recvfrom(1024)

    if data == HELLO_SERVER:

        print '\nSending HI_THERE message ...'  
        sleep(1);      
        sent = sock.sendto(HI_THERE, address)

    elif data == WHATS_MY_ID:

        print 'Sending new node id message ...'
        sleep(1);      
        Nodes.append(address)
        sent = sock.sendto(len(Nodes), address)

    else:
        print data
        pass