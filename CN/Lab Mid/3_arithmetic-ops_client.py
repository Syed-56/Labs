import socket

s = socket.socket()
s.connect(('localhost',9999))

num1 = input("Enter num1: ")
num2 = input("Enter num2: ")
op = input("Enter operation: ")

s.send(f"{num1} {num2} {op}".encode())
result = s.recv(1024).decode()
print("Result: ", result)
s.close()