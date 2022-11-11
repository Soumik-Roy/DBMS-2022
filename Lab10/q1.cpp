#include <iostream>
#include <windows.h>
#include <mysql.h>
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

    char tableName1[2048] = "Book_Details";
    char query1[2048];
    snprintf(query1, 2048, "CREATE TABLE `%s` (`Author_ID` varchar(255), `Book_ID` varchar(255), `Book_Name` varchar(255));", tableName1);
    int createTableStatus1 = mysql_query(conn, query1);
    

    char tableName2[2048] = "Author_Details";
    char query2[2048];
    snprintf(query2, 2048, "CREATE TABLE `%s` (`Author_ID` varchar(255), `Author_Name` varchar(255));", tableName2);
    int createTableStatus2 = mysql_query(conn, query2);
    

    char tableName3[4096] = "Book_Purchase_Details";
    char query3[4096];
    snprintf(query3, 4096, "CREATE TABLE `%s` (`Book_ID` varchar(255), `Purchase_Dt` varchar(255), `Copies` int, `Price` int, `Purchase_Price` int NULL, `Book_Value` int NULL);", tableName3);
    int createTableStatus3 = mysql_query(conn, query3);

    if(createTableStatus1 != 0 && createTableStatus2 != 0 && createTableStatus3 != 0){
        cout << "Error in creating table" << mysql_error(conn) << endl;
    }
    else{
        cout << "All tables created successfully" << mysql_error(conn) << endl;
    }

    char query4[2048];
    snprintf(query4, 2048, "INSERT INTO `%s` VALUES ('Da_001', 'Da001_Sel', 'Self Comes to Mind'),('Mi_009','Mi009_Emo','Emotion Machine'),('Mi_009','Mi009_Soc','Society of Mind'),('Ra_001','Ra001_Pha','Phantoms in the Brain'),('Ro_015','Ro015_Fan','Fantastic Beasts and Where to Find Them'),('Ro_015','Ro015_Gob','Goblet of Fire_Harry Potter'),('Ro_015','Ro015_Phi','Philosophers Stone_Harry Potter'),('Ro_015','Ro015_Pri','Prisoner of Azkaban_Harry Potter'),('Sa_001','Sa001_Voy','Voyage of the Turtle'),('Sa_001','Sa001_Wha','What Animals Think'),('Sa_001','To015_Fel','Fellowship of the Rings_Lord of the Rings'),('Wo_015','Wo015_Wod','Wodehouse at the Wicket');", tableName1);
    int studentInsertionStatus1 = mysql_query(conn, query4);
    if (studentInsertionStatus1 != 0){
        cout << "Error while inserting in table1: " << mysql_error(conn) << endl;
    }

    char query5[2048];
    snprintf(query5,2048,"INSERT INTO `%s` VALUES ('Da_001', 'Damasio'),('Mi_009', 'Minsky'),('Ra_001', 'Damasio'),('Ro_015', 'Rowling'),('Ru_021', 'Russel'),('Sa_001', 'Safina'),('Ta_001', 'Tagore'),('To_015', 'Tolkein'),('Wo_015', 'Woodhouse');",tableName2);
    int studentInsertionStatus2 = mysql_query(conn, query5);
    if (studentInsertionStatus2 != 0){
        cout << "Error while inserting in table2: " << mysql_error(conn) << endl;
    }

    char query6[4096];
    snprintf(query6, 4096, "INSERT INTO `%s` VALUES ('Da001_Sel', 'Sep 1, 2021', '1', '50',NULL,NULL),('Da001_Sel', 'Sep 7, 2021', '5', '50',NULL,NULL),('Mi009_Emo', 'Sep 2, 2021', '2', '50',NULL,NULL),('Mi009_Soc', 'Sep 1, 2021', '2', '50',NULL,NULL),('Ra001_Pha', 'Sep 2, 2021', '2', '50',NULL,NULL),('Ro015_Fan', 'Sep 1, 2021', '3', '50',NULL,NULL),('Ro015_Fan', 'Sep 9, 2021', '12', '35',NULL,NULL),('Ro015_Gob', 'Sep 1, 2021', '3', '50',NULL,NULL),('Ro015_Phi', 'Sep 1, 2021', '3', '50',NULL,NULL),('Ro015_Phi', 'Sep 10, 2021', '20', '75',NULL,NULL),('Ro015_Pri', 'Sep 1, 2021', '3', '50',NULL,NULL),('Sa001_Voy', 'Sep 2, 2021', '2', '50',NULL,NULL),('Sa001_Wha', 'Sep 2, 2021', '2', '50',NULL,NULL),('To015_Fel', 'Sep 1, 2021', '3', '50',NULL,NULL),('To015_Fel', 'Sep 12, 2021', '9', '55',NULL,NULL),('Wo015_Wod', 'Sep 5, 2021', '1', '50',NULL,NULL);", tableName3);
    int studentInsertionStatus3 = mysql_query(conn, query6);
    if (studentInsertionStatus3 != 0){
        cout << "Error while inserting in table3: " << mysql_error(conn) << endl;
    }

    // a
    time_t t1,t2,t3,t4;

    time(&t1);

    if (mysql_query(conn, "create view income as(SELECT Author_Name, Book_Name, SUM(Copies) FROM Author_Details, Book_Details, Book_Purchase_Details WHERE Author_Details.Author_ID=Book_Details.Author_ID and Book_Details.Book_ID=Book_Purchase_Details.Book_ID GROUP BY Book_Name);")==0){
        time(&t2);
        if(mysql_query(conn, "SELECT * FROM income;")==0){
            display();
            cout << "Query a Answwered !" << endl;
    }
    }
    else{
        cout << " Error in answering query a !" << mysql_error(conn) << endl;
    }

    // b

    time(&t3);
    if(mysql_query(conn,"SELECT Author_Name, Book_Name, Copies FROM Author_Details, Book_Details, Book_Purchase_Details WHERE Author_Details.Author_ID=Book_Details.Author_ID and Book_Details.Book_ID=Book_Purchase_Details.Book_ID;")==0){
        time(&t4);
    }
    if(double(t2-t1)>double(t4-t3))
    cout << "SELECT IS FASTER THAN VIEW" << endl;
    else if(double(t2-t1)<double(t4-t3))
    cout << "SELECT IS SLOWER THAN VIEW" << endl;
    else
    cout << "Both take equal time" << endl;

    // c

    if (mysql_query(conn, "DELETE FROM Author_Details WHERE Author_ID='Ro_015';")==0){
        if(mysql_query(conn, "SELECT * FROM income;")==0){
            display();
            cout << "Query c answered !" << endl;
    }
    }
    if (mysql_query(conn, "INSERT INTO Author_Details VALUES('Su_1010','Susim');")==0){
        if(mysql_query(conn, "SELECT * FROM income;")==0){
            display();
            cout << "Query c Answered !" << endl;
    }
    }
    else{
        cout << " Error in answering query c !" << mysql_error(conn) << endl;
    }

    // d

    if (mysql_query(conn, "UPDATE income SET Author_Name='Susim' WHERE Book_Name='Emotion Machine';")==0){
        if(mysql_query(conn, "SELECT * FROM income;")==0){
            display();
            cout << "Query d Answwered !" << endl;
    }
    }
    else{
        cout << " Error in answering query d !" << mysql_error(conn) << endl;
    }

    // Different code file for 1(e)

    // f

    if (mysql_query(conn, "CREATE TRIGGER question ON income INSTEAD OF INSERT AS SET NOCOUNT ON INSERT INTO income ('Author_Name','Book_Name','SUM(Copies)') VALUES('Susim','Bio Myself','2');")==0){
        if(mysql_query(conn, "SELECT * FROM income;")==0){
            display();
            cout << "Query f Answwered !" << endl;
    }
    }
    else{
        cout << " Error in answering query f !" << mysql_error(conn) << endl;
    }

    // g 

    if (mysql_query(conn, "CREATE TRIGGER trRestrictAlterTable ON DATABASE FOR ALTER_TABLE AS PRINT 'YOU CANNOT ALTER THIS TABLE' ROLLBACK TRANSACTION;")==0){
            cout << "Query g Answwered !" << endl;
    }
    else{
        cout << " Error in answering query g !" << mysql_error(conn) << endl;
    }

    //Different code file for 1(h)

    //Different code file for 1(i)

    //j 

    

    return 0;

}