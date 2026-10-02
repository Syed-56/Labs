import socket
import json
import os

def calc(num1, num2, op):
    if op == '+':    return num1+num2
    elif op == '-':    return num1-num2
    elif op == '*':    return num1*num2
    elif op == '/':    
        if num2==0: return "Error"
        else:   return num1/num2
        
s = socket.socket()
s.bind(('localhost',9999))
s.listen(5)
print("Waiting For Connection")

while True:
    c, addr = s.accept()
    print("Got Connection From ", addr)
    data = c.recv(1024).decode()
    num1,num2,op = data.split()
    num1,num2 = float(num1), float(num2)
    result = calc(num1,num2,op)
    #now add the data in json file as records
    record = {'num1': num1, 'num2':num2, 'op':op}
    records = []
    
    if os.path.exists('3_calcs.json'):
        with open('3_calcs.json', 'r') as f:
            records = json.load(f)
    records.append(record)
    with open('3_calcs.json', 'w') as f:
        json.dump(records,f,indent=4)
    
    c.send(str(result).encode())    #reply to client
    c.close()