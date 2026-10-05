import socket

s = socket.socket()
s.connect('localhost',8888)
inputValue = input("Enter Value: ")
opValue = input("Enter Operation: ")
s.send(f"{inputValue} {opValue}".encode())
result = s.recv(1024).decode()
print("Result: ", result)
s.close()