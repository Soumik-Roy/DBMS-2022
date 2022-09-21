//Command to Compile: g++ q3_create_table.cpp -o q3_create_table.exe -lmysql

/*

Here we connect our MySQL database, named dbms_lab2_3, with c++, 
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

    if (mysql_real_connect(conn, "localhost", "group50_dbms", "password", "dbms_lab2_3", 3306, NULL, 0)) {
        cout<<"Connected Successfully!"<<endl; 

        // CATEGORIES Table
        vector<string> Salesmen_Columns = {"salesman_id", "name", "address_city", "coverage_city", "commission"};
        vector<string> Salesmen_Columns_Types = {"int AUTO_INCREMENT NOT NULL PRIMARY KEY", "varchar(255)", "varchar(255)", "varchar(255)", "int"};

        string tableName = "salesmen";
        createTable(tableName, Salesmen_Columns, Salesmen_Columns_Types);

        vector<string> fields = {"name", "address_city", "coverage_city", "commission"};

        insertValue(tableName, fields, {"raj", "mumbai", "delhi", "750"});
        insertValue(tableName, fields, {"tom", "bhopal", "pune", "450"});
        insertValue(tableName, fields, {"manya", "delhi", "kolkata", "700"});
        insertValue(tableName, fields, {"abc", "mumbai", "chennai", "600"});
        insertValue(tableName, fields, {"bhim", "surat", "bhopal", "500"});
        insertValue(tableName, fields, {"sara", "delhi", "mumbai", "600"});
        insertValue(tableName, fields, {"raj", "chennai", "bhopal", "450"});
        insertValue(tableName, fields, {"manu", "chennai", "kolkata", "850"});
        insertValue(tableName, fields, {"garry", "mumbai", "mumbai", "450"});
        insertValue(tableName, fields, {"binny", "delhi", "delhi", "500"});
        insertValue(tableName, fields, {"geeta", "bhopal", "pune", "450"});
        insertValue(tableName, fields, {"blue", "kolkata", "kolkata", "500"});
        insertValue(tableName, fields, {"abc", "pune", "chennai", "500"});
        insertValue(tableName, fields, {"xyz", "pune", "bhopal", "500"});
        insertValue(tableName, fields, {"feeli", "delhi", "mumbai", "700"});
        insertValue(tableName, fields, {"raj", "mumbai", "mumbai", "450"});
        insertValue(tableName, fields, {"raj", "mumbai", "kolkata", "900"});
        insertValue(tableName, fields, {"raj", "pune", "pune", "450"});
        insertValue(tableName, fields, {"raj", "delhi", "chennai", "850"});



    }
    else {
        cout << "Error while connecting! : "<<mysql_error(conn)<<endl;
    }

    return 0;
}
