//Command to Compile: g++ create_table.cpp -o create_table.exe -lmysql

/*

Here we connect our MySQL database, named dbms_lab_3_4, with c++, 
And then we create the required tables in the databse

*/

#include <iostream>
#include <fstream>
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

void insertValue(string tableName, vector<string> columnNames, vector<string> values) {
    string command = "INSERT INTO " + tableName;

    if(columnNames.size()==values.size())
    {
        command +=  + " ( ";
        for (int i=0; i < columnNames.size(); i++) 
        {
            command += "`" + columnNames[i] + "`";
            if (i == columnNames.size()-1) command += ") ";
            else command += ",";
        }
    }

    command += " VALUES ( ";

    for (int i=0; i < values.size(); i++) 
    {
        command += "'" + values[i] + "'";
        if (i == values.size()-1) command += ");";
        else command += ", ";
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

    if (mysql_real_connect(conn, "localhost", "group50_dbms", "password", "dbms_lab4_5", 3306, NULL, 0)) {
        cout<<"Connected Successfully!"<<endl; 

        // Library Catalogue Table
        vector<string> lib_cat_Columns = {"author_id", "book_id", "author_name", "book"};
        vector<string> lib_cat_Columns_Types = {"varchar(255)", "varchar(255) NOT NULL PRIMARY KEY", "varchar(255)", "varchar(512)"};

        string tableName = "library_catalogue";
        createTable(tableName, lib_cat_Columns, lib_cat_Columns_Types);

        // reading data from library_catalogue.txt file, and inserting it into the table
        ifstream data_file("library_catalogue.txt");
        string row;

        while (getline(data_file, row)) {
            vector<string> values;
            string val = "";
            for (int i=0; i<row.length(); i++) {
                if(row[i] == ',') 
                {
                    values.push_back(val);
                    val = "";

                    if(i<row.length()-1 && row[i+1] == ' ')
                        i++;
                }
                else val.push_back(row[i]);
            }
            values.push_back(val);
            insertValue(tableName, lib_cat_Columns, values);
        }

    }
    else {
        cout << "Error while connecting! : "<<mysql_error(conn)<<endl;
    }

    return 0;
}
