#include <iostream>
#include <fstream>
#include <windows.h>
#include <mysql.h>
#include <vector>
#include <string>
#include <time.h>

using namespace std;

MYSQL *conn;

int createTable(string tableName, vector<string> colNames, vector<string> colType, string extras="") {
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
    return createTableStatus;
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
        vector<string> book_det_Columns_Types = {"varchar(255)", "varchar(255) NOT NULL PRIMARY KEY", "varchar(512)"};

        int createTableStatus1 = createTable(tableName1, book_det_Columns, book_det_Columns_Types);
        
        /* Author Details Table */
        string tableName2 = "Author_Details";
        vector<string> auth_det_Columns = {"author_id", "author_name"};
        vector<string> auth_det_Columns_Types = {"varchar(255) NOT NULL PRIMARY KEY", "varchar(255)"};

        int createTableStatus2 = createTable(tableName2, auth_det_Columns, auth_det_Columns_Types);
        
        /* Book Purchase Table */
        string tableName3 = "Book_Purchase_Details";
        vector<string> book_pur_Columns = {"book_id", "purchase_date", "copies", "price", "purchase_price", "book_value"};
        vector<string> book_pur_Columns_Types = {"varchar(255) NOT NULL", "varchar(255) NOT NULL", "int NOT NULL", "int NOT NULL", "int NULL", "int NULL"};

        int createTableStatus3 = createTable(tableName3, book_pur_Columns, book_pur_Columns_Types);

        if(createTableStatus1 == 0 && createTableStatus2 == 0 && createTableStatus3 == 0)
        {
            cout<<"Tables created successfully!"<<endl;
        }

        /* Inserting values into Book Details Table */
        // tableName = "Book_Details";

        bool insertStatus = 0;

        insertStatus += insertValue(tableName1, book_det_Columns, {"Da_001", "Da001_Sel", "Self Comes to Mind"});
        insertStatus += insertValue(tableName1, book_det_Columns, {"Mi_009", "Mi009_Emo", "Emotion Machine"});
        insertStatus += insertValue(tableName1, book_det_Columns, {"Mi_009", "Mi009_Soc", "Society of Mind"});
        insertStatus += insertValue(tableName1, book_det_Columns, {"Ra_001", "Ra001_Pha", "Phantoms in the Brain"});
        insertStatus += insertValue(tableName1, book_det_Columns, {"Ro_015", "Ro015_Fan", "Fantastic Beasts and Where to Find Them"});
        insertStatus += insertValue(tableName1, book_det_Columns, {"Ro_015", "Ro015_Gob", "Goblet of Fire_Harry Potter"});
        insertStatus += insertValue(tableName1, book_det_Columns, {"Ro_015", "Ro015_Phi", "Philosopher’s Stone_Harry Potter"});
        insertStatus += insertValue(tableName1, book_det_Columns, {"Ro_015", "Ro015_Pri", "Prisoner of Azkaban_Harry Potter"});
        insertStatus += insertValue(tableName1, book_det_Columns, {"Sa_001", "Sa001_Voy", "Voyage of the Turtle"});
        insertStatus += insertValue(tableName1, book_det_Columns, {"Sa_001", "Sa001_Wha", "What Animals Think"});
        insertStatus += insertValue(tableName1, book_det_Columns, {"To_015", "To015_Fel", "Fellowship of the Rings_Lord of the Rings"});
        insertStatus += insertValue(tableName1, book_det_Columns, {"Wo_015", "Wo015_Wod", "Wodehouse at the Wicket"});
        

        insertStatus += insertValue(tableName2, auth_det_Columns, {"Da_001", "Damasio"});
        insertStatus += insertValue(tableName2, auth_det_Columns, {"Mi_009", "Minsky"});
        insertStatus += insertValue(tableName2, auth_det_Columns, {"Ra_001", "Ramachandran"});
        insertStatus += insertValue(tableName2, auth_det_Columns, {"Ro_015"," Rowling"});
        insertStatus += insertValue(tableName2, auth_det_Columns, {"Ru_021", "Russel"});
        insertStatus += insertValue(tableName2, auth_det_Columns, {"Sa_001"," Safina"});
        insertStatus += insertValue(tableName2, auth_det_Columns, {"Ta_001", "Tagore"});
        insertStatus += insertValue(tableName2, auth_det_Columns, {"To_015", "Tolkien"});
        insertStatus += insertValue(tableName2, auth_det_Columns, {"Wo_015", "Wodehouse"});

        vector<string> book_pur_Columns2 = {"book_id", "purchase_date", "copies", "price"};

        insertStatus += insertValue(tableName3, book_pur_Columns2, {"Da001_Sel", "Sep 1, 2021", "1", "50"});
        insertStatus += insertValue(tableName3, book_pur_Columns2, {"Da001_Sel", "Sep 7, 2021", "5" , "50"});
        insertStatus += insertValue(tableName3, book_pur_Columns2, {"Mi009_Emo", "Sep 2, 2021", "2", "50"});
        insertStatus += insertValue(tableName3, book_pur_Columns2, {"Mi009_Soc", "Sep 1, 2021", "2", "50"});
        insertStatus += insertValue(tableName3, book_pur_Columns2, {"Ra001_Pha", "Sep 2, 2021", "2", "50"});
        insertStatus += insertValue(tableName3, book_pur_Columns2, {"Ro015_Fan", "Sep 1, 2021", "3", "50"});
        insertStatus += insertValue(tableName3, book_pur_Columns2, {"Ro015_Fan", "Sep 9, 2021", "12", "35"});
        insertStatus += insertValue(tableName3, book_pur_Columns2, {"Ro015_Gob", "Sep 1, 2021", "3", "50"});
        insertStatus += insertValue(tableName3, book_pur_Columns2, {"Ro015_Phi", "Sep 1, 2021", "3", "50"});
        insertStatus += insertValue(tableName3, book_pur_Columns2, {"Ro015_Phi", "Sep 10, 2021","20", "75"});
        insertStatus += insertValue(tableName3, book_pur_Columns2, {"Ro015_Pri", "Sep 1, 2021", "3", "50"});
        insertStatus += insertValue(tableName3, book_pur_Columns2, {"Sa001_Voy", "Sep 2, 2021", "2", "50"});
        insertStatus += insertValue(tableName3, book_pur_Columns2, {"To015_Fel", "Sep 1, 2021", "3", "50"});
        insertStatus += insertValue(tableName3, book_pur_Columns2, {"To015_Fel", "Sep 12, 2021","9", "55"});
        insertStatus += insertValue(tableName3, book_pur_Columns2, {"Wo015_Wod", "Sep 5, 2021", "1", "50"});

        if(insertStatus == 0)
        {
            cout<<"Values inserted into table successfully!"<<endl;
        }
        else{
            cout<<"All values not inserted into table!"<<endl;
        }
        

    } 
    else 
    {
        cout<<"Error while connecting!"<<endl;
    }    

    return 0;

}