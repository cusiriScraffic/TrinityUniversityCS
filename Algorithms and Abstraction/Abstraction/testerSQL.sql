CREATE TABLE Customers
(
Customer_ID int,
First_Name varchar(255),
Last_Name varchar(255),
Customer_Address varchar(255),
Age int
);

CREATE TABLE Employees
(
Employee_ID int, 
First_Name varchar(255),
Last_Name varchar(255),
Address varchar(255)
);

CREATE TABLE Store
(
Store_ID int,
Store_Address varchar(255),
Employee_ID int
);

INSERT INTO Customers (Customer_ID,First_Name, Last_Name, Customer_Address, Age)
VALUES (1,’Tom’,’Baines’,’1 Trinity PL’, 21);
INSERT INTO Customers (First_Name, Last_Name, Customer_Address, Age)
VALUES (2,‘Tim’,’Locke’,’1 Trinity PL’, 22);
INSERT INTO Customers (First_Name, Last_Name, Customer_Address, Age)
VALUES (3,‘King’,’stairs’,’1 Trinity PL’, 22);
INSERT INTO Customers (First_Name, Last_Name, Customer_Address, Age)
VALUES (4,‘Mark’,’Lewis’,’1 Trinity PL’, 21);
INSERT INTO Customers (First_Name, Last_Name, Customer_Address, Age)
VALUES (5,‘Willian’,’Lopez’,’1 Trinity PL’, 21);
INSERT INTO Customers (First_Name, Last_Name, Customer_Address, Age)
VALUES (6,‘Kevin’,’Luiz’,’1 Trinity PL’, 25);
INSERT INTO Customers (First_Name, Last_Name, Customer_Address, Age)
VALUES (7,‘Diego’,’Costa’,’1 Trinity PL’, 21);
INSERT INTO Customers (First_Name, Last_Name, Customer_Address, Age)
VALUES (8,‘Frank’,’Lampard’,’1 Trinity PL’, 21);
INSERT INTO Customers (First_Name, Last_Name, Customer_Address, Age)
VALUES (9,‘Victor’,’Moses’,’1 Trinity PL’, 21);
INSERT INTO Customers (First_Name, Last_Name, Customer_Address, Age)
VALUES (10,‘Matic’,’Michael’,’1 Trinity PL’, 21);

INSERT INTO Employees(Employee_ID,First_Name,Last_Name,Employee_Address)
VALUES(1,’Frank’,’timothy’,’1 Scotsdale TN’);
INSERT INTO Employees(Employee_ID,First_Name,Last_Name,Employee_Address)
VALUES(2,’Tim’,’Titus’,’1 Scotsdale TN’);
INSERT INTO Employees(Employee_ID,First_Name,Last_Name,Employee_Address)
VALUES(3,’Fredrick’,’Tester’,’1 Kimsel NY’);
INSERT INTO Employees(Employee_ID,First_Name,Last_Name,Employee_Address)
VALUES(4,’Frank’,’Fern’,’dale TX’);
INSERT INTO Employees(Employee_ID,First_Name,Last_Name,Employee_Address)
VALUES(5,’Fin’,’Ficey’,’1 Scotsdale TN’);
INSERT INTO Employees(Employee_ID,First_Name,Last_Name,Employee_Address)
VALUES(6,’Friend’,’Best’,’sdale TN’);
INSERT INTO Employees(Employee_ID,First_Name,Last_Name,Employee_Address)
VALUES(7,’Fetch’,’Finger’,’1 Times TN’);
INSERT INTO Employees(Employee_ID,First_Name,Last_Name,Employee_Address)
VALUES(8,’Red’,’Meat’,’1 California TN’);
INSERT INTO Employees(Employee_ID,First_Name,Last_Name,Employee_Address)
VALUES(9,’Finder’,’Mac’,’1 Finding CA’);
INSERT INTO Employees(Employee_ID,First_Name,Last_Name,Employee_Address)
VALUES(10,’Example’,’Testing’,’1 FakeCity Utah’);

INSERT INTO Store(Store_ID,Store_Address,Employee_Id)
VALUES(1,’1 Trinity PL’,1);
INSERT INTO Store(Store_ID,Store_Address,Employee_Id)
VALUES(1,’1 Trinity PL’,2);
INSERT INTO Store(Store_ID,Store_Address,Employee_Id)
VALUES(1,’1 Trinity PL’,3);
INSERT INTO Store(Store_ID,Store_Address,Employee_Id)
VALUES(1,’1 Trinity PL’,4);
INSERT INTO Store(Store_ID,Store_Address,Employee_Id)
VALUES(2,’Utah Tester’,5);
INSERT INTO Store(Store_ID,Store_Address,Employee_Id)
VALUES(3,’1 Times PL’,6);
INSERT INTO Store(Store_ID,Store_Address,Employee_Id)
VALUES(4,’1 Favorite PL’,7);
INSERT INTO Store(Store_ID,Store_Address,Employee_Id)
VALUES(5,’1 Bread crum PL’,8);
INSERT INTO Store(Store_ID,Store_Address,Employee_Id)
VALUES(6,’1 Serious Tester PL’,9);
INSERT INTO Store(Store_ID,Store_Address,Employee_Id)
VALUES(7,’1 London PL’,10);

SELECT First_Name, Last_Name, Employee_Address
FROM Employees
;
