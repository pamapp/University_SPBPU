
--Э5 курсовая

USE restaurant;

-- ПРОСТЫЕ ЗАПРОСЫ


-- 1. Вывод всех блюд в меню
SELECT * FROM Dishes

--поиск по названию
SELECT Title, Weight, Price FROM Dishes WHERE Title LIKE '%Яичница%'

-- 2. Вывод всех покупателей
CREATE VIEW Clients_List
AS 
(SELECT Clients.Name, Clients.Phone, COUNT(Orders.IdOrder) AS OrderCount FROM Clients
JOIN Orders ON Orders.ClientId = Clients.IdClient
GROUP BY Clients.name, Clients.Phone)
UNION ALL
(SELECT Clients.Name, Clients.Phone, 0 AS OrderCount FROM Clients
WHERE NOT EXISTS (SELECT * FROM Orders WHERE Orders.ClientId = Clients.IdClient))

select * from Clients_List
-- 3. Вывод всех сотрудников
SELECT Surname, Name, Salary, Position FROM Employees

-- 4. Вывод всех ингредиентов
SELECT * FROM Ingredients 

-- 5. Изменение значения флага, отвечающего за готовность блюда
DECLARE 
    @tempOrderId int,
	@tempDoneDishId int
SET @tempOrderId = 1
SET @tempDoneDishId = 1

UPDATE DishList 
SET DishList.IsDone = 1
WHERE DishList.OrderId = 4 AND DishList.DishId = 3

-- 6. Изменение информации о сотруднике
DECLARE 
    @tempEmoloyeeId int,
	@tempEmoloyeeSurname varchar(64),
	@tempEmoloyeeName varchar(64),
	@tempEmoloyeeSalary money,
	@tempEmoloyeePosition varchar(64)
SET @tempEmoloyeeId = 5
SET @tempEmoloyeeSurname = 'Абрамов'
SET @tempEmoloyeeName = 'Петр'
SET @tempEmoloyeeSalary = 31000
SET @tempEmoloyeePosition = 'Работник кухни'

UPDATE Employees
SET Surname = @tempEmoloyeeSurname, Name = @tempEmoloyeeName, Salary = @tempEmoloyeeSalary, Position = @tempEmoloyeePosition
WHERE IdEmployee = @tempEmoloyeeId

-- 7. Изменение информации о блюде
DECLARE 
    @tempDishId int,
	@tempDishTitle varchar(64),
	@tempDishPrice money,
	@tempDishWeight int
SET @tempDishId = 4
SET @tempDishTitle = 'Овощной салат'
SET @tempDishPrice = 150
SET @tempDishWeight = 100

UPDATE Dishes
SET Title = @tempDishTitle, Price = @tempDishPrice, Weight = @tempDishWeight
WHERE IdDish = @tempDishId

-- 8. Изменение информации об ингредиенте блюда
DECLARE 
    @tempDishId int,
	@amount int,
	@unit varchar(20)
SET @tempDishId = 2
SET @amount = '2'
SET @unit = 'шт.'

UPDATE IngredientList
SET Amount = @amount, Unit = @unit
WHERE DishId = @tempDishId

-- 9. Изменение информации об ингредиенте
DECLARE 
    @tempIngredientId int,
	@tempIngredientTitle varchar(64)
SET @tempIngredientTitle = 'Яйцо'

UPDATE Ingredients
SET Title = @tempIngredientTitle
WHERE IdIngredient = @tempIngredientId

-- 10. Удаление ингредиента
DECLARE @delIngredientTitle VARCHAR(64)
SET @delIngredientTitle = 'Курица'

DELETE FROM Ingredients 
WHERE Ingredients.Title = @delIngredientTitle

DELETE FROM Ingredients WHERE Ingredients.Title = 'Молоко'
-- 11. Удаление ингредиента блюда
DECLARE 
	@dishTitle varchar(64),
	@delIngredientTitle varchar(64)
SET @dishTitle = 'Фруктовый салат'
SET @delIngredientTitle = 'Груша'

DELETE FROM IngredientList WHERE DishId = (SELECT IdDish FROM Dishes WHERE Dishes.Title = @dishTitle) 
AND IngredientId = (SELECT IdIngredient FROM Ingredients WHERE Ingredients.Title = @delIngredientTitle)

-- 12. Удаление блюда из меню
DECLARE 
	@delDishTitle VARCHAR(64)
SET @delDishTitle = 'Фруктовый салат'

DELETE FROM Dishes WHERE Dishes.Title = @delDishTitle

-- 13. Удаление сотрудника 
DECLARE @name VARCHAR(64), @surname VARCHAR(64)
SET @name = 'Виктория'
SET @surname = 'Гукова'

DELETE FROM Users WHERE Users.IdUser = (SELECT UserId FROM Employees WHERE Employees.Name = @name AND Employees.Surname = @surname)

--проверка

SELECT * FROM Employees
SELECT * FROM Orders
select * from IngredientList
select * from Ingredients
select * from dishes
select * from dishlist

-- СЛОЖНЫЕ ЗАПРОСЫ

-- Сотрудник
-- 1. Вывод списка блюд с выбранным статусом в заказе
-- готовы (заказ 7)
SELECT Dishes.Title FROM Orders, Dishes, DishList 
WHERE DishList.IsDone = 1 AND DishList.DishId = Dishes.IdDish 
AND DishList.OrderId = Orders.IdOrder AND Orders.IdOrder = '7'
-- не готовы (заказ 1)
SELECT Dishes.Title FROM Orders, Dishes, DishList 
WHERE DishList.IsDone = 0 AND DishList.DishId = Dishes.IdDish 
AND DishList.OrderId = Orders.IdOrder AND Orders.IdOrder = '1'


-- Клиент
-- 2. Вывод всех блюд в заказе (заказ 7)
SELECT Dishes.Title, DishList.Number, Dishes.Price * DishList.Number AS 'Total Price' FROM Dishes 
JOIN DishList ON DishList.DishId = Dishes.IdDish 
JOIN Orders ON Orders.IdOrder = DishList.OrderId AND Orders.IdOrder = 11
JOIN OrderStatus ON Orders.StatusId = OrderStatus.IdStatus


-- Сотрудник
-- 2. Вывод всех блюд в заказе (заказ 1)
SELECT Dishlist.DishId, Dishes.Title, DishList.Number, DishList.IsDone FROM Dishes 
JOIN DishList ON DishList.DishId = Dishes.IdDish 
JOIN Orders ON Orders.IdOrder = DishList.OrderId AND Orders.IdOrder = 2
JOIN OrderStatus ON Orders.StatusId = OrderStatus.IdStatus 


-- Клиент
-- 3. Вывод информации о выбранном блюде ('Английский завтрак')
SELECT Ingredients.Title FROM Ingredients
JOIN IngredientList ON IngredientList.IngredientId = Ingredients.IdIngredient
JOIN Dishes ON Dishes.IdDish = IngredientList.DishId AND Dishes.Title = 'Английский завтрак'


-- Сотрудник
-- 3. Вывод информации о выбранном блюде ('Паста Карбонара')
SELECT Ingredients.Title, IngredientList.Amount, IngredientList.Unit FROM Ingredients 
JOIN IngredientList ON IngredientList.IngredientId = Ingredients.IdIngredient
JOIN Dishes ON Dishes.IdDish = '5' AND Dishes.IdDish = IngredientList.DishId  

-- Сотрудник
-- 4. Вывод информации о заказе (заказ 1)
SELECT OrderStatus.NameStatus, Employees.Surname AS 'Employee', Clients.Name AS 'Client', 
FORMAT(Orders.CreationTime, 'dd.MM.yyyy HH:mm') AS 'Creation Time', Orders.Price FROM Orders
JOIN OrderStatus ON Orders.StatusId = OrderStatus.IdStatus AND Orders.IdOrder = 28
JOIN Employees ON Orders.EmployeeId = Employees.IdEmployee 
JOIN Clients ON Orders.ClientId = Clients.IdClient 

SELECT OrderStatus.NameStatus, Employees.Surname AS 'Employee', Clients.Name AS 'Client', Clients.Phone,
    FORMAT(Orders.CreationTime, 'dd.MM.yyyy HH:mm') AS 'Creation Time', Orders.Price FROM Orders
    JOIN OrderStatus ON Orders.StatusId = OrderStatus.IdStatus AND Orders.IdOrder = 20
    JOIN Employees ON Orders.EmployeeId = Employees.IdEmployee 
    JOIN Clients ON Orders.ClientId = Clients.IdClient

-- Клиент
-- 4. Вывод информации о заказе (заказ 1)
SELECT OrderStatus.NameStatus, 
FORMAT(Orders.CreationTime, 'dd.MM.yyyy HH:mm') AS 'Creation Time', Orders.Price FROM Orders
JOIN OrderStatus ON Orders.StatusId = OrderStatus.IdStatus AND Orders.IdOrder = 1
JOIN Employees ON Orders.EmployeeId = Employees.IdEmployee 
JOIN Clients ON Orders.ClientId = Clients.IdClient 


-- 5. Вывод всех неприготовленных блюд 
SELECT Dishes.Title, DishList.Number FROM Dishes
JOIN Dishlist ON DishList.IsDone = 0 AND DishList.DishId = Dishes.IdDish


-- 6. Вывод всех приготовленных блюд
SELECT Dishes.Title, DishList.Number FROM Dishes
JOIN Dishlist ON DishList.IsDone = 1 AND DishList.DishId = Dishes.IdDish


-- 7. Вывод всех блюд в заказах
SELECT Dishes.Title, DishList.Number FROM Dishes
JOIN Dishlist ON DishList.DishId = Dishes.IdDish


-- 8. Вывод всех созданных пользователем заказов (Екатерина)
SELECT Orders.IdOrder, OrderStatus.NameStatus, FORMAT(Orders.CreationTime, 'dd.MM.yyyy HH:mm') AS 'Creation Time', Orders.Price 
FROM Orders 
JOIN OrderStatus ON OrderStatus.IdStatus = Orders.StatusId 
JOIN Clients ON Clients.IdClient = Orders.ClientId AND Clients.IdClient = 1


-- 9. Вывод списка заказов с определенным статусом
ALTER PROCEDURE orderListByStatus
	@statusName varchar(64)
AS
BEGIN
	SELECT Orders.IdOrder, FORMAT(Orders.CreationTime, 'dd.MM.yyyy HH:mm') AS 'Creation Time', Clients.Name AS 'Client', Clients.Phone, Orders.Price, OrderStatus.NameStatus FROM Orders
	JOIN OrderStatus ON Orders.StatusId = OrderStatus.IdStatus AND NameStatus = @statusName AND Orders.Price != 0
	JOIN Clients ON Orders.ClientId = Clients.IdClient 
	ORDER BY Orders.CreationTime DESC
END;
Exec orderListByStatus 'Обрабатывается'


SELECT Dishes.IdDish, Dishes.Title, DishList.Number, DishList.IsDone, DishList.OrderId FROM Dishes
    JOIN Dishlist ON DishList.DishId = Dishes.IdDish
	JOIN Orders On Orders.IdOrder = DishList.OrderId 

--всех заказов
SELECT Orders.IdOrder, FORMAT(Orders.CreationTime, 'dd.MM.yyyy HH:mm') AS 'Creation Time', Clients.Name AS 'Client', Clients.Phone, Orders.Price, OrderStatus.NameStatus 
FROM Orders
JOIN OrderStatus ON Orders.StatusId = OrderStatus.IdStatus 
JOIN Employees ON Orders.EmployeeId = Employees.IdEmployee 
JOIN Clients ON Orders.ClientId = Clients.IdClient
ORDER BY Orders.CreationTime DESC


-- 9. Добавление связи между сотрудником и заказом
DECLARE 
    @tempOrderId int,
	@tempEmployeeName varchar(64),
	@tempEmployeeSurname varchar(64)
SET @tempOrderId = 12
SET @tempEmployeeName = 'Валерий'
SET @tempEmployeeSurname = 'Пушкин'

UPDATE Orders
SET EmployeeId = (SELECT Employees.IdEmployee FROM Employees WHERE Name = @tempEmployeeName AND Surname = @tempEmployeeSurname)
WHERE IdOrder = @tempOrderId
select * from orders
select * from employees
-- 10. Изменение значения статуса заказа 
DECLARE 
    @tempStatusOrderId int,
	@tempStatusName varchar(64)
SET @tempStatusOrderId = 3
SET @tempStatusName = 'Приготовлен'
UPDATE Orders SET Orders.StatusId = (SELECT IdStatus FROM OrderStatus WHERE NameStatus = @tempStatusName) 
WHERE Orders.IdOrder = @tempStatusOrderId



--ПРЕДСТАВЛЕНИЯ

--1. Вывод всех блюд по убыванию популярности
CREATE VIEW TopDishes
AS 
(SELECT TOP 100 Dishes.IdDish, Dishes.Title, Dishes.Weight, Dishes.Price FROM Dishes JOIN DishList ON DishList.DishId = Dishes.IdDish
GROUP BY Dishes.IdDish, Dishes.Title, Dishes.Weight, Dishes.Price HAVING SUM(DishList.Number) > 0 ORDER BY SUM(DishList.Number) DESC)
UNION ALL
(SELECT TOP 100 Dishes.IdDish, Dishes.Title, Dishes.Weight, Dishes.Price FROM Dishes
WHERE NOT EXISTS (SELECT * FROM DishList WHERE DishList.DishId = Dishes.IdDish) ORDER BY Dishes.Title DESC)

--вывод
SELECT * FROM Employees
select * from Users


--2. Вывод всех клиентов по убыванию количества заказов
CREATE VIEW TopClients
AS 
(SELECT TOP 100 Clients.Name, Clients.Phone, COUNT(Orders.IdOrder) AS OrderCount FROM Clients
JOIN Orders ON Orders.ClientId = Clients.IdClient
GROUP BY Clients.name, Clients.Phone
ORDER BY OrderCount DESC)
UNION ALL
(SELECT TOP 100 Clients.Name, Clients.Phone, 0 AS OrderCount FROM Clients
WHERE NOT EXISTS (SELECT * FROM Orders WHERE Orders.ClientId = Clients.IdClient))

--вывод
SELECT * FROM TopClients

(SELECT COUNT(Orders.IdOrder) AS OrderCount FROM Clients
JOIN Orders ON Orders.ClientId = Clients.IdClient AND ClientId = 11)
UNION
(SELECT 0 AS OrderCount FROM Clients
WHERE NOT EXISTS (SELECT * FROM Orders WHERE Orders.ClientId = Clients.IdClient))

-- ПРОЦЕДУРЫ

--1. Регистрация сотрудника (Таблицы: Employees, Users)

ALTER PROCEDURE regEmployee
	@login VARCHAR(64),
	@password VARCHAR(64),
	@surname VARCHAR(64),
	@name VARCHAR(64),
	@salary money,
	@position VARCHAR(64)
AS
BEGIN TRY
BEGIN TRANSACTION
	INSERT INTO Users(login, password)
	VALUES (@login, @password)

	INSERT INTO Employees(UserId, Surname, Name, Salary, Position)
	VALUES (SCOPE_IDENTITY(), @surname, @name, @salary, @position)

	SELECT IdEmployee FROM Employees WHERE IdEmployee = SCOPE_IDENTITY()
COMMIT TRANSACTION
END TRY
BEGIN CATCH 
ROLLBACK TRANSACTION;
END CATCH

--2. Регистрация клиента (Таблицы: Clients, Users)

Alter PROCEDURE regClient
	@login VARCHAR(64),
	@password VARCHAR(64),
	@name VARCHAR(64),
	@phone VARCHAR(15)
AS
BEGIN TRY
BEGIN TRANSACTION
	INSERT INTO Users(login, password)
	VALUES (@login, @password)

	INSERT INTO Clients(UserId, Name, Phone)
	VALUES (SCOPE_IDENTITY(), @name, @phone)

	SELECT IdClient FROM Clients WHERE IdClient = SCOPE_IDENTITY()
COMMIT TRANSACTION
END TRY
BEGIN CATCH 
ROLLBACK TRANSACTION;
END CATCH

EXEC regClient 'user3', 'password108', 'Said', '7(800)555-31-08'

select * from Users
select * from Clients



-- 3. Добавление ингредиента
ALTER PROCEDURE addIngredient
	@title VARCHAR(64)
AS
BEGIN TRY
BEGIN TRANSACTION
	INSERT INTO Ingredients(Title)
	VALUES (@title)
	SELECT IdIngredient FROM Ingredients WHERE IdIngredient = SCOPE_IDENTITY()
COMMIT TRANSACTION
END TRY
BEGIN CATCH 
ROLLBACK TRANSACTION;
END CATCH

exec addIngredient 'Соль'

-- 4. Добавление блюда с ингредиентами
Alter PROCEDURE addDish
	@title varchar(64),
	@price money,
	@weight int
AS
BEGIN TRY
BEGIN TRANSACTION
	INSERT INTO Dishes(Title, Weight, Price)
	VALUES (@title, @weight, @price)

	SELECT IdDish FROM Dishes WHERE IdDish = SCOPE_IDENTITY()
COMMIT TRANSACTION
END TRY
BEGIN CATCH 
ROLLBACK TRANSACTION;
END CATCH



Alter PROCEDURE addDishIngredient
	@dishId int,
	@ingredientTitle varchar(64),
	@amount int,
	@unit varchar(20)
AS
BEGIN
	INSERT INTO IngredientList(DishId, IngredientId, Amount, Unit)
	VALUES (@dishId, (SELECT Ingredients.IdIngredient FROM Ingredients WHERE Title = @ingredientTitle) , @amount, @unit)
END;
SELECT Ingredients.IdIngredient FROM Ingredients WHERE Title = 'Морская капуста'

-- 5. Добавление заказа

-- создание заказа
Alter PROCEDURE addOrder
	@clientId int
AS
BEGIN
	INSERT INTO Orders(ClientId, StatusId)
	VALUES (@clientId, (SELECT IdStatus FROM OrderStatus WHERE NameStatus = 'Обрабатывается'))

	UPDATE DishList SET DishList.OrderId = SCOPE_IDENTITY() 
	WHERE DishList.OrderId IS NULL

	SELECT Orders.IdOrder FROM Orders
    JOIN OrderStatus ON Orders.StatusId = OrderStatus.IdStatus 
    JOIN Clients ON Clients.IdClient = Orders.ClientId AND Clients.IdClient = @clientId AND Orders.Price is null
END;

EXEC addOrder 4


-- удаление заказа
CREATE PROCEDURE deleteOrder
	@order_id int
AS
BEGIN
	DELETE FROM Orders WHERE Orders.IdOrder = @order_id
END;

EXEC deleteOrder 19
select * from orders
select Orders.IdOrder from orders 
join clients on clients.IdClient = Orders.ClientId AND Clients.IdClient = 4 AND Orders.Price is null

SELECT Orders.IdOrder, OrderStatus.NameStatus, FORMAT(Orders.CreationTime, 'dd.MM.yyyy HH:mm'), Orders.Price FROM Orders
    JOIN OrderStatus ON Orders.StatusId = OrderStatus.IdStatus 
    JOIN Clients ON Clients.IdClient = Orders.ClientId AND Clients.IdClient = 4 AND Orders.Price is null
	select * from users
select * from clients
select * from orders
select * from dishList

-- добавление блюда в заказ
CREATE PROCEDURE addDishInDishList 
	@order_id int,
	@dishTitle varchar(64),
	@number int
AS
BEGIN
	INSERT INTO DishList(OrderId, DishId, Number, IsDone)
	VALUES (@order_id, (SELECT IdDish FROM Dishes WHERE Title = @dishTitle), @number, '0')

	UPDATE Orders SET Orders.Price = (SELECT SUM(Dishes.Price * DishList.Number) FROM Dishes, DishList WHERE DishList.DishId = Dishes.IdDish AND DishList.OrderId = @order_id)
	WHERE Orders.IdOrder = @order_id

END;

EXEC addDishInDishList 12, 'Паста Карбонара', 1
EXEC addDishInDishList 12, 'Яичница', 7

-- 6. Добавление статуса

CREATE PROCEDURE addStatus
	@title varchar(64)
AS
BEGIN TRY
BEGIN TRANSACTION
	INSERT INTO OrderStatus(NameStatus)
	VALUES (@title)
COMMIT TRANSACTION
END TRY
BEGIN CATCH 
ROLLBACK TRANSACTION;
END CATCH


EXEC addStatus 'Обрабатывается'
EXEC addStatus 'Принят'
EXEC addStatus 'Приготовлен'
EXEC addStatus 'Выдан'
EXEC addStatus 'Отменен'

SELECT * FROM OrderStatus Order by IdStatus

SELECT * FROM Orders 

-- 7. Вход в систему

ALTER PROCEDURE log_in
	@login varchar(64),
	@password varchar(64)
AS
BEGIN
	(SELECT IdClient AS Id, 0 AS Role FROM Clients 
	JOIN Users ON Clients.UserId = Users.IdUser WHERE Users.Login = @login AND Users.Password = @password)
	UNION ALL
	(SELECT IdEmployee AS Id, 1 AS Role FROM Employees 
	JOIN Users ON Employees.UserId = Users.IdUser WHERE Users.Login = @login AND Users.Password = @password AND Employees.Position != 'Администратор')
	UNION ALL
	(SELECT IdEmployee AS Id, 2 AS Role FROM Employees
	JOIN Users ON Employees.UserId = Users.IdUser WHERE Users.Login = @login AND Users.Password = @password AND Employees.Position = 'Администратор')
END;

EXEC log_in 'admin', 'admin'


--Вывод личного кабинета клиента
SELECT Users.Login, Users.Password, Clients.Name, Clients.Phone FROM Users 
JOIN Clients ON Clients.UserId = Users.IdUser AND Clients.IdClient = 1 

select * from users
select * from clients

EXEC changeClientInfo 1, 'qubblr', 'qubblr', 'Петр', '7(922)345-11-11'

--Изменение информации о клиенте 
CREATE PROCEDURE changeClientInfo
	@clientId int,
	@login varchar(64),
	@password varchar(64),
	@name varchar(64),
	@phone varchar(16)
AS
BEGIN TRY
BEGIN TRANSACTION
	UPDATE Users SET Login = @login, Password = @password
	WHERE IdUser = (SELECT UserId From Clients WHERE IdClient = @clientId)

	UPDATE Clients SET Name = @name, Phone = @phone
	WHERE IdClient = @clientId
COMMIT TRANSACTION
END TRY
BEGIN CATCH 
ROLLBACK TRANSACTION;
END CATCH


--Изменение информации о сотруднике 
CREATE PROCEDURE changeEmployeeUser
	@employeeId int,
	@login varchar(64),
	@password varchar(64)
AS
BEGIN TRY
BEGIN TRANSACTION
	UPDATE Users SET Login = @login, Password = @password
	WHERE IdUser = (SELECT UserId From Employees WHERE Employees.IdEmployee = @employeeId)
COMMIT TRANSACTION
END TRY
BEGIN CATCH 
ROLLBACK TRANSACTION;
END CATCH


--SELECT Dishes.IdDish, Dishes.Title, DishList.Number, DishList.IsDone, DishList.OrderId FROM Dishes
--    JOIN Dishlist ON DishList.DishId = Dishes.IdDish
--	JOIN Orders On Orders.IdOrder = DishList.OrderId 
--	JOIN Employees ON Employees.IdEmployee = Orders.EmployeeId AND Employees.IdEmployee = ${employee_id}

SELECT Ingredients.Title, IngredientList.Amount, IngredientList.Unit FROM Ingredients 
    JOIN IngredientList ON IngredientList.IngredientId = Ingredients.IdIngredient
    JOIN Dishes ON Dishes.IdDish = ${dish_id} AND Dishes.IdDish = IngredientList.DishId

select * from orders
select * from DishList

SELECT Surname, Name, Salary, Position, IdEmployee FROM Employees ORDER BY Surname

SELECT OrderStatus.NameStatus, Clients.Name, Clients.Phone,
    FORMAT(Orders.CreationTime, 'dd.MM.yyyy HH:mm'), Orders.Price, Employees.Surname FROM Orders
    JOIN OrderStatus ON Orders.StatusId = OrderStatus.IdStatus AND Orders.IdOrder = 12
    JOIN Employees ON Employees.IdEmployee = Orders.EmployeeId
    JOIN Clients ON Orders.ClientId = Clients.IdClient

