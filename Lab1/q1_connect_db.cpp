//Command to Compile: g++ q1_connect_db.cpp -o q1_connect_db.exe -lmysql

#include <iostream>
#include <windows.h>
#include <mysql.h>

using namespace std;

MYSQL *conn;

int main()
{
    conn = mysql_init(NULL);
    if (conn == NULL) {
        cout<<"Error: "<<mysql_error(conn)<<endl;
        exit(1);
    }

    // mysql_real_connect(Connection Instance, Username, Password, Database, Port, Unix Socket, Client Flag)
    if (mysql_real_connect(conn, "localhost", "group50_dbms", "password", "dbms_lab1", 3306, NULL, 0)) 
    {
        cout<<"Connected Successfully!"<<endl;
    } 
    else 
    {
        cout<<"Error while connecting! : "<<mysql_error(conn)<<endl;
    }

    return 0;
}
