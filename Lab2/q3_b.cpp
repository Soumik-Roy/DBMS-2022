//Command to Compile: g++ q3_b.cpp -o q3_b.exe -lmysql

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

int display()
{
    MYSQL_RES *results = mysql_store_result(conn);
    MYSQL_ROW record;
    MYSQL_FIELD *fields;
    int num_fields = mysql_num_fields(results);

    fields = mysql_fetch_fields(results);
    for(int i = 0; i < num_fields; i++)
    {
        cout<<fields[i].name<<" ";
    }
    cout<<endl;
    if(results->row_count == 0)
        return 0;
    
    while ((record = mysql_fetch_row(results)))
    {
        for(int i = 0; i < num_fields; i++)
        {
            char *val = record[i];
            cout<<record[i]<<" ";
        }
        cout<<endl;
    }
    mysql_free_result(results);
    return 0;
}

void writeQuery(string Query, string tableName, bool printOutput = true)
{
    char query[1000];
    
    snprintf(query, 1000, Query.c_str(), tableName.c_str());

    int queryStatus = mysql_query(conn, query);

    if(printOutput) display();

    cout<<endl;

    if (queryStatus != 0) {
        cout<<"Error while running query: "<<mysql_error(conn)<<endl;
    }
}

void writeQuery(string Query)
{
    char query[1000];
    
    snprintf(query, 1000, Query.c_str());

    int queryStatus = mysql_query(conn, query);

    if (queryStatus != 0) {
        cout<<"Error while running query: "<<mysql_error(conn)<<endl;
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

    if (mysql_real_connect(conn, "localhost", "group50_dbms", "password", "dbms_demo", 3306, NULL, 0)) {
        cout<<"Connected Successfully!"<<endl; 

        vector<string> Commissions_Columns = {"salesman_id", "address_city", "coverage_city", "commission"};
        vector<string> Commissions_Columns_Types = {"int", "varchar(255)", "varchar(255)", "int"};

        string tableName = "commissions";
        createTable(tableName, Commissions_Columns, Commissions_Columns_Types);
        
        writeQuery("ALTER TABLE Commissions ADD CONSTRAINT PK_Commissions PRIMARY KEY (`salesman_id`, `address_city`, `coverage_city`)");
        writeQuery("ALTER TABLE Commissions ADD FOREIGN KEY (`salesman_id`) REFERENCES Salesmen(`salesman_id`)");

        writeQuery("INSERT INTO Commissions SELECT DISTINCT `salesman_id`, `address_city`, `coverage_city`, `commission` FROM Salesmen");


        writeQuery("ALTER TABLE Salesmen DROP COLUMN `address_city`");
        writeQuery("ALTER TABLE Salesmen DROP COLUMN `coverage_city`");
        writeQuery("ALTER TABLE Salesmen DROP COLUMN `commission`");

    }
    else {
        cout << "Error while connecting! : "<<mysql_error(conn)<<endl;
    }

    return 0;
}


/* ROUGH SECTION



*/

