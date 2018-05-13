#pragma once
#include "mylistctrl.h"
#include "Product.h"
#include "Customer.h"
#include "Order.h"
#include "afxdtctl.h"
#include "afxwin.h"
#include "history.h"
#include "Order.h"
// M_O_detail 对话框

class M_O_detail : public CDialogEx
{
	DECLARE_DYNAMIC(M_O_detail)

public:
	M_O_detail(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~M_O_detail();

// 对话框数据
	enum { IDD = IDD_M_O_detail };
	void show();
	SYSTEMTIME  CurTime;/////定义SYSTEMTIME类的对象
	Product p;
	Customer customer;
	Order *oder;
	int orderNum;
	CString year;
	bool changeColor;
	void shownext(CString SQL);
	history h;
	Order order;
	int m_Row,m_Col;
	CString start_date;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	MyListCtrl m_list;
	MyListCtrl m_lists;
	CDateTimeCtrl m_d1;
	CDateTimeCtrl m_d2;
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CEdit m_edit;
	afx_msg void OnNMRClickList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void On32772();
	CEdit m_edits;
	afx_msg void OnNMDblclkList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnKillfocusEdit2();
};
