-- JOINS: retrieve data from two or more tables based on their relationship (Linked by keys)
-- Natural Join: Joins tables based on all columns that have values
SELECT * FROM EMPLOYEES NATURAL JOIN REGIONS;
--Display all basic info
SELECT FIRST_NAME,LAST_NAME,SALARY,JOB_TITLE,DEPARTMENT_NAME,COUNTRY_NAME,STATE_PROVINCE FROM EMPLOYEES
NATURAL JOIN DEPARTMENTS NATURAL JOIN LOCATIONS NATURAL JOIN COUNTRIES NATURAL JOIN JOBS;
-- but this is bad because natural join only shows those where all column values of table1 are find in table2. but like we only want wrt FKs so use join using..
-- USING CLAUSE: When both tables contain the column and we want to specify that explicitly 
SELECT FIRST_NAME,LAST_NAME,SALARY,JOB_TITLE,DEPARTMENT_NAME,COUNTRY_NAME,STATE_PROVINCE FROM EMPLOYEES
JOIN DEPARTMENTS USING (DEPARTMENT_ID) JOIN LOCATIONS USING (LOCATION_ID) JOIN COUNTRIES USING (COUNTRY_ID) JOIN JOBS USING (JOB_ID);

--CROSS JOIN: returns all possible combinations from 2 tables. If tableA has 10 rows and table2 has 5 rows then retruned = 50 rows. It follows no rule (where condition)
--Q: Display all possible combination of employee names and departments
SELECT E.FIRST_NAME, E.LAST_NAME, D.DEPARTMENT_NAME FROM EMPLOYEES E
CROSS JOIN DEPARTMENTS D;   --each employee will appear with each department

--INNER JOIN (or default JOIN): Shows only those results which have both attributes mentioned in join. like DEPARTMENT ID in Employees is a FK and in Department its PK so we join them
SELECT E.FIRST_NAME,E.LAST_NAME,E.SALARY,D.DEPARTMENT_ID,D.DEPARTMENT_NAME FROM EMPLOYEES E
INNER JOIN DEPARTMENTS D ON E.DEPARTMENT_ID = D.DEPARTMENT_ID;  --hence only employees assigned to a department will appear

--OUTER JOINS: They show matched rows plus the rows which are not matched from either of table (left or right)
--LEFT JOIN: Also retrieves the value from last table which are not related (i.e those employees which dont have a dept id)
SELECT E.FIRST_NAME,E.LAST_NAME,E.SALARY,D.DEPARTMENT_ID,D.DEPARTMENT_NAME FROM EMPLOYEES E
LEFT JOIN DEPARTMENTS D ON E.DEPARTMENT_ID = D.DEPARTMENT_ID;

--RIGHT JOIN: Same as above but works for right table
SELECT E.FIRST_NAME,E.LAST_NAME,E.SALARY,D.DEPARTMENT_ID,D.DEPARTMENT_NAME FROM EMPLOYEES E
RIGHT  JOIN DEPARTMENTS D ON E.DEPARTMENT_ID = D.DEPARTMENT_ID;

--FULL JOIN: Combines result of both inner and outer join. matched+left+right
SELECT E.FIRST_NAME, D.DEPARTMENT_NAME FROM EMPLOYEES E
FULL OUTER JOIN DEPARTMENTS D ON E.DEPARTMENT_ID=D.DEPARTMENT_ID;

--SELF JOIN: Join a table with itself by aliasing them with diff names. Like we can find who an employee's manager is even though both fall in entity of EMPLOYEE
SELECT CONCAT(E.FIRST_NAME,' ',E.LAST_NAME) AS EMP_NAME,E.SALARY AS EMP_SALARY,
       CONCAT(M.FIRST_NAME,' ',M.LAST_NAME) AS MANAGER_NAME,M.SALARY AS MANAGER_SALARY FROM EMPLOYEES E
JOIN EMPLOYEES M ON E.MANAGER_ID=M.EMPLOYEE_ID;
--similarly, E.EMPLOYEE_ID=M.EMPLOYEE_ID will show those employees who are managers
--this was inner self, we can do left right too.

--SETs: Combine results of multiple SELECT statements
--Union: Combine results of both selects and remove duplicates
SELECT EMPLOYEE_ID FROM EMPLOYEES UNION
SELECT EMPLOYEE_ID FROM JOB_HISTORY;    --retrieve current and previous employee ids
--Union ALL: Same as union but keep duplicates
SELECT EMPLOYEE_ID FROM EMPLOYEES UNION
SELECT EMPLOYEE_ID FROM JOB_HISTORY;    --same result as above but duplicates repeated (employee who also worked previously here at different post)

--Intersection: return common rows between 2 queries
SELECT EMPLOYEE_ID FROM EMPLOYEES INTERSECT
SELECT EMPLOYEE_ID FROM JOB_HISTORY;    --only employees who prevviously worked here

--minus: return rows in first queries but not in second
SELECT EMPLOYEE_ID FROM EMPLOYEES MINUS
SELECT EMPLOYEE_ID FROM JOB_HISTORY;    --employees who never left this job

--VIEWS: virtual tables of any attributes can be created in database which reflect the changes made on them. can act like a real table
CREATE VIEW EMP_INFO AS
SELECT FIRST_NAME,LAST_NAME,EMPLOYEE_ID,SALARY,JOB_ID,DEPARTMENT_ID FROM EMPLOYEES;
SELECT * FROM EMP_INFO; --retrieve data from the view created

--we can also limit rows while creating views with WHERE
CREATE VIEW RICH_EMPS AS
SELECT FIRST_NAME,LAST_NAME,EMPLOYEE_ID,SALARY,JOB_ID,DEPARTMENT_ID FROM EMPLOYEES
WHERE SALARY > 10000;
SELECT SALARY FROM RICH_EMPS;

--COMPLEX VIEWS: created with aggregates,groupby,joins and multiple tables. might not support DML queries
--view to display employee's name,salary,department,job,country
CREATE VIEW EMP_REAL_INFO AS
SELECT CONCAT(E.FIRST_NAME,' ',E.LAST_NAME) AS NAME, E.SALARY, D.DEPARTMENT_NAME, J.JOB_TITLE, C.COUNTRY_NAME FROM EMPLOYEES E
JOIN DEPARTMENTS D ON E.DEPARTMENT_ID=D.DEPARTMENT_ID
JOIN JOBS J ON E.JOB_ID=J.JOB_ID
JOIN LOCATIONS L ON D.LOCATION_ID=L.LOCATION_ID
JOIN COUNTRIES C ON L.COUNTRY_ID=C.COUNTRY_ID;

SELECT * FROM EMP_REAL_INFO;

--READ ONLY VIEW: Stops user from modifying the view
CREATE VIEW DEPT_READONLY AS 
SELECT * FROM DEPARTMENTS 
WITH READ ONLY;
--this wont run
UPDATE DEPT_READONLY
SET DEPARTMENT_NAME='Finance'
WHERE DEPARTMENT_ID=50;

--Check Option VIEW: after creating view with where condition, this make sures that the condition is met afterwards in DML.
CREATE VIEW DEPT50_VIEW AS
SELECT FIRST_NAME,DEPARTMENT_ID FROM EMPLOYEES
WHERE DEPARTMENT_ID=50
WITH CHECK OPTION;
--now before insertion in this view it will check if the department id is 50
INSERT INTO dept50_view 
VALUES ('Sultan',90);   --will give error

DROP VIEW EMP_INFO; --to drop a view

--CREATE OR REPLACE VIEWif we dont know that we created the view or want to update its definition. we can use it
CREATE OR REPLACE VIEW EMP_INFO AS
SELECT EMPLOYEE_ID,
FIRST_NAME,
LAST_NAME,
SALARY
FROM EMPLOYEES;

--INLINE VIEW: subquery written in FROM, it is not stored and only exist in runtime.
--Display employees who earn more than avg salary
SELECT * FROM (SELECT CONCAT(FIRST_NAME,' ',LAST_NAME), EMPLOYEE_ID, SALARY FROM EMPLOYEES)
WHERE SALARY > (SELECT AVG(SALARY) FROM EMPLOYEES);

--theres also a materialized view which occupies physical storage hence increasing performance.
