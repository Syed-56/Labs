import socket
import json
import os


def calc(num1, num2, op):
    if op == '+': return num1 + num2
    elif op == '-': return num1 - num2
    elif op == '*': return num1 * num2
    elif op == '/':
        if num2 != 0:
            return num1 / num2
        else:
            return "Wrong Division"


s = socket.socket()
s.bind(('localhost', 9999))
s.listen(5)
print("Waiting for connection...")


while True:
    c, addr = s.accept()
    print("Got connection from", addr)


    data = c.recv(1024).decode()
    num1, op, num2 = data.split()
    num1, num2 = float(num1), float(num2)


    result = calc(num1, num2, op)


    record = {"num1": num1, "op": op, "num2": num2, "result": result}
    records = []
    if os.path.exists("calculations.json"):
        with open("calculations.json", 'r') as f:
            records = json.load(f)
    records.append(record)
    with open("calculations.json", 'w') as f:
        json.dump(records, f, indent=4)


    c.send(str(result).encode())
    c.close()
