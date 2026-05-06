--PL/SQL combines sql with conditional logic of programming
DECLARE
	-- Declarations section (optional)
BEGIN
	-- Executable statements (required)
EXCEPTION
	-- Exception handling section (optional)
END;
/

--output and variable
SET SERVEROUTPUT ON

DECLARE
    sec_name VARCHAR(20) := 'Sec E';
    sub_name VARCHAR(20) := 'DBMS';
BEGIN
    DBMS_OUTPUT.PUT_LINE('This is ' || sec_name || ' of subject ' || sub_name);
END;
/

--arithmetic
SET SERVEROUTPUT ON

DECLARE
    var1 INTEGER := 5;
    var2 INTEGER := 10;
    var3 INTEGER;
    var4 INTEGER;
BEGIN
    var3 := var1+var2;
    var4 := var3/2.0;
    DBMS_OUTPUT.PUT_LINE('var3='||var3||'var4='||var4);
END;
/

--nested begins and global variable
SET SERVEROUTPUT ON;
 
DECLARE
    -- Global variables
    num1 NUMBER := 95;
    num2 NUMBER := 85;
BEGIN
    DBMS_OUTPUT.PUT_LINE('Outer Variable num1: ' || num1);
    DBMS_OUTPUT.PUT_LINE('Outer Variable num2: ' || num2);
 
    DECLARE
        -- Local variables (shadow the outer ones)
        num1 NUMBER := 195;
        num2 NUMBER := 185;
    BEGIN
        DBMS_OUTPUT.PUT_LINE('Inner Variable num1: ' || num1);
        DBMS_OUTPUT.PUT_LINE('Inner Variable num2: ' || num2);
    END;
END;
/

--inherit datatype of column with TYPE
SET SERVEROUTPUT ON

DECLARE
    e_id    employees.employee_id%TYPE;
    e_name  employees.FIRST_NAME%TYPE;
    e_lname employees.LAST_NAME%TYPE;
    d_name  departments.DEPARTMENT_NAME%TYPE;
BEGIN
    SELECT e.EMPLOYEE_ID, e.FIRST_NAME, e.LAST_NAME, d.DEPARTMENT_NAME
    INTO e_id, e_name, e_lname, d_name FROM employees e
    JOIN departments d ON e.DEPARTMENT_ID = d.DEPARTMENT_ID
    WHERE  e.EMPLOYEE_ID = 100;

    DBMS_OUTPUT.PUT_LINE('EMPLOYEE ID: '         || e_id);
    DBMS_OUTPUT.PUT_LINE('EMPLOYEE First Name: ' || e_name);
    DBMS_OUTPUT.PUT_LINE('EMPLOYEE Last Name: '  || e_lname);
    DBMS_OUTPUT.PUT_LINE('DEPARTMENT Name: '     || d_name);
END;
/

--if else
SET SERVEROUTPUT ON;
 
DECLARE
    e_id  employees.EMPLOYEE_ID%TYPE := 100;
    e_sal employees.SALARY%TYPE;
BEGIN
    SELECT salary INTO e_sal FROM employees WHERE EMPLOYEE_ID = e_id;
 
    IF (e_sal <= 15000) THEN
        UPDATE employees SET salary = e_sal + 300 WHERE EMPLOYEE_ID = e_id;
    ELSIF (e_sal <= 20000) THEN
        UPDATE employees SET salary = e_sal + 200 WHERE EMPLOYEE_ID = e_id;
    ELSIF (e_sal <= 25000) THEN
        UPDATE employees SET salary = e_sal + 100 WHERE EMPLOYEE_ID = e_id;
    ELSE
        UPDATE employees SET salary = e_sal + 400 WHERE EMPLOYEE_ID = e_id;
    END IF;
 
    DBMS_OUTPUT.PUT_LINE('Salary updated: ' || e_sal);
END;
/

--case
SET SERVEROUTPUT ON

DECLARE
    e_sal EMPLOYEES.salary%TYPE;
    e_id  EMPLOYEES.employee_id%TYPE:=100;
BEGIN
    SELECT salary INTO e_sal FROM EMPLOYEES
    WHERE employee_id=e_id;
    
    CASE
        WHEN e_sal > 5000 THEN
            UPDATE EMPLOYEES SET SALARY = e_sal + 1000 WHERE e_id=employee_id;
        ELSE
            DBMS_OUTPUT.PUT_LINE('No Such Record');
    END CASE;
END;
/

--loop
SET SERVEROUTPUT ON

DECLARE
    
BEGIN
    FOR c IN (SELECT EMPLOYEE_ID, FIRST_NAME, SALARY FROM employees
              WHERE DEPARTMENT_ID = 90)
    LOOP 
        DBMS_OUTPUT.PUT_LINE('Employee '||c.FIRST_NAME||' has salary '||c.SALARY);
    END LOOP;
END;

--prodecures
CREATE [OR REPLACE] PROCEDURE procedure_name
    (parameter_name [IN | OUT | IN OUT] data_type)	--IN is accept parameters and OUT for returning
IS
    -- Declarative section (variables, constants, etc.)
BEGIN
    -- Executable section (the logic)
EXCEPTION
    -- Exception handling section
END procedure_name;

--example
SET SERVEROUTPUT ON;
CREATE OR REPLACE PROCEDURE Get_Salary (
    e_id  IN  NUMBER,
    e_sal OUT NUMBER
)
IS
BEGIN
    SELECT SALARY INTO e_sal FROM EMPLOYEES WHERE e_id=employee_id;
END;
/

DECLARE
    salary_temp INTEGER;
BEGIN
    Get_salary(100,salary_temp);
    DBMS_OUTPUT.PUT_LINE('Salary of Employee '||100||' is '||salary_temp);
END;
/
