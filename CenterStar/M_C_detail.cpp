// M_C_detail.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CenterStar.h"
#include "M_C_detail.h"
#include "afxdialogex.h"


// M_C_detail �Ի���

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


// M_C_detail ��Ϣ�������


BOOL M_C_detail::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_Row=-1;
	m_Col=-1;
	m_ok.LoadBitmaps(IDB_BITMAP36);
	m_ok.MoveWindow(813,12,32,32);//1,65,847,35
	m_cancel.LoadBitmaps(IDB_BITMAP62);
	m_cancel.MoveWindow(20,12,32,32);
	m_edit.MoveWindow(605,20,200,24);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
void M_C_detail::show()
{
	m_list.SetRedraw(0);
	m_list.DeleteAllItems();
	while(m_list.DeleteColumn(0));
	CRect rect(0,50,850,712);
	m_list.MoveWindow(rect);
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT| LVS_EX_GRIDLINES| LVS_EX_TWOCLICKACTIVATE | LVS_EX_TRACKSELECT /*�Զ�����*/| LVS_EX_FLATSB/*��ƽ������*/ );
	m_list.SetTextBkColor(RGB(229,232,177));
	m_list.InsertColumn(0,"",LVCFMT_CENTER,rect.Width()/10-50,0);
	m_list.InsertColumn(1,"����",LVCFMT_CENTER,rect.Width()/5,1);
	m_list.InsertColumn(2,"��ϵ��ʽ",LVCFMT_CENTER,rect.Width()/5,2);
	m_list.InsertColumn(3,"��ϵ��ַ",LVCFMT_CENTER,rect.Width()*3/10+50,3);
	m_list.InsertColumn(4,"��������",LVCFMT_CENTER,rect.Width()/5,4);
	//
	CString text;
	m_edit.GetWindowTextA(text);
	CString sql;
	if(text.IsEmpty())
		sql.Format("SELECT * FROM tally.customer;");
	else
		sql.Format("SELECT * FROM tally.customer where C_name like '%s%s%s' or C_phone like '%s%s%s' or C_address like '%s%s%s' or C_logistics like '%s%s%s';","%",text,"%","%",text,"%","%",text,"%","%",text,"%");
	//ִ�в�ѯ
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
	mysql_free_result(m_result); //�������ڴ���ͷ�
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
	grphics.SetSmoothingMode(SmoothingModeHighQuality); //����ƽ������

	grphics.FillRectangle(&SolidBrush(Color(255,255,255,255)),Rect(-1,-1,851,713));
	
	Pen p1(Color(255,210,210,210),3.0f);
	grphics.DrawRectangle(&p1,Rect(600,10,245,35));



	dc.StretchBlt(0,0,850,712,&mdc,0,0,850,712,SRCCOPY);
	//�ͷ���Դ
	mdc.DeleteDC();
	m_back.DeleteObject();
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
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
				//1.��ȡ��ǰʱ��,������ʷ��¼
				GetLocalTime(&CurTime);////��ȡ����ʱ�� 
				h.time.Format("%d:%d:%d",CurTime.wHour,CurTime.wMinute,CurTime.wSecond);
				h.content="ɾ���ͻ�\n"+name;
				h.table="customer";
				h.tableId=atoi(str);
				h.add();
				//2.����listcontrol
				m_ListCtrl.InsertItem(0,h.time);
				m_ListCtrl.SetItemText(0,1,h.content);
			}else{
				CString stri;
				stri.Format("%d",i+1);
				MessageBox("��"+stri+"��ɾ��ʧ��","��ʾ",MB_ICONEXCLAMATION);
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
	m_Row = pNMListView->iItem;//���ѡ�е���
	m_Col = pNMListView->iSubItem;//���ѡ����

	if   (pNMListView->iSubItem != 0 && pNMListView->iItem !=-1 )
	{
		m_list.GetSubItemRect(m_Row,m_Col,LVIR_LABEL,rc);//��������RECT��
		rc.bottom=rc.bottom-1;
		m_edits.SetParent(&m_list);//ת������Ϊ�б���е�����
		m_edits.MoveWindow(rc);//�ƶ�Edit��RECT���ڵ�λ��;
		m_edits.SetWindowText(m_list.GetItemText(m_Row,m_Col));//���������е�ֵ����Edit�ؼ��У�
		m_edits.ShowWindow(SW_SHOW);//��ʾEdit�ؼ���
		m_edits.SetFocus();//����Edit����
		m_edits.ShowCaret();//��ʾ���
		m_edits.SetSel(-1);//������ƶ������
		start_date=m_list.GetItemText(m_Row,m_Col);//��ԭ��ʼ����
	}
	*pResult = 0;
}


void M_C_detail::OnEnKillfocusEdit2()
{
	CString tem;
	m_edits.GetWindowText(tem);    //�õ��û�������µ�����
	m_list.SetItemText(m_Row,m_Col,tem);   //���ñ༭���������
	m_edits.ShowWindow(SW_HIDE); //Ӧ�ر༭��
	CString sql;
	CString Id;
	Id=m_list.GetItemText(m_Row,0);
	customer.id=atoi(Id);	
	//1.��ȡ��ǰʱ��,������ʷ��¼
	GetLocalTime(&CurTime);////��ȡ����ʱ�� 
	h.time.Format("%d:%d:%d",CurTime.wHour,CurTime.wMinute,CurTime.wSecond);
	if(m_Col==1&&tem!=start_date)
	{	
		sql.Format("update tally.customer set C_name='%s' where C_id=%s",tem,Id);
		if(customer.update(sql))
		{
			//1.������ʷ��¼
			h.content="�༭�ͻ�����\n"+start_date+"��"+m_list.GetItemText(m_Row,1);
			h.table="customer";
			h.tableId=customer.id;
			h.add();
			//2.����listcontrol
			m_ListCtrl.InsertItem(0,h.time);
			m_ListCtrl.SetItemText(0,1,h.content);
			//3.����
			show();		
		}else{
			MessageBox("�޸�ʧ��","��ʾ",MB_ICONEXCLAMATION);
		}
	}
	if(m_Col==2&&tem!=start_date)
	{
		sql.Format("update tally.customer set C_phone='%s' where C_id=%s",tem,Id);
		if(customer.update(sql))
		{
			//1.������ʷ��¼
			h.content="�༭�ͻ���ϵ��ʽ\n"+m_list.GetItemText(m_Row,1)+"\n"+start_date+"��"+m_list.GetItemText(m_Row,2);
			h.table="customer";
			h.tableId=customer.id;
			h.add();
			//2.����listcontrol
			m_ListCtrl.InsertItem(0,h.time);
			m_ListCtrl.SetItemText(0,1,h.content);
			//3.����
			show();		
		}else{
			MessageBox("�޸�ʧ��","��ʾ",MB_ICONEXCLAMATION);
		}
	}
	if(m_Col==3&&tem!=start_date)
	{
		sql.Format("update tally.customer set C_address='%s' where C_id=%s",tem,Id);
		if(customer.update(sql))
		{
			//1.������ʷ��¼
			h.content="�༭�ͻ���ϵ��ַ\n"+m_list.GetItemText(m_Row,1)+"\n"+start_date+"��"+m_list.GetItemText(m_Row,3);
			h.table="customer";
			h.tableId=customer.id;
			h.add();
			//2.����listcontrol
			m_ListCtrl.InsertItem(0,h.time);
			m_ListCtrl.SetItemText(0,1,h.content);
			//3.����
			show();		
		}else{
			MessageBox("�޸�ʧ��","��ʾ",MB_ICONEXCLAMATION);
		}
	}
	if(m_Col==4&&tem!=start_date)
	{
		sql.Format("update tally.customer set C_logistics='%s' where C_id=%s",tem,Id);
		if(customer.update(sql))
		{
			//1.������ʷ��¼
			h.content="�༭�ͻ���������\n"+m_list.GetItemText(m_Row,1)+"\n"+start_date+"��"+m_list.GetItemText(m_Row,4);
			h.table="customer";
			h.tableId=customer.id;
			h.add();
			//2.����listcontrol
			m_ListCtrl.InsertItem(0,h.time);
			m_ListCtrl.SetItemText(0,1,h.content);
			//3.����
			show();		
		}else{
			MessageBox("�޸�ʧ��","��ʾ",MB_ICONEXCLAMATION);
		}
	}
}
