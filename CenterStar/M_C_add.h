#pragma once
#include "mylistctrl.h"
#include "afxext.h"
#include "afxwin.h"
#include "Customer.h"
#include "history.h"
// M_C_add 对话框

class M_C_add : public CDialogEx
{
	DECLARE_DYNAMIC(M_C_add)

public:
	M_C_add(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~M_C_add();
	SYSTEMTIME  CurTime;/////定义SYSTEMTIME类的对象
	history h;

// 对话框数据
	enum { IDD = IDD_M_C_add };
	int m_Row,m_Col;
	Customer customer;


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	MyListCtrl m_list;
	CBitmapButton m_ok;
	CBitmapButton m_cancel;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	CEdit m_edit;
	afx_msg void OnEnKillfocusEdit1();
	afx_msg void OnOk();
	afx_msg void OnCancel();
};
