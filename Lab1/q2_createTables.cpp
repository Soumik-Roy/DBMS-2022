//Command to Compile: g++ q2_createTables.cpp -o q2_createTables.exe -lmysql

/*

Here we connect our MySQL database, named dbms_lab1, with c++, 
And then we create the required tables in the databse

*/

#include <iostream>
#include <windows.h>
#include <mysql.h>
#include <vector>
#include <string>

using namespace std;

MYSQL *conn;

void createTable(string tableName, vector<string> colNames, vector<string> colType, string extras="") {
    string command = "CREATE TABLE `" + tableName + "` (";

    for (int i=0; i<colNames.size(); i++) {
        command += "`" + colNames[i] + "` " + colType[i];
        if (i != colNames.size()-1) command += ", ";
        else 
        {
            if(extras != "")
                command = command + ", " + extras;
            command += ");";
        }
    }    

    char query[1000];
    snprintf(query, 1000, command.c_str());

    int createTableStatus = mysql_query(conn, query);
    if (createTableStatus != 0) {
        cout<<"Error while creating "<<tableName<<" table: "<<mysql_error(conn)<<endl;
    }
}

void insertValue(string tableName, vector<string> values) {
    string command = "INSERT INTO " + tableName + " VALUES (";

    for (int i=0; i < values.size(); i++) {
        command += "'" + values[i] + "'";
        if (i == values.size()-1) command += ");";
        else command += ",";
    }

    char query[1000];
    snprintf(query, 1000, command.c_str());

    int insertValStatus = mysql_query(conn, query);
    if (insertValStatus != 0) {
        cout << "Error while inserting row. " << mysql_error(conn) << endl;
    }
}

int main()
{
    conn = mysql_init(NULL);
    if (conn == NULL) {
        cout<<"Error: "<<mysql_error(conn)<<endl;
        exit(1);
    }

    // mysql_real_connect(Connection Instance, Host, Username, Password, Database, Port, Unix Socket, Client Flag)

    if (mysql_real_connect(conn, "localhost", "group50_dbms", "password", "dbms_lab1", 3306, NULL, 0)) {
        cout<<"Connected Successfully!"<<endl; 

        // CATEGORIES Table
        vector<string> Categories_Columns = {"name"};
        vector<string> Categories_Columns_Types = {"varchar(255) NOT NULL PRIMARY KEY"};

        createTable("Categories", Categories_Columns, Categories_Columns_Types);
        
        insertValue("Categories", {"Magazine"});
        insertValue("Categories", {"Book"});
        insertValue("Categories", {"Newspaper"});
        insertValue("Categories", {"Research Journal"});

        // GENRES Table
        vector<string> Genres_Columns = {"name"};
        vector<string> Genres_Columns_Types = {"varchar(255) NOT NULL PRIMARY KEY"};

        createTable("Genres", Genres_Columns, Genres_Columns_Types);

        insertValue("Genres", {"Drama"});
        insertValue("Genres", {"Suspense"});
        insertValue("Genres", {"Biography"});
        insertValue("Genres", {"Educational"});

        // ITEMS Table
        vector<string> Items_Columns = {"iId", "name", "totalCopies", "copiesLeft", "category", "genre"};
        vector<string> Items_Columns_Types = {"int NOT NULL PRIMARY KEY", "varchar(255)", "int", "int", "varchar(255)", "varchar(255)"};

        createTable("Items", Items_Columns, Items_Columns_Types, "FOREIGN KEY(category) REFERENCES Categories(name), FOREIGN KEY(genre) REFERENCES Genres(name)");
        
        insertValue("Items", {"53", "Fifty Shades of Grey", "69", "42", "Book",	"Drama"});
        insertValue("Items", {"18", "Wings of Fire", "100", "35", "Book", "Biography"});
        insertValue("Items", {"41", "Forbes", "30", "20", "Magazine", "Educational"});
        insertValue("Items", {"32", "The Hindu", "20", "15", "Newspaper", "Educational"});
        insertValue("Items", {"27", "Research Journal of Biotechnology", "10", "2", "Research Journal",	"Educational"});


        // READERS Table
        vector<string> Readers_Columns = {"rId", "name", "email", "phoneNumber"};
        vector<string> Readers_Columns_Types = {"int NOT NULL PRIMARY KEY", "varchar(255)", "varchar(255)", "varchar(14)"};

        createTable("Readers", Readers_Columns, Readers_Columns_Types);
        
        insertValue("Readers", {"1", "John Watts", "jwatts12@gmail.com", "+91-9789782378"});
        insertValue("Readers", {"2", "Kyle Butler", "kb7892@gmail.com", "7891238982"});
        insertValue("Readers", {"3", "Emily James", "emilyj89@gmail.com", "+91 8879123898"});
        insertValue("Readers", {"4", "Adam Williams", "adwill@yahoo.com", "6890123975"});
        insertValue("Readers", {"5", "Blaire Johnson", "bjohnson@gmail.com", "8798278923"});

        // LIBRARIANS Table
        vector<string> Librarians_Columns = {"lId", "name", "workingHours", "sex", "salary"};
        vector<string> Librarians_Columns_Types = {"int NOT NULL PRIMARY KEY", "varchar(255)", "varchar(255)", "varchar(20)", "int"};

        createTable("Librarians", Librarians_Columns, Librarians_Columns_Types);
        
        insertValue("Librarians", {"101", "Ram Sharma", "05 AM - 01 PM", "Male", "10000"});
        insertValue("Librarians", {"102", "Neha Singh", "01 PM - 09 PM", "Female", "12000"});
        insertValue("Librarians", {"103", "Prem Prakash", "09 PM - 05 AM", "Male", "11000"});

        // Issues Table
        vector<string> Issues_Columns = {"issueId", "itemId", "readerId", "librarianId", "issueDate", "returnDate"};
        vector<string> Issues_Columns_Types = {"int NOT NULL PRIMARY KEY", "int", "int", "int", "date", "date"};

        createTable("Issues", Issues_Columns, Issues_Columns_Types, "FOREIGN KEY(itemId) REFERENCES Items(iId), FOREIGN KEY(readerId) REFERENCES Readers(rId), FOREIGN KEY(librarianId) REFERENCES Librarians(lId)");
        
        insertValue("Issues", {"1", "18", "2", "102", "2022 10 01", "2022 10 08"});
        insertValue("Issues", {"2", "32", "1", "103", "2022 10 02", "2022 10 05"});
        insertValue("Issues", {"3", "27", "5", "101", "2022 10 03", "2022 10 10"});
        insertValue("Issues", {"4", "41", "3", "102", "2022 10 03", "2022 10 09"});
        insertValue("Issues", {"5", "53", "4", "102", "2022 10 05", "2022 10 12"});
    }
    else {
        cout << "Error while connecting! : "<<mysql_error(conn)<<endl;
    }

    return 0;
}
