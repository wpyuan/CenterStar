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
	Product selectId(Product p);//�����ϸ��ѯ

	void selectIndex();//��ҳ��ѯ
	void selectInfor();//��Ʒ��Ϣҳ��ѯ
	void selectText(CString name);//��Ʒ��ϢƷ������
	void selectContent(CString content);//��Ʒ��Ϣ����
	bool update(CString name,CString id);//�޸�Ʒ��
	bool updatePrcie(CString price,CString id);//�޸ĵ���
	bool updateKc(CString kc,CString id);//�޸Ŀ��
	bool updateUnit(CString Unit,CString id);//�޸Ŀ�浥λ
	bool updateContent(CString content,CString id);//�޸�˵��
	bool updateImage(CString image,CString id);//�޸�˵��
};

