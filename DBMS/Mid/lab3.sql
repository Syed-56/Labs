--Task1
CREATE TABLE EMPLOYEES1(
    emp_id1 VARCHAR2(10) PRIMARY KEY,
    emp_name1 VARCHAR2(50),
    age1 NUMBER,
    salary1 NUMBER,
    join_date1 DATE
);

--Task2
ALTER TABLE EMPLOYEES1
MODIFY emp_name1 VARCHAR2(100);

--Task3
ALTER TABLE EMPLOYEES1
ADD email1 VARCHAR2(100);

--Task4
ALTER TABLE EMPLOYEES1
ADD CONSTRAINT unique_email1 UNIQUE(email1); 

--Task5
ALTER TABLE EMPLOYEES1
ADD CHECK (age1>=18); 

--Task6
INSERT INTO EMPLOYEES1(emp_id1,emp_name1,age1,salary1,join_date1,email1)
VALUES ('100','Sultan',19,200000,'19-AUG-2025','sultan100@gmail.com');
INSERT INTO EMPLOYEES1(emp_id1,emp_name1,age1,salary1,join_date1,email1)
VALUES ('101','Ali',21,50000,'14-SEP-2026','ali101@gmail.com');
INSERT INTO EMPLOYEES1(emp_id1,emp_name1,age1,salary1,join_date1,email1)
VALUES ('102','Hammad',20,175000,'14-JUL-2025','hammad102@gmail.com');
INSERT INTO EMPLOYEES1(emp_id1,emp_name1,age1,salary1,join_date1,email1)
VALUES ('103','Huzaifa',21,150000,'08-DEC-2025','huzaifa103@gmail.com');
INSERT INTO EMPLOYEES1(emp_id1,emp_name1,age1,salary1,join_date1,email1)
VALUES ('xyz','Mufti',20,100000,'19-JAN-2025','mufti104@gmail.com');

--Task7
INSERT INTO EMPLOYEES1(emp_id1,emp_name1,age1,salary1,join_date1,email1)
VALUES ('167','Ismail',16,900000,'07-FEB-2027','silat167@gmail.com');

--Task8
INSERT INTO EMPLOYEES1(emp_id1,emp_name1,age1,salary1,join_date1,email1)
VALUES ('168','Majid',19,60000,'14-FEB-2027','mufti104@gmail.com');
 
--Task9
DELETE FROM EMPLOYEES1 WHERE emp_id1 = 'xyz';
ROLLBACK;

--Task10
TRUNCATE TABLE EMPLOYEES1;