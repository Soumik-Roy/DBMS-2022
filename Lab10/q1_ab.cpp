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

        // a
        cout<<"PART A";
        time_t t1,t2,t3,t4;

        time(&t1);

        int queryStatus = writeQuery("CREATE OR REPLACE VIEW income as(SELECT author_Name, book_name, SUM(copies) FROM Author_Details, Book_Details, Book_Purchase_Details WHERE Author_Details.author_id=Book_Details.author_id and Book_Details.book_id=Book_Purchase_Details.book_id GROUP BY book_name);");

        if (queryStatus==0){
            int q_stat = writeQuery("select * from income;");
            if(q_stat==0){
                time(&t2);
                display();
                cout << "Query a Answered !" << endl;
            }
        }
        else{
            cout << " Error in answering query a ! " << mysql_error(conn) << endl;
        }

        // b

        cout<<"\n----------\n\nPART B\n";

        time(&t3);
        queryStatus = writeQuery("SELECT author_name, book_name, copies FROM Author_Details, Book_Details, Book_Purchase_Details WHERE Author_Details.author_id=Book_Details.author_id and Book_Details.book_id=Book_Purchase_Details.book_id;");
        if(queryStatus==0){
            time(&t4);
            if(double(t2-t1)>double(t4-t3))
                cout << "SELECT IS FASTER THAN VIEW" << endl;
            else if(double(t2-t1)<double(t4-t3))
                cout << "SELECT IS SLOWER THAN VIEW" << endl;
            else
                cout << "Both take equal time" << endl;
        }
        else
        {
            cout << " Error in running normal Select Query! " << mysql_error(conn) << endl;
        }

    } 
    else 
    {
        cout<<"Error while connecting!"<<endl;
    }    

    return 0;

}