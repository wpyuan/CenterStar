#pragma once
#include "mylistctrl.h"
#include "afxext.h"
#include "afxwin.h"
#include "history.h"
#include "Order.h"
#include "Product.h"
#include "Customer.h"

// M_O_add 对话框

class M_O_add : public CDialogEx
{
	DECLARE_DYNAMIC(M_O_add)

public:
	M_O_add(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~M_O_add();

// 对话框数据
	enum { IDD = IDD_M_O_add };
	int m_Row,m_Col;
	history h;
	SYSTEMTIME  CurTime;/////定义SYSTEMTIME类的对象
	Order order;
	Product p;
	Customer customer;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	MyListCtrl m_list;
	CBitmapButton m_ok;
	CBitmapButton m_cancel;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	CEdit m_edit;
	afx_msg void OnEnKillfocusEdit1();
	afx_msg void OnOk();
	afx_msg void OnPaint();
	afx_msg void OnCancel();
};
