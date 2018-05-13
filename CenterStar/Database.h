#pragma once
class Database
{
public:
	
	CString ip;
	CString SQL_account;
	CString SQL_password;
	CString SQL_name;
	int port;
	bool linkSql(Database database);//连接数据库
	void CloseMySQLConn();
	Database(void);
	~Database(void);
};

