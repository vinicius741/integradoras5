import socket

UDP_IP = "192.168.1.4"
UDP_PORT = 555
MESSAGE = "Hello, World!"

print ("UDP target IP:", UDP_IP)
print ("UDP target port:", UDP_PORT)
print ("message:", MESSAGE)

sock = socket.socket(socket.AF_INET,  socket.SOCK_DGRAM) # UDP
sock.sendto(MESSAGE.encode(), (UDP_IP , UDP_PORT))
