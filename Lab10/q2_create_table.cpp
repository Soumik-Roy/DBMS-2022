#include <iostream>
#include <windows.h>
#include <mysql.h>
#include <vector>
#include <string>

MYSQL *conn;

void createTable(string tableName, vector<string> colNames, vector<string> colType, string extras = "") {
    string command = "CREATE TABLE `" + tableName + "` (";

    for (int i = 0; i < colNames.size(); i++) {
        command += "`" + colNames[i] + "` " + colType[i];
        if (i != colNames.size() - 1) {
            command += ", ";
        }
        else {
            if (extras != "")
                command = command + ", " + extras;
            command += ");";
        }
    }

    char query[1000];
    snprintf(query, 1000, command.c_str());

    int createTableStatus = mysql_query(conn, query);
    if (createTableStatus != 0) {
        cout << "Error while creating " << tableName << " table: " << mysql_error(conn) << endl;
    }
}

void insertValue(string tableName, vector<string> columnNames, vector<string> values) {
    string command = "INSERT INTO " + tableName;

    if (columnNames.size() == values.size()) {
        command += +" ( ";
        for (int i = 0; i < columnNames.size(); i++) {
            command += "`" + columnNames[i] + "`";
            if (i == columnNames.size() - 1) {
                command += ") ";
            }
            else {
                command += ",";
            }
        }
    }

    command += " VALUES ( ";

    for (int i = 0; i < values.size(); i++) {
        command += "'" + values[i] + "'";
        if (i == values.size() - 1) {
            command += ");";
        }
        else {
            command += ", ";
        }
    }

    char query[1000];
    snprintf(query, 1000, command.c_str());

    int insertValStatus = mysql_query(conn, query);
    if (insertValStatus != 0) {
        cout << "Error while inserting row. " << mysql_error(conn) << endl;
    }
}

int main() {
    conn = mysql_init(NULL);

    if (conn == NULL) {
        cout << "Error: " << mysql_error(conn) << endl;
        exit(1);
    }

    if (mysql_real_connect(conn, "localhost", "group50_dbms", "password", "dbms_lab10", 3306, NULL, 0)) {
        cout << "Connected Successfully!" << endl;

        // APPLICATION Table
        vector<string> Application_Columns = {"SID", "Date", "State"};
        vector<string> Application_Columns_Type = {"int NOT NULL PRIMARY KEY", "text", "varchar(255)"};

        string tableName1 = "APPLICATION";
        createTable(tableName1, Application_Columns, Application_Columns_Type);

        vector<string> table1_fields = {"SID", "Date", "State"};

        insertValue(tableName1, table1_fields, {'1', '12.05.21', NULL});
        insertValue(tableName1, table1_fields, {'2', '11.05.21', NULL});
        insertValue(tableName1, table1_fields, {'3', '10.05.21', NULL});
        insertValue(tableName1, table1_fields, {'4', '10.05.21', NULL});
        insertValue(tableName1, table1_fields, {'5', '11.05.21', NULL});

        // COURSE Table
        vector<string> Course_Columns = {"CID", "Title", "Credits"};
        vector<string> Course_Columns_Type = {"int NOT NULL PRIMARY KEY", "varchar(255)", "int"};

        string tableName2 = "COURSE";
        createTable(tableName2, Course_Columns, Course_Columns_Type);

        vector<string> table2_fields = {"CID", "Title", "Credits"};

        insertValue(tableName2, table2_fields, {'2010', 'Networks', '4'});
        insertValue(tableName2, table2_fields, {'3010', 'Architecture', '5'});
        insertValue(tableName2, table2_fields, {'4010', 'Systems', '4'});
        insertValue(tableName2, table2_fields, {'2020', 'Database', '5'});
        insertValue(tableName2, table2_fields, {'3020', 'Intelligence', '4'});
        insertValue(tableName2, table2_fields, {'4020', 'Automation', '6'});

        // RANK Table
        vector<string> Rank_Columns = {"SID", "Avg", "Credits", "Rank"};
        vector<string> Rank_Columns_Type = {"int NOT NULL PRIMARY KEY", "int", "int", "int"};

        string tableName3 = "RANK";
        createTable(tableName3, Rank_Columns, Rank_Columns_Type);

        vector<string> table3_fields = {"SID", "Avg", "Credits", "Rank"};

        insertValue(tableName3, table3_fields, {'1', '21', '46', NULL});
        insertValue(tableName3, table3_fields, {'2', '28', '49', NULL});
        insertValue(tableName3, table3_fields, {'3', '26', '40', NULL});
        insertValue(tableName3, table3_fields, {'4', '27', '46', NULL});
        insertValue(tableName3, table3_fields, {'5', '28', '47', NULL});

        // EXAM Table
        vector<string> Exam_Columns = {"CID", "SID", "Date", "Grade"};
        vector<string> Exam_Columns_Type = {"int NOT NULL", "int NOT NULL", "text", "varchar(255)"};

        string tableName4 = "EXAM";
        createTable(tableName4, Exam_Columns, Exam_Columns_Type, "PRIMARY KEY (CID, SID)");

        vector<string> table4_fields = {"CID", "SID", "Date", "Grade"};

        insertValue(tableName4, table4_fields, {'2010', '1', '24.07.20', 'B'});
        insertValue(tableName4, table4_fields, {'3010', '2', '26.07.20', 'A'});
        insertValue(tableName4, table4_fields, {'4010', '3', '30.07.20', 'C'});
        insertValue(tableName4, table4_fields, {'2020', '4', '20.07.20', 'B'});
        insertValue(tableName4, table4_fields, {'3020', '5', '22.07.20', 'A'});
        insertValue(tableName4, table4_fields, {'4020', '3', '25.07.20', 'B'});

    }
    else {
        cout << "Error while connecting! : " << mysql_error(conn) << endl;
    }

    return 0;
}