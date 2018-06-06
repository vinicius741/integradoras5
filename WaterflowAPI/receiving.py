import socket
import sys
from time import sleep

HELLO_SERVER = "hellooooooo"
HI_THERE     = "1"
WHATS_MY_ID  = "2"

NodeArray = {}

# Create a TCP/IP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Bind the socket to the port
# print >>sys.stderr, 'Starting up on %s port %s' % server_address
sock.bind(('192.168.1.2', 555))

while True:
    print >>sys.stderr, '\nWaiting to receive message ...'
    data, address = sock.recvfrom(4096)

    print >>sys.stderr, 'Received [ %s ] bytes from [ %s ]' % (len(data), address)
    print >>sys.stderr, 'Data: ', data
    
    if data:
        sent = sock.sendto(str(int(data) + 10), address)
        print >>sys.stderr, 'Sent [ %s ] bytes back to [ %s ]' % (sent, address)