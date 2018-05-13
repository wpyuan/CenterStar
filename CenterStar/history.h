#pragma once
class history
{
public:
	history(void);
	~history(void);
	int id;
	CString time;
	CString content;
	CString table;//±íÃû
	int tableId;
	bool add();
	bool delet();
	bool update();
	void search(CString SQL);
};

