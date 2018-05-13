#include "StdAfx.h"
#include "Product.h"

Product::Product(void)
{
}


Product::~Product(void)
{
}
bool Product::add()
{
	CString sql=NULL;
	CString dj,KC;
	dj.Format("%.2f",price);
	KC.Format("%.2f",kc);
	image.Replace(92, '/');
	sql.Format("INSERT INTO tally.goods value(null, '%s', %s, '%s', %s, '%s', '%s')", name,dj,unit,KC,image,content );	
	
	if(  mysql_query(&m_sqlCons, sql)==0 )
		return true;
	else
		return false;
}
Product Product::select(Product p)
{
	CString sql=NULL;
	sql.Format("SELECT * FROM tally.goods where G_name='%s' ;",name);
	//执行查询
	MYSQL_RES *m_result;
	mysql_query(&m_sqlCons,sql);
	m_result=mysql_use_result(&m_sqlCons);
	int i=0;
	MYSQL_ROW row;
	if((row=mysql_fetch_row(m_result)))
	{
		CString ID;
		CString PrICE;
		CString Kc;
		//获取数据
		ID=row[0];
		p.name=row[1];
		PrICE=row[2];
		p.unit=row[3];
		Kc=row[4];
		p.image=row[5];
		p.content=row[6];
		p.id=atoi(ID);
		p.price=atof(PrICE);
		p.kc=atof(Kc);
	}	
	mysql_free_result(m_result); //关联的内存会释放
	return p;
}
Product Product::selectId(Product p)
{
	CString sql=NULL;
	CString strId;
	if(p.id!=0)
	{
		strId.Format("%d",p.id);
		sql.Format("SELECT * FROM tally.goods where G_id=%s ;",strId);
		//执行查询
		MYSQL_RES *m_result;
		mysql_query(&m_sqlCons,sql);
		m_result=mysql_use_result(&m_sqlCons);
		int i=0;
		MYSQL_ROW row;
		if((row=mysql_fetch_row(m_result)))
		{
			CString ID;
			CString PrICE;
			CString Kc;
			//获取数据
			ID=row[0];
			p.name=row[1];
			PrICE=row[2];
			p.unit=row[3];
			Kc=row[4];
			p.image=row[5];
			p.content=row[6];
			p.id=atoi(ID);
			p.price=atof(PrICE);
			p.kc=atof(Kc);
		}	
		mysql_free_result(m_result); //关联的内存会释放
	}
	return p;
}
void Product::selectIndex()
{
	CString sql=NULL;
	indexNum=0;
	sql.Format("SELECT * FROM tally.goods where G_kc<2 order by G_kc ASC;");
	//执行查询
	MYSQL_RES *m_result;
	mysql_query(&m_sqlCons,sql);
	m_result=mysql_use_result(&m_sqlCons);
	int i=0;
	MYSQL_ROW row;
	//获取对象数组大小
	while((row=mysql_fetch_row(m_result)))
		indexNum++;	

	pindex=new Product[indexNum];//动态分配数组

	mysql_free_result(m_result); //关联的内存会释放
	
	mysql_query(&m_sqlCons,sql);
	m_result=mysql_use_result(&m_sqlCons);
	while((row=mysql_fetch_row(m_result)))
	{
		CString ID;
		CString PrICE;
		CString Kc;
		//获取数据
		ID=row[0];
		pindex[i].name=row[1];
		PrICE=row[2];
		pindex[i].unit=row[3];
		Kc=row[4];
		pindex[i].image=row[5];
		pindex[i].content=row[6];

		pindex[i].id=atoi(ID);
		pindex[i].price=atof(PrICE);
		pindex[i].kc=atof(Kc);

		i++;
	}
	mysql_free_result(m_result); //关联的内存会释放
	return ;
}
void Product::selectInfor()
{
	delete[infoNum] pinfo;
	CString sql=NULL;
	infoNum=0;
	sql.Format("SELECT * FROM tally.goods order by G_id DESC;");
	//执行查询
	MYSQL_RES *m_result;
	mysql_query(&m_sqlCons,sql);
	m_result=mysql_use_result(&m_sqlCons);
	int i=0;
	MYSQL_ROW row;
	//获取对象数组大小
	while((row=mysql_fetch_row(m_result)))
		infoNum++;	

	pinfo=new Product[infoNum];//动态分配数组

	mysql_free_result(m_result); //关联的内存会释放
	
	mysql_query(&m_sqlCons,sql);
	m_result=mysql_use_result(&m_sqlCons);
	while((row=mysql_fetch_row(m_result)))
	{
		CString ID;
		CString PrICE;
		CString Kc;
		//获取数据
		ID=row[0];
		pinfo[i].name=row[1];
		PrICE=row[2];
		pinfo[i].unit=row[3];
		Kc=row[4];
		pinfo[i].image=row[5];
		pinfo[i].content=row[6];

		pinfo[i].id=atoi(ID);
		pinfo[i].price=atof(PrICE);
		pinfo[i].kc=atof(Kc);

		i++;
	}
	mysql_free_result(m_result); //关联的内存会释放
	return ;
}
void Product::selectText(CString name)
{
	delete[infoNum] pinfo;
	CString sql=NULL;
	infoNum=0;
	sql.Format("SELECT * FROM tally.goods where G_name like '%s%s%s' order by G_id DESC;","%",name,"%");
	//执行查询
	MYSQL_RES *m_result;
	mysql_query(&m_sqlCons,sql);
	m_result=mysql_use_result(&m_sqlCons);
	int i=0;
	MYSQL_ROW row;
	//获取对象数组大小
	while((row=mysql_fetch_row(m_result)))
		infoNum++;	

	pinfo=new Product[infoNum];//动态分配数组

	mysql_free_result(m_result); //关联的内存会释放
	
	mysql_query(&m_sqlCons,sql);
	m_result=mysql_use_result(&m_sqlCons);
	while((row=mysql_fetch_row(m_result)))
	{
		CString ID;
		CString PrICE;
		CString Kc;
		//获取数据
		ID=row[0];
		pinfo[i].name=row[1];
		PrICE=row[2];
		pinfo[i].unit=row[3];
		Kc=row[4];
		pinfo[i].image=row[5];
		pinfo[i].content=row[6];

		pinfo[i].id=atoi(ID);
		pinfo[i].price=atof(PrICE);
		pinfo[i].kc=atof(Kc);

		i++;
	}
	mysql_free_result(m_result); //关联的内存会释放
	return ;
}
void Product::selectContent(CString content)
{
	delete[infoNum] pinfo;
	CString sql=NULL;
	infoNum=0;
	sql.Format("SELECT * FROM tally.goods where G_content like '%s%s%s' order by G_id DESC;","%",content,"%");
	//执行查询
	MYSQL_RES *m_result;
	mysql_query(&m_sqlCons,sql);
	m_result=mysql_use_result(&m_sqlCons);
	int i=0;
	MYSQL_ROW row;
	//获取对象数组大小
	while((row=mysql_fetch_row(m_result)))
		infoNum++;	

	pinfo=new Product[infoNum];//动态分配数组

	mysql_free_result(m_result); //关联的内存会释放
	
	mysql_query(&m_sqlCons,sql);
	m_result=mysql_use_result(&m_sqlCons);
	while((row=mysql_fetch_row(m_result)))
	{
		CString ID;
		CString PrICE;
		CString Kc;
		//获取数据
		ID=row[0];
		pinfo[i].name=row[1];
		PrICE=row[2];
		pinfo[i].unit=row[3];
		Kc=row[4];
		pinfo[i].image=row[5];
		pinfo[i].content=row[6];

		pinfo[i].id=atoi(ID);
		pinfo[i].price=atof(PrICE);
		pinfo[i].kc=atof(Kc);

		i++;
	}
	mysql_free_result(m_result); //关联的内存会释放
	return ;
}
bool Product::update(CString name,CString id)
{
	CString sql=NULL;
	sql.Format("update tally.goods set G_name='%s' where G_id=%s", name,id);
	/*AfxMessageBox(sql);*/
	if(  mysql_query(&m_sqlCons, sql)==0 )
	{
		return true;
	}
	else{
		return false;
	}
}
bool Product::updatePrcie(CString price,CString id)
{
	CString sql=NULL;
	sql.Format("update tally.goods set G_price=%s where G_id=%s", price,id);
	if(  mysql_query(&m_sqlCons, sql)==0 )
	{
		return true;
	}
	else{
		return false;
	}
}
bool Product::updateKc(CString kc,CString id)
{
	CString sql=NULL;
	sql.Format("update tally.goods set G_kc=%s where G_id=%s", kc,id);
	if(  mysql_query(&m_sqlCons, sql)==0 )
	{
		return true;
	}
	else{
		return false;
	}
}
bool Product::updateUnit(CString unit,CString id)
{
	CString sql=NULL;
	sql.Format("update tally.goods set G_unit='%s' where G_id=%s", unit,id);
	if(  mysql_query(&m_sqlCons, sql)==0 )
	{
		return true;
	}
	else{
		return false;
	}
}
bool Product::updateContent(CString content,CString id)
{
	CString sql=NULL;
	sql.Format("update tally.goods set G_content='%s' where G_id=%s", content,id);
	if(  mysql_query(&m_sqlCons, sql)==0 )
	{
		return true;
	}
	else{
		return false;
	}
}
bool Product::delet(CString id)
{
	CString sql=NULL;
	sql.Format("DELETE FROM tally.goods where G_id=%s",id);
	if( mysql_query(&m_sqlCons,sql)==0 )
	{
		return true;
	}else{
		return false;
	}
}
bool Product::updateImage(CString image,CString id)
{
	image.Replace(92, '/');
	CString sql=NULL;
	sql.Format("update tally.goods set G_image='%s' where G_id=%s", image,id);
	if(  mysql_query(&m_sqlCons, sql)==0 )
	{
		return true;
	}
	else{
		return false;
	}
}