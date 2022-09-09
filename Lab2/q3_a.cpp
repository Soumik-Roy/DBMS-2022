//Command to Compile: g++ q3_a.cpp -o q3_a.exe -lmysql

#include <iostream>
#include <windows.h>
#include <mysql.h>
#include <vector>
#include <string>

using namespace std;

MYSQL *conn;

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

void writeQuery(string tableName, string Query, bool printOutput = true)
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

        string tableName = "salesmen";
        
        // a
        writeQuery(tableName, "SELECT * FROM %s");
        // b
        writeQuery(tableName, "SELECT * FROM %s WHERE `name` = 'abc'");
        // c
        writeQuery(tableName, "SELECT `address_city`, `commission` FROM %s WHERE `address_city` IN ('Mumbai', 'Chennai')");
        // d
        writeQuery(tableName, "SELECT `salesman_id`, `name`, `address_city` FROM %s ORDER BY `address_city`");
        // e
        writeQuery(tableName, "SELECT `salesman_id`, `name`, `address_city`, `coverage_city` FROM %s WHERE `address_city` <> `coverage_city`");
        // f
        writeQuery(tableName, "SELECT `name`, `coverage_city`, `commission` FROM %s WHERE `coverage_city` = 'mumbai' ORDER BY `commission` DESC LIMIT 1");
        // g
        writeQuery(tableName, "SELECT `coverage_city` FROM %s ORDER BY `commission` DESC LIMIT 1");
        // h
        writeQuery(tableName, "SELECT AVG(`commission`) AS `average_commission`, `coverage_city` FROM %s GROUP BY `coverage_city`");
        // i
        writeQuery(tableName, "SELECT `coverage_city`, COUNT(DISTINCT(`commission`)) AS `dist_comcount` FROM %s GROUP BY `coverage_city` HAVING `dist_comcount` = 1");
        // j
        writeQuery(tableName, "SELECT `commission` FROM %s GROUP BY `salesman_id` HAVING COUNT(DISTINCT(`coverage_city`)) = (SELECT COUNT(DISTINCT(`coverage_city`)) FROM `" + tableName + "`)");
        // k
        writeQuery(tableName, "SELECT * FROM %s GROUP BY `salesman_id` HAVING COUNT(DISTINCT(`coverage_city`)) = (SELECT COUNT(DISTINCT(`coverage_city`)) FROM " + tableName + ")");
        // l
        writeQuery(tableName, "ALTER TABLE %s ADD COLUMN `date_of_employment` date, ADD COLUMN `date_of_release` date", false);

    }
    else {
        cout << "Error while connecting! : "<<mysql_error(conn)<<endl;
    }

    return 0;
}
