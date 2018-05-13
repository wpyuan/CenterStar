// M_C_detail.cpp : 实现文件
//

#include "stdafx.h"
#include "CenterStar.h"
#include "M_C_detail.h"
#include "afxdialogex.h"


// M_C_detail 对话框

IMPLEMENT_DYNAMIC(M_C_detail, CDialogEx)

M_C_detail::M_C_detail(CWnd* pParent /*=NULL*/)
	: CDialogEx(M_C_detail::IDD, pParent)
{

}

M_C_detail::~M_C_detail()
{
}

void M_C_detail::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDOK, m_ok);
	DDX_Control(pDX, IDCANCEL, m_cancel);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
	DDX_Control(pDX, IDC_EDIT2, m_edits);
}


BEGIN_MESSAGE_MAP(M_C_detail, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDOK, &M_C_detail::OnOk)
	ON_BN_CLICKED(IDCANCEL, &M_C_detail::OnDelet)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &M_C_detail::OnNMDblclkList1)
	ON_EN_KILLFOCUS(IDC_EDIT2, &M_C_detail::OnEnKillfocusEdit2)
END_MESSAGE_MAP()


// M_C_detail 消息处理程序


BOOL M_C_detail::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_Row=-1;
	m_Col=-1;
	m_ok.LoadBitmaps(IDB_BITMAP36);
	m_ok.MoveWindow(813,12,32,32);//1,65,847,35
	m_cancel.LoadBitmaps(IDB_BITMAP62);
	m_cancel.MoveWindow(20,12,32,32);
	m_edit.MoveWindow(605,20,200,24);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
void M_C_detail::show()
{
	m_list.SetRedraw(0);
	m_list.DeleteAllItems();
	while(m_list.DeleteColumn(0));
	CRect rect(0,50,850,712);
	m_list.MoveWindow(rect);
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT| LVS_EX_GRIDLINES| LVS_EX_TWOCLICKACTIVATE | LVS_EX_TRACKSELECT /*自动换行*/| LVS_EX_FLATSB/*扁平滚动条*/ );
	m_list.SetTextBkColor(RGB(229,232,177));
	m_list.InsertColumn(0,"",LVCFMT_CENTER,rect.Width()/10-50,0);
	m_list.InsertColumn(1,"姓名",LVCFMT_CENTER,rect.Width()/5,1);
	m_list.InsertColumn(2,"联系方式",LVCFMT_CENTER,rect.Width()/5,2);
	m_list.InsertColumn(3,"联系地址",LVCFMT_CENTER,rect.Width()*3/10+50,3);
	m_list.InsertColumn(4,"发货物流",LVCFMT_CENTER,rect.Width()/5,4);
	//
	CString text;
	m_edit.GetWindowTextA(text);
	CString sql;
	if(text.IsEmpty())
		sql.Format("SELECT * FROM tally.customer;");
	else
		sql.Format("SELECT * FROM tally.customer where C_name like '%s%s%s' or C_phone like '%s%s%s' or C_address like '%s%s%s' or C_logistics like '%s%s%s';","%",text,"%","%",text,"%","%",text,"%","%",text,"%");
	//执行查询
	MYSQL_RES *m_result;
	mysql_query(&m_sqlCons,sql);
	m_result=mysql_use_result(&m_sqlCons);
	MYSQL_ROW row;
	int i=0;
	while((row=mysql_fetch_row(m_result)))
	{
		m_list.InsertItem(i,row[0]);
		m_list.SetItemText(i,1,row[1]);
		m_list.SetItemText(i,2,row[2]);
		m_list.SetItemText(i,3,row[3]);
		m_list.SetItemText(i,4,row[4]);
		i++;
	}
	mysql_free_result(m_result); //关联的内存会释放
	//
	m_list.SetRedraw(1);
	m_list.Invalidate();
}

void M_C_detail::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CDC mdc;
	mdc.CreateCompatibleDC(&dc);
	CBitmap m_back;
	m_back.CreateCompatibleBitmap(&dc,850,712);
	mdc.SelectObject(m_back);

	HDC hdc = mdc.GetSafeHdc();
	Graphics grphics(hdc);
	grphics.SetSmoothingMode(SmoothingModeHighQuality); //设置平滑画线

	grphics.FillRectangle(&SolidBrush(Color(255,255,255,255)),Rect(-1,-1,851,713));
	
	Pen p1(Color(255,210,210,210),3.0f);
	grphics.DrawRectangle(&p1,Rect(600,10,245,35));



	dc.StretchBlt(0,0,850,712,&mdc,0,0,850,712,SRCCOPY);
	//释放资源
	mdc.DeleteDC();
	m_back.DeleteObject();
	// 不为绘图消息调用 CDialogEx::OnPaint()
}


void M_C_detail::OnOk()
{
	show();
}


void M_C_detail::OnDelet()
{
	CString str;
	CString name;
	for(int i=0; i<m_list.GetItemCount();i++)
	{
		if( m_list.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED )
		{
			str=m_list.GetItemText(i,0);
			name=m_list.GetItemText(i,1);
			if(customer.delet(str))
			{
				//1.获取当前时间,插入历史记录
				GetLocalTime(&CurTime);////获取本地时间 
				h.time.Format("%d:%d:%d",CurTime.wHour,CurTime.wMinute,CurTime.wSecond);
				h.content="删除客户\n"+name;
				h.table="customer";
				h.tableId=atoi(str);
				h.add();
				//2.插入listcontrol
				m_ListCtrl.InsertItem(0,h.time);
				m_ListCtrl.SetItemText(0,1,h.content);
			}else{
				CString stri;
				stri.Format("%d",i+1);
				MessageBox("第"+stri+"行删除失败","提示",MB_ICONEXCLAMATION);
				break;
			}
		}
	}
	show();
}


void M_C_detail::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_LISTVIEW* pNMListView=(NM_LISTVIEW*)pNMHDR;
	CRect rc;
	m_Row = pNMListView->iItem;//获得选中的行
	m_Col = pNMListView->iSubItem;//获得选中列

	if   (pNMListView->iSubItem != 0 && pNMListView->iItem !=-1 )
	{
		m_list.GetSubItemRect(m_Row,m_Col,LVIR_LABEL,rc);//获得子项的RECT；
		rc.bottom=rc.bottom-1;
		m_edits.SetParent(&m_list);//转换坐标为列表框中的坐标
		m_edits.MoveWindow(rc);//移动Edit到RECT坐在的位置;
		m_edits.SetWindowText(m_list.GetItemText(m_Row,m_Col));//将该子项中的值放在Edit控件中；
		m_edits.ShowWindow(SW_SHOW);//显示Edit控件；
		m_edits.SetFocus();//设置Edit焦点
		m_edits.ShowCaret();//显示光标
		m_edits.SetSel(-1);//将光标移动到最后
		start_date=m_list.GetItemText(m_Row,m_Col);//还原初始数据
	}
	*pResult = 0;
}


void M_C_detail::OnEnKillfocusEdit2()
{
	CString tem;
	m_edits.GetWindowText(tem);    //得到用户输入的新的内容
	m_list.SetItemText(m_Row,m_Col,tem);   //设置编辑框的新内容
	m_edits.ShowWindow(SW_HIDE); //应藏编辑框
	CString sql;
	CString Id;
	Id=m_list.GetItemText(m_Row,0);
	customer.id=atoi(Id);	
	//1.获取当前时间,插入历史记录
	GetLocalTime(&CurTime);////获取本地时间 
	h.time.Format("%d:%d:%d",CurTime.wHour,CurTime.wMinute,CurTime.wSecond);
	if(m_Col==1&&tem!=start_date)
	{	
		sql.Format("update tally.customer set C_name='%s' where C_id=%s",tem,Id);
		if(customer.update(sql))
		{
			//1.插入历史记录
			h.content="编辑客户姓名\n"+start_date+"→"+m_list.GetItemText(m_Row,1);
			h.table="customer";
			h.tableId=customer.id;
			h.add();
			//2.插入listcontrol
			m_ListCtrl.InsertItem(0,h.time);
			m_ListCtrl.SetItemText(0,1,h.content);
			//3.更新
			show();		
		}else{
			MessageBox("修改失败","提示",MB_ICONEXCLAMATION);
		}
	}
	if(m_Col==2&&tem!=start_date)
	{
		sql.Format("update tally.customer set C_phone='%s' where C_id=%s",tem,Id);
		if(customer.update(sql))
		{
			//1.插入历史记录
			h.content="编辑客户联系方式\n"+m_list.GetItemText(m_Row,1)+"\n"+start_date+"→"+m_list.GetItemText(m_Row,2);
			h.table="customer";
			h.tableId=customer.id;
			h.add();
			//2.插入listcontrol
			m_ListCtrl.InsertItem(0,h.time);
			m_ListCtrl.SetItemText(0,1,h.content);
			//3.更新
			show();		
		}else{
			MessageBox("修改失败","提示",MB_ICONEXCLAMATION);
		}
	}
	if(m_Col==3&&tem!=start_date)
	{
		sql.Format("update tally.customer set C_address='%s' where C_id=%s",tem,Id);
		if(customer.update(sql))
		{
			//1.插入历史记录
			h.content="编辑客户联系地址\n"+m_list.GetItemText(m_Row,1)+"\n"+start_date+"→"+m_list.GetItemText(m_Row,3);
			h.table="customer";
			h.tableId=customer.id;
			h.add();
			//2.插入listcontrol
			m_ListCtrl.InsertItem(0,h.time);
			m_ListCtrl.SetItemText(0,1,h.content);
			//3.更新
			show();		
		}else{
			MessageBox("修改失败","提示",MB_ICONEXCLAMATION);
		}
	}
	if(m_Col==4&&tem!=start_date)
	{
		sql.Format("update tally.customer set C_logistics='%s' where C_id=%s",tem,Id);
		if(customer.update(sql))
		{
			//1.插入历史记录
			h.content="编辑客户发货物流\n"+m_list.GetItemText(m_Row,1)+"\n"+start_date+"→"+m_list.GetItemText(m_Row,4);
			h.table="customer";
			h.tableId=customer.id;
			h.add();
			//2.插入listcontrol
			m_ListCtrl.InsertItem(0,h.time);
			m_ListCtrl.SetItemText(0,1,h.content);
			//3.更新
			show();		
		}else{
			MessageBox("修改失败","提示",MB_ICONEXCLAMATION);
		}
	}
}
