import socket


def get_grade(marks):
    if marks >= 90:   return "A+", 4.33, "Excellent"
    elif marks >= 85: return "A",  4.00, "Excellent"
    elif marks >= 80: return "A-", 3.66, "Very good"
    elif marks >= 75: return "B+", 3.33, "Very good"
    elif marks >= 70: return "B",  3.00, "Very good"
    elif marks >= 65: return "B-", 2.66, "Good"
    elif marks >= 60: return "C+", 2.33, "Good"
    elif marks >= 55: return "C",  2.00, "Good"
    elif marks >= 50: return "C-", 1.66, "Passable"
    elif marks >= 45: return "D+", 1.33, "Passable"
    elif marks >= 40: return "D",  1.00, "Passable"
    else:             return "E",  0.00, "Failure"


s = socket.socket()
s.bind(('localhost', 6060))
s.listen(5)
print("Grade server waiting...")


while True:
    c, addr = s.accept()
    print("Got connection from", addr)


    marks = float(c.recv(1024).decode())
    letter, gp, qual = get_grade(marks)


    response = f"Letter Grade: {letter} | Grade Points: {gp} | Qualification: {qual}"
    c.send(response.encode())
    c.close()
