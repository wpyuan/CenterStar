#pragma once
#include "mylistctrl.h"
#include "afxext.h"
#include "afxwin.h"
#include "afxdtctl.h"
#include "Inventory.h"
#include "Product.h"
#include "SkinHeaderCtrl.h"
#include "history.h"
// M_I_detail 对话框

class M_I_detail : public CDialogEx
{
	DECLARE_DYNAMIC(M_I_detail)

public:
	M_I_detail(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~M_I_detail();

// 对话框数据
	enum { IDD = IDD_KCDetail };
	CTime tm;
	SYSTEMTIME  CurTime;/////定义SYSTEMTIME类的对象
	Inventory inventory;
	Product product;
	history h;
	CSkinHeaderCtrl ListHeader;
	int m_Row,m_Col;
	CString start_date;
	bool penPic;
	double rk[12],ck[12];
	double rkMonth[31],ckMonth[31];
	double rkMax,rkMin,rkMonthMax,rkMonthMin;
	double ckMax,ckMin,ckMonthMax,ckMonthMin;
	bool isShowck,isShowrk;//是否显示折线
	int page,pageMax;//条形折线图页数
	bool isChoose0,isChoose1,isChoose3,isChoose4;//是否选择图名
	CString pageName;
	CString *pageIDs;
	CButton *pc;
	CButton *pr;
	CString year;
	int chooseMonth;
	int chooseDay;
	int dmax;
	bool picMonth;
	CString unit;
	bool changeColor;
	bool fanchart,barchart;
	//double *cksum,*rksum;
	int jrkPie[12],jckPie[12];
	int FcMonth;//扇形图详情月份
	bool Fcdetail;
	int PanPie;//画扇形的序号
	bool isPanrk;//是否画入库的
	int FcpageMax;//扇形图详情最大页数
	int Fcpage;//扇形图当前页
	CString stime,etime;
	void show();
	void tally();
	void tallyMonth(int month);
	void tallyFanchart();
	double Sumck(int month,int goodsid);
	double Sumrk(int month,int goodsid);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	MyListCtrl m_list;
	afx_msg void OnPaint();
	CBitmapButton m_ok;
	CStatic m_startDate;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CDateTimeCtrl m_d1;
	CDateTimeCtrl m_d2;

	afx_msg void OnDtnCloseupstartdate(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMKillfocusstartdate(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDtnCloseupenddate(NMHDR *pNMHDR, LRESULT *pResult);
	CEdit m_edit;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnHdnItemclickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg void OnEnKillfocusEdit1();
	CEdit m_edit1;
	afx_msg void OnEnKillfocusEdit2();
	CBitmapButton m_cancel;
	afx_msg void OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void On32772();
	afx_msg void OnCancel();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	CBitmapButton m_lastpage;
	CBitmapButton m_nextpage;
	afx_msg void Onlastpage();
	afx_msg void Onnextpage();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CBitmapButton m_changePic;
	afx_msg void OnBnClickedCk();
	afx_msg void OnBnClickedRk();
	afx_msg void OnFanchart();
	CBitmapButton m_changePics;
	afx_msg void OnBarchart();
	afx_msg void OnOk();
	afx_msg void OnNMKillfocusenddate(NMHDR *pNMHDR, LRESULT *pResult);
};
