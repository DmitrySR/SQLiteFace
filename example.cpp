#include <iostream>
#include <string>
#include "SQLiteFace.h"
using namespace std;
int main() {
	string sql;//example query
	string name, surname, email, phone;
	cin >> name;
	cin >> surname;
	cin >> email;
	cin >> phone;

	Database DB1; //default constructor. dbname = data.db, table_name = tab
	DB1.open();//creates or opens table with dbname = data.db, table_name = tab
	sql = "INSERT INTO " + DB1.get_table_name() + " (name, surname,email,phone)\
			 VALUES('" + name + "','" + surname + "','" + email + "','" + phone + "');";
	DB1.exec(sql);
	DB1.exec_select();//shows full table by default
	DB1.close();

	string table_name = "newtab", dbname = "newdb.db"; //always add .db extention
	Database DB2(dbname.c_str(), table_name); //constructor with setted name. use c_str() with dbname
	DB2.open(DB2.get_table_name(),DB2.get_dbname());
	sql = "INSERT INTO " + DB2.get_table_name() + " (name, surname,email,phone)\
			 VALUES('" + name + "','" + surname + "','" + email + "','" + phone + "');";
	DB2.exec(sql);
	sql = "SELECT * FROM " + DB2.get_table_name() + ";";
	DB2.exec_select(sql);
	DB2.close();

	return 0;
}