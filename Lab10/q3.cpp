#include <iostream>
#include <windows.h>
#include <mysql.h>

using namespace std;

MYSQL *conn;


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

    char tableName1[512] = "Student";
    char query1[512];
    snprintf(query1, 512, "CREATE TABLE `%s` (`ID` int, `name` text, `class` int);", tableName1);
    int createTableStatus1 = mysql_query(conn, query1);

    char tableName2[512] = "Friend";
    char query2[512];
    snprintf(query2, 512, "CREATE TABLE `%s` (`ID1` int, `ID2` int);", tableName2);
    int createTableStatus2 = mysql_query(conn, query2);

    if(createTableStatus1 != 0 && createTableStatus2 != 0){
        cout << "Error in creating table" << mysql_error(conn) << endl;
    }
    else{
        cout << "All tables created successfully" << mysql_error(conn) << endl;
    }

    char query3[512];
    snprintf(query3, 512, "INSERT INTO `%s` VALUES ('1','Susim','10'),('2','Chucho','10'),('3','Osik','11'),('4','Zoeham','9'),('5','Dpu','8');", tableName1);
    int studentInsertionStatus1 = mysql_query(conn, query3);
    if (studentInsertionStatus1 != 0){
        cout << "Error while inserting in table1: " << mysql_error(conn) << endl;
    }

    char query4[512];
    snprintf(query4, 512, "INSERT INTO `%s` VALUES ('1','2'),('1','3'),('1','4'),('1','5'),('2','3'),('4','5'),('3','4'),('3','5');", tableName2);
    int studentInsertionStatus2 = mysql_query(conn, query4);
    if (studentInsertionStatus2 != 0){
        cout << "Error while inserting in table2: " << mysql_error(conn) << endl;
    }

    //a

    if(mysql_query(conn, "CREATE TRIGGER F1_DEL AFTER DELETE ON Friend FOR EACH ROW WHEN exists (SELECT * FROM Friend WHERE ID1=Old.ID2 and ID2=Old.ID1) BEGIN DELETE FROM Friend WHERE(ID1=Old.ID2 and ID2=Old.ID1);END")==0)
    cout << "Trigger a created successfully !" << endl;
    else
    cout << "Trigger failed !!" << mysql_error(conn) << endl;

    //b 

    if(mysql_query(conn, "create trigger graduation after update of grade on Student for each row when new.grade>12 begin delete from Student where ID=New.ID;end")==0)
    cout << "Trigger b created successfully !" << endl;
    else
    cout << "Trigger failed !!" << mysql_error(conn) << endl;

    //c

    if(mysql_query(conn, "create trigger upgrade after update of grade on Student for each row when new.grade=old.grade+1 begin update Student set grade=grade+1 where ID in(select ID2 from Friend where ID1=New.ID);end")==0)
    cout << "Trigger c created successfully !" << endl;
    else
    cout << "Trigger failed !!" << mysql_error(conn) << endl;

    return 0;
}