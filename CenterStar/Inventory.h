#pragma once
class Inventory
{
public:
	Inventory(void);
	~Inventory(void);

	int id;
	int goodsId;
	double rk;
	double ck;
	double kc;
	CString remark;
	CString time;

	bool add(Inventory inventory);
	bool delet(CString sql);
	bool update(CString sql);
	Inventory searchAuto(Inventory inventory,CString I_time);
	void selectKcIndex();
	void selectSql(CString sql);//¸ù¾ÝsqlÓï¾ä²éÑ¯
	
};

