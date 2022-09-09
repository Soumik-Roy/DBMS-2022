//Command to Compile: g++ q4_a.cpp -o q4_a.exe -lmysql

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
    string command = "CREATE TABLE IF NOT EXISTS `" + tableName + "` (";

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

        // Groceries Table
        vector<string> groceries_Columns = {"purchase_id", "item_name", "quantity_bought", "cur_stock", "date","price"};
        vector<string> groceries_Columns_Types = {"int AUTO_INCREMENT NOT NULL PRIMARY KEY", "varchar(255)", "int", "int", "date","int"};

        string tableName = "groceries";
        createTable(tableName, groceries_Columns, groceries_Columns_Types);

        // Thresholds Table
        vector<string> thresholds_Columns = {"item_name", "critical_threshold", "borderline_threshold"};
        vector<string> thresholds_Columns_Types = {"varchar(255) NOT NULL PRIMARY KEY", "int", "int"};

        // thresholds entries
        string tableName2 = "thresholds";
        createTable(tableName2, thresholds_Columns, thresholds_Columns_Types);

        vector<string> fields_t = {"item_name", "quantity_bought", "cur_stock", "date","price"};

        insertValue(tableName2, fields_t, {"flour", "250", "500"});
        insertValue(tableName2, fields_t, {"oil", "250", "500"});
        insertValue(tableName2, fields_t, {"ghee", "0", "100"});
        insertValue(tableName2, fields_t, {"dal", "250", "500"});
        insertValue(tableName2, fields_t, {"rice", "250", "500"});
        insertValue(tableName2, fields_t, {"milk", "0", "200"});
        insertValue(tableName2, fields_t, {"potato", "-1", "100"});
        insertValue(tableName2, fields_t, {"tomato", "100", "250"});
        insertValue(tableName2, fields_t, {"onion", "100", "250"});
        insertValue(tableName2, fields_t, {"watermelon", "-1", "200"});
        insertValue(tableName2, fields_t, {"apple", "-1", "200"});
        insertValue(tableName2, fields_t, {"chicken", "-1", "200"});
        insertValue(tableName2, fields_t, {"fish", "-1", "0"});
        insertValue(tableName2, fields_t, {"mutton", "-1", "0"});
        insertValue(tableName2, fields_t, {"tiger prawns", "-1", "-1"});
        insertValue(tableName2, fields_t, {"sugar", "100", "200"});
        insertValue(tableName2, fields_t, {"paneer", "-1", "0"});
        insertValue(tableName2, fields_t, {"nutella", "-1", "-1"});


        // groceries entries
        vector<string> fields = {"item_name", "quantity_bought", "cur_stock", "date","price"};

        insertValue(tableName, fields, {"flour", "5000", "5000", "2022-07-1","200"});
        insertValue(tableName, fields, {"oil", "2000", "2000", "2022-07-1","200"});
        insertValue(tableName, fields, {"ghee", "200", "200", "2022-07-1","200"});
        insertValue(tableName, fields, {"dal", "5000", "5000", "2022-07-1","400"});
        insertValue(tableName, fields, {"rice", "5000", "5000", "2022-07-1","200"});
        insertValue(tableName, fields, {"milk", "2000", "2000", "2022-07-1","100"});
        insertValue(tableName, fields, {"potato", "1000", "1000", "2022-07-1","40"});
        insertValue(tableName, fields, {"tomato", "1000", "1000", "2022-07-1","60"});
        insertValue(tableName, fields, {"onion", "1000", "1000", "2022-07-1","30"});
        insertValue(tableName, fields, {"watermelon", "500", "500", "2022-07-1","50"});
        insertValue(tableName, fields, {"apple", "500", "500", "2022-07-1","80"});
        insertValue(tableName, fields, {"chicken", "1000", "1000", "2022-07-1","250"});

        insertValue(tableName, fields, {"milk", "1000", "1000", "2022-07-4","50"});
        insertValue(tableName, fields, {"milk", "1000", "1000", "2022-07-7","50"});




        insertValue(tableName, fields, {"fish", "1000", "1000", "2022-07-9","300"});
        insertValue(tableName, fields, {"milk", "1000", "1000", "2022-07-12","50"});


        insertValue(tableName, fields, {"mutton", "1000", "1000", "2022-07-15","500"});
        insertValue(tableName, fields, {"milk", "1000", "1000", "2022-07-17","50"});
        insertValue(tableName, fields, {"tiger prawns", "1000", "1000", "2022-07-22","1000"});

        insertValue(tableName, fields, {"milk", "2000", "2000", "2022-07-25","100"});

        insertValue(tableName, fields, {"milk", "1000", "1000", "2022-07-26","50"});

        // August
        insertValue(tableName, fields, {"flour", "5000", "5400", "2022-08-1","220"});
        insertValue(tableName, fields, {"oil", "2000", "2100", "2022-08-1","250"});
        insertValue(tableName, fields, {"ghee", "200", "200", "2022-08-1","185"});
        insertValue(tableName, fields, {"dal", "5000", "5010", "2022-08-1","390"});
        insertValue(tableName, fields, {"rice", "5000", "5700", "2022-08-1","207"});
        insertValue(tableName, fields, {"milk", "2000", "2000", "2022-08-1","100"});
        insertValue(tableName, fields, {"tomato", "1000", "1000", "2022-08-1","69"});
        insertValue(tableName, fields, {"onion", "1000", "1000", "2022-08-1","25"});
        insertValue(tableName, fields, {"sugar", "2000", "2000", "2022-08-1","90"});

        insertValue(tableName, fields, {"milk", "1000", "1000", "2022-08-4","50"});
        insertValue(tableName, fields, {"milk", "1000", "1000", "2022-08-7","50"});

        insertValue(tableName, fields, {"chicken", "1000", "1000", "2022-08-9","250"});
        insertValue(tableName, fields, {"milk", "1000", "1000", "2022-08-12","50"});

        insertValue(tableName, fields, {"mutton", "1000", "1000", "2022-08-15","500"});
        insertValue(tableName, fields, {"milk", "1000", "1000", "2022-08-17","50"});

        insertValue(tableName, fields, {"milk", "2000", "2000", "2022-08-25","100"});

        insertValue(tableName, fields, {"milk", "1000", "1000", "2022-08-26","50"});

        // September
        insertValue(tableName, fields, {"flour", "5000", "5500", "2022-09-1","200"});
        insertValue(tableName, fields, {"oil", "2000", "2000", "2022-09-1","200"});
        insertValue(tableName, fields, {"ghee", "200", "250", "2022-09-1","200"});
        insertValue(tableName, fields, {"dal", "5000", "5100", "2022-09-1","400"});
        insertValue(tableName, fields, {"rice", "5000", "5250", "2022-09-1","200"});
        insertValue(tableName, fields, {"milk", "2000", "2000", "2022-09-1","100"});
        insertValue(tableName, fields, {"potato", "1000", "1000", "2022-09-1","40"});
        insertValue(tableName, fields, {"tomato", "1000", "1000", "2022-09-1","60"});
        insertValue(tableName, fields, {"onion", "1000", "1000", "2022-09-1","30"});
        insertValue(tableName, fields, {"apple", "500", "530", "2022-09-1","80"});
        insertValue(tableName, fields, {"chicken", "1000", "1000", "2022-09-1","250"});

        insertValue(tableName, fields, {"milk", "1000", "1200", "2022-09-4","50"});
        insertValue(tableName, fields, {"milk", "1000", "1000", "2022-09-7","50"});

        insertValue(tableName, fields, {"paneer", "500", "500", "2022-09-9","200"});
        insertValue(tableName, fields, {"nutella", "1000", "1000", "2022-09-9","750"});

        insertValue(tableName, fields, {"milk", "1000", "1000", "2022-09-12","50"});

        insertValue(tableName, fields, {"mutton", "1000", "1000", "2022-09-15","500"});
        insertValue(tableName, fields, {"milk", "1000", "1000", "2022-09-17","50"});
        insertValue(tableName, fields, {"chicken", "1000", "1000", "2022-09-21","250"});

        insertValue(tableName, fields, {"milk", "2000", "2000", "2022-09-25","100"});

        insertValue(tableName, fields, {"milk", "1000", "1500", "2022-09-27","50"});


    }
    else {
        cout << "Error while connecting! : "<<mysql_error(conn)<<endl;
    }

    return 0;
}
