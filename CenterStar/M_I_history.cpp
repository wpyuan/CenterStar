// M_I_history.cpp : 实现文件
//

#include "stdafx.h"
#include "CenterStar.h"
#include "M_I_history.h"
#include "afxdialogex.h"


// M_I_history 对话框

IMPLEMENT_DYNAMIC(M_I_history, CDialogEx)

M_I_history::M_I_history(CWnd* pParent /*=NULL*/)
	: CDialogEx(M_I_history::IDD, pParent)
{

}

M_I_history::~M_I_history()
{
}

void M_I_history::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
	DDX_Control(pDX, IDC_COMBO1, m_combox);
}


BEGIN_MESSAGE_MAP(M_I_history, CDialogEx)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_CBN_CLOSEUP(IDC_COMBO1, &M_I_history::OnCbnCloseupCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &M_I_history::OnCbnSelchangeCombo1)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// M_I_history 消息处理程序


BOOL M_I_history::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	selectColor=1;
	chooseColor=-1;

	CRect rect(0,100,850,714);
	m_list.MoveWindow(rect);
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT| LVS_EX_GRIDLINES| LVS_EX_TWOCLICKACTIVATE | LVS_EX_TRACKSELECT /*自动换行*/| LVS_EX_FLATSB/*扁平滚动条*/ );
	m_list.InsertColumn(0,"",LVCFMT_CENTER,rect.Width()/7-40,0);
	m_list.InsertColumn(1,"内容",LVCFMT_CENTER,rect.Width()*5/7,1);
	m_list.InsertColumn(2,"时间",LVCFMT_CENTER,rect.Width()/7+40,2);

	m_edit.MoveWindow(480,40,320,20);
	m_combox.MoveWindow(120,35,100,20);
	
	show();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
void M_I_history::show()
{
	m_list.SetRedraw(0);
	m_list.DeleteAllItems();
	while(m_list.DeleteColumn(0));
	CRect rect(0,100,850,714);
	m_list.MoveWindow(rect);
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT| LVS_EX_GRIDLINES| LVS_EX_TWOCLICKACTIVATE | LVS_EX_TRACKSELECT /*自动换行*/| LVS_EX_FLATSB/*扁平滚动条*/ );
	m_list.SetTextBkColor(RGB(229,232,177));
	m_list.InsertColumn(0,"",LVCFMT_CENTER,rect.Width()/7-40,0);
	m_list.InsertColumn(1,"内容",LVCFMT_CENTER,rect.Width()*5/7,1);
	m_list.InsertColumn(2,"时间",LVCFMT_CENTER,rect.Width()/7+40,2);
	CString sql;
	sql.Format("SELECT * FROM tally.history where H_table='inventory';");
	h.search(sql);
	if(kclsNum>0)
	{
		CString stri,rk,ck,kc;
		for(int i=0;i<kclsNum;i++)
		{
			stri.Format("%d",i+1);
			m_list.InsertItem(i,stri);
			m_list.SetItemText(i,1,kchistory[i].content);
			m_list.SetItemText(i,2,kchistory[i].time);
		}
	}
	m_list.SetRedraw(1);
	m_list.Invalidate();
}

void M_I_history::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CDC mdc;
	mdc.CreateCompatibleDC(&dc);
	CBitmap m_back;
	m_back.CreateCompatibleBitmap(&dc,850,712);
	mdc.SelectObject(m_back);

	USES_CONVERSION;
	WCHAR *string;
	HDC hdc = mdc.GetSafeHdc();
	Graphics grphics(hdc);
	grphics.SetSmoothingMode(SmoothingModeHighQuality); //设置平滑画线
	Gdiplus::Font fbig(L"幼圆", 14);
	Gdiplus::Font fmedium(L"幼圆", 12);
	Gdiplus::Font fsmall(L"幼圆", 10);
	Pen p1(Color(100,217,194,116),3.0f);
	Pen p2(Color(50,45,85,255),1.0f);
	Pen p3(Color(255,217,194,116),2.0f);
	grphics.FillRectangle(&SolidBrush(Color(255,255,255,255)),Rect(-1,-1,851,101));
	string=T2W((LPCTSTR)"我的库存历史记录"); 
	grphics.DrawString(string,-1,&fbig,PointF(0,5),&SolidBrush(Color(255,0,0,0)));
	grphics.DrawLine(&p1,Point(3,30),Point(840,30));

	string=T2W((LPCTSTR)"交易时间:"); 
	grphics.DrawString(string,-1,&fbig,PointF(20,35),&SolidBrush(Color(200,0,0,0)));
	string=T2W((LPCTSTR)"关键字:");
	grphics.DrawString(string,-1,&fbig,PointF(400,35),&SolidBrush(Color(200,0,0,0)));

	if(selectColor==-1||selectColor==1)
		grphics.FillRectangle(&SolidBrush(Color(255,160,160,160)),Rect(-1,75,81,35));
	else if(chooseColor==1)
		grphics.FillRectangle(&SolidBrush(Color(100,160,160,160)),Rect(-1,75,81,35));
	else
		grphics.FillRectangle(&SolidBrush(Color(200,160,160,160)),Rect(-1,75,81,35));
	string=T2W((LPCTSTR)"所有类型");
	grphics.DrawString(string,-1,&fmedium,PointF(0,78),&SolidBrush(Color(255,255,255,255)));

	if(selectColor==2)
		grphics.FillRectangle(&SolidBrush(Color(255,160,160,160)),Rect(80,75,81,35));
	else if(chooseColor==2)
		grphics.FillRectangle(&SolidBrush(Color(100,160,160,160)),Rect(80,75,81,35));
	else
		grphics.FillRectangle(&SolidBrush(Color(200,160,160,160)),Rect(80,75,81,35));	
	string=T2W((LPCTSTR)"出入库");
	grphics.DrawString(string,-1,&fmedium,PointF(91,78),&SolidBrush(Color(255,255,255,255)));

	if(selectColor==3)
		grphics.FillRectangle(&SolidBrush(Color(255,160,160,160)),Rect(161,75,81,35));
	else if(chooseColor==3)
		grphics.FillRectangle(&SolidBrush(Color(100,160,160,160)),Rect(161,75,81,35));
	else
		grphics.FillRectangle(&SolidBrush(Color(200,160,160,160)),Rect(161,75,81,35));
	string=T2W((LPCTSTR)"变更品名");
	grphics.DrawString(string,-1,&fmedium,PointF(164,78),&SolidBrush(Color(255,255,255,255)));

	if(selectColor==4)
		grphics.FillRectangle(&SolidBrush(Color(255,160,160,160)),Rect(242,75,81,35));
	else if(chooseColor==4)
		grphics.FillRectangle(&SolidBrush(Color(100,160,160,160)),Rect(242,75,81,35));
	else
		grphics.FillRectangle(&SolidBrush(Color(200,160,160,160)),Rect(242,75,81,35));
	string=T2W((LPCTSTR)"变更入库");
	grphics.DrawString(string,-1,&fmedium,PointF(245,78),&SolidBrush(Color(255,255,255,255)));

	if(selectColor==5)
		grphics.FillRectangle(&SolidBrush(Color(255,160,160,160)),Rect(323,75,81,35));
	else if(chooseColor==5)
		grphics.FillRectangle(&SolidBrush(Color(100,160,160,160)),Rect(323,75,81,35));
	else
		grphics.FillRectangle(&SolidBrush(Color(200,160,160,160)),Rect(323,75,81,35));
	string=T2W((LPCTSTR)"变更出库");
	grphics.DrawString(string,-1,&fmedium,PointF(326,78),&SolidBrush(Color(255,255,255,255)));

	if(selectColor==6)
		grphics.FillRectangle(&SolidBrush(Color(255,160,160,160)),Rect(404,75,81,35));
	else if(chooseColor==6)
		grphics.FillRectangle(&SolidBrush(Color(100,160,160,160)),Rect(404,75,81,35));
	else
		grphics.FillRectangle(&SolidBrush(Color(200,160,160,160)),Rect(404,75,81,35));
	string=T2W((LPCTSTR)"变更库存");
	grphics.DrawString(string,-1,&fmedium,PointF(407,78),&SolidBrush(Color(255,255,255,255)));

	if(selectColor==7)
		grphics.FillRectangle(&SolidBrush(Color(255,160,160,160)),Rect(485,75,81,35));
	else if(chooseColor==7)
		grphics.FillRectangle(&SolidBrush(Color(100,160,160,160)),Rect(485,75,81,35));
	else
		grphics.FillRectangle(&SolidBrush(Color(200,160,160,160)),Rect(485,75,81,35));
	string=T2W((LPCTSTR)"变更时间");
	grphics.DrawString(string,-1,&fmedium,PointF(488,78),&SolidBrush(Color(255,255,255,255)));

	if(selectColor==8)
		grphics.FillRectangle(&SolidBrush(Color(255,160,160,160)),Rect(566,75,81,35));
	else if(chooseColor==8)
		grphics.FillRectangle(&SolidBrush(Color(100,160,160,160)),Rect(566,75,81,35));
	else
		grphics.FillRectangle(&SolidBrush(Color(200,160,160,160)),Rect(566,75,81,35));
	string=T2W((LPCTSTR)"变更备注");
	grphics.DrawString(string,-1,&fmedium,PointF(569,78),&SolidBrush(Color(255,255,255,255)));

	grphics.FillRectangle(&SolidBrush(Color(255,217,194,116)),Rect(803,34,37,27));
	grphics.DrawRectangle(&p3,Rect(478,35,325,25));
	string=T2W((LPCTSTR)"搜索");
	grphics.DrawString(string,-1,&fmedium,PointF(801,38),&SolidBrush(Color(255,255,255,255)));
	
	dc.StretchBlt(0,0,850,712,&mdc,0,0,850,712,SRCCOPY);
	//释放资源
	m_back.DeleteObject();
	mdc.DeleteDC();

	// 不为绘图消息调用 CDialogEx::OnPaint()
}


void M_I_history::OnMouseMove(UINT nFlags, CPoint point)
{
	CDialogEx::OnMouseMove(nFlags, point);
	CRect rect;
	CRect sxrect(0,75,648,100);
	for(int i=0;i<8;i++)
	{
		rect.left=0+81*i;
		rect.top=75;
		rect.bottom=75+35;
		rect.right=rect.left+81;
		if(rect.PtInRect(point))
		{
			chooseColor=i+1;
			InvalidateRect(sxrect,0);
		}
	}
	if(!sxrect.PtInRect(point))
	{
		chooseColor=0;
		InvalidateRect(sxrect,0);
	}
}


void M_I_history::OnCbnCloseupCombo1()
{
	/*CString text;
	m_combox.GetWindowTextA(text);
	if(text=="自定义时间")
	{
	}*/
}


void M_I_history::OnCbnSelchangeCombo1()
{
	/*CString text;
	m_combox.GetWindowTextA(text);
	if(text=="自定义时间")
	{
	}*/
}


void M_I_history::OnLButtonDown(UINT nFlags, CPoint point)
{
	CRect rect;
	for(int i=0;i<8;i++)
	{
		rect.left=0+81*i;
		rect.top=75;
		rect.bottom=75+35;
		rect.right=rect.left+81;
		if(rect.PtInRect(point))
		{
			selectColor=i+1;
			InvalidateRect(CRect(0,75,648,110),0);
			changeList(selectColor);
		}
	}
	//搜索
	CRect rectcx(803,34,803+37,34+27);
	if(rectcx.PtInRect(point))
	{
		CString time,y,m,d;
		m_combox.GetWindowTextA(time);
		GetLocalTime(&CurTime);////获取本地时间 
		y.Format("%d",CurTime.wYear);
		m.Format("%d",CurTime.wMonth);
		d.Format("%d",CurTime.wDay);

		CString text;
		m_edit.GetWindowTextA(text);
		CString SQL;
		if(time.IsEmpty()||time=="全部")
		{
			switch(selectColor)
			{
			case 1:
				SQL.Format("SELECT * FROM tally.history where H_table='inventory' and H_content like '%s%s%s';","%",text,"%");
				break;
			case 2:
				SQL.Format("SELECT * FROM tally.history where H_table='inventory' and H_content like '%s出入库操作%s' and H_content like '%s%s%s' ;","%","%","%",text,"%");
				break;
			case 3:
				SQL.Format("SELECT * FROM tally.history where H_table='inventory' and H_content like '%s的品名%s' and H_content like '%s%s%s' ;","%","%","%",text,"%");
				break;
			case 4:
				SQL.Format("SELECT * FROM tally.history where H_table='inventory' and H_content like '%s的入库%s' and H_content like '%s%s%s' ;","%","%","%",text,"%");
				break;
			case 5:
				SQL.Format("SELECT * FROM tally.history where H_table='inventory' and H_content like '%s的出库%s' and H_content like '%s%s%s' ;","%","%","%",text,"%");
				break;
			case 6:
				SQL.Format("SELECT * FROM tally.history where H_table='inventory' and H_content like '%s的库存%s' and H_content like '%s%s%s' ;","%","%","%",text,"%");
				break;
			case 7:
				SQL.Format("SELECT * FROM tally.history where H_table='inventory' and H_content like '%s的时间%s' and H_content like '%s%s%s' ;","%","%","%",text,"%");
				break;
			case 8:
				SQL.Format("SELECT * FROM tally.history where H_table='inventory' and H_content like '%s的备注%s' and H_content like '%s%s%s' ;","%","%","%",text,"%");
				break;
			}
		}
		else if(time=="最近一个月"||time=="最近三个月")
		{
			CString lastm;
			if(time=="最近三个月")
				lastm.Format("%d",atoi(m)-3);
			else
				lastm.Format("%d",atoi(m)-1);
			switch(selectColor)
			{
			case 1:
				SQL.Format("SELECT * FROM tally.history where H_table='inventory' and H_time>='%s-%s-%s' and H_time<='%s-%s-%s' and H_content like '%s%s%s';",y,lastm,d,y,m,d,"%",text,"%");
				break;
			case 2:
				SQL.Format("SELECT * FROM tally.history where H_table='inventory' and H_time>='%s-%s-%s' and H_time<='%s-%s-%s' and H_content like '%s出入库操作%s' and H_content like '%s%s%s' ;",y,lastm,d,y,m,d,"%","%","%",text,"%");
				break;
			case 3:
				SQL.Format("SELECT * FROM tally.history where H_table='inventory' and H_time>='%s-%s-%s' and H_time<='%s-%s-%s' and H_content like '%s的品名%s' and H_content like '%s%s%s' ;",y,lastm,d,y,m,d,"%","%","%",text,"%");
				break;
			case 4:
				SQL.Format("SELECT * FROM tally.history where H_table='inventory' and H_time>='%s-%s-%s' and H_time<='%s-%s-%s' and H_content like '%s的入库%s' and H_content like '%s%s%s' ;",y,lastm,d,y,m,d,"%","%","%",text,"%");
				break;
			case 5:
				SQL.Format("SELECT * FROM tally.history where H_table='inventory' and H_time>='%s-%s-%s' and H_time<='%s-%s-%s' and H_content like '%s的出库%s' and H_content like '%s%s%s' ;",y,lastm,d,y,m,d,"%","%","%",text,"%");
				break;
			case 6:
				SQL.Format("SELECT * FROM tally.history where H_table='inventory' and H_time>='%s-%s-%s' and H_time<='%s-%s-%s' and H_content like '%s的库存%s' and H_content like '%s%s%s' ;",y,lastm,d,y,m,d,"%","%","%",text,"%");
				break;
			case 7:
				SQL.Format("SELECT * FROM tally.history where H_table='inventory' and H_time>='%s-%s-%s' and H_time<='%s-%s-%s' and H_content like '%s的时间%s' and H_content like '%s%s%s' ;",y,lastm,d,y,m,d,"%","%","%",text,"%");
				break;
			case 8:
				SQL.Format("SELECT * FROM tally.history where H_table='inventory' and H_time>='%s-%s-%s' and H_time<='%s-%s-%s' and H_content like '%s的备注%s' and H_content like '%s%s%s' ;",y,lastm,d,y,m,d,"%","%","%",text,"%");
				break;
			}
		}
		else if(time=="最近一年")
		{
			CString lasty;
			lasty.Format("%d",atoi(y)-1);
			switch(selectColor)
			{
			case 1:
				SQL.Format("SELECT * FROM tally.history where H_table='inventory' and H_time>='%s-%s-%s' and H_time<='%s-%s-%s' and H_content like '%s%s%s';",lasty,m,d,y,m,d,"%",text,"%");
				break;
			case 2:
				SQL.Format("SELECT * FROM tally.history where H_table='inventory' and H_time>='%s-%s-%s' and H_time<='%s-%s-%s' and H_content like '%s出入库操作%s' and H_content like '%s%s%s' ;",lasty,m,d,y,m,d,"%","%","%",text,"%");
				break;
			case 3:
				SQL.Format("SELECT * FROM tally.history where H_table='inventory' and H_time>='%s-%s-%s' and H_time<='%s-%s-%s' and H_content like '%s的品名%s' and H_content like '%s%s%s' ;",lasty,m,d,y,m,d,"%","%","%",text,"%");
				break;
			case 4:
				SQL.Format("SELECT * FROM tally.history where H_table='inventory' and H_time>='%s-%s-%s' and H_time<='%s-%s-%s' and H_content like '%s的入库%s' and H_content like '%s%s%s' ;",lasty,m,d,y,m,d,"%","%","%",text,"%");
				break;
			case 5:
				SQL.Format("SELECT * FROM tally.history where H_table='inventory' and H_time>='%s-%s-%s' and H_time<='%s-%s-%s' and H_content like '%s的出库%s' and H_content like '%s%s%s' ;",lasty,m,d,y,m,d,"%","%","%",text,"%");
				break;
			case 6:
				SQL.Format("SELECT * FROM tally.history where H_table='inventory' and H_time>='%s-%s-%s' and H_time<='%s-%s-%s' and H_content like '%s的库存%s' and H_content like '%s%s%s' ;",lasty,m,d,y,m,d,"%","%","%",text,"%");
				break;
			case 7:
				SQL.Format("SELECT * FROM tally.history where H_table='inventory' and H_time>='%s-%s-%s' and H_time<='%s-%s-%s' and H_content like '%s的时间%s' and H_content like '%s%s%s' ;",lasty,m,d,y,m,d,"%","%","%",text,"%");
				break;
			case 8:
				SQL.Format("SELECT * FROM tally.history where H_table='inventory' and H_time>='%s-%s-%s' and H_time<='%s-%s-%s' and H_content like '%s的备注%s' and H_content like '%s%s%s' ;",lasty,m,d,y,m,d,"%","%","%",text,"%");
				break;
			}
		}
		h.search(SQL);
		m_list.SetRedraw(0);
		m_list.DeleteAllItems();
		if(kclsNum>0)
		{
			CString stri,rk,ck,kc;
			for(int i=0;i<kclsNum;i++)
			{
				stri.Format("%d",i+1);
				m_list.InsertItem(i,stri);
				m_list.SetItemText(i,1,kchistory[i].content);
				m_list.SetItemText(i,2,kchistory[i].time);
			}
		}
		m_list.SetRedraw(1);
		m_list.Invalidate();
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}
void M_I_history::changeList(int type)
{
	m_list.SetRedraw(0);
	m_list.DeleteAllItems();
	while(m_list.DeleteColumn(0));
	CRect rect(0,100,850,714);
	m_list.MoveWindow(rect);
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT| LVS_EX_GRIDLINES| LVS_EX_TWOCLICKACTIVATE | LVS_EX_TRACKSELECT /*自动换行*/| LVS_EX_FLATSB/*扁平滚动条*/ );
	m_list.SetTextBkColor(RGB(229,232,177));
	m_list.InsertColumn(0,"",LVCFMT_CENTER,rect.Width()/7-40,0);
	m_list.InsertColumn(1,"内容",LVCFMT_CENTER,rect.Width()*5/7,1);
	m_list.InsertColumn(2,"时间",LVCFMT_CENTER,rect.Width()/7+40,2);
	CString sql;
	switch(type)
	{
	case 1:
		sql.Format("SELECT * FROM tally.history where H_table='inventory';");
		h.search(sql);
		break;
	case 2:
		sql.Format("SELECT * FROM tally.history where H_table='inventory' and H_content like '%s出入库操作%s' ;","%","%");
		h.search(sql);
		break;
	case 3:
		sql.Format("SELECT * FROM tally.history where H_table='inventory' and H_content like '%s的品名%s' ;","%","%");
		h.search(sql);
		break;
	case 4:
		sql.Format("SELECT * FROM tally.history where H_table='inventory' and H_content like '%s的入库%s' ;","%","%");
		h.search(sql);
		break;
	case 5:
		sql.Format("SELECT * FROM tally.history where H_table='inventory' and H_content like '%s的出库%s' ;","%","%");
		h.search(sql);
		break;
	case 6:
		sql.Format("SELECT * FROM tally.history where H_table='inventory' and H_content like '%s的库存%s' ;","%","%");
		h.search(sql);
		break;
	case 7:
		sql.Format("SELECT * FROM tally.history where H_table='inventory' and H_content like '%s的时间%s' ;","%","%");
		h.search(sql);
		break;
	case 8:
		sql.Format("SELECT * FROM tally.history where H_table='inventory' and H_content like '%s的备注%s' ;","%","%");
		h.search(sql);
		break;
	//default 
	}
	if(kclsNum>0)
	{
		CString stri,rk,ck,kc;
		for(int i=0;i<kclsNum;i++)
		{
			stri.Format("%d",i+1);
			m_list.InsertItem(i,stri);
			m_list.SetItemText(i,1,kchistory[i].content);
			m_list.SetItemText(i,2,kchistory[i].time);
		}
	}
	m_list.SetRedraw(1);
	m_list.Invalidate();
}