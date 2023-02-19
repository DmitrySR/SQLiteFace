#pragma once
#include <string>
#include <iostream>
#include "sqlite3.h"

using namespace std;
class Database {
	sqlite3* db = 0; 
	char* err = 0;
	const char* DBname=0;
	const char* unused = 0;
	string Table_name ;
	const char* SQL = 0;
	static int callback(void* unused, int argc, char** argv, char** azColName) {
		int i;
		for (i = 0; i < argc; i++) {
			printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
		}
		printf("\n");
		return 0;
	}
public:
	Database() {
		Table_name = "tab";
		DBname = "data.db";
	}

	Database(const char* dbname, string table_name) {
		DBname = dbname;
		Table_name = table_name;
	}
	string get_table_name() {
		return Table_name;
	}
	void set_table_name(string table_name) {
		Table_name = table_name;
	}
	const char* get_dbname() {
		return DBname;
	}
	
	void open(string table_name="tab", const char* dbname = "data.db") { //create or open DB and tab"
		string sqls = "CREATE TABLE IF NOT EXISTS " + table_name + "\
		 (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, \
		name TEXT NOT NULL, surname INTEGER NOT NULL, \ \
		email TEXT NOT NULL,phone TEXT NOT NULL);";  // example query
		SQL = sqls.c_str();
		
		int rc = sqlite3_open(dbname, &db);
		if (rc) cout << "Can't open/create datase " << sqlite3_errmsg(db);
		else if (sqlite3_exec(db, SQL, 0, 0, &err))
		{
			cout << "Wrong SQL-query: " << err;
			sqlite3_free(err);
		}

	}

	void exec(string sqls) { //execute any sql-query
		SQL = sqls.c_str();
		if (sqlite3_exec(db, SQL, 0, 0, &err))
		{
			cout << "Wrong SQL-query: " << err;
			sqlite3_free(err);
		}
	}

	void exec_select(string sqls = "SELECT * FROM tab;") { //execute for SELECT query. 
		//this function uses callback function to print data in console
		
		SQL = sqls.c_str();
		int rc = sqlite3_exec(db, SQL, callback, (void*)unused, &err);
		if (rc != SQLITE_OK) {
			fprintf(stderr, "SQL error: %s\n", err);
			sqlite3_free(err);
		}
	}
	
	void close() {
		sqlite3_close(db);
	}
};

