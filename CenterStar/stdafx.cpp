
// stdafx.cpp : 只包括标准包含文件的源文件
// CenterStar.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

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