
// CenterStarDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxext.h"
#include "M_P_add.h"
#include "DLEdit.h"
#include "Product.h"
#include "M_P_detail.h"
#include "M_I_io.h"
#include "M_I_detail.h"
#include "M_I_history.h"
#include "M_O_add.h"
#include "M_C_add.h"
#include "M_C_detail.h"
#include "M_O_detail.h"
#include "mylistctrl.h"
#include "history.h"
// CCenterStarDlg 对话框
class CCenterStarDlg : public CDialogEx
{
// 构造
public:
	Product product;
	CStatic p;
	CStatic p1;
	CStatic p_picindex[4];
	int  cx,cy;
	int page;
	CString pageAll;
	history h;
	CCenterStarDlg(CWnd* pParent = NULL);	// 标准构造函数
	SYSTEMTIME  CurTime;/////定义SYSTEMTIME类的对象
// 对话框数据
	enum { IDD = IDD_CENTERSTAR_DIALOG };
	
	void _initPictrue();
	void _initDialog();
	void _initButton();
	void history();

	protected:
		M_P_add c_cpadd;
		M_P_detail c_cpdeai;
		M_I_io c_kcio;
		M_I_detail c_kcdt;
		M_I_history c_kcls;
		M_O_add c_ddadd;
		M_C_add c_khadd;
		M_C_detail c_khdt;
		M_O_detail c_dddt;
		CRect m_c;
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	//l...start//
	/*void EnableBkImage(BOOL bEnable);
	void RecreateListControl(const DWORD &dwStyles, const DWORD &dwStylesEx);

	void InitListCtrlCols();
	void InsertItems();
	BOOL InitImageList();
	CImageList	m_cImageListNormal, m_cImageListSmall, m_cImageListState;*/
	//l...end//

	HICON m_hIcon;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();

	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	CDLEdit m_edit;
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	CBitmapButton m_close;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CBitmapButton m_min;
	CBitmapButton m_test;
	afx_msg void OnBnClickedTest();
	
	CBitmapButton m_changekc;
	CBitmapButton m_kcdetail;
	CBitmapButton m_kchistory;
	CBitmapButton m_product;
	CBitmapButton m_addproduct;
	CBitmapButton m_P_Detail;
	CBitmapButton m_order;
	CBitmapButton m_O_add;
	CBitmapButton m_O_detail;
	CBitmapButton m_customer;
	CBitmapButton m_C_add;
	CBitmapButton m_C_search;
	afx_msg void OnM_P_add();
	virtual BOOL DestroyWindow();
	CBitmapButton m_lastpage;
	CBitmapButton m_nextpage;
	afx_msg void OnBnClickednextpage();
	afx_msg void OnBnClickedlastpage();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnM_Pdeai();
	afx_msg void OnBnClickedOk();
	afx_msg void OnM_I_io();
	afx_msg void OnM_I_detail();
	afx_msg void OnM_I_history();
	afx_msg void OnM_O_add();
	afx_msg void OnM_C_add();
	afx_msg void OnM_C_detail();
	afx_msg void OnM_O_Detail();
	MyListCtrl m_lists;
	afx_msg void OnMin();
};
