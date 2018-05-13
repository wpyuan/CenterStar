#pragma once
#include "mylistctrl.h"
#include "dledit.h"
#include "afxwin.h"


// M_I_history �Ի���

class M_I_history : public CDialogEx
{
	DECLARE_DYNAMIC(M_I_history)

public:
	M_I_history(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~M_I_history();

// �Ի�������
	enum { IDD = IDD_KChistory };
	void show();
	history h;
	int selectColor;
	int chooseColor;
	void changeList(int type);
	SYSTEMTIME  CurTime;/////����SYSTEMTIME��Ķ���

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	MyListCtrl m_list;
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	CEdit m_edit;
	CComboBox m_combox;
	afx_msg void OnCbnCloseupCombo1();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
