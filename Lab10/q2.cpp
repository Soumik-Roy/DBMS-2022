#include <iostream>
#include <windows.h>
#include <mysql.h>

using namespace std;

MYSQL *conn;

int main() {
    conn = mysql_init(NULL);
    if (conn == NULL) {
        cout<<"Error: "<<mysql_error(conn)<<endl;
        exit(1);
    }

    // mysql_real_connect(Connection Instance, Host, Username, Password, Database, Port, Unix Socket, Client Flag)
    if (mysql_real_connect(conn, "localhost", "group50_dbms", "password", "dbms_lab2_3", 3306, NULL, 0)) {
        cout<<"Connected Successfully!"<<endl; 

        // a
        if (mysql_query(conn, 
            "Create trigger Checker after insert on APPLICATION for each row declare M,C "
            "number: M:=(select avg(Grade) from EXAM where StudentID=new.StudentID and Date<=new.Date) "
            "C:=(select sum( Credits ) from  EXAM JOIN COURSE ON EXAM.CourseID = COURSE.CourseID "
            "where StudentID = new.StudentID and Date <= new.Date) if (M >= 25 and C >= 45)  "
            "then  (  update APPLICATION set State='accepted' where StudentID = new.StudentID; "
            "insert into RANKING values ( new.StudentID, M, C, NULL );) else update APPLICATION "
            "set State='rejected' where StudentID = new.StudentID;") == 0
            ) {
            cout << "Trigger a created successfully !" << endl;
        }
        else {
            cout << "Trigger a failed !!" << mysql_error(conn) << endl;
        }

        // b
        if (mysql_query(conn, 
            "Create trigger rank update after insert on RANKING for each row begin "
            "POS:=select count(*) from RANKING where(Average>new.Average) "
            "OR (Average=new.Average AND Credits>new.Credits) "
            "OR (Average = new.Average AND Credits = new.Credits);") == 0
            ) {
            if (mysql_query(conn, 
                "update RANKING set Rank=Rank+1 where Rank > POS;") == 0
                ) {
                if (mysql_query(conn, 
                    "update RANKING set Rank=POS+1 where StudentID=new.StudentID;") == 0
                    ) {
                    if (mysql_query(conn, 
                        "Create trigger rank2 after delete from RANKING for each row update RANKING "
                        "set Rank=Rank-1 where Rank>old.Rank;")
                        ) {
                        cout << "Trigger b created successfully !" << endl;
                    }
                }
            }
        }
        else {
            cout << "Trigger b failed !!" << mysql_error(conn) << endl;
        }
    }
    else {
        cout << "Error while connecting! : " << mysql_error(conn) << endl;
    }

    return 0;
}
