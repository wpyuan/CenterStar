#include "StdAfx.h"
#include "Inventory.h"


Inventory::Inventory(void)
{
}


Inventory::~Inventory(void)
{
}

bool Inventory::add(Inventory inventory)
{
	CString sql=NULL;
	CString goodsID;
	CString rK,cK,kC;
	goodsID.Format("%d",inventory.goodsId);
	rK.Format("%.2f",inventory.rk);
	cK.Format("%.2f",inventory.ck);
	kC.Format("%.2f",inventory.kc);
	sql.Format("INSERT INTO tally.inventory value(null, %s, %s, %s, %s, '%s', now())", goodsID,rK,cK,kC,inventory.remark);	

	if(  mysql_query(&m_sqlCons, sql)==0 )
	{
		sql.Format("SELECT * FROM tally.inventory where I_time=now();");
		//执行查询
		MYSQL_RES *m_result;
		mysql_query(&m_sqlCons,sql);
		m_result=mysql_use_result(&m_sqlCons);
		MYSQL_ROW row;
		while((row=mysql_fetch_row(m_result)))
			h_Itime=row[6];
		
		mysql_free_result(m_result); //关联的内存会释放
		return true;
	}
	else
		return false;
}
Inventory Inventory::searchAuto(Inventory inventory,CString I_time)
{
	CString sql;
	sql.Format("SELECT * FROM tally.inventory where I_time='%s';",I_time);
	//执行查询
	MYSQL_RES *m_result;
	mysql_query(&m_sqlCons,sql);
	m_result=mysql_use_result(&m_sqlCons);
	int i=0;
	MYSQL_ROW row;
	CString ID,gID,RK,CK,KC;
	while((row=mysql_fetch_row(m_result)))
	{
		ID=row[0];
		inventory.id=atof(ID);
		gID=row[1];
		inventory.goodsId=atof(gID);
		RK=row[2];
		inventory.rk=atof(RK);
		CK=row[3];
		inventory.ck=atof(CK);
		KC=row[4];
		inventory.kc=atof(KC);
		inventory.remark=row[5];
		inventory.time=row[6];
		i++;
	}
	mysql_free_result(m_result); //关联的内存会释放
	return inventory;
}
void Inventory::selectKcIndex()
{
	delete[kcdtNum] kcindex;
	kcdtNum=0;
	CString sql;
	sql.Format("SELECT * FROM tally.inventory order by I_time asc;");
	//执行查询
	MYSQL_RES *m_result;
	mysql_query(&m_sqlCons,sql);
	m_result=mysql_use_result(&m_sqlCons);
	int i=0;
	MYSQL_ROW row;
	while((row=mysql_fetch_row(m_result)))
		kcdtNum++;
	mysql_free_result(m_result); //关联的内存会释放
	kcindex=new Inventory[kcdtNum];

	mysql_query(&m_sqlCons,sql);
	m_result=mysql_use_result(&m_sqlCons);
	CString ID,gID,RK,CK,KC;
	while((row=mysql_fetch_row(m_result)))
	{
		ID=row[0];
		kcindex[i].id=atof(ID);
		gID=row[1];
		kcindex[i].goodsId=atof(gID);
		RK=row[2];
		kcindex[i].rk=atof(RK);
		CK=row[3];
		kcindex[i].ck=atof(CK);
		KC=row[4];
		kcindex[i].kc=atof(KC);
		kcindex[i].remark=row[5];
		kcindex[i].time=row[6];
		i++;
	}
	mysql_free_result(m_result); //关联的内存会释放
}
void Inventory::selectSql(CString sql)
{
	delete[kcdtNum] kcindex;
	kcdtNum=0;
	//执行查询
	MYSQL_RES *m_result;
	mysql_query(&m_sqlCons,sql);
	m_result=mysql_use_result(&m_sqlCons);
	int i=0;
	MYSQL_ROW row;
	while((row=mysql_fetch_row(m_result)))
		kcdtNum++;
	mysql_free_result(m_result); //关联的内存会释放
	kcindex=new Inventory[kcdtNum];

	mysql_query(&m_sqlCons,sql);
	m_result=mysql_use_result(&m_sqlCons);
	CString ID,gID,RK,CK,KC;
	while((row=mysql_fetch_row(m_result)))
	{
		ID=row[0];
		kcindex[i].id=atof(ID);
		gID=row[1];
		kcindex[i].goodsId=atof(gID);
		RK=row[2];
		kcindex[i].rk=atof(RK);
		CK=row[3];
		kcindex[i].ck=atof(CK);
		KC=row[4];
		kcindex[i].kc=atof(KC);
		kcindex[i].remark=row[5];
		kcindex[i].time=row[6];
		i++;
	}
	mysql_free_result(m_result); //关联的内存会释放
}
bool Inventory::update(CString sql)
{
	if(  mysql_query(&m_sqlCons, sql)==0 )
	{
		return true;
	}
	else{
		return false;
	}
}
bool Inventory::delet(CString sql)
{
	if( mysql_query(&m_sqlCons,sql)==0 )
	{
		return true;
	}else{
		return false;
	}
}