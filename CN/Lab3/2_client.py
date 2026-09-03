import socket


s = socket.socket()
s.connect(('localhost', 6060))


marks = input("Enter your marks (0-100): ")
s.send(marks.encode())


response = s.recv(1024).decode()
print("Server response:", response)


s.close()
