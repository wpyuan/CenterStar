#pragma once
#include "afxext.h"
#include "dledit.h"
#include "Product.h"
#include "history.h"
#include "Inventory.h"
// M_P_add 对话框

class M_P_add : public CDialogEx
{
	DECLARE_DYNAMIC(M_P_add)

public:
	Product p;
	history h;
	Product pr;
	Inventory inventory;
	SYSTEMTIME  CurTime;/////定义SYSTEMTIME类的对象

	M_P_add(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~M_P_add();

// 对话框数据
	enum { IDD = IDD_M_P_add };
	CString strFilePath;
	CString strFilepath[4];
	CString pname[4];
	CString pkc[4];
	CString pjg[4];
	CString pwords[4];
	CString punit[4];
	int num;
	BOOL HasChineseChar(CString Cstr);
	void _initButton();
	void _initEdit();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	CDLEdit e_name;
	CDLEdit e_price;
	CDLEdit e_unit;
	CDLEdit e_kc;
	CDLEdit e_content;
	CStatic p1;
	CStatic p2;
	CStatic p3;
	CStatic p0;
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CBitmapButton M_OK;
	CBitmapButton m_cancel;
	CBitmapButton m_remove;
	afx_msg void OnRemove();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnStnClickedaddpic();
	
};
