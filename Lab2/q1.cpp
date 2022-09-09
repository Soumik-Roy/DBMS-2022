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

void writeQuery(string Query, bool printOutput = true)
{
    char query[1000];
    snprintf(query, 1000, Query.c_str());
    int queryStatus = mysql_query(conn, query);

    if(printOutput) display();

    cout<<endl;

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

        createTable("t1", {"num1", "num2", "num3"}, {"int NOT NULL PRIMARY KEY", "int", "int"});
        insertValue("t1", {}, {"1", "2", "3"});
        insertValue("t1", {}, {"2", "4", "6"});


        writeQuery("SELECT * FROM `t1`");

    }
    else {
        cout << "Error while connecting! : "<<mysql_error(conn)<<endl;
    }

    return 0;
}

