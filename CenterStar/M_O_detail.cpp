// M_O_detail.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CenterStar.h"
#include "M_O_detail.h"
#include "afxdialogex.h"


// M_O_detail �Ի���

IMPLEMENT_DYNAMIC(M_O_detail, CDialogEx)

M_O_detail::M_O_detail(CWnd* pParent /*=NULL*/)
	: CDialogEx(M_O_detail::IDD, pParent)
{

}

M_O_detail::~M_O_detail()
{
}

void M_O_detail::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_LIST2, m_lists);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_d1);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_d2);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
	DDX_Control(pDX, IDC_EDIT2, m_edits);
}


BEGIN_MESSAGE_MAP(M_O_detail, CDialogEx)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_CTLCOLOR()
	ON_NOTIFY(NM_RCLICK, IDC_LIST2, &M_O_detail::OnNMRClickList2)
	ON_COMMAND(ID_32772, &M_O_detail::On32772)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST2, &M_O_detail::OnNMDblclkList2)
	ON_EN_KILLFOCUS(IDC_EDIT2, &M_O_detail::OnEnKillfocusEdit2)
END_MESSAGE_MAP()


// M_O_detail ��Ϣ�������


BOOL M_O_detail::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	orderNum=0;
	changeColor=false;
	m_Row=-1;
	m_Col=-1;

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
void M_O_detail::show()
{

	CRect rects(0,400,850,712);
	m_lists.MoveWindow(rects);
	m_d1.MoveWindow(rects.left+5,rects.top-30,100,20);
	m_d2.MoveWindow(rects.left+110,rects.top-30,100,20);
	GetDlgItem(IDC_RADIO1)->MoveWindow(rects.left+220,rects.top-30,80,20);
	GetDlgItem(IDC_RADIO2)->MoveWindow(rects.left+310,rects.top-30,80,20); 
	m_edit.MoveWindow(rects.left+400,rects.top-30,200,20);

	m_list.SetRedraw(0);
	m_list.DeleteAllItems();
	while(m_list.DeleteColumn(0));
	CRect rect(0,30,850,325);
	m_list.MoveWindow(rect);
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT| LVS_EX_GRIDLINES| LVS_EX_TWOCLICKACTIVATE | LVS_EX_TRACKSELECT /*�Զ�����*/| LVS_EX_FLATSB/*��ƽ������*/ );
	m_list.InsertColumn(0,"",LVCFMT_CENTER,rect.Width()/12-50,0);
	m_list.InsertColumn(1,"Ʒ��",LVCFMT_CENTER,rect.Width()/6,1);
	m_list.InsertColumn(2,"�ͻ�",LVCFMT_CENTER,rect.Width()/6,2);
	m_list.InsertColumn(3,"����",LVCFMT_CENTER,rect.Width()*3/12+50,3);
	m_list.InsertColumn(4,"����",LVCFMT_CENTER,rect.Width()/6,4);
	m_list.InsertColumn(5,"��ע",LVCFMT_CENTER,rect.Width()/6,5);
	//1.��ȡ��ǰʱ��,������ʷ��¼
	GetLocalTime(&CurTime);////��ȡ����ʱ�� 
	year.Format("%d",CurTime.wYear);
	CString time;
	CString m,d;
	if(CurTime.wMonth<10)
		m.Format("0%d",CurTime.wMonth);
	else
		m.Format("%d",CurTime.wMonth);
	if(CurTime.wDay<10)
		d.Format("0%d",CurTime.wDay);
	else
		d.Format("%d",CurTime.wDay);
	time.Format("%d",CurTime.wYear);
	time=time+"-"+m+"-"+d;

	CString sql;
	sql.Format("SELECT * FROM tally.orders where O_time>='%s' and O_time<=now();",time);
	MYSQL_RES *m_result;
	mysql_query(&m_sqlCons,sql);
	m_result=mysql_use_result(&m_sqlCons);
	MYSQL_ROW rows;
	CString csql,goodsid;
	if(orderNum!=0)
		delete [orderNum]oder;
	orderNum=0;
	while((rows=mysql_fetch_row(m_result)))
	{
		m_list.InsertItem(orderNum,rows[0]);	
		orderNum++;
	}
	mysql_free_result(m_result); //�������ڴ���ͷ�

	oder=new Order[orderNum];

	mysql_query(&m_sqlCons,sql);
	m_result=mysql_use_result(&m_sqlCons);
	int i=0;
	CString cid;
	while((rows=mysql_fetch_row(m_result)))
	{
		oder[i].id=atoi(rows[0]);
		oder[i].time=rows[1];
		oder[i].goodsId=atoi(rows[2]);
		oder[i].customerId=atoi(rows[3]);
		oder[i].number=atof(rows[4]);
		oder[i].remark=rows[5];
		oder[i].profit=atof(rows[6]);

		m_list.SetItemText(i,3,rows[4]);
		m_list.SetItemText(i,4,rows[6]);
		m_list.SetItemText(i,5,rows[5]);
		i++;
	}
	mysql_free_result(m_result); //�������ڴ���ͷ�


	for(int i=0;i<orderNum;i++)
	{
		p.id=oder[i].goodsId;
		p=p.selectId(p);
		m_list.SetItemText(i,1,p.name);

		customer.id=oder[i].customerId;
		customer=customer.selectId(customer);
		m_list.SetItemText(i,2,customer.name);
	}
	m_list.SetRedraw(1);
	m_list.Invalidate();
}

void M_O_detail::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CDC mdc;
	CBitmap m_back;
	mdc.CreateCompatibleDC(&dc);
	m_back.CreateCompatibleBitmap(&dc,850,712);
	mdc.SelectObject(&m_back);
	USES_CONVERSION;
	WCHAR *string;
	HDC hdc = mdc.GetSafeHdc();
	Graphics grphics(hdc);
	grphics.SetSmoothingMode(SmoothingModeHighQuality); //����ƽ������
	grphics.FillRectangle(&SolidBrush(Color(255,255,255,255)),Rect(-1,-1,851,713));
	Gdiplus::Font fbig(L"��Բ", 14);
	Gdiplus::Font f(L"��Բ", 10);
	string=T2W((LPCTSTR)"���충��"); 
	grphics.DrawString(string,-1,&fbig,PointF(0,5),&SolidBrush(Color(255,0,0,0)));
	
	string=T2W((LPCTSTR)"������¼"+year); //���һ��
	grphics.DrawString(string,-1,&fbig,PointF(0,345),&SolidBrush(Color(255,0,0,0)));
	
	Pen p1(Color(100,45,85,211),2.0f); //
	grphics.DrawRectangle(&p1,Rect(399,369,200,21));
	grphics.DrawRectangle(&p1,Rect(600,369,50,21));
	if(changeColor)
		grphics.FillRectangle(&SolidBrush(Color(200,45,85,211)),Rect(600,369,50,21));
	else
		grphics.FillRectangle(&SolidBrush(Color(100,45,85,211)),Rect(600,369,50,21));
	string = T2W((LPCTSTR)"ͳ��");
	grphics.DrawString(string,-1,&f,PointF(608.0f,373.0f),&SolidBrush(Color(200,0,255,255)));
	
	
	dc.StretchBlt(0,0,850,712,&mdc,0,0,850,712,SRCCOPY);
	//�ͷ���Դ
	m_back.DeleteObject();
	mdc.DeleteDC();

	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
}


void M_O_detail::OnMouseMove(UINT nFlags, CPoint point)
{
	CRect retur(600,370,650,390);
	if(retur.PtInRect(point))
	{
		changeColor=true;
		InvalidateRect(retur,0);
	}else{
		changeColor=false;
		InvalidateRect(retur,0);
	}

	CDialogEx::OnMouseMove(nFlags, point);
}


void M_O_detail::OnLButtonDown(UINT nFlags, CPoint point)
{
	CRect retur(600,370,650,390);
	if(retur.PtInRect(point))
	{
		CString stime,etime;
		CTime tm;
		m_d1.GetTime(tm);
		stime=tm.Format("%Y-%m-%d");
		m_d2.GetTime(tm);
		
		etime=tm.Format("%Y-%m-%d");
		etime=etime+" 23:59:59";

		CButton *p1=(CButton *)GetDlgItem(IDC_RADIO1);
		CButton *p2=(CButton *)GetDlgItem(IDC_RADIO2);
		CString str;
		m_edit.GetWindowTextA(str);
		if(p1->GetCheck())
		{
			CString sql;
			if(str.IsEmpty())
				sql.Format("SELECT * FROM tally.orders where O_time>='%s' and O_time<='%s' order by O_goodsId asc ",stime,etime);
			else
			{
				p.id=0;
				p.name=str;
				p=p.select(p);
				CString strid;
				strid.Format("%d",p.id);
				sql.Format("SELECT * FROM tally.orders where O_time>='%s' and O_time<='%s' and O_remark like '%s%s%s' or O_goodsId=%s order by O_goodsId asc ",stime,etime,"%",str,"%",strid);
			}
			shownext(sql);
		}
		else if(p2->GetCheck())
		{
			CString sql;
			if(str.IsEmpty())
				sql.Format("SELECT * FROM tally.orders where O_time>='%s' and O_time<='%s' order by O_customerId asc ",stime,etime);
			else
			{
				customer.id=0;
				customer.name=str;
				CString cstrsql;
				cstrsql.Format("SELECT * FROM tally.customer where C_name='%s';",customer.name);
				customer=customer.select(customer,cstrsql);
				CString strid;
				strid.Format("%d",customer.id);
				sql.Format("SELECT * FROM tally.orders where O_time>='%s' and O_time<='%s' and O_remark like '%s%s%s' or O_customerId=%s order by O_customerId asc ",stime,etime,"%",str,"%",strid);
			}
			shownext(sql);
		}
		else
		{
			CString sql;
			if(str.IsEmpty())
				sql.Format("SELECT * FROM tally.orders where O_time>='%s' and O_time<='%s' ",stime,etime);
			else
				sql.Format("SELECT * FROM tally.orders where O_time>='%s' and O_time<='%s' and O_remark like '%s%s%s' ",stime,etime,"%",str,"%");
			shownext(sql);
		}
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}
void M_O_detail::shownext(CString sql)
{
	CRect rect(0,400,850,712);
	m_lists.MoveWindow(rect);
	
	m_lists.SetRedraw(0);
	m_lists.DeleteAllItems();
	while(m_lists.DeleteColumn(0));
	m_lists.SetExtendedStyle(LVS_EX_FULLROWSELECT| LVS_EX_GRIDLINES| LVS_EX_TWOCLICKACTIVATE | LVS_EX_TRACKSELECT /*�Զ�����*/| LVS_EX_FLATSB/*��ƽ������*/ );
	m_lists.InsertColumn(0,"",LVCFMT_CENTER,rect.Width()/12-50,0);
	m_lists.InsertColumn(1,"Ʒ��",LVCFMT_CENTER,rect.Width()/6,1);
	m_lists.InsertColumn(2,"�ͻ�",LVCFMT_CENTER,rect.Width()/6,2);
	m_lists.InsertColumn(3,"����",LVCFMT_CENTER,rect.Width()*3/12+50,3);
	m_lists.InsertColumn(4,"����",LVCFMT_CENTER,rect.Width()/6,4);
	m_lists.InsertColumn(5,"��ע",LVCFMT_CENTER,rect.Width()/6,5);

	MYSQL_RES *m_result;
	mysql_query(&m_sqlCons,sql);
	m_result=mysql_use_result(&m_sqlCons);
	MYSQL_ROW rows;
	CString csql,goodsid;
	if(orderNum!=0)
		delete [orderNum]oder;
	orderNum=0;
	while((rows=mysql_fetch_row(m_result)))
	{
		m_lists.InsertItem(orderNum,rows[0]);	
		orderNum++;
	}
	mysql_free_result(m_result); //�������ڴ���ͷ�

	oder=new Order[orderNum];

	mysql_query(&m_sqlCons,sql);
	m_result=mysql_use_result(&m_sqlCons);
	int i=0;
	CString cid,lr;
	double Lr=0;
	while((rows=mysql_fetch_row(m_result)))
	{
		oder[i].id=atoi(rows[0]);
		oder[i].time=rows[1];
		oder[i].goodsId=atoi(rows[2]);
		oder[i].customerId=atoi(rows[3]);
		oder[i].number=atof(rows[4]);
		oder[i].remark=rows[5];
		oder[i].profit=atof(rows[6]);

		m_lists.SetItemText(i,3,rows[4]);
		m_lists.SetItemText(i,4,rows[6]);
		m_lists.SetItemText(i,5,rows[5]);
		Lr=Lr+atof(rows[6]);
		i++;
	}
	lr.Format("%.2f",Lr);
	m_lists.InsertItem(i,"");
	m_lists.SetItemText(i,1,"�ܼ�");
	m_lists.SetItemText(i,4,lr);
	mysql_free_result(m_result); //�������ڴ���ͷ�


	for(int i=0;i<orderNum;i++)
	{
		p.id=oder[i].goodsId;
		p=p.selectId(p);
		m_lists.SetItemText(i,1,p.name);

		customer.id=oder[i].customerId;
		customer=customer.selectId(customer);
		m_lists.SetItemText(i,2,customer.name);
	}
	m_lists.SetRedraw(1);
	m_lists.Invalidate();
}

HBRUSH M_O_detail::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if ((pWnd->GetDlgCtrlID() == (IDC_RADIO1))||(pWnd->GetDlgCtrlID() == (IDC_RADIO2)) )
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0,0,0));
		CFont f;
		f.CreatePointFont(140,"����");
		pDC->SelectObject(&f);
		return HBRUSH(GetStockObject(HOLLOW_BRUSH));
	}
	return hbr;
}


void M_O_detail::OnNMRClickList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if(pNMListView->iItem != -1)
	{
		DWORD dwPos = GetMessagePos();
		CPoint point( LOWORD(dwPos), HIWORD(dwPos) );
		CMenu menu;
		VERIFY( menu.LoadMenu( IDR_MENU1 ) );
		CMenu* popup = menu.GetSubMenu(0);
		ASSERT( popup != NULL );
		popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this );	
	} 
	*pResult = 0;
}


void M_O_detail::On32772()
{
	for(int i=0; i<m_lists.GetItemCount();i++)
	{
		if( m_lists.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED )
		{
			CString sql;
			int Id;
			Id=atoi(m_lists.GetItemText(i,0));
			sql.Format("DELETE FROM tally.orders where O_id=%s",m_lists.GetItemText(i,0));
			if(order.delet(sql))
			{
				//1.��ȡ��ǰʱ��,������ʷ��¼
				GetLocalTime(&CurTime);////��ȡ����ʱ�� 
				h.time.Format("%d:%d:%d",CurTime.wHour,CurTime.wMinute,CurTime.wSecond);
				h.content="ɾ������\n��Ʒ"+m_lists.GetItemText(i,1)+"��һ��\n"+"��¼";
				h.table="orders";
				h.tableId=Id;
				h.add();
				//2.����listcontrol
				m_ListCtrl.InsertItem(0,h.time);
				m_ListCtrl.SetItemText(0,1,h.content);
				//3.���±�
				m_lists.DeleteItem(i);
			}else{
				CString stri;
				stri.Format("%d",i+1);
				MessageBox("��"+stri+"��ɾ��ʧ��","��ʾ",MB_ICONEXCLAMATION);
				break;
			}
		}
	}
}


void M_O_detail::OnNMDblclkList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_LISTVIEW* pNMListView=(NM_LISTVIEW*)pNMHDR;
	CRect rc;
	m_Row = pNMListView->iItem;//���ѡ�е���
	m_Col = pNMListView->iSubItem;//���ѡ����

	if   (pNMListView->iSubItem != 0 && pNMListView->iItem !=-1 && pNMListView->iItem !=m_lists.GetItemCount()-1 )
	{
		m_lists.GetSubItemRect(m_Row,m_Col,LVIR_LABEL,rc);//��������RECT��
		rc.bottom=rc.bottom-1;
		m_edits.SetParent(&m_lists);//ת������Ϊ�б���е�����
		m_edits.MoveWindow(rc);//�ƶ�Edit��RECT���ڵ�λ��;
		m_edits.SetWindowText(m_lists.GetItemText(m_Row,m_Col));//���������е�ֵ����Edit�ؼ��У�
		m_edits.ShowWindow(SW_SHOW);//��ʾEdit�ؼ���
		m_edits.SetFocus();//����Edit����
		m_edits.ShowCaret();//��ʾ���
		m_edits.SetSel(-1);//������ƶ������
		start_date=m_lists.GetItemText(m_Row,m_Col);//��ԭ��ʼ����
	}
	*pResult = 0;
}


void M_O_detail::OnEnKillfocusEdit2()
{
	CString tem;
	m_edits.GetWindowText(tem);    //�õ��û�������µ�����
	m_lists.SetItemText(m_Row,m_Col,tem);   //���ñ༭���������
	m_edits.ShowWindow(SW_HIDE); //Ӧ�ر༭��
	CString sql;
	CString Id;
	Id.Format("%d",m_lists.GetItemText(m_Row,0));
	//if(m_Col==1&&tem!=start_date)
}
