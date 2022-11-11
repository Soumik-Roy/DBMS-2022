#include <iostream>
#include <fstream>
#include <windows.h>
#include <mysql.h>
#include <vector>
#include <string>
#include <time.h>

using namespace std;

MYSQL *conn;

int display(){
    
    printf("Displaying Result\n");
    MYSQL_RES *results = mysql_store_result(conn);
    MYSQL_ROW record;
    MYSQL_FIELD *fields;
    int num_fields = mysql_num_fields(results);
    fields = mysql_fetch_fields(results);
    for(int i = 0; i < num_fields; i++){
        cout << fields[i].name <<" ";
    }
    cout<<endl;
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

int insertValue(string tableName, vector<string> columnNames, vector<string> values) {
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
    return insertValStatus;
}


int writeQuery(string Query, bool printOutput = false)
{
    char query[1000];
    snprintf(query, 1000, Query.c_str());
    int queryStatus = mysql_query(conn, query);

    if(printOutput) display();

    cout<<endl;

    if (queryStatus != 0) {
        cout<<"Error while running query: "<<mysql_error(conn)<<endl;
    }
    return queryStatus;
}

int main(){
    conn = mysql_init(NULL);
    if (conn == NULL) {
        cout<<"Error: "<<mysql_error(conn)<<endl;
        exit(1);
    }
    
    if (mysql_real_connect(conn, "localhost", "group50_dbms", "password", "dbms_lab10", 3306, NULL, 0)) 
    {
        cout<<"Connected Successfully!"<<endl;

        /* Book Details Table */
        string tableName1 = "Book_Details";
        vector<string> book_det_Columns = {"author_id", "book_id", "book_name"};
        
        /* Author Details Table */
        string tableName2 = "Author_Details";
        vector<string> auth_det_Columns = {"author_id", "author_name"};
        
        /* Book Purchase Table */
        string tableName3 = "Book_Purchase_Details";
        vector<string> book_pur_Columns = {"book_id", "purchase_date", "copies", "price", "purchase_price", "book_value"};
        
        // d
        cout<<"\nPART D\n-----------\n\n";

        int queryStatus = writeQuery("UPDATE income SET author_name='Soumik' WHERE book_name='Emotion Machine';");

        if(queryStatus==0){
            int q_stat = writeQuery("SELECT * FROM income;");
            if(q_stat==0){
                display();
                cout << "Query d Answwered !" << endl;
            }
            else
            {
                cout<<"Error while selecting from income view ! "<< mysql_error(conn) <<endl;
            }
            
        }
        else{
            cout << " Error while Updating income View" << mysql_error(conn) << endl;
        }

    } 
    else 
    {
        cout<<"Error while connecting!"<<endl;
    }    

    return 0;

}