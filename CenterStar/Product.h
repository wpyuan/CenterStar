#pragma once

class Product
{
public:
	Product(void);
	~Product(void);
	
public:
	int id;
	CString name;
	double price;
	CString unit;
	double kc;
	CString image;
	CString content;
	bool add();
	bool delet(CString id);
	Product select(Product p);
	Product selectId(Product p);//库存明细查询

	void selectIndex();//首页查询
	void selectInfor();//产品信息页查询
	void selectText(CString name);//产品信息品名搜索
	void selectContent(CString content);//产品信息搜索
	bool update(CString name,CString id);//修改品名
	bool updatePrcie(CString price,CString id);//修改单价
	bool updateKc(CString kc,CString id);//修改库存
	bool updateUnit(CString Unit,CString id);//修改库存单位
	bool updateContent(CString content,CString id);//修改说明
	bool updateImage(CString image,CString id);//修改说明
};

