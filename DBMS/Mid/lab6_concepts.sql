--Single Row Subquery - inner query returns 1 element
--Employee with Highest Salary
SELECT FIRST_NAME, LAST_NAME,SALARY FROM MY_EMPLOYEES
WHERE SALARY = (SELECT MAX(SALARY) FROM MY_EMPLOYEES);
--Employees earning more than avg salary
SELECT FIRST_NAME,LAST_NAME, SALARY FROM MY_EMPLOYEES
WHERE SALARY > (SELECT AVG(SALARY) FROM MY_EMPLOYEES);

--multiple row subquery - inner row returns multiple values
--employee who are in departments where there's a ST_MAN (stock manager)
SELECT FIRST_NAME, DEPARTMENT_ID, SALARY, JOB_ID FROM MY_EMPLOYEES
WHERE DEPARTMENT_ID IN (SELECT DEPARTMENT_ID FROM MY_EMPLOYEES WHERE JOB_ID='ST_MAN');

--employees whose salary is greater than atleast 1 shipping clerk
SELECT FIRST_NAME,EMPLOYEE_ID,SALARY FROM MY_EMPLOYEES
WHERE SALARY > ANY(SELECT SALARY FROM MY_EMPLOYEES WHERE JOB_ID='SH_CLERK');
--employees whose salary is greater than all shipping clerk
SELECT FIRST_NAME,EMPLOYEE_ID,SALARY FROM MY_EMPLOYEES
WHERE SALARY > ALL(SELECT SALARY FROM MY_EMPLOYEES WHERE JOB_ID='SH_CLERK');

--correlated subqueries
--employees who earn more than the average salary of their department
SELECT employee_id, first_name, salary, department_id FROM my_employees e
WHERE salary > (SELECT AVG(salary) FROM my_employees WHERE department_id = e.department_id);

--row subquery - checks multiple rows
--employees who have same job id and work in same department as of employee 103
SELECT FIRST_NAME,LAST_NAME,JOB_ID,DEPARTMENT_ID FROM MY_EMPLOYEES
WHERE (JOB_ID,DEPARTMENT_ID) = (SELECT JOB_ID,DEPARTMENT_ID FROM MY_EMPLOYEES WHERE EMPLOYEE_ID=103);

--inline view - create temperory group to perform query
-- departments where avg salary is more than 8000
SELECT DEPARTMENT_ID, ROUND(AVG_SALARY,1) FROM (SELECT DEPARTMENT_ID, AVG(SALARY) AS AVG_SALARY FROM MY_EMPLOYEES GROUP BY DEPARTMENT_ID)
WHERE AVG_SALARY > 8000;

--subqueries with DML
--increase the salary of a job by 10% where the minimum salary is 3000
UPDATE EMPLOYEES
SET salary = salary + (salary*0.10)
WHERE JOB_ID IN (SELECT JOB_ID FROM JOBS WHERE MIN_SALARY=3000);

--EXIST check if subquery returns a value and NOT EXIST check if it dont
--check if any employee is a manager
SELECT EMPLOYEE_ID, FIRST_NAME, LAST_NAME FROM EMPLOYEES E
WHERE EXISTS (SELECT 1 FROM EMPLOYEES WHERE MANAGER_ID = E.EMPLOYEE_ID);

--check if theres no department with 0 employees (handles NULL better)
SELECT DEPARTMENT_ID, DEPARTMENT_NAME FROM DEPARTMENTS D
WHERE NOT EXISTS (SELECT 1 FROM EMPLOYEES WHERE DEPARTMENT_ID = D.DEPARTMENT_ID);
