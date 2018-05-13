#pragma once
#include "mylistctrl.h"
#include "Customer.h"
#include "afxext.h"
#include "afxwin.h"
#include "history.h"
// M_C_detail �Ի���

class M_C_detail : public CDialogEx
{
	DECLARE_DYNAMIC(M_C_detail)

public:
	M_C_detail(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~M_C_detail();

// �Ի�������
	enum { IDD = IDD_M_C_detail };
	void show();
	Customer customer;
	SYSTEMTIME  CurTime;/////����SYSTEMTIME��Ķ���
	history h;
	int m_Row,m_Col;
	CString start_date;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
