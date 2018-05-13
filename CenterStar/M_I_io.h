#pragma once
#include "mylistctrl.h"
#include "afxwin.h"
#include "Inventory.h"
#include "Product.h"
#include "history.h"
#include "afxext.h"
// M_I_io 对话框

class M_I_io : public CDialogEx
{
	DECLARE_DYNAMIC(M_I_io)

public:
	M_I_io(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~M_I_io();

// 对话框数据
	enum { IDD = IDD_IO };
	int m_Row,m_Col;
	CStatic pic[6];
	CString image[6];
	Inventory inventory;
	history h;
	SYSTEMTIME  CurTime;/////定义SYSTEMTIME类的对象
	Product product;
	void _initPicture();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	MyListCtrl m_list;

	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	CEdit m_edit;
	afx_msg void OnEnKillfocusEdit1();
	afx_msg void OnOk();
//	afx_msg void OnNMHoverList1(NMHDR *pNMHDR, LRESULT *pResult);
	CBitmapButton m_ok;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CBitmapButton m_cancel;
	afx_msg void OnCancel();
};
