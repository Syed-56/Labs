-- Triggers: Stored procedure which is auto-fired when an event hits table, no manual calling.
-- Event on table --> trigger fires --> runs SQL
--Syntax:- (dont run)
CREATE OR REPLACE TRIGGER trigger_name
  BEFORE | AFTER | INSTEAD OF   -- WHEN
  INSERT | UPDATE | DELETE       -- EVENT
  ON table_name
  FOR EACH ROW | FOR EACH STATEMENT  -- GRANULARITY
BEGIN
  -- your SQL here
END;

-- Example, hrie date set when an employee is inserted by a trigger, it is set to be current sysdate
CREATE OR REPLACE TRIGGER set_created_at
  BEFORE INSERT ON employees
  FOR EACH ROW
BEGIN
  :NEW.hire_date := SYSDATE;
END;
/

INSERT INTO employees (employee_id, last_name, email, hire_date, job_id)
VALUES (999, 'Smith', 'jsmith@example.com', SYSDATE, 'IT_PROG');
SELECT employee_id, last_name, hire_date 
FROM employees 
WHERE employee_id = 999;

--to drop disable enable
DROP TRIGGER set_created_at;
ALTER TRIGGER set_created_at DISABLE;
ALTER TRIGGER set_created_at ENABLE;

--DML Triggers, most common
--Fire on INSERT/UPDATE/DELETE
CREATE OR REPLACE TRIGGER trg_dml_example
  BEFORE INSERT ON employees
  FOR EACH ROW
BEGIN
  :NEW.created_at := SYSDATE;
END;

--DDL Triggers
--Fire on schema changes: CREATE, ALTER, DROP.
CREATE OR REPLACE TRIGGER trg_ddl_audit
  AFTER CREATE ON SCHEMA
BEGIN
  INSERT INTO ddl_log(event, obj_name, happened_at)
  VALUES (ORA_SYSEVENT, ORA_DICT_OBJ_NAME, SYSDATE);
END;

--System Event Triggers
--Fire on DB-level events: STARTUP, SHUTDOWN, LOGON, LOGOFF, SERVERERROR
CREATE OR REPLACE TRIGGER trg_logon_audit
  AFTER LOGON ON DATABASE
BEGIN
  INSERT INTO login_log(username, login_time)
  VALUES (USER, SYSDATE);
END;

--Instead of triggers
--in normal table, or a view on single table we can easily do triggers but on a view created with join? confusion
-- This view joins 2 tables
CREATE VIEW emp_dept_view AS
  SELECT e.employee_id, e.first_name, e.last_name d.department_id
  FROM employees e JOIN departments d ON e.department_id = d.department_id;

-- Try insert → FAILS
INSERT INTO emp_dept_view VALUES (101, 'Ali', 'HR');
-- ERROR: cannot insert into join view

--to run your trigger instead of this default insert. we use INSTEAD OF trigger
CREATE OR REPLACE TRIGGER trg_instead_insert
  INSTEAD OF INSERT ON emp_dept_view
  FOR EACH ROW
BEGIN
  INSERT INTO employees(emp_id, first_name, last_name, dept_id)
  VALUES (:NEW.emp_id, :NEW.first_name, NEW.last_name, :NEW.dept_id);  -- now valid
END;

INSERT INTO emp_dept_view VALUES (101, 'Ali', 90);
