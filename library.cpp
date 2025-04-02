#include <iostream>
#include <mysql/mysql.h>

using namespace std;

void addBook(MYSQL *conn);
void addMember(MYSQL *conn);
void lendBook(MYSQL *conn);
void returnBook(MYSQL *conn);
void updateBook(MYSQL *conn);
void updateMember(MYSQL *conn);
void deleteBook(MYSQL *conn);
void deleteMember(MYSQL *conn);
void deleteTransaction(MYSQL *conn);
void listBooks(MYSQL *conn);
void listMembers(MYSQL *conn);
void listTransactions(MYSQL *conn);


void executeQuery(MYSQL *conn, const char *query);


void executeQuery(MYSQL *conn, const char *query)
{
	if(mysql_query(conn,query))
	{
		cerr << "Query failed" << endl << mysql_error(conn) << endl;
	}
	else
	{
		cout << "Query executed successful" << endl;	
	}	
}


void addBook(MYSQL *conn)
{
	string title, author;
    	int year, copies;
	cin.ignore();
    	cout << "Enter Book Title: ";
    	getline(cin, title);
    	cout << "Enter Author: ";
    	getline(cin, author);
    	cout << "Enter Year: ";
    	cin >> year;
    	cout << "Enter Available Copies: ";
    	cin >> copies;
    	cin.ignore(); 
    	
  	string query = "INSERT INTO books(title, author, year, copies) VALUES ('"  
                + title + "', '"  
                + author + "', "  
                + to_string(year) + ", "  
                + to_string(copies) + ");";  

	executeQuery(conn, query.c_str());
}


void addMember(MYSQL *conn) {
    string name, email, phone;

    cout << "Enter Member Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter Email: ";
    getline(cin, email);
    cout << "Enter Phone Number: ";
    getline(cin, phone);


    string query = "INSERT INTO lenders (name, email, phone, joined_on) VALUES ('" + 
                   name + "', '" + email + "', " + phone + ", CURDATE());";

    if (mysql_query(conn, query.c_str())) {
        cout << "Error: " << mysql_error(conn) << endl;
    } else {
        cout << "Member added successfully!" << endl;
    }
}



void lendBook(MYSQL *conn) {
    int book_id, member_id;

    cout << "Enter Book ID: ";
    cin >> book_id;
    cout << "Enter Member ID: ";
    cin >> member_id;

    string query = "INSERT INTO transactions (book_id, member_id) VALUES ("
                   + to_string(book_id) + ", " + to_string(member_id) + ");";

    if (mysql_query(conn, query.c_str())) {
        cout << "Error: " << mysql_error(conn) << endl;
    } else {
        cout << "Book lent successfully!" << endl;
    }
}


void returnBook(MYSQL *conn) {
    int transaction_id;

    cout << "Enter Transaction ID: ";
    cin >> transaction_id;

    string query = "UPDATE transactions SET date_returned = CURDATE() WHERE id = " 
                   + to_string(transaction_id) + " AND date_returned IS NULL;";

    if (mysql_query(conn, query.c_str())) {
        cout << "Error: " << mysql_error(conn) << endl;
    } else {
        cout << "Book returned successfully!" << endl;
    }
}


void updateBook(MYSQL *conn) {
    int book_id, copies;
    string title, author;

    cout << "Enter Book ID to Update: ";
    cin >> book_id;
    cout << "Enter New Title: ";
    cin.ignore();
    getline(cin, title);
    cout << "Enter New Author: ";
    getline(cin, author);
    cout << "Enter New Copies Count: ";
    cin >> copies;

    string query = "UPDATE books SET title = '" + title + "', author = '" + author + "', copies = " + to_string(copies) + " WHERE id = " + to_string(book_id) + ";";

    if (mysql_query(conn, query.c_str())) {
        cout << "Error: " << mysql_error(conn) << endl;
    } else {
        cout << "Book updated successfully!" << endl;
    }
}


void updateMember(MYSQL *conn) {
    int member_id;
    string name, email, phone;

    cout << "Enter Member ID to Update: ";
    cin >> member_id;
    cout << "Enter New Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter New Email: ";
    getline(cin, email);
    cout << "Enter New Phone Number: ";
    getline(cin, phone);

    string query = "UPDATE lenders SET name = '" + name + "', email = '" + email + "', phone = '" + phone + "' WHERE id = " + to_string(member_id) + ";";

    if (mysql_query(conn, query.c_str())) {
        cout << "Error: " << mysql_error(conn) << endl;
    } else {
        cout << "Member updated successfully!" << endl;
    }
}


void deleteBook(MYSQL *conn) {
    int book_id;

    cout << "Enter Book ID to Delete: ";
    cin >> book_id;

    string query = "DELETE FROM books WHERE id = " + to_string(book_id) + ";";

    if (mysql_query(conn, query.c_str())) {
        cout << "Error: " << mysql_error(conn) << endl;
    } else {
        cout << "Book deleted successfully!" << endl;
    }
}


void deleteMember(MYSQL *conn) {
    int member_id;

    cout << "Enter Member ID to Delete: ";
    cin >> member_id;

    string query = "DELETE FROM lenders WHERE id = " + to_string(member_id) + ";";

    if (mysql_query(conn, query.c_str())) {
        cout << "Error: " << mysql_error(conn) << endl;
    } else {
        cout << "Member deleted successfully!" << endl;
    }
}


void deleteTransaction(MYSQL *conn) {
    int transaction_id;

    cout << "Enter Transaction ID to Delete: ";
    cin >> transaction_id;

    string query = "DELETE FROM transactions WHERE id = " + to_string(transaction_id) + ";";

    if (mysql_query(conn, query.c_str())) {
        cout << "Error: " << mysql_error(conn) << endl;
    } else {
        cout << "Transaction deleted successfully!" << endl;
    }
}

void listBooks(MYSQL *conn) {
    string query = "SELECT * FROM books;";
    mysql_query(conn, query.c_str());

    MYSQL_RES *result = mysql_store_result(conn);
    MYSQL_ROW row;

    cout << "Books Available:\n";
    while ((row = mysql_fetch_row(result))) {
        cout << "ID: " << row[0] << ", Title: " << row[1] << ", Author: " << row[2] << ", Year: " << row[3] << ", Copies: " << row[4] << endl;
    }
    mysql_free_result(result);
}



void listMembers(MYSQL *conn) {
    string query = "SELECT * FROM lenders;";
    mysql_query(conn, query.c_str());

    MYSQL_RES *result = mysql_store_result(conn);
    MYSQL_ROW row;

    cout << "Library Members:\n";
    while ((row = mysql_fetch_row(result))) {
        cout << "ID: " << row[0] << ", Name: " << row[1] << ", Email: " << row[2] << ", Phone: " << row[3] << ", Joined On: " << row[4] << endl;
    }
    mysql_free_result(result);
}




void listTransactions(MYSQL *conn) {
    string query = "SELECT * FROM transactions;";
    mysql_query(conn, query.c_str());

    MYSQL_RES *result = mysql_store_result(conn);
    MYSQL_ROW row;

    cout << "Transactions:\n";
    while ((row = mysql_fetch_row(result))) {
        cout << "ID: " << row[0] << ", Book ID: " << row[1] << ", Member ID: " << row[2] << ", Issued: " << row[3] << ", Returned: " << (row[4] ? row[4] : "Not Returned") << endl;
    }
    mysql_free_result(result);
}









int main() 
{
	MYSQL *conn;
	conn = mysql_init(NULL);
	
	
	if(!mysql_real_connect(conn,"localhost","gyan", "Gyan123@", NULL, 3306, NULL,0))
	{
		cerr << "MySQL connection failed " << mysql_error(conn) << endl;
		return 1;
	}
	
	cout << "Connection success" << endl;
	
	const char *createDB = "create database if not exists library";
	executeQuery(conn, createDB);
	
	const char *useDB = " use library" ;
	if(mysql_query(conn, useDB))
	{
		cerr << "Database selection failed" << mysql_error(conn) << endl;
	}
	else
	{
		cout << "Database selected successfully" << endl;
	}		
	
	// Create books table
	const char *createBooksTable = "CREATE TABLE if not exists books (id INT PRIMARY KEY AUTO_INCREMENT,title VARCHAR(255),author VARCHAR(255),year INT,copies INT);" ;


    	executeQuery(conn, createBooksTable);

    	// Create Lenders Table
    	const char *createLendersTable = "CREATE TABLE if not exists lenders (id INT PRIMARY KEY AUTO_INCREMENT, name VARCHAR(255),email VARCHAR(255) UNIQUE,phone VARCHAR(15),joined_on DATE);"; 
					
   	 executeQuery(conn, createLendersTable);
	
    	// Create Transactions Table
   	 const char *createTransactionsTable = 
		    "CREATE TABLE IF NOT EXISTS transactions ("
		    "id INT PRIMARY KEY AUTO_INCREMENT, "
		    "book_id INT NOT NULL, "
		    "member_id INT NOT NULL, "
		    "date_issued TIMESTAMP DEFAULT CURRENT_TIMESTAMP, "
		    "date_returned DATE DEFAULT NULL, "
		    "FOREIGN KEY (book_id) REFERENCES books(id) ON DELETE CASCADE, "
		    "FOREIGN KEY (member_id) REFERENCES lenders(id) ON DELETE CASCADE"
		    ");";


 					
    	executeQuery(conn, createTransactionsTable);

   	 cout << "All tables created successfully!" << endl;
	
	int input;
	
	while(true)
	{
		cout << "1. Insert a book " << endl;
		cout << "2. Add new member to library" << endl;
		cout << "3. Lend a book " << endl;
		cout << "4. Return a book" << endl;
		cout << "5. Update book details" << endl;
		cout << "6. Update member details" << endl;
		cout << "7. Delete a book " << endl;
		cout << "8. Delete a member" << endl;
		cout << "9. Delete a transaction" << endl;
		cout << "10. List all books" << endl;
		cout << "11. List all members" << endl;
		cout << "12. List all transactions" << endl;
		
		cout << "13. Exit" << endl;
		
		cin >> input;
		
		switch(input)
		{
			case 1 : addBook(conn); break;
			case 2 : addMember(conn); break; 
			case 3 : lendBook(conn);break;
			case 4 : returnBook(conn);break;
			case 5 : updateBook(conn);break;
			case 6 : updateMember(conn);break;
			case 7 : deleteBook(conn);break;
			case 8 : deleteMember(conn);break;
			case 9 : deleteTransaction(conn);break;
			case 10 : listBooks(conn);break;
			case 11: listMembers(conn);break;
			case 12: listTransactions(conn);break;
			
		}
		
		if(input == 13)
		break; 
	}
	
	
	mysql_close(conn);
	
	return 0;
}	
	
	
	
	
	
