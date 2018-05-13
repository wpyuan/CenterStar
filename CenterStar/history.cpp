#include "StdAfx.h"
#include "history.h"


history::history(void)
{
}


history::~history(void)
{
}

bool history::add()
{
	CString sql=NULL;
	CString id;
	id.Format("%d",tableId);
	sql.Format("INSERT INTO tally.history value(null, now(), '%s', '%s' ,%s)",content,table,id );	
	if(  mysql_query(&m_sqlCons, sql)==0 )
		return true;
	else
		return false;
}
void history::search(CString sql)
{
	delete[kclsNum] kchistory;
	kclsNum=0;
	//执行查询
	MYSQL_RES *m_result;
	mysql_query(&m_sqlCons,sql);
	m_result=mysql_use_result(&m_sqlCons);
	int i=0;
	MYSQL_ROW row;
	while((row=mysql_fetch_row(m_result)))
		kclsNum++;
	mysql_free_result(m_result); //关联的内存会释放
	kchistory=new history[kclsNum];

	mysql_query(&m_sqlCons,sql);
	m_result=mysql_use_result(&m_sqlCons);
	CString ID,tableID;
	while((row=mysql_fetch_row(m_result)))
	{
		ID=row[0];
		kchistory[i].id=atof(ID);
		kchistory[i].time=row[1];
		kchistory[i].content=row[2];
		kchistory[i].table=row[3];
		tableID=row[4];
		kchistory[i].tableId=atof(tableID);
		i++;
	}
	mysql_free_result(m_result); //关联的内存会释放
}