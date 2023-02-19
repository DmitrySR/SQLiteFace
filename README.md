# **SQLiteFace**
### *Interface for easier interaction with SQLite.* 

**How to use**

1. Include SQLiteFace.h in project

2. Create variable of Database type

3. Use methods from list of methods to interact with database. Also check the example.cpp

4. Enjoy!

---
**List of methods**

- DB.open() - create/open database
- DB.exec() - execute any sql-query
- DB.exec_select() - execute for SELECT query. This function uses callback function to print data in console