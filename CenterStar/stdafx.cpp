
// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// CenterStar.pch ����ΪԤ����ͷ
// stdafx.obj ������Ԥ����������Ϣ

#include "stdafx.h"
MYSQL m_sqlCons;
ULONG_PTR gdiplustoken;
bool f_M_P_add;
MyListCtrl m_ListCtrl;
int indexNum=0;
int infoNum=0;
int kcdtNum=0;
int kclsNum=0;
Product *pindex=NULL;
Product *pinfo=NULL;
Database database;
Inventory *kcindex=NULL;
CString h_Itime=NULL;
history *kchistory=NULL;