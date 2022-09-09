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
        
        // i
        writeQuery("SELECT * FROM purchase GROUP BY `item_name`");
        // ii
        writeQuery("SELECT * FROM purchase WHERE MONTH(`date`) = 8");
        // iii
        writeQuery("SELECT * FROM stock INNER JOIN thresholds ON stock.item_name = thresholds.item_name WHERE stock.cur_stock <= thresholds.critical_threshold");
        // iv
        writeQuery("SELECT * FROM stock INNER JOIN thresholds ON stock.item_name = thresholds.item_name WHERE stock.cur_stock <= thresholds.borderline_threshold AND stock.cur_stock > thresholds.critical_threshold");
        // v
        writeQuery("SELECT * FROM stock INNER JOIN thresholds ON stock.item_name = thresholds.item_name WHERE stock.cur_stock > thresholds.borderline_threshold");
        // vi
        writeQuery("SELECT MONTH(`date`) AS `month`, SUM(`price`) AS `total expenditure`, AVG(`price`) AS `avg expenditure` FROM purchase GROUP BY MONTH(`date`) ORDER BY MONTH(`date`) LIMIT 3");
        // vii
        writeQuery("SELECT * FROM purchase GROUP BY `item_name` HAVING COUNT(DISTINCT(MONTH(`date`))) = (SELECT COUNT(DISTINCT(MONTH(`date`))) FROM groceries)");
        

    }
    else {
        cout << "Error while connecting! : "<<mysql_error(conn)<<endl;
    }

    return 0;
}
