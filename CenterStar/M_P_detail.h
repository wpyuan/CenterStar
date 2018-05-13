#pragma once
#include "afxext.h"
#include "afxwin.h"
#include "history.h"
// M_P_detail �Ի���

class M_P_detail : public CDialogEx
{
	DECLARE_DYNAMIC(M_P_detail)

public:
	M_P_detail(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~M_P_detail();

// �Ի�������
	enum { IDD = IDD_M_P_detail };
	CStatic pic[12];
	Product product;
	CFileDialog *fileDlg;
	history h;
	int page;
	CString pageAll;
	SYSTEMTIME  CurTime;/////����SYSTEMTIME��Ķ���
	CToolTipCtrl m_Mytip;
	bool isEdit;//�Ƿ�򿪱༭
	int sx;
	CString str_start[5];//�޸ģ���ʼ���ݻָ�
	CString strFilePath;
	void _initButton();
	void _initPicture();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	CBitmapButton m_ok;
	CBitmapButton m_cancel;
	CBitmapButton m_info;
	afx_msg void OnCancel();
	afx_msg void Oninfo();
	CEdit m_edit;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnSearchText();
	CBitmapButton m_lastpage;
	CBitmapButton m_nextpage;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedlastpage();
	afx_msg void OnBnClickednextpage();
	CBitmapButton b_edit;
	CBitmapButton b_delete;
	CEdit e_name;
	CEdit e_price;
	CEdit e_kc;
	CEdit e_unit;
	CEdit e_content;
	afx_msg void OnEnKillfocusEdit2();
	afx_msg void OnEnKillfocusEdit3();
	afx_msg void OnEnKillfocusEdit4();
	afx_msg void OnEnKillfocusEdit5();
	afx_msg void OnEnKillfocusEdit6();
//	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
