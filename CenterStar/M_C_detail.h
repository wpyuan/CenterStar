#pragma once
#include "mylistctrl.h"
#include "Customer.h"
#include "afxext.h"
#include "afxwin.h"
#include "history.h"
// M_C_detail 对话框

class M_C_detail : public CDialogEx
{
	DECLARE_DYNAMIC(M_C_detail)

public:
	M_C_detail(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~M_C_detail();

// 对话框数据
	enum { IDD = IDD_M_C_detail };
	void show();
	Customer customer;
	SYSTEMTIME  CurTime;/////定义SYSTEMTIME类的对象
	history h;
	int m_Row,m_Col;
	CString start_date;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	MyListCtrl m_list;
	afx_msg void OnOk();
	CBitmapButton m_ok;
	CBitmapButton m_cancel;
	afx_msg void OnDelet();
	CEdit m_edit;
	CEdit m_edits;
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnKillfocusEdit2();
};
