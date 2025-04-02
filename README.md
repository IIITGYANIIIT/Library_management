# Library Management System

## Introduction
The **Library Management System** is a C++ application that integrates with MySQL to manage books, members, and transactions in a library. It provides a command-line interface to perform **CRUD (Create, Read, Update, Delete)** operations on books, members, and lending transactions.

## Features
- **Add, update, and delete books**
- **Register, update, and remove members**
- **Lend and return books**
- **View a list of books, members, and transactions**
- **MySQL database integration for persistent storage**

## Technologies Used
- **Programming Language:** C++
- **Database:** MySQL
- **Library:** MySQL Connector/C++
- **Development Environment:** Ubuntu

## Database Schema
The system consists of three main tables:

### 1. `books` Table
```plaintext
| Column  | Type           | Description         |
|---------|--------------|---------------------|
| id      | INT (PK, AI) | Unique book ID     |
| title   | VARCHAR(255) | Title of the book  |
| author  | VARCHAR(255) | Author name        |
| year    | INT          | Year of publication |
| copies  | INT          | Available copies   |
```

### 2. `lenders` Table
```plaintext
| Column    | Type           | Description          |
|-----------|--------------|----------------------|
| id        | INT (PK, AI) | Unique member ID    |
| name      | VARCHAR(255) | Member name         |
| email     | VARCHAR(255) | Unique email        |
| phone     | VARCHAR(15)  | Contact number      |
| joined_on | DATE         | Membership start date |
```

### 3. `transactions` Table
```plaintext
| Column        | Type           | Description                |
|--------------|--------------|----------------------------|
| id           | INT (PK, AI) | Unique transaction ID      |
| book_id      | INT (FK)     | References `books(id)`     |
| member_id    | INT (FK)     | References `lenders(id)`   |
| date_issued  | TIMESTAMP   | Book issue date           |
| date_returned| DATE (NULL) | Date when book was returned |
```

## Installation & Setup
### 1. Install MySQL
```sh
sudo apt update
sudo apt install mysql-server
```

### 2. Install MySQL Connector/C++
```sh
sudo apt install libmysqlclient-dev
```

### 3. Compile the C++ Program
```sh
g++ library.cpp -o library -lmysqlclient
```

### 4. Run the Program
```sh
./library
```

## Functionalities
### 1. Adding a Book
Prompts the user for book details and inserts them into the `books` table.
```cpp
void addBook(MYSQL *conn);
```

### 2. Registering a Member
Registers a new library member with contact details.
```cpp
void addMember(MYSQL *conn);
```

### 3. Lending a Book
Records a transaction when a book is borrowed.
```cpp
void lendBook(MYSQL *conn);
```

### 4. Returning a Book
Updates the `date_returned` field in `transactions`.
```cpp
void returnBook(MYSQL *conn);
```

### 5. Updating Book Details
Modifies book information such as title, author, and copies.
```cpp
void updateBook(MYSQL *conn);
```

### 6. Updating Member Details
Modifies member information like name, email, and phone number.
```cpp
void updateMember(MYSQL *conn);
```

### 7. Deleting a Book
Removes a book entry from the database.
```cpp
void deleteBook(MYSQL *conn);
```

### 8. Deleting a Member
Deletes a library member from the database.
```cpp
void deleteMember(MYSQL *conn);
```

### 9. Deleting a Transaction
Removes a transaction record.
```cpp
void deleteTransaction(MYSQL *conn);
```

### 10. Listing All Books
Displays all books in the library.
```cpp
void listBooks(MYSQL *conn);
```

### 11. Listing All Members
Displays all registered members.
```cpp
void listMembers(MYSQL *conn);
```

### 12. Listing All Transactions
Displays all lending transactions.
```cpp
void listTransactions(MYSQL *conn);
```

## Conclusion
This **Library Management System** provides essential functionalities to manage a **small to medium-sized library efficiently**. With **MySQL integration**, data persistence and reliability are ensured, making it a **robust system for library operations**.

