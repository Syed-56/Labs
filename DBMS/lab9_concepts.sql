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
  SELECT e.employee_id, e.first_name, e.last_name d.department_id, d.department_name
  FROM employees e JOIN departments d ON e.department_id = d.department_id;

-- Try insert → FAILS
CREATE OR REPLACE TRIGGER insteadoftrigger
    INSTEAD OF INSERT ON emp_dept_view
    BEGIN
        INSERT INTO EMPLOYEES (employee_id, first_name, last_name)
        VALUES (:NEW.employee_id, :NEW.first_name, :NEW.last_name);
        INSERT INTO DEPARTMENTS (department_id, department_name)
        VALUES (:NEW.department_id, :NEW.department_name);
    END;
/

INSERT INTO emp_dept_view (employee_id, first_name, last_name, department_id, department_name)
VALUES (300, 'Sultan', 'Khan', 90, 'IT');

--PL/SQL
--outputinng
SET SERVEROUTPUT ON;
CREATE TRIGGER printwheninsert
    AFTER INSERT ON EMPLOYEES
    BEGIN
        DBMS_OUTPUT.PUT_LINE('You Inserted');
    END;
/
INSERT INTO EMPLOYEES (employee_id,last_name,email,job_id,hire_date)
VALUES (10000,'sutlan','non@gmail.com','IT_PROG',SYSDATE);

--audit table
-- first create a table to store audits
CREATE OR REPLACE TRIGGER auditing
    BEFORE INSERT OR UPDATE OR DELETE ON EMPLOYEES
    FOR EACH ROW ENABLE
    DECLARE
        v_user VARCHAR(20);
        v_date DATE;
        v_new_name VARCHAR(20);
        v_old_name VARCHAR(20);
    BEGIN
        SELECT user,sysdate INTO v_user,v_date FROM dual;
        v_new_name := :NEW.first_name || ' ' || :NEW.last_name;
        v_old_name := :OLD.first_name || ' ' || :OLD.last_name;
        IF INSERTING THEN
            INSERT INTO SH_USER(new_name,old_name,user_name,entry_date,operation)
            VALUES (v_new_name,NULL,v_user,v_date,'INSERT');
        ELSIF UPDATING THEN
            INSERT INTO SH_USER(new_name,old_name,user_name,entry_date,operation)
            VALUES (v_new_name,v_old_name,v_user,v_date,'UPDATE');
        ELSIF DELETING THEN
            INSERT INTO SH_USER(new_name,old_name,user_name,entry_date,operation)
            VALUES (NULL,v_old_name,v_user,v_date,'DELETE');
        END IF;
    END;
/

--if else
CREATE OR REPLACE TRIGGER newtrigger
    BEFORE INSERT OR UPDATE OR DELETE ON EMPLOYEES
    FOR EACH ROW
    DECLARE
        vuser VARCHAR(50);
    BEGIN
        SELECT USER INTO vuser FROM dual;
        IF INSERTING THEN
            DBMS_OUTPUT.PUT_LINE('Inserting ' || vuser);
        ELSIF UPDATING THEN
            DBMS_OUTPUT.PUT_LINE('Updating ' || vuser);
        ELSIF DELETING THEN
            DBMS_OUTPUT.PUT_LINE('Deleting ' || vuser);
        END IF;
    END;
/

--backup table
CREATE TABLE superheroes (Sh_name VARCHAR2(30));
 
CREATE TABLE superheroes_backup
AS SELECT * FROM superheroes WHERE 1 = 2;

CREATE OR REPLACE TRIGGER backuptrigger1
    BEFORE INSERT OR UPDATE OR DELETE ON superheroes
    FOR EACH ROW ENABLE
    BEGIN
        IF INSERTING THEN
            INSERT INTO superheroes_backup(sh_name)
            VALUES (:NEW.sh_name);
        ELSIF DELETING THEN
            DELETE FROM superheroes_backup
            WHERE sh_name = :OLD.sh_name;
        ELSIF UPDATING THEN
            UPDATE superheroes_backup
            SET sh_name = :NEW.sh_name
            WHERE sh_name = :OLD.sh_name;
        END IF;
    END;
/

--DDL TRIGGERS
CREATE TABLE schema_audit (
    ddl_date DATE,
    ddl_user VARCHAR(20),
    object_created VARCHAR(20),
    object_user VARCHAR(20),
    operation VARCHAR(20)
);

CREATE OR REPLACE TRIGGER ddltrigger
    AFTER DDL ON SCHEMA    --we can alsu type DATABASE
    BEGIN
        INSERT INTO schema_audit VALUES(
            sysdate,sys_context('USERENV','CURRENT_USER'),
            ora_dict_obj_type, ora_dict_obj_name, ora_sysevent
        );    
    END;
/

--system triggers
--logon
CREATE TABLE hr_evnt_audit (
    event_type   VARCHAR2(30),
    logon_date   DATE,
    logon_time   VARCHAR2(15),
    logof_date   DATE,
    logof_time   VARCHAR2(15)
);
CREATE OR REPLACE TRIGGER hr_lgon_audit
AFTER LOGON ON SCHEMA
BEGIN
    INSERT INTO hr_evnt_audit VALUES (
        ora_sysevent, sysdate,
        TO_CHAR(sysdate, 'hh24:mi:ss'),
        NULL, NULL
    );
    COMMIT;
END;

--logof
CREATE OR REPLACE TRIGGER log_off_audit
BEFORE LOGOFF ON SCHEMA
BEGIN
    INSERT INTO hr_evnt_audit VALUES (
        ora_sysevent, NULL, NULL,
        SYSDATE, TO_CHAR(sysdate, 'hh24:mi:ss')
    );
    COMMIT;
END;
/
--we can use DATABASE instead of SCHEMA with admin privileges
--startup
CREATE TABLE startup_audit (
    Event_type   VARCHAR2(15),
    event_date   DATE,
    event_time   VARCHAR2(15)
);
 
CREATE OR REPLACE TRIGGER startup_audit
AFTER STARTUP ON DATABASE
BEGIN
    INSERT INTO startup_audit VALUES (
        ora_sysevent, SYSDATE,
        TO_CHAR(sysdate, 'hh24:mm:ss')
    );
END;
/

--shutdown and gather system stats
CREATE OR REPLACE TRIGGER before_shutdown
BEFORE SHUTDOWN ON DATABASE
BEGIN
    gather_system_stats;
END;
/