#pragma once
#include "mylistctrl.h"
#include "dledit.h"
#include "afxwin.h"


// M_I_history 对话框

class M_I_history : public CDialogEx
{
	DECLARE_DYNAMIC(M_I_history)

public:
	M_I_history(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~M_I_history();

// 对话框数据
	enum { IDD = IDD_KChistory };
	void show();
	history h;
	int selectColor;
	int chooseColor;
	void changeList(int type);
	SYSTEMTIME  CurTime;/////定义SYSTEMTIME类的对象

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
