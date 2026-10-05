import socket
import os

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(('localhost',9999))
s.listen(5)
print("Waiting For Connection")

while True:
    c, addr = s.accept()
    print("Got Connection From ", addr)
    data = c.recv(1024).decode()
    if not data:    break
    if data == "quit":  break
    reply = data.upper()
    c.send(str(reply).encode())
    
    if os.path.exists("records.txt"):
        with open("records.txt") as f:
            f.write(f"{data} - {reply}")
    c.close()