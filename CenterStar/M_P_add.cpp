// M_P_add.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CenterStar.h"
#include "M_P_add.h"
#include "afxdialogex.h"



// M_P_add �Ի���

IMPLEMENT_DYNAMIC(M_P_add, CDialogEx)

M_P_add::M_P_add(CWnd* pParent /*=NULL*/)
	: CDialogEx(M_P_add::IDD, pParent)
{
}

M_P_add::~M_P_add()
{
	delete p0;
	delete p1;
	delete p2;
	delete p3;
}

void M_P_add::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, e_name);
	DDX_Control(pDX, IDC_EDIT2, e_price);
	DDX_Control(pDX, IDC_EDIT3, e_unit);
	DDX_Control(pDX, IDC_EDIT4, e_kc);
	DDX_Control(pDX, IDC_EDIT5, e_content);
	DDX_Control(pDX, IDOK, M_OK);
	DDX_Control(pDX, IDCANCEL, m_cancel);
	DDX_Control(pDX, IDC_remove, m_remove);
}


BEGIN_MESSAGE_MAP(M_P_add, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDCANCEL, &M_P_add::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &M_P_add::OnBnClickedOk)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_remove, &M_P_add::OnRemove)
	ON_WM_LBUTTONDOWN()
	ON_STN_CLICKED(IDC_addpic, &M_P_add::OnStnClickedaddpic)
END_MESSAGE_MAP()


// M_P_add ��Ϣ�������


BOOL M_P_add::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	_initButton();
	_initEdit();
	SetTimer(1,200,NULL); 
	num=0;
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void M_P_add::_initButton()
{
	CRect rects(600,29,632,61);
	m_remove.MoveWindow(rects);
	m_remove.LoadBitmaps(IDB_BITMAP43);

	GetDlgItem(IDOK)->MoveWindow(750,400,32,32);
	M_OK.LoadBitmaps(IDB_BITMAP39,IDB_BITMAP40,IDB_BITMAP41);
	M_OK.SizeToContent();  
	
	GetDlgItem(IDCANCEL)->MoveWindow(800,400,32,32);
	m_cancel.LoadBitmaps(IDB_BITMAP42);
	m_cancel.SizeToContent();  
}
void M_P_add:: _initEdit()
{
	e_name.MoveWindow(330,30,265,30);
	e_price.MoveWindow(330,70,300,30);
	e_kc.MoveWindow(330,110,300,30);
	e_unit.MoveWindow(330,150,300,30);
	e_content.MoveWindow(20,275,810,100);
	e_name.SetWindowTextA("�������Ʒ����");
	e_price.SetWindowTextA("�������Ʒ����");
	e_unit.SetWindowTextA("�����뵥λ,��:��/��/�׵�");
	e_kc.SetWindowTextA("�������Ʒ���");
	e_content.SetWindowTextA("�������Ʒ��Ϣ(��100��)");
	CRect rect(20,20,221,221);
	GetDlgItem(IDC_addpic)->MoveWindow(rect);
	
	if(NULL == p0.GetSafeHwnd())
		p0.Create(_T( "" ), WS_BORDER | WS_EX_TRANSPARENT|WS_CHILD | WS_VISIBLE  | SS_BITMAP| SS_CENTERIMAGE, CRect (20,450,221,651), this,IDC_PIC);
	if(NULL == p1.GetSafeHwnd())
		p1.Create(_T( "" ), WS_BORDER | WS_EX_TRANSPARENT|WS_CHILD | WS_VISIBLE  | SS_BITMAP| SS_CENTERIMAGE, CRect (230,450,431,651), this,IDC_PIC+1);
			
	if(NULL ==p2.GetSafeHwnd())
		p2.Create(_T( "" ), WS_BORDER | WS_EX_TRANSPARENT|WS_CHILD | WS_VISIBLE  | SS_BITMAP| SS_CENTERIMAGE, CRect (440,450,641,651), this,IDC_PIC+2);
	if(NULL ==p3.GetSafeHwnd())
		p3.Create(_T( "" ), WS_BORDER | WS_EX_TRANSPARENT|WS_CHILD | WS_VISIBLE  | SS_BITMAP| SS_CENTERIMAGE, CRect (649,450,850,651), this,IDC_PIC+3);
	p1.ShowWindow(0);
	p2.ShowWindow(0);
	p3.ShowWindow(0);
	p0.ShowWindow(0);
}
void M_P_add::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CBitmap m_Back;
	m_Back.LoadBitmap(IDB_BITMAP37);
	CDC mdc;
	mdc.CreateCompatibleDC(&dc); 
	mdc.SelectObject(&m_Back);
	dc.BitBlt(0,0,850,712,&mdc,0,0,SRCCOPY);

	if (!strFilePath.IsEmpty())
    {
		CRect rc;
		GetDlgItem(IDC_addpic)->GetClientRect(rc);
		CImage image;
		image.Load(strFilePath); //ͼƬ�ļ�·��
		
		CDC* dcs;
		dcs = GetDlgItem(IDC_addpic)->GetDC();
		double x,y;
		if(image.GetWidth()<200||image.GetHeight()<200){
			//MessageBox("ͼƬС��200X200���������������","��ʾ");
		}else{
			if(image.GetWidth()>=image.GetHeight())
			{
				double IndexWH=(double) image.GetWidth()/(double)200; 
				x=200;
				y=(double)image.GetHeight()/(double)IndexWH; 

				CStatic* pStatic = (CStatic*)GetDlgItem(IDC_addpic);
				CRect lRect;
				pStatic->GetClientRect(&lRect);
				pStatic->GetDC()->FillSolidRect(lRect.left+1 ,lRect.top+1 ,lRect.Width()-2,lRect.Height()/2-y/2, RGB(255, 255, 255));//��
				pStatic->GetDC()->FillSolidRect(lRect.left+1 ,lRect.Height()/2+y/2-1 ,lRect.Width()-2,lRect.Height()/2+1-y/2, RGB(255, 255, 255));//��
			}else	{
				double IndexWH=(double) image.GetHeight()/(double)200;
				y=200;
				x=(double)image.GetWidth()/(double)IndexWH;

				CStatic* pStatic = (CStatic*)GetDlgItem(IDC_addpic);
				CRect lRect;
				pStatic->GetClientRect(&lRect);
				pStatic->GetDC()->FillSolidRect(lRect.left+1 ,lRect.top+1 ,lRect.Width()/2-x/2,lRect.Height()-2, RGB(255, 255, 255));//��
				pStatic->GetDC()->FillSolidRect(lRect.Width()/2+x/2-1 ,lRect.top+1 ,lRect.Width()/2-x/2+1,lRect.Height()-2, RGB(255, 255, 255));//��
			}
			::SetStretchBltMode(dcs->m_hDC,COLORONCOLOR);
			image.StretchBlt(dcs->m_hDC,rc.Width()/2-x/2+1,rc.Height()/2-y/2+1,x-1,y-1,0,0,image.GetWidth(),image.GetHeight(),SRCCOPY);
			ReleaseDC(dcs);
			dcs->DeleteDC();
		}   
	} 
	if(num>0)
	{
		if(num==4)
		{
			p3.ShowWindow(1);
			UpdateWindow();
			CRect rc;
			p0.GetClientRect(rc);
			CImage image;
			image.Load(strFilepath[3]); //ͼƬ�ļ�·��

			CDC* dcs;
			dcs = p0.GetDC();
			double x,y;

			if(image.GetWidth()>=image.GetHeight())
			{
				double IndexWH=(double)image.GetWidth()/(double)200;
				x=200;
				y=(double)image.GetHeight()/(double)IndexWH;	
			}else	{
				double IndexWH=(double)image.GetHeight()/(double)200;
				y=200;
				x=(double)image.GetWidth()/(double)IndexWH;	
			}
			::SetStretchBltMode(dcs->m_hDC,COLORONCOLOR);
			image.StretchBlt(dcs->m_hDC,rc.Width()/2-x/2+1,rc.Height()/2-y/2+1,x-1,y-1,0,0,image.GetWidth(),image.GetHeight(),SRCCOPY);
			image.Destroy();
			dcs->SetBkMode(TRANSPARENT);
			dcs->SetTextColor(RGB(0,0,0));
			dcs->TextOutA(rc.right-70,rc.bottom-15,"��"+pjg[3]);
			
			p3.GetClientRect(rc);
			CImage image0;
			image0.Load(strFilepath[0]); //ͼƬ�ļ�·��		
			dcs = p3.GetDC();
			if(image0.GetWidth()>=image0.GetHeight())
			{
				double IndexWH=(double)image0.GetWidth()/(double)200;
				x=200;
				y=(double)image0.GetHeight()/(double)IndexWH;	
			}else	{
				double IndexWH=(double)image0.GetHeight()/(double)200;
				y=200;
				x=(double)image0.GetWidth()/(double)IndexWH;	
			}
			::SetStretchBltMode(dcs->m_hDC,COLORONCOLOR);
			image0.StretchBlt(dcs->m_hDC,rc.Width()/2-x/2+1,rc.Height()/2-y/2+1,x-1,y-1,0,0,image0.GetWidth(),image0.GetHeight(),SRCCOPY);
			image0.Destroy();
			dcs->SetBkMode(TRANSPARENT);
			dcs->SetTextColor(RGB(0,0,0));
			dcs->TextOutA(rc.right-70,rc.bottom-15,"��"+pjg[0]);

			p2.GetClientRect(rc);
			CImage image1;
			image1.Load(strFilepath[1]); //ͼƬ�ļ�·��

			dcs = p2.GetDC();

			if(image1.GetWidth()>=image1.GetHeight())
			{
				double IndexWH=(double)image1.GetWidth()/(double)200;
				x=200;
				y=(double)image1.GetHeight()/(double)IndexWH;	
			}else	{
				double IndexWH=(double)image1.GetHeight()/(double)200;
				y=200;
				x=(double)image1.GetWidth()/(double)IndexWH;	
			}
			::SetStretchBltMode(dcs->m_hDC,COLORONCOLOR);
			image1.StretchBlt(dcs->m_hDC,rc.Width()/2-x/2+1,rc.Height()/2-y/2+1,x-1,y-1,0,0,image1.GetWidth(),image1.GetHeight(),SRCCOPY);
			image1.Destroy();
			dcs->SetBkMode(TRANSPARENT);
			dcs->SetTextColor(RGB(0,0,0));
			dcs->TextOutA(rc.right-70,rc.bottom-15,"��"+pjg[1]);

			p1.GetClientRect(rc);
			CImage image2;
			image2.Load(strFilepath[2]); //ͼƬ�ļ�·��
			dcs = p1.GetDC();
			if(image2.GetWidth()>=image2.GetHeight())
			{
				double IndexWH=(double)image2.GetWidth()/(double)200;
				x=200;
				y=(double)image2.GetHeight()/(double)IndexWH;	
			}else	{
				double IndexWH=(double)image2.GetHeight()/(double)200;
				y=200;
				x=(double)image2.GetWidth()/(double)IndexWH;	
			}
			::SetStretchBltMode(dcs->m_hDC,COLORONCOLOR);
			image2.StretchBlt(dcs->m_hDC,rc.Width()/2-x/2+1,rc.Height()/2-y/2+1,x-1,y-1,0,0,image2.GetWidth(),image2.GetHeight(),SRCCOPY);
			image2.Destroy();
			dcs->SetBkMode(TRANSPARENT);
			dcs->SetTextColor(RGB(0,0,0));
			dcs->TextOutA(rc.right-70,rc.bottom-15,"��"+pjg[2]);

			ReleaseDC(dcs);
			dcs->DeleteDC();	
		}else{
			p0.ShowWindow(1);
			UpdateWindow();
			CRect rc;
			p0.GetClientRect(rc);
			CImage image;
			image.Load(strFilepath[num-1]); //ͼƬ�ļ�·��
	
			CDC* dcs;
			dcs = p0.GetDC();
			double x,y;

			if(image.GetWidth()>=image.GetHeight())
			{
				double IndexWH=(double)image.GetWidth()/(double)200;
				x=200;
				y=(double)image.GetHeight()/(double)IndexWH;	
			}else	{
				double IndexWH=(double)image.GetHeight()/(double)200;
				y=200;
				x=(double)image.GetWidth()/(double)IndexWH;	
			}
			::SetStretchBltMode(dcs->m_hDC,COLORONCOLOR);
			image.StretchBlt(dcs->m_hDC,rc.Width()/2-x/2+1,rc.Height()/2-y/2+1,x-1,y-1,0,0,image.GetWidth(),image.GetHeight(),SRCCOPY);
			image.Destroy();

			dcs->SetBkMode(TRANSPARENT);
			dcs->SetTextColor(RGB(0,0,0));
			dcs->TextOutA(rc.right-70,rc.bottom-15,"��"+pjg[num-1]);

			if(num==2)
			{
				p1.ShowWindow(1);
				UpdateWindow();
				p1.GetClientRect(rc);
				CImage image0;
				image0.Load(strFilepath[0]); //ͼƬ�ļ�·��
				dcs = p1.GetDC();
				if(image0.GetWidth()>=image0.GetHeight())
				{
					double IndexWH=(double)image0.GetWidth()/(double)200;
					x=200;
					y=(double)image0.GetHeight()/(double)IndexWH;	
				}else	{
					double IndexWH=(double)image0.GetHeight()/(double)200;
					y=200;
					x=(double)image0.GetWidth()/(double)IndexWH;	
				}
				::SetStretchBltMode(dcs->m_hDC,COLORONCOLOR);
				image0.StretchBlt(dcs->m_hDC,rc.Width()/2-x/2+1,rc.Height()/2-y/2+1,x-1,y-1,0,0,image0.GetWidth(),image0.GetHeight(),SRCCOPY);
				image0.Destroy();	

				dcs->SetBkMode(TRANSPARENT);
				dcs->SetTextColor(RGB(0,0,0));
				dcs->TextOutA(rc.right-70,rc.bottom-15,"��"+pjg[0]);
			}
			if(num==3)
			{
				p2.ShowWindow(1);
				UpdateWindow();
				p2.GetClientRect(rc);
				CImage image0;
				image0.Load(strFilepath[0]); //ͼƬ�ļ�·��
				dcs = p2.GetDC();
				if(image0.GetWidth()>=image0.GetHeight())
				{
					double IndexWH=(double)image0.GetWidth()/(double)200;
					x=200;
					y=(double)image0.GetHeight()/(double)IndexWH;	
				}else	{
					double IndexWH=(double)image0.GetHeight()/(double)200;
					y=200;
					x=(double)image0.GetWidth()/(double)IndexWH;	
				}
				::SetStretchBltMode(dcs->m_hDC,COLORONCOLOR);
				image0.StretchBlt(dcs->m_hDC,rc.Width()/2-x/2+1,rc.Height()/2-y/2+1,x-1,y-1,0,0,image0.GetWidth(),image0.GetHeight(),SRCCOPY);
				image0.Destroy();

				dcs->SetBkMode(TRANSPARENT);
				dcs->SetTextColor(RGB(0,0,0));
				dcs->TextOutA(rc.right-70,rc.bottom-15,"��"+pjg[0]);

				p1.GetClientRect(rc);
				CImage image1;
				image1.Load(strFilepath[1]); //ͼƬ�ļ�·��
				dcs = p1.GetDC();
				if(image1.GetWidth()>=image1.GetHeight())
				{
					double IndexWH=(double)image1.GetWidth()/(double)200;
					x=200;
					y=(double)image1.GetHeight()/(double)IndexWH;	
				}else	{
					double IndexWH=(double)image1.GetHeight()/(double)200;
					y=200;
					x=(double)image1.GetWidth()/(double)IndexWH;	
				}
				::SetStretchBltMode(dcs->m_hDC,COLORONCOLOR);
				image1.StretchBlt(dcs->m_hDC,rc.Width()/2-x/2+1,rc.Height()/2-y/2+1,x-1,y-1,0,0,image1.GetWidth(),image1.GetHeight(),SRCCOPY);
				image1.Destroy();

				dcs->SetBkMode(TRANSPARENT);
				dcs->SetTextColor(RGB(0,0,0));
				dcs->TextOutA(rc.right-70,rc.bottom-15,"��"+pjg[1]);
			}
			ReleaseDC(dcs);
			dcs->DeleteDC();	
		}
	}
	for(int i=0;i<4;i++)
	{
		if(!pname[i].IsEmpty())
		{			
			dc.SetBkMode(TRANSPARENT);
			dc.SetTextColor(RGB(112,112,112));
			dc.TextOutA(20+210*i,656,pname[num-i-1]);
			dc.TextOutA(20+210*i,676,"���("+punit[num-i-1]+"):"+pkc[num-i-1]);
			dc.TextOutA(20+210*i,696,pwords[num-i-1]);	
		}
	}
	//��ͼ��ɺ������  
	m_Back.DeleteObject();  
	mdc.DeleteDC();
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
}

void M_P_add::OnBnClickedCancel()
{
	e_name.SetWindowTextA("");
	e_price.SetWindowTextA("");
	e_unit.SetWindowTextA("");
	e_kc.SetWindowTextA("");
	strFilePath="";
	Invalidate(0);
	e_content.SetWindowTextA("");
}

BOOL M_P_add::HasChineseChar(CString Cstr)
{
	int nLen = Cstr.GetLength();
	unsigned char ch1;
	for(int i = 0; i != nLen; ++i)
	{
		ch1 = Cstr[i];
		if (ch1 >= 0xA0)
		{
			return TRUE;
		}
		else
		{
			continue;
		}
	}  
	return FALSE;
}
void M_P_add::OnBnClickedOk()
{
	e_name.GetWindowTextA(p.name);
	CString price;
	e_price.GetWindowTextA(price);
	p.price=atof(price);
	e_unit.GetWindowTextA(p.unit);
	CString kc;
	e_kc.GetWindowTextA(kc);
	p.kc=atof(kc);
	p.image=strFilePath;
	e_content.GetWindowTextA(p.content);
	if(p.content=="��������Ϣ"||p.content=="�������Ʒ��Ϣ(��100��)")
		p.content="";
	if((!HasChineseChar(p.name)&&p.name.GetLength()>9)||p.name.GetLength()>12||p.name.IsEmpty()||p.name=="��������Ϣ"||p.name=="�������Ʒ����"|| p.price==0 || !(price.SpanIncluding(_T("0123456789.")) == price) || p.kc==0 || !(kc.SpanIncluding(_T("0123456789.")) == kc) || p.unit.IsEmpty()||p.unit=="�����뵥λ,��:��/��/�׵�"||p.unit=="��������Ϣ" || p.content.GetLength()>200)
	{	
		if(p.name.IsEmpty()||p.name=="��������Ϣ"||p.name=="�������Ʒ����")
		{	
			InvalidateRect(CRect(632,30,1050,60),0);
			CPaintDC dc(this);
			dc.SetBkMode(TRANSPARENT);
			dc.SetTextColor(RGB(255,0,0));
			dc.TextOutA(635,35,"����δ��д");
			ReleaseDC(&dc);
		}else{
			InvalidateRect(CRect(632,30,1050,60),0);
			CPaintDC dc(this);
			dc.SetBkMode(TRANSPARENT);
			dc.SetTextColor(RGB(255,255,255));
			dc.TextOutA(635,35,"����δ��д");
			ReleaseDC(&dc);
		}
		if(p.name.GetLength()>12||(!HasChineseChar(p.name)&&p.name.GetLength()>9))
		{
			InvalidateRect(CRect(632,30,1050,60),0);
			CPaintDC dc(this);
			dc.SetBkMode(TRANSPARENT);
			dc.SetTextColor(RGB(255,0,0));
			dc.TextOutA(635,35,"���Ƴ��ȳ�������");
			ReleaseDC(&dc);
		}else{
			InvalidateRect(CRect(632,30,1050,60),0);
			CPaintDC dc(this);
			dc.SetBkMode(TRANSPARENT);
			dc.SetTextColor(RGB(255,255,255));
			dc.TextOutA(635,35,"���Ƴ��ȳ�������");
			ReleaseDC(&dc);
		}
		if(p.price==0)
		{
			InvalidateRect(CRect(632,70,1050,100),0);
			CPaintDC dc(this);
			dc.SetBkMode(TRANSPARENT);
			dc.SetTextColor(RGB(255,0,0));
			dc.TextOutA(635,75,"������д���Ϸ�");
			ReleaseDC(&dc);
		}else{
			InvalidateRect(CRect(632,70,1050,100),0);
			CPaintDC dc(this);
			dc.SetBkMode(TRANSPARENT);
			dc.SetTextColor(RGB(255,255,255));
			dc.TextOutA(635,75,"������д���Ϸ�");
			ReleaseDC(&dc);
		}
		if(p.kc==0)
		{
			InvalidateRect(CRect(632,110,1050,140),0);
			CPaintDC dc(this);
			dc.SetBkMode(TRANSPARENT);
			dc.SetTextColor(RGB(255,0,0));
			dc.TextOutA(635,115,"�����д���Ϸ�");
			ReleaseDC(&dc);
		}else{
			InvalidateRect(CRect(632,110,1050,140),0);
			CPaintDC dc(this);
			dc.SetBkMode(TRANSPARENT);
			dc.SetTextColor(RGB(255,255,255));
			dc.TextOutA(635,115,"�����д���Ϸ�");
			ReleaseDC(&dc);
		}
		if(p.unit.IsEmpty()||p.unit=="�����뵥λ,��:��/��/�׵�"||p.unit=="��������Ϣ")
		{
			InvalidateRect(CRect(632,150,1050,180),0);
			CPaintDC dc(this);
			dc.SetBkMode(TRANSPARENT);
			dc.SetTextColor(RGB(255,0,0));
			dc.TextOutA(635,155,"��浥λδ��д");
			ReleaseDC(&dc);
		}else{
			InvalidateRect(CRect(632,150,1050,180),0);
			CPaintDC dc(this);
			dc.SetBkMode(TRANSPARENT);
			dc.SetTextColor(RGB(255,255,255));
			dc.TextOutA(635,155,"��浥λδ��д");
			ReleaseDC(&dc);
		}
		if( p.content.GetLength()>200)
		{
			InvalidateRect(CRect(160,250,320,270),0);
			CPaintDC dc(this);
			dc.SetBkMode(TRANSPARENT);
			dc.SetTextColor(RGB(255,0,0));
			dc.TextOutA(165,255,"�����ѳ�����");
			ReleaseDC(&dc);
		}else{	
			InvalidateRect(CRect(160,250,320,270),0);
			CPaintDC dc(this);
			dc.SetBkMode(TRANSPARENT);
			dc.SetTextColor(RGB(255,255,255));
			dc.TextOutA(165,255,"�����ѳ�����");
			ReleaseDC(&dc);
		}
		MessageBox("��Ϣ��ȫ�������������������Ե�������ť���!","����",MB_ICONEXCLAMATION);
	}else{
		if(p.add())
		{	
			//1.��ȡ��ǰʱ��,������ʷ��¼
			GetLocalTime(&CurTime);////��ȡ����ʱ�� 
			h.time.Format("%d:%d:%d",CurTime.wHour,CurTime.wMinute,CurTime.wSecond);
			h.content="¼���Ʒ\n"+p.name;
			h.table="goods";
			pr=p.select(p);
			h.tableId=pr.id;
			h.add();
			//2.����listcontrol
			m_ListCtrl.InsertItem(0,h.time);
			m_ListCtrl.SetItemText(0,1,h.content);
			//3.������inventory��ļ�¼
			inventory.goodsId=pr.id;
			inventory.rk=p.kc;
			inventory.ck=0;
			inventory.kc=p.kc;
			inventory.remark="¼���Ʒ";
			inventory.add(inventory);	

			if(num==4)
			{
				strFilepath[0]=strFilepath[1];
				strFilepath[1]=strFilepath[2];
				strFilepath[2]=strFilepath[3];
				strFilepath[3]=strFilePath;
				pname[0]=pname[1];	
				pname[1]=pname[2];	
				pname[2]=pname[3];	
				pname[3]=p.name;
				CString KCS;
				KCS.Format("%.2f",p.kc);
				pkc[0]=pkc[1];
				pkc[1]=pkc[2];
				pkc[2]=pkc[3];
				pkc[3]=KCS;
				CString JG;
				JG.Format("%.2f",p.price);
				pjg[0]=pjg[1];
				pjg[1]=pjg[2];
				pjg[2]=pjg[3];
				pjg[3]=JG;
				punit[0]=punit[1];
				punit[1]=punit[2];
				punit[2]=punit[3];
				punit[3]=p.unit;
				pwords[0]=pwords[1];
				pwords[1]=pwords[2];
				pwords[2]=pwords[3];
				pwords[3]=p.content;
				if(pwords[3].GetLength()>24)					
					pwords[3]=pwords[num].Left(24)+"...";

			}else{
				strFilepath[num]=strFilePath;		
				pname[num]=p.name;
				CString KCS;
				KCS.Format("%.2f",p.kc);
				pkc[num]=KCS;
				CString JG;
				JG.Format("%.2f",p.price);
				pjg[num]=JG;
				pwords[num]=p.content;
				punit[num]=p.unit;
				if(pwords[num].GetLength()>12)					
					pwords[num]=pwords[num].Left(12)+"...";
				num++;	
			}
			if(MessageBox("����ɹ�,������ӣ�","��ʾ",MB_ICONEXCLAMATION|MB_OKCANCEL)==IDOK)
			{				
				strFilePath="";
				e_name.SetWindowTextA("");
				e_price.SetWindowTextA("");
				e_unit.SetWindowTextA("");
				e_kc.SetWindowTextA("");			
				e_content.SetWindowTextA("");
				Invalidate(0);
			}else{
				f_M_P_add=false;
				//��治��Ԥ��
				pr.selectIndex();
				CDialog::OnOK();
			}
		}
		else
			MessageBox(" ���ʧ��","��ʾ",MB_ICONEXCLAMATION);
	}
	/*int t2;
	t2=GetTickCount();
	CString T1;
	T1.Format("ȫ:%d ��һ��:%d,�ڶ���:%d",t2-t1,t4-t3,t2-t4);
	MessageBox(T1);*/
}


void M_P_add::OnTimer(UINT_PTR nIDEvent)
{
	if (1==nIDEvent)  
     {
		 CString str;
		 e_name.GetWindowTextA(str);
		 if( !str.IsEmpty() && str!="��������Ϣ" && str!="�������Ʒ����")
		 {
			 m_remove.ShowWindow(1);
		 }else{
			 m_remove.ShowWindow(0);
		 }
	     POINT p;  
		 GetCursorPos(&p);     
		 CWnd *hwnd;  
		 hwnd=WindowFromPoint(p);        //���������а���ָ���ĵ�;�����ָ����Ļ��������Ļ�ϵ�һ���㡣     
		 CWnd *hwnd3=GetDlgItem(IDOK);  
		 if (hwnd3 == hwnd)         //�������ڰ�ť��  
		 {  
			 if (GetFocus()!=hwnd3)        
				 hwnd3->SetFocus() ;  
		 }  
		 else          //�����겻�ڰ�ť�ϣ�  
		 {  
			 if (GetFocus() == hwnd3 )                   
				 GetDlgItem(IDCANCEL)->SetFocus();      
		 } 
	}

	CDialogEx::OnTimer(nIDEvent);
}


void M_P_add::OnRemove()
{
	p.id=0;
	p.name="";
	p.price=0;
	p.kc=0;
	p.unit="";
	p.content="";

	e_name.GetWindowTextA(p.name);
	p=p.select(p);
	if(p.id>0){
		/*CString strinfo;
		strinfo.Format(p.name+":%.2f %.2f"+p.unit,p.price,p.kc);*/
		MessageBox("�Ѵ���","��ʾ");
	}else{
		MessageBox("������","��ʾ");
	}
}


void M_P_add::OnLButtonDown(UINT nFlags, CPoint point )
{
	/*CString x;
	x.Format("%d %d",point.x,point.y);
	MessageBox(x);*/
	CRect pic0;
	p0.GetWindowRect(pic0);

	if (pic0.PtInRect(point))         //�������ڰ�ť��  
	{
		
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void M_P_add::OnStnClickedaddpic()
{
	    CString str;
		str=strFilePath;
	    CFileDialog fileDlg(TRUE, _T("image"), NULL, 0, _T("ͼƬ(*.png;*.jpg;*.bmp;*.jpeg)|*.png;*.jpg;*.bmp;*.jpeg||"), this);//�ı��ļ�(*.txt)|*.txt|�����ļ�(*.*)|*.*||
		fileDlg.DoModal();
		strFilePath = fileDlg.GetPathName();
		if (strFilePath == _T(""))
		{
			MessageBox("��Ч�ļ�·��","��ʾ");
			strFilePath=str;
			return;
		}
		CImage image;
		image.Load(strFilePath); //ͼƬ�ļ�·��

		if(image.GetWidth()<200||image.GetHeight()<200){
			MessageBox("ͼƬС��200X200���������������","��ʾ");
		}else{
			
		}
}
