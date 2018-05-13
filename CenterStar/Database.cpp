#include "StdAfx.h"
#include "Database.h"



Database::Database(void)
{
    FILE * fp = fopen("databaseSetup.txt", "r");//打开exe同级数据库配置文件
	char ip[100],account[100],password[100],name[100],port[100];//定义接受文件数据的字符数组，长度100
	CString PORT;//为下面int 型数据处理数据用
	fscanf(fp, " %s %s %s %s %s", ip, account, password,name,port);//接受文件数据
    fclose(fp);//关闭文件
	        //char-->CString
	Database::ip.Format("%s",ip);
	Database::SQL_account.Format("%s",account);
	Database::SQL_password.Format("%s",password);
	Database::SQL_name.Format("%s",name);
	PORT.Format("%s",port);
	        //法1：删除指定长度字符
    Database::ip.Delete(0,3);
	Database::SQL_account.Delete(0,12);
	Database::SQL_password.Delete(0,13);
	Database::SQL_name.Delete(0,9);
	PORT.Delete(0,5);
	Database::port=atoi(PORT);


	//法2：去掉指定字符
	/*s.Remove('i');
	s.Remove('p');
	s.Remove(':');*/
	//测试：数据库连接
	//Database::ip="localhost";
	//Database::SQL_account="root";
	//Database::SQL_password="123";
	//Database::SQL_name="tally";
	//Database::port=3307;

	mysql_init(&m_sqlCons);
	if(!mysql_real_connect(&m_sqlCons,database.ip,database.SQL_account,database.SQL_password,database.SQL_name,database.port,NULL,0))
	{
		MessageBox(NULL,_T("访问数据库失败!"),"系统提示",NULL);
		CString e=mysql_error(&m_sqlCons);//需要将项目属性中字符集修改为“使用多字节字符集”或“未设置”
		MessageBox(NULL,e,"错误",NULL);
	}else{
		//MessageBox(NULL,"连接数据库成功","系统提示",NULL);
		mysql_query(&m_sqlCons,"set names gbk;");//解决录入信息到数据库中后汉字乱码显示的问题
	}
}


Database::~Database(void)
{
}
bool Database::linkSql(Database database)
{
	
	mysql_init(&m_sqlCons);
	if(!mysql_real_connect(&m_sqlCons,database.ip,database.SQL_account,database.SQL_password,database.SQL_name,database.port,NULL,0))
	{
		MessageBox(NULL,_T("访问数据库失败!"),"系统提示",NULL);
		CString e=mysql_error(&m_sqlCons);//需要将项目属性中字符集修改为“使用多字节字符集”或“未设置”
		MessageBox(NULL,e,"错误",NULL);
		return false;
	}else{
		//MessageBox(NULL,"连接数据库成功","系统提示",NULL);
		mysql_query(&m_sqlCons,"set names gbk;");//解决录入信息到数据库中后汉字乱码显示的问题
	    return true;
	}
}
void Database::CloseMySQLConn()
{
	
	 mysql_close(&m_sqlCons);
}