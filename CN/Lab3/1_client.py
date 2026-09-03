import socket


s = socket.socket()
s.connect(('localhost', 9999))


num1 = input("First number: ")
op = input("Operation (+, -, *, /): ")
num2 = input("Second number: ")


s.send(f"{num1} {op} {num2}".encode())


result = s.recv(1024).decode()
print("Result:", result)


s.close()
