#include "StdAfx.h"
#include "Customer.h"

Customer::Customer(void)
{
}


Customer::~Customer(void)
{
}

bool Customer::add(Customer customer)
{
	CString sql=NULL;
	sql.Format("INSERT INTO tally.customer value(null, '%s', '%s', '%s' ,'%s')",customer.name,customer.phone,customer.address,customer.logistics );	
	if(  mysql_query(&m_sqlCons, sql)==0 )
		return true;
	else
		return false;
}
Customer Customer::select(Customer customer,CString sql)
{
	//执行查询
	MYSQL_RES *m_result;
	mysql_query(&m_sqlCons,sql);
	m_result=mysql_use_result(&m_sqlCons);
	MYSQL_ROW row;
	CString ID;
	while((row=mysql_fetch_row(m_result)))
	{
		ID=row[0];
		customer.id=atoi(ID);
		customer.name=row[1];
		customer.phone=row[2];
		customer.address=row[3];
		customer.logistics=row[4];
	}
	mysql_free_result(m_result); //关联的内存会释放
	return customer;
}
bool Customer::delet(CString ID)
{
	CString sql;
	sql.Format("DELETE FROM tally.customer where C_id=%s",ID);
	if( mysql_query(&m_sqlCons,sql)==0 )
	{
		return true;
	}else{
		return false;
	}
}
bool Customer::update(CString sql)
{
	if(  mysql_query(&m_sqlCons, sql)==0 )
	{
		return true;
	}
	else{
		return false;
	}
}
Customer Customer::selectId(Customer customer)
{
	CString sql=NULL;
	CString strId;
	if(customer.id!=0)
	{
		strId.Format("%d",customer.id);
		sql.Format("SELECT * FROM tally.customer where C_id=%s;",strId);
		//执行查询
		MYSQL_RES *m_result;
		mysql_query(&m_sqlCons,sql);
		m_result=mysql_use_result(&m_sqlCons);
		MYSQL_ROW row;
		CString ID;
		if((row=mysql_fetch_row(m_result)))
		{
			ID=row[0];
			customer.id=atoi(ID);
			customer.name=row[1];
			customer.phone=row[2];
			customer.address=row[3];
			customer.logistics=row[4];
		}	
		mysql_free_result(m_result); //关联的内存会释放
	}
	return customer;
}