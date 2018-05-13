// M_O_add.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CenterStar.h"
#include "M_O_add.h"
#include "afxdialogex.h"


// M_O_add �Ի���

IMPLEMENT_DYNAMIC(M_O_add, CDialogEx)

M_O_add::M_O_add(CWnd* pParent /*=NULL*/)
	: CDialogEx(M_O_add::IDD, pParent)
{

}

M_O_add::~M_O_add()
{
}

void M_O_add::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDOK, m_ok);
	DDX_Control(pDX, IDCANCEL, m_cancel);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
}


BEGIN_MESSAGE_MAP(M_O_add, CDialogEx)
	ON_WM_TIMER()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &M_O_add::OnNMDblclkList1)
	ON_EN_KILLFOCUS(IDC_EDIT1, &M_O_add::OnEnKillfocusEdit1)
	ON_BN_CLICKED(IDOK, &M_O_add::OnOk)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDCANCEL, &M_O_add::OnCancel)
END_MESSAGE_MAP()


// M_O_add ��Ϣ�������


BOOL M_O_add::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRect rect(0,30,850,668);
	m_list.MoveWindow(rect);
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT| LVS_EX_GRIDLINES| LVS_EX_TWOCLICKACTIVATE | LVS_EX_TRACKSELECT /*�Զ�����*/| LVS_EX_FLATSB/*��ƽ������*/ );
	m_list.InsertColumn(0,"",LVCFMT_CENTER,rect.Width()/12-50,0);
	m_list.InsertColumn(1,"Ʒ��",LVCFMT_CENTER,rect.Width()/6,1);
	m_list.InsertColumn(2,"�ͻ�",LVCFMT_CENTER,rect.Width()/6,2);
	m_list.InsertColumn(3,"����",LVCFMT_CENTER,rect.Width()*3/12+50,3);
	m_list.InsertColumn(4,"����",LVCFMT_CENTER,rect.Width()/6,4);
	m_list.InsertColumn(5,"��ע",LVCFMT_CENTER,rect.Width()/6,5);
	CString stri;
	for(int i=0;i<36;i++)
	{
		stri.Format("%d",i+1);
		m_list.InsertItem(i,stri);
	}
	SetTimer(1,200,NULL);
	GetDlgItem(IDOK)->MoveWindow(750,680,32,32);
	m_ok.LoadBitmaps(IDB_BITMAP39,IDB_BITMAP40,IDB_BITMAP41);
	m_ok.SizeToContent();  

	GetDlgItem(IDCANCEL)->MoveWindow(800,680,32,32);
	m_cancel.LoadBitmaps(IDB_BITMAP42);
	m_cancel.SizeToContent(); 

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void M_O_add::OnTimer(UINT_PTR nIDEvent)
{
	
	if (1==nIDEvent)  
     {
	     POINT p;  
		 GetCursorPos(&p);     
		 CWnd *hwnd;  
		 hwnd=WindowFromPoint(p);        //���������а���ָ���ĵ�;�����ָ����Ļ��������Ļ�ϵ�һ���㡣     
		 CWnd *hwnd1=GetDlgItem(IDOK);  
		 if (hwnd1 == hwnd)         //�������ڰ�ť��  
		 {  
			 if (GetFocus()!=hwnd1)        
				 hwnd1->SetFocus() ;  
		 }  
		 else          //�����겻�ڰ�ť�ϣ�  
		 {  
			 if (GetFocus() == hwnd1 )                   
				 GetDlgItem(IDCANCEL)->SetFocus();      
		 } 
	}
	CDialogEx::OnTimer(nIDEvent);
}


void M_O_add::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_LISTVIEW* pNMListView=(NM_LISTVIEW*)pNMHDR;
	CRect rc;
	m_Row = pNMListView->iItem;//���ѡ�е���
	m_Col = pNMListView->iSubItem;//���ѡ����

	if(pNMListView->iSubItem != 0)
	{
		m_list.GetSubItemRect(m_Row,m_Col,LVIR_LABEL,rc);//��������RECT��
		rc.left=rc.left+1;
		rc.bottom=rc.bottom-1;
		m_edit.SetParent(&m_list);//ת������Ϊ�б���е�����
		m_edit.MoveWindow(rc);//�ƶ�Edit��RECT���ڵ�λ��;
		m_edit.SetWindowText(m_list.GetItemText(m_Row,m_Col));//���������е�ֵ����Edit�ؼ��У�
		m_edit.ShowWindow(SW_SHOW);//��ʾEdit�ؼ���
		m_edit.SetFocus();//����Edit����
		m_edit.ShowCaret();//��ʾ���
		m_edit.SetSel(-1);//������ƶ������
		//start_date=m_list.GetItemText(m_Row,m_Col);//��ԭ��ʼ����
	}
	*pResult = 0;
}


void M_O_add::OnEnKillfocusEdit1()
{
	CString tem;
	m_edit.GetWindowText(tem);    //�õ��û�������µ�����
	m_list.SetItemText(m_Row,m_Col,tem);   //���ñ༭���������
	m_edit.ShowWindow(SW_HIDE); //Ӧ�ر༭��
}


void M_O_add::OnOk()
{
	CString name;//Ʒ�� �ͻ� ���� ���� ��ע
	for(int i=0;i<36;i++)
	{
		if( !( name=m_list.GetItemText(i,1) ).IsEmpty() )
		{
			p.id=0;
			p.name=name;
			p=p.select(p);
			order.goodsId=p.id;//1
			customer.id=0;
			customer.name=m_list.GetItemText(i,2);
			CString sql;
			sql.Format("SELECT * FROM tally.customer where C_name='%s';",customer.name);
			customer=customer.select(customer,sql);
			order.customerId=customer.id;//2
			order.number=atof(m_list.GetItemText(i,3));//3
			order.remark=m_list.GetItemText(i,5);//4
			order.profit=atof(m_list.GetItemText(i,4));//5
			if(order.goodsId!=0&&order.customerId!=0)
			{
				//�Ƿ�����С�ڿ��
				if(order.number<=p.kc)
				{
					if(order.add())
					{
						CString Kc,Id;
						Kc.Format("%.2f",p.kc-order.number);
						Id.Format("%d",p.id);
						p.updateKc(Kc,Id);

						CString sql;
						sql.Format("SELECT * FROM tally.orders");
						order=order.select(order,sql);
						//1.��ȡ��ǰʱ��,������ʷ��¼
						GetLocalTime(&CurTime);////��ȡ����ʱ�� 
						h.time.Format("%d:%d:%d",CurTime.wHour,CurTime.wMinute,CurTime.wSecond);
						h.content="�ͻ�:"+customer.name+"\n���ɶ���"+name+"\n����:"+m_list.GetItemText(i,3);
						h.table="orders";
						h.tableId=order.id;
						h.add();
						//2.����listcontrol
						m_ListCtrl.InsertItem(0,h.time);
						m_ListCtrl.SetItemText(0,1,h.content);
						//��ձ�
						m_list.SetItemText(i,1,"");
						m_list.SetItemText(i,2,"");
						m_list.SetItemText(i,3,"");
						m_list.SetItemText(i,4,"");
						m_list.SetItemText(i,5,"");
					}else{
						MessageBox(name+"�������ʧ��","��ʾ",MB_ICONEXCLAMATION);
					}
				}else{
					MessageBox(name+"�������ʧ��,��治�������ɸ���������","��ʾ",MB_ICONEXCLAMATION);
				}
			
			}else{
				if(order.goodsId==0)
					MessageBox(name+"���ʧ��,�����ڸò�Ʒ","��ʾ",MB_ICONEXCLAMATION);
				else
					MessageBox("���ʧ�ܡ�"+m_list.GetItemText(i,2)+"�������ڸÿͻ�","��ʾ",MB_ICONEXCLAMATION);
			}
		}
	}
}


void M_O_add::OnPaint()
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
	grphics.SetSmoothingMode(SmoothingModeHighQuality); //����ƽ������
	grphics.FillRectangle(&SolidBrush(Color(255,255,255,255)),Rect(-1,-1,851,713));
	Gdiplus::Font fbig(L"��Բ", 14);
	string=T2W((LPCTSTR)"���ɶ���"); 
	grphics.DrawString(string,-1,&fbig,PointF(0,5),&SolidBrush(Color(255,0,0,0)));

	
	
	dc.StretchBlt(0,0,850,712,&mdc,0,0,850,712,SRCCOPY);
	//�ͷ���Դ
	m_back.DeleteObject();
	mdc.DeleteDC();
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
}


void M_O_add::OnCancel()
{
	for(int i=0;i<36;i++)
	{
		//��ձ�
		m_list.SetItemText(i,1,"");
		m_list.SetItemText(i,2,"");
		m_list.SetItemText(i,3,"");
		m_list.SetItemText(i,4,"");
		m_list.SetItemText(i,5,"");
	}
}
