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
    if (mysql_real_connect(conn, "localhost", "group50_dbms", "password", "dbms_lab10", 3306, NULL, 0)) {
        cout<<"Connected Successfully!"<<endl; 

        // a
        if (mysql_query(conn, 
            "create trigger checker after insert on APPLICATION for each row begin declare M integer; declare C integer; set @M:=(select avg(Grade) from EXAM where SID=new.SID and Date<=new.Date); set @C:=(select sum( Credits ) from  EXAM JOIN COURSE ON EXAM.CourseID = COURSE.CourseID where SID = new.SID and Date <= new.Date); if (M >= 25 and C >= 45)  then update APPLICATION set State='accepted' where SID = new.SID; insert into RANKING values ( new.SID, M, C, NULL ); else update APPLICATION set State='rejected' where SID = new.SID; end if; end") == 0
            ) {
            cout << "Trigger a created successfully !" << endl;
        }
        else {
            cout << "Trigger a failed !!" << mysql_error(conn) << endl;
        }

         // b

        if (mysql_query(conn, "Create trigger rank after insert on RANK for each row begin declare POS integer; set @POS:=(select count(*) from RANKING where (Avg>new.Avg OR (Avg=new.Avg AND Credits>new.Credits) OR (Avg = new.Avg AND Credits = new.Credits))); update RANK set Rank=Rank+1 where Rank > POS; update RANK set Rank=POS+1 where SID=new.SID; end;") == 0) {
            cout << "Trigger B1 created successfully!" << endl;
        }
        else {
            cout << "Trigger B failed: " << mysql_error(conn) << endl;
        }

        if (mysql_query(conn, "Create trigger rank2 after delete from RANK for each row update RANK set Rank=Rank-1 where Rank>old.Rank;")) {
            cout << "Trigger B2 created successfully!" << endl;
        }
        else {
            cout << "Trigger B2 failed: " << mysql_error(conn) << endl;
        }
    }
    else {
        cout << "Error while connecting! : " << mysql_error(conn) << endl;
    }

    return 0;
}
