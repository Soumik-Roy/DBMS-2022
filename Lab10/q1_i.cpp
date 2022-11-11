#include <iostream>
#include <windows.h>
#include <mysql.h>

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


int main(){
    conn = mysql_init(NULL);
    if (conn == NULL) {
        cout<<"Error: "<<mysql_error(conn)<<endl;
        exit(1);
    }
    
    if (mysql_real_connect(conn, "localhost", "susim", "12345#ghs","dbms_lab10", 3306, NULL, 0)) {

    cout<<"Connected Successfully!"<<endl;
    } else {
    cout<<"Error while connecting!"<<endl;
    }

    char tableName3[4096] = "purchase_values_by_books_table";
    char query3[4096];
    snprintf(query3, 4096, "CREATE TABLE `%s` (`Book_ID` varchar(255), `Cost` int NULL);", tableName3);
    int createTableStatus3 = mysql_query(conn, query3);

    if(createTableStatus3 != 0){
        cout << "Error in creating table" << mysql_error(conn) << endl;
    }
    else{
        cout << "All tables created successfully" << mysql_error(conn) << endl;
    }

    //i

    if (mysql_query(conn, "CREATE TRIGGER book_price_tag BEFORE INSERT ON Book_Purchase_Details FOR EACH ROW BEGIN UPDATE purchase_values_by_books_table set purchase_values_by_books_table.cost = purchase_values_by_books_table.cost + new.Purchase_Price WHERE purchase_values_by_books_table.Book_ID = New.Book_ID;END")==0){
        char query6[4096];
        snprintf(query6, 4096, "INSERT INTO `%s` VALUES ('Da001_Sel', NULL),('Da001_Sel', NULL),('Mi009_Emo', NULL),('Mi009_Soc', NULL),('Ra001_Pha', NULL),('Ro015_Fan', NULL),('Ro015_Fan', NULL),('Ro015_Gob', NULL),('Ro015_Phi',NULL),('Ro015_Phi', NULL),('Ro015_Pri', NULL),('Sa001_Voy', NULL),('Sa001_Wha', NULL),('To015_Fel',NULL),('To015_Fel',NULL),('Wo015_Wod', NULL);", tableName3);
        int studentInsertionStatus3 = mysql_query(conn, query6);
        if (studentInsertionStatus3 != 0){
            cout << "Error while inserting in table3: " << mysql_error(conn) << endl;
        }

        if(mysql_query(conn, "SELECT * FROM purchase_values_by_books_table;")==0){
            display();
            cout << "Query i Answwered !" << endl;
    }
    }
    else{
        cout << " Error in answering query i !" << mysql_error(conn) << endl;
    }



    return 0;

}