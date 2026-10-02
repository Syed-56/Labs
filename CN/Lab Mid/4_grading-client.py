import socket

s = socket.socket()
s.connect(('localhost',9999))
gradepoint = input("Enter GPA: ")
s.send(gradepoint.encode())
response = s.recv(1024).decode()
print("Server Response: ", response)
s.close()