// M_C_add.cpp : 实现文件
//

#include "stdafx.h"
#include "CenterStar.h"
#include "M_C_add.h"
#include "afxdialogex.h"


// M_C_add 对话框

IMPLEMENT_DYNAMIC(M_C_add, CDialogEx)

M_C_add::M_C_add(CWnd* pParent /*=NULL*/)
	: CDialogEx(M_C_add::IDD, pParent)
{

}

M_C_add::~M_C_add()
{
}

void M_C_add::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDOK, m_ok);
	DDX_Control(pDX, IDCANCEL, m_cancel);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
}


BEGIN_MESSAGE_MAP(M_C_add, CDialogEx)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &M_C_add::OnNMDblclkList1)
	ON_EN_KILLFOCUS(IDC_EDIT1, &M_C_add::OnEnKillfocusEdit1)
	ON_BN_CLICKED(IDOK, &M_C_add::OnOk)
	ON_BN_CLICKED(IDCANCEL, &M_C_add::OnCancel)
END_MESSAGE_MAP()


// M_C_add 消息处理程序


BOOL M_C_add::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CRect rect(0,50,850,668);
	m_list.MoveWindow(rect);
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT| LVS_EX_GRIDLINES| LVS_EX_TWOCLICKACTIVATE | LVS_EX_TRACKSELECT /*自动换行*/| LVS_EX_FLATSB/*扁平滚动条*/ );
	m_list.InsertColumn(0,"",LVCFMT_CENTER,rect.Width()/10-50,0);
	m_list.InsertColumn(1,"姓名",LVCFMT_CENTER,rect.Width()/5,1);
	m_list.InsertColumn(2,"联系方式",LVCFMT_CENTER,rect.Width()/5,2);
	m_list.InsertColumn(3,"联系地址",LVCFMT_CENTER,rect.Width()*3/10+50,3);
	m_list.InsertColumn(4,"发货物流",LVCFMT_CENTER,rect.Width()/5,4);
	CString stri;
	for(int i=0;i<35;i++)
	{
		stri.Format("%d",i+1);
		m_list.InsertItem(i,stri);
	}
	m_Row=-1;
	m_Col=-1;
	SetTimer(1,200,NULL);
	GetDlgItem(IDOK)->MoveWindow(750,680,32,32);
	m_ok.LoadBitmaps(IDB_BITMAP39,IDB_BITMAP40,IDB_BITMAP41);
	m_ok.SizeToContent();  

	GetDlgItem(IDCANCEL)->MoveWindow(800,680,32,32);
	m_cancel.LoadBitmaps(IDB_BITMAP42);
	m_cancel.SizeToContent(); 

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void M_C_add::OnPaint()
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
	grphics.FillRectangle(&SolidBrush(Color(255,255,255,255)),Rect(-1,-1,851,713));
	Gdiplus::Font f(L"幼圆", 14);
	string= T2W((LPCTSTR)"添加客户信息");
	grphics.DrawString(string,-1,&f,PointF(5.0f,5.0f),&SolidBrush(Color(255,0,0,0)));



	dc.StretchBlt(0,0,850,712,&mdc,0,0,850,712,SRCCOPY);
	//释放资源
	m_back.DeleteObject();
	mdc.DeleteDC();
	// 不为绘图消息调用 CDialogEx::OnPaint()
}


void M_C_add::OnTimer(UINT_PTR nIDEvent)
{
	if (1==nIDEvent)  
     {
	     POINT p;  
		 GetCursorPos(&p);     
		 CWnd *hwnd;  
		 hwnd=WindowFromPoint(p);        //检索窗口中包含指定的点;点必须指定屏幕坐标在屏幕上的一个点。     
		 CWnd *hwnd1=GetDlgItem(IDOK);  
		 if (hwnd1 == hwnd)         //如果鼠标在按钮上  
		 {  
			 if (GetFocus()!=hwnd1)        
				 hwnd1->SetFocus() ;  
		 }  
		 else          //如果鼠标不在按钮上；  
		 {  
			 if (GetFocus() == hwnd1 )                   
				 GetDlgItem(IDCANCEL)->SetFocus();      
		 } 
	}

	CDialogEx::OnTimer(nIDEvent);
}


void M_C_add::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_LISTVIEW* pNMListView=(NM_LISTVIEW*)pNMHDR;
	CRect rc;
	m_Row = pNMListView->iItem;//获得选中的行
	m_Col = pNMListView->iSubItem;//获得选中列

	if(pNMListView->iSubItem != 0)
	{
		m_list.GetSubItemRect(m_Row,m_Col,LVIR_LABEL,rc);//获得子项的RECT；
		rc.left=rc.left+1;
		rc.bottom=rc.bottom-1;
		m_edit.SetParent(&m_list);//转换坐标为列表框中的坐标
		m_edit.MoveWindow(rc);//移动Edit到RECT坐在的位置;
		m_edit.SetWindowText(m_list.GetItemText(m_Row,m_Col));//将该子项中的值放在Edit控件中；
		m_edit.ShowWindow(SW_SHOW);//显示Edit控件；
		m_edit.SetFocus();//设置Edit焦点
		m_edit.ShowCaret();//显示光标
		m_edit.SetSel(-1);//将光标移动到最后
		//start_date=m_list.GetItemText(m_Row,m_Col);//还原初始数据
	}
	*pResult = 0;
}


void M_C_add::OnEnKillfocusEdit1()
{
	CString tem;
	m_edit.GetWindowText(tem);    //得到用户输入的新的内容
	m_list.SetItemText(m_Row,m_Col,tem);   //设置编辑框的新内容
	m_edit.ShowWindow(SW_HIDE); //应藏编辑框
	
}	


void M_C_add::OnOk()
{
	for(int i=0;i<35;i++)
	{
		if( !( customer.name=m_list.GetItemText(i,1) ).IsEmpty() )
		{
			customer.phone=m_list.GetItemText(i,2);
			customer.address=m_list.GetItemText(i,3);
			customer.logistics=m_list.GetItemText(i,4);
			if(customer.add(customer))
			{
				CString sql;
				sql.Format("SELECT * FROM tally.customer where C_name='%s'",customer.name);
				customer=customer.select(customer,sql);
				//1.获取当前时间,插入历史记录
				GetLocalTime(&CurTime);////获取本地时间 
				h.time.Format("%d:%d:%d",CurTime.wHour,CurTime.wMinute,CurTime.wSecond);
				h.content="添加客户\n"+customer.name;
				h.table="customer";
				h.tableId=customer.id;
				h.add();
				//2.插入listcontrol
				m_ListCtrl.InsertItem(0,h.time);
				m_ListCtrl.SetItemText(0,1,h.content);
				//清空表
				m_list.SetItemText(i,1,"");
				m_list.SetItemText(i,2,"");
				m_list.SetItemText(i,3,"");
				m_list.SetItemText(i,4,"");
			}else{
				MessageBox(customer.name+"添加失败","提示",MB_ICONEXCLAMATION);
			}
		}
	}
	
}


void M_C_add::OnCancel()
{
	for(int i=0;i<35;i++)
	{
		//清空表
		m_list.SetItemText(i,1,"");
		m_list.SetItemText(i,2,"");
		m_list.SetItemText(i,3,"");
		m_list.SetItemText(i,4,"");
	}
}
