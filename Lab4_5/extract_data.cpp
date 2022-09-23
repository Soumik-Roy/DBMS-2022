//Command to Compile: g++ extract_data.cpp -o extract_data.exe -lmysql

#include <iostream>
#include <windows.h>
#include <mysql.h>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

MYSQL *conn;

int display_results(string exportResults_fname = "")
{
    MYSQL_RES *results = mysql_store_result(conn);
    MYSQL_ROW record;
    MYSQL_FIELD *fields;
    int num_fields = mysql_num_fields(results);

    ofstream outputFile(exportResults_fname);

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
            
            if(exportResults_fname.size()>0)
                outputFile << record[i] << " ";
        }
        cout<<endl;
        if(exportResults_fname.size()>0)
            outputFile<<endl;
    }

    outputFile.close();
    mysql_free_result(results);

    return 0;
}


void writeQuery(string Query, bool printOutput = true, string exportOutput_fname = "")
{
    char query[1000];
    snprintf(query, 1000, Query.c_str());
    int queryStatus = mysql_query(conn, query);

    if(printOutput)
    {
        display_results(exportOutput_fname);
    }

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

    if (mysql_real_connect(conn, "localhost", "group50_dbms", "password", "dbms_lab4_5", 3306, NULL, 0)) {
        cout<<"Connected Successfully!"<<endl; 

        string tableName = "library_catalogue";
        
        writeQuery("SELECT book_id FROM library_catalogue", true, "bookIDs.txt");

    }
    else {
        cout << "Error while connecting! : "<<mysql_error(conn)<<endl;
    }

    return 0;
}
