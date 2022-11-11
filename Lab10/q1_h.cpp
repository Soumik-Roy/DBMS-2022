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

    char tableName3[4096] = "Book_Purchase_Details";
    char query3[4096];
    snprintf(query3, 4096, "CREATE TABLE `%s` (`Book_ID` varchar(255), `Purchase_Dt` varchar(255), `Copies` int, `Price` int, `Purchase_Price` int NULL, `Book_Value` int NULL);", tableName3);
    int createTableStatus3 = mysql_query(conn, query3);

    if(createTableStatus3 != 0){
        cout << "Error in creating table" << mysql_error(conn) << endl;
    }
    else{
        cout << "All tables created successfully" << mysql_error(conn) << endl;
    }

    //i

    if (mysql_query(conn, "CREATE TRIGGER book_values BEFORE INSERT ON Book_Purchase_Details FOR EACH ROW SET new.Book_Value = new.Purchase_Price + 0.4*(new.Purchase_Price);")==0){
        char query6[4096];
        snprintf(query6, 4096, "INSERT INTO `%s` VALUES ('Da001_Sel', 'Sep 1, 2021', '1', '50','50',NULL),('Da001_Sel', 'Sep 7, 2021', '5', '50','250',NULL),('Mi009_Emo', 'Sep 2, 2021', '2', '50','100',NULL),('Mi009_Soc', 'Sep 1, 2021', '2', '50','100',NULL),('Ra001_Pha', 'Sep 2, 2021', '2', '50','100',NULL),('Ro015_Fan', 'Sep 1, 2021', '3', '50','150',NULL),('Ro015_Fan', 'Sep 9, 2021', '12', '35','420',NULL),('Ro015_Gob', 'Sep 1, 2021', '3', '50','150',NULL),('Ro015_Phi', 'Sep 1, 2021', '1', '50','50',NULL),('Ro015_Phi', 'Sep 10, 2021', '20', '75','1500',NULL),('Ro015_Pri', 'Sep 1, 2021', '3', '50','150',NULL),('Sa001_Voy', 'Sep 2, 2021', '2', '50','100',NULL),('Sa001_Wha', 'Sep 2, 2021', '2', '50','100',NULL),('To015_Fel', 'Sep 1, 2021', '3', '50','150',NULL),('To015_Fel', 'Sep 12, 2021', '9', '55','495',NULL),('Wo015_Wod', 'Sep 5, 2021', '1', '50','50',NULL);", tableName3);
        int studentInsertionStatus3 = mysql_query(conn, query6);
        if (studentInsertionStatus3 != 0){
            cout << "Error while inserting in table3: " << mysql_error(conn) << endl;
        }

        if(mysql_query(conn, "SELECT * FROM Book_Purchase_Details;")==0){
            display();
            cout << "Query h Answwered !" << endl;
    }
    }
    else{
        cout << " Error in answering query h !" << mysql_error(conn) << endl;
    }



    return 0;

}