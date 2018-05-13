#pragma once
class Order
{
public:
	Order(void);
	~Order(void);
	int id;
	CString time;
	int goodsId;
	int customerId;
	double number;
	CString remark;
	double profit;
	bool add();
	Order select(Order order,CString sql);
	bool delet(CString sql);
};

