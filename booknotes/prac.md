### DQL 查询练习

以下是您给出的 SQL 练习题的解答。针对每一项的查询要求，提供了 SQL 查询示例。

---

### 1. 最简单查询语句：

**查询所有员工信息**
```sql
SELECT * FROM emp;
```

**查询所有部门信息**
```sql
SELECT * FROM dept;
```

**查询所有员工的编号, 姓名，基本工资，工作岗位信息**
```sql
SELECT EMPNO, ENAME, SAL, JOB FROM emp;
```

---

### 2. 使用算术表达式的查询语句：

**查询所有员工的编号, 姓名，基本工资，涨8%之后的基本工资信息**
```sql
SELECT EMPNO, ENAME, SAL, SAL * 1.08 AS NEW_SAL FROM emp;
```

**查询所有员工的编号, 姓名，基本工资，年薪信息**  
（假设年薪 = 基本工资 * 12）
```sql
SELECT EMPNO, ENAME, SAL, SAL * 12 AS ANNUAL_SAL FROM emp;
```

**查询所有员工的编号, 姓名，基本工资，年薪+1000后的信息**  
```sql
SELECT EMPNO, ENAME, SAL, (SAL * 12 + 1000) AS NEW_SALARY FROM emp;
```

---

### 3. 使用字段别名：

**查询所有员工的编号, 姓名，年薪信息并将查询的字段取别名**
```sql
SELECT EMPNO AS "Employee Number", ENAME AS "Employee Name", SAL * 12 AS "Annual Salary" FROM emp;
```

**查询所有员工的编号, 姓名，年薪信息并将查询的字段取别名（省略 `AS`）**
```sql
SELECT EMPNO "Employee Number", ENAME "Employee Name", SAL * 12 "Annual Salary" FROM emp;
```

**查询所有员工的年度总工资（包括年终奖）信息并将查询的字段取别名**  
（假设年终奖是 `COMM` 列）
```sql
SELECT EMPNO, ENAME, (SAL * 12 + COALESCE(COMM, 0)) AS "Total Annual Salary" FROM emp;
```

---

### 4. 去重查询：

**查询所有员工的部门编号信息**
```sql
SELECT DEPTNO FROM emp;
```

**查询所有员工的部门编号信息 , 要求部门编号不重复**
```sql
SELECT DISTINCT DEPTNO FROM emp;
```

**查询所有员工的职位信息 ，要求职位不重复**
```sql
SELECT DISTINCT JOB FROM emp;
```

**查询所有员工的部门编号，职位 ，要求部门编号不重复**
```sql
SELECT DISTINCT DEPTNO, JOB FROM emp;
```

---

### 5. 排序查询：

**查询所有员工的部门编号，姓名，基本工资信息并按照基本工资升序排序**
```sql
SELECT DEPTNO, ENAME, SAL FROM emp ORDER BY SAL ASC;
```

**查询所有员工的部门编号，姓名，基本工资信息并按照基本工资降序排序**
```sql
SELECT DEPTNO, ENAME, SAL FROM emp ORDER BY SAL DESC;
```

**按多字段排序，查询所有员工的部门编号，姓名，基本工资信息并按照部门编号和基本工资升序排序**
```sql
SELECT DEPTNO, ENAME, SAL FROM emp ORDER BY DEPTNO ASC, SAL ASC;
```

**使用字段别名排序，查询所有员工的部门编号，姓名，年薪信息并按照年薪升序排序（年薪取别名）**
```sql
SELECT DEPTNO, ENAME, SAL * 12 AS "Annual Salary" FROM emp ORDER BY "Annual Salary" ASC;
```

---

### 6. 分页查询：

**查询前3名员工信息**
```sql
SELECT * FROM emp LIMIT 3;
```

**查询第3-6名员工信息**
```sql
SELECT * FROM emp LIMIT 2, 4;  -- 从第3条开始，查询4条数据
```

---

### 7. 合并查询：

**查询出部门编号为10和20的员工信息**
```sql
SELECT * FROM emp WHERE DEPTNO = 10
UNION ALL
SELECT * FROM emp WHERE DEPTNO = 20;
```

**查询出部门编号为10和20的员工信息，过滤掉重复的数据**
```sql
SELECT * FROM emp WHERE DEPTNO = 10
UNION
SELECT * FROM emp WHERE DEPTNO = 20;
```

---

### 8. `WHERE` 子句查询条件：

**查询属于10号部门的员工信息**
```sql
SELECT * FROM emp WHERE DEPTNO = 10;
```

**查询姓名为"king"的员工信息**
```sql
SELECT * FROM emp WHERE ENAME = 'KING';
```

**查询入职日期为:'1981-05-01'的员工信息**
```sql
SELECT * FROM emp WHERE HIREDATE = '1981-05-01';
```

---

### 9. 查询条件中使用比较运算符：

**查询基本工资大于2900元的员工信息**
```sql
SELECT * FROM emp WHERE SAL > 2900;
```

**查询部门编号不等于30的员工信息**
```sql
SELECT * FROM emp WHERE DEPTNO != 30;
```

**查询基本工资在1600元到3200元之间的员工信息**
```sql
SELECT * FROM emp WHERE SAL BETWEEN 1600 AND 3200;
```

**查询姓名为： 'SMITH','CLARK','KING' 中，其中一个的员工信息**
```sql
SELECT * FROM emp WHERE ENAME IN ('SMITH', 'CLARK', 'KING');
```

---

### 10. 使用 `LIKE` 运算符执行模糊查询：

**查询姓名以S开头的员工信息**
```sql
SELECT * FROM emp WHERE ENAME LIKE 'S%';
```

**查询姓名为5个字母并且以S结尾的员工信息**
```sql
SELECT * FROM emp WHERE ENAME LIKE '_____S';
```

**查询姓名中包含A的员工信息**
```sql
SELECT * FROM emp WHERE ENAME LIKE '%A%';
```

---

### 11. 使用 `IS NULL` 运符进行空值判断：

**查询奖金为null的员工信息**
```sql
SELECT * FROM emp WHERE COMM IS NULL;
```

**查询奖金不为null的员工信息**
```sql
SELECT * FROM emp WHERE COMM IS NOT NULL;
```

---

### 12. 查询条件中可以使用逻辑运算符：

**查询属于10号部门并且基本工资大于1000的员工信息**
```sql
SELECT * FROM emp WHERE DEPTNO = 10 AND SAL > 1000;
```

**查询属于10号部门或者职位为："CLERK"的员工信息**
```sql
SELECT * FROM emp WHERE DEPTNO = 10 OR JOB = 'CLERK';
```

**查询基本工资不为：800，1500和2000的员工信息**
```sql
SELECT * FROM emp WHERE SAL NOT IN (800, 1500, 2000);
```

---

### 13. 可使用小括号强行改变运算顺序：

**查询职位为："SALESMAN"或者"CLERK"并且基本工资大于等于1280的员工信息**
```sql
SELECT * FROM emp WHERE (JOB = 'SALESMAN' OR JOB = 'CLERK') AND SAL >= 1280;
```

---

### 14. 多行函数：

**查询基本工资的平均值，最大值，最小值，和的信息**
```sql
SELECT AVG(SAL) AS avg_salary, MAX(SAL) AS max_salary, MIN(SAL) AS min_salary, SUM(SAL) AS total_salary FROM emp;
```

**查询入职日期的最大值，最小值信息**
```sql
SELECT MAX(HIREDATE) AS latest_hire_date, MIN(HIREDATE) AS earliest_hire_date FROM emp;
```

---

### 15. 多行函数与空值：

**查询奖金的条数，和，平均值信息**
```sql
SELECT COUNT(COMM) AS num_comm, SUM(COMM) AS total_comm, AVG(COMM) AS avg_comm FROM emp;
```

**查询奖金的条数，和，平均值信息, 奖金为null时，用0代替**
```sql
SELECT COUNT(COALESCE(COMM, 0)) AS num_comm, SUM(COALESCE(COMM, 0)) AS total_comm, AVG(COALESCE(COMM, 0)) AS avg_comm FROM emp;
```

---

### 16. `COUNT` 函数的说明：

**查询员工表的总记录数**
```sql
SELECT COUNT(*) FROM emp;
```

**查询奖金不为空的总记录数**
```sql
SELECT COUNT(COMM) FROM emp WHERE COMM IS NOT NULL;
```

**查询奖金不为空且不重复的总记录数**
```sql
SELECT COUNT(DISTINCT COMM) FROM emp WHERE COMM IS NOT NULL;
```

**查询奖金不为空且不重复的总记录数，奖金为null则使用0代替**
```sql
SELECT COUNT(DISTINCT COALESCE(COMM, 0)) FROM emp;
```

---

### 17. `GROUP BY` 子句：



**查询按照部门编号分组后的：部门编号，基本工资平均值的信息**
```sql
SELECT DEPTNO, AVG(SAL) AS avg_salary FROM emp GROUP BY DEPTNO;
```

**查询按照部门编号分组后的：部门编号，总记录数，基本工资平均值的信息**
```sql
SELECT DEPTNO, COUNT(*) AS num_employees, AVG(SAL) AS avg_salary FROM emp GROUP BY DEPTNO;
```

---

### 18. `HAVING` 子句：

**列出平均工资大于2000元的部门ID**
```sql
SELECT DEPTNO FROM emp GROUP BY DEPTNO HAVING AVG(SAL) > 2000;
```

**统计人数小于4的部门的平均工资。**
```sql
SELECT DEPTNO, AVG(SAL) AS avg_salary FROM emp GROUP BY DEPTNO HAVING COUNT(*) < 4;
```

**统计各部门的最高工资，排除最高工资小于3000的部门。**
```sql
SELECT DEPTNO, MAX(SAL) AS max_salary FROM emp GROUP BY DEPTNO HAVING MAX(SAL) >= 3000;
```

**显示部门编号大于10的部门的人数，要求人数大于3**
```sql
SELECT DEPTNO, COUNT(*) AS num_employees FROM emp GROUP BY DEPTNO HAVING DEPTNO > 10 AND COUNT(*) > 3;
```

---

以上是针对您的练习题的 SQL 查询解答。通过这些查询，您可以加深对 SQL 基本操作的理解。