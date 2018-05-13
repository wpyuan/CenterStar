#pragma once
class Customer
{
public:
	Customer(void);
	~Customer(void);
	int id;
	CString name;
	CString phone;
	CString address;
	CString logistics;
	bool add(Customer customer);
	Customer select(Customer customer,CString sql);
	bool delet(CString ID);
	bool update(CString sql);
	Customer selectId(Customer customer);
};

