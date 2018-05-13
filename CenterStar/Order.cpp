#include "StdAfx.h"
#include "Order.h"


Order::Order(void)
{
}


Order::~Order(void)
{
}

bool Order::add()
{
	CString sql=NULL;
	CString goodsid,customerid,num,pro;
	goodsid.Format("%d",goodsId);
	customerid.Format("%d",customerId);
	num.Format("%.2f",number);
	pro.Format("%.2f",profit);
	sql.Format("INSERT INTO tally.orders value(null, now(), %s, %s ,%s,'%s',%s)",goodsid,customerid,num,remark,pro );	
	if(  mysql_query(&m_sqlCons, sql)==0 )
		return true;
	else
		return false;
}

Order Order::select(Order order,CString sql)
{
	//执行查询
	MYSQL_RES *m_result;
	mysql_query(&m_sqlCons,sql);
	m_result=mysql_use_result(&m_sqlCons);
	MYSQL_ROW row;
	while((row=mysql_fetch_row(m_result)))
	{
		order.id=atoi(row[0]);
		order.time=row[1];
		order.goodsId=atoi(row[2]);
		order.customerId=atoi(row[3]);
		order.remark=row[4];
		order.profit=atof(row[5]);
	}
	mysql_free_result(m_result); //关联的内存会释放
	return order;
}
bool Order::delet(CString sql)
{
	if( mysql_query(&m_sqlCons,sql)==0 )
	{
		return true;
	}else{
		return false;
	}
}