import socket

def grade(gradePoint):
    letterGrade = ''
    qualification = ''

    if gradePoint == 4.33:
        letterGrade = 'A+'
        qualification = 'Excellent'
    elif gradePoint == 4.00:
        letterGrade = 'A'
        qualification = 'Excellent'
    elif gradePoint == 3.67:
        letterGrade = 'A-'
        qualification = 'Very Good'
    elif gradePoint == 3.33:
        letterGrade = 'B+'
        qualification = 'Very Good'
    elif gradePoint == 3.00:
        letterGrade = 'B'
        qualification = 'Very Good'
    elif gradePoint == 2.67:
        letterGrade = 'B-'
        qualification = 'Good'
    elif gradePoint == 2.33:
        letterGrade = 'C+'
        qualification = 'Good'
    elif gradePoint == 2.00:
        letterGrade = 'C'
        qualification = 'Good'
    elif gradePoint == 1.67:
        letterGrade = 'C-'
        qualification = 'Pass'
    elif gradePoint == 1.33:
        letterGrade = 'D+'
        qualification = 'Pass'
    elif gradePoint == 1.00:
        letterGrade = 'D'
        qualification = 'Pass'
    else:
        letterGrade = 'F'
        qualification = 'Fail'
    
    return letterGrade,qualification

s = socket.socket()
s.bind(('localhost',9999))
s.listen(5)
print("Waiting for Connection")

while True:
    c, addr = s.accept()
    print("Got Connection From ", addr)
    gradePoint = float(c.recv(1024).decode())
    lG,qf = grade(gradePoint)
    response = f"Letter Grade: {lG} | Qualification: {qf}"
    c.send(response.encode())
    c.close()
    