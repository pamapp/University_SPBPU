USE restaurant

CREATE TABLE Users
(IdUser int IDENTITY(1,1) PRIMARY KEY,
 Login varchar(64) NOT NULL,
 Password varchar(64) NOT NULL,
 CONSTRAINT AK_Login UNIQUE(Login))
Go

CREATE TABLE Clients
(IdClient int IDENTITY(1,1) PRIMARY KEY,
 UserId int NOT NULL FOREIGN KEY REFERENCES Users ON DELETE CASCADE ON UPDATE CASCADE, 
 Name varchar(64) NOT NULL,
 Phone varchar(16) NOT NULL, 
 CONSTRAINT AK_Phone UNIQUE(Phone))
Go

CREATE TABLE Employees
(IdEmployee int IDENTITY(1,1) PRIMARY KEY,
 UserId int FOREIGN KEY REFERENCES Users ON DELETE CASCADE ON UPDATE CASCADE, 
 Surname varchar(64) NOT NULL,
 Name varchar(64) NOT NULL,
 Salary money NOT NULL, 
 Position varchar(64) NOT NULL)
Go


CREATE TABLE OrderStatus
(IdStatus int IDENTITY(1,1) PRIMARY KEY,
 NameStatus varchar(32) NOT NULL,
 CONSTRAINT AK_NameStatus UNIQUE(NameStatus))
Go


CREATE TABLE Orders
(IdOrder int IDENTITY(1,1) PRIMARY KEY,
 StatusId int NOT NULL FOREIGN KEY REFERENCES OrderStatus ON DELETE CASCADE ON UPDATE CASCADE,
 EmployeeId int FOREIGN KEY REFERENCES Employees ON DELETE SET NULL ON UPDATE CASCADE,
 ClientId int NOT NULL FOREIGN KEY REFERENCES Clients ON DELETE NO ACTION ON UPDATE NO ACTION,
 CreationTime datetime DEFAULT GETDATE(),
 Price money)
Go

CREATE TABLE Ingredients
(IdIngredient int IDENTITY(1,1) PRIMARY KEY,
 Title varchar(64) NOT NULL,
 CONSTRAINT AK_Title UNIQUE(Title))
Go

CREATE TABLE Dishes
(IdDish int IDENTITY(1,1) PRIMARY KEY,
 Title varchar(64) NOT NULL,
 CONSTRAINT AK_DishTitle UNIQUE(Title),
 Price money NOT NULL,
 Weight int NOT NULL)
Go

CREATE TABLE IngredientList
(DishId int NOT NULL FOREIGN KEY REFERENCES Dishes ON DELETE CASCADE ON UPDATE CASCADE,
 IngredientId int FOREIGN KEY REFERENCES Ingredients ON DELETE SET NULL ON UPDATE CASCADE,
 Amount int NOT NULL,
 Unit varchar(20) NOT NULL)
Go

CREATE TABLE DishList
(DishId int FOREIGN KEY REFERENCES Dishes ON DELETE SET NULL ON UPDATE CASCADE,
 OrderId int NOT NULL FOREIGN KEY REFERENCES Orders ON DELETE CASCADE ON UPDATE CASCADE,
 Number int NOT NULL,
 IsDone bit DEFAULT 0)
Go