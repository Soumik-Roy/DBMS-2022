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

        vector<string> purchase_Columns = {"purchase_id", "item_name", "quantity", "date","price"};
        vector<string> purchase_Columns_Types = {"int AUTO_INCREMENT NOT NULL PRIMARY KEY", "varchar(255)", "int", "date","int"};

        vector<string> stock_Columns = {"item_name", "cur_stock", "last_purchase_date"};
        vector<string> stock_Columns_Types = {"varchar(256) NOT NULL PRIMARY KEY", "int", "date", "int"};

        string tableName1 = "purchase";
        createTable(tableName1, purchase_Columns, purchase_Columns_Types);

        string tableName2 = "stock";
        createTable(tableName2, stock_Columns, stock_Columns_Types);

        // writeQuery("ALTER TABLE purchase ADD FOREIGN KEY (`item_name`) REFERENCES stock(`item_name`)");

        writeQuery("INSERT INTO stock SELECT * FROM (SELECT DISTINCT `item_name`, `cur_stock`-`quantity_bought` AS `curr_stock`, `date` FROM groceries WHERE MONTH(`date`)=9 ORDER BY `date`) AS a GROUP BY `item_name`");

        writeQuery("INSERT INTO purchase SELECT DISTINCT `purchase_id`, `item_name`, `quantity_bought`, `date`, `price` FROM groceries");

        // writeQuery("INSERT INTO stock(`item_name`) SELECT `item_name` FROM groceries");

        // writeQuery("INSERT INTO stock ((SELECT DISTINCT `item_name` FROM (SELECT DISTINCT `item_name`, `cur_stock`-`quantity_bought` AS `curr_stock`, `date` FROM groceries WHERE MONTH(`date`)=9 ORDER BY `date`) AS a GROUP BY `item_name`), 0, 2022-08-01)");

    }
    else {
        cout << "Error while connecting! : "<<mysql_error(conn)<<endl;
    }

    return 0;
}


/* ROUGH SECTION



*/

