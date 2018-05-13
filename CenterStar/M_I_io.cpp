// M_I_io.cpp : 实现文件
//

#include "stdafx.h"
#include "CenterStar.h"
#include "M_I_io.h"
#include "afxdialogex.h"


// M_I_io 对话框

IMPLEMENT_DYNAMIC(M_I_io, CDialogEx)

M_I_io::M_I_io(CWnd* pParent /*=NULL*/)
	: CDialogEx(M_I_io::IDD, pParent)
{

}

M_I_io::~M_I_io()
{
}

void M_I_io::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
	DDX_Control(pDX, IDOK, m_ok);
	DDX_Control(pDX, IDCANCEL, m_cancel);
}


BEGIN_MESSAGE_MAP(M_I_io, CDialogEx)
	ON_WM_PAINT()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &M_I_io::OnNMDblclkList1)
	ON_EN_KILLFOCUS(IDC_EDIT1, &M_I_io::OnEnKillfocusEdit1)
	ON_BN_CLICKED(IDOK, &M_I_io::OnOk)
//	ON_NOTIFY(NM_HOVER, IDC_LIST1, &M_I_io::OnNMHoverList1)
ON_WM_TIMER()
ON_BN_CLICKED(IDCANCEL, &M_I_io::OnCancel)
END_MESSAGE_MAP()


// M_I_io 消息处理程序


BOOL M_I_io::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_Row=0;
	m_Col=0;
	m_edit.LimitText(100);
	//固定表头的宽度
	CHeaderCtrl*   pHeaderCtrl   =   (CHeaderCtrl*)m_list.GetHeaderCtrl();   
	pHeaderCtrl->EnableWindow(   FALSE   );

	CRect rect(100,30,850,652);
	m_list.MoveWindow(rect);	
	m_list.SetRowHeight(100);
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT| LVS_EX_GRIDLINES| LVS_EX_TWOCLICKACTIVATE | LVS_EX_TRACKSELECT /*自动换行*/| LVS_EX_FLATSB/*扁平滚动条*/);
	
    m_list.InsertColumn(0, _T("品名"), LVCFMT_CENTER, rect.Width()/6, 0);   
    m_list.InsertColumn(1, _T("入库"), LVCFMT_CENTER, rect.Width()/6, 1); 
	m_list.InsertColumn(2, _T("出库"), LVCFMT_CENTER, rect.Width()/6, 2); 
	m_list.InsertColumn(3, _T("库存"), LVCFMT_CENTER, rect.Width()/6, 3); 
	m_list.InsertColumn(4, _T("备注"), LVCFMT_CENTER, rect.Width()/3, 4); 
	
	//CFont   *pfont1   =   m_list.GetFont();  
 //   pfont1->GetLogFont(   &logfont   );  
 //   logfont.lfHeight   =logfont.lfHeight   *   2;   //这里可以修改字体的高比例
 //   logfont.lfWidth     =   logfont.lfWidth   *   2;   //这里可以修改字体的宽比例
 //   static   CFont   font1;  
 //   font1.CreateFontIndirect(&logfont);  
 //   m_list.SetFont(&font1);  
 //   font1.Detach();
	static CFont   font1;
	font1.CreatePointFont(150,"宋体");
	m_edit.SetFont(&font1);

	CString stri;
	for(int i=0;i<6;i++)
	{
		
		m_list.InsertItem(i,"");
	}
	m_Row=0;
	m_Col=0;
	_initPicture();
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
void M_I_io::_initPicture()
{
	int j=0,k=0;
	CRect rc;
	for(int i=0;i<6;i++)
	{
		if(NULL==pic[i].GetSafeHwnd())
		{
				pic[i].Create(_T( "" ), /*WS_BORDER |*/ WS_EX_TRANSPARENT|WS_CHILD | WS_VISIBLE  | SS_BITMAP| SS_CENTERIMAGE | SS_NOTIFY, CRect (20+205*j,50+205*k,221+205*j,251+205*k), this,IDC_MYPICTURE+i);		
		}
		j++;
		if(i==3)
		{
			j=0;
			k++;
		}
		pic[i].MoveWindow(0,50+100*i,100,100);
		
	}
}

void M_I_io::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CBitmap m_Back;
	m_Back.LoadBitmap(IDB_BITMAP57);
	CDC mdc;
	mdc.CreateCompatibleDC(&dc); 
	mdc.SelectObject(&m_Back);
	dc.StretchBlt(0,0,850,712,&mdc,0,0,850,712,SRCCOPY);
	USES_CONVERSION;
	WCHAR* pBuf;
	for(int i=0;i<6;i++)
	{
		if(!image[i].IsEmpty())
		{
			pBuf = T2W((LPCTSTR)image[i]);


			CDC *pCDC = GetDlgItem(IDC_MYPICTURE+i)->GetDC();
			HDC hdc = pCDC->GetSafeHdc();

			Graphics grphics(hdc);
			CRect rect;
			GetDlgItem(IDC_MYPICTURE+i)->GetClientRect(&rect);
	
			Bitmap bitmap(rect.Width(), rect.Height());
			Graphics grp(&bitmap);
	
			Bitmap b(pBuf);
			double x,y;
			if(b.GetWidth()>=b.GetHeight())
			{
				double IndexWH=(double)b.GetWidth()/(double)100;
				x=100;
				y=(double)b.GetHeight()/(double)IndexWH;
					
				CStatic* pStatic = (CStatic*)GetDlgItem(IDC_MYPICTURE+i);
				CRect lRect;
				pStatic->GetClientRect(&lRect);
				pStatic->GetDC()->FillSolidRect((int)lRect.left ,(int)lRect.top ,(int)lRect.Width(),(int)(lRect.Height()/2-(int)y/2+1), RGB(255, 255, 255));//上
				pStatic->GetDC()->FillSolidRect((int)lRect.left ,(int)(lRect.Height()/2+y/2) ,(int)lRect.Width(),(int)(lRect.Height()/2+1-y/2), RGB(255, 255, 255));//下		
					
				grp.DrawImage(&b,0,0,(int)x,(int)y);
				grphics.DrawImage(&bitmap,0,(int)(50-y/2));	
			}else	{
				double IndexWH=(double)b.GetHeight()/(double)100;
				y=100;
				x=(double)b.GetWidth()/(double)IndexWH;
					
				CStatic* pStatic = (CStatic*)GetDlgItem(IDC_MYPICTURE+i);
				CRect lRect;
				pStatic->GetClientRect(&lRect);
				pStatic->GetDC()->FillSolidRect((int)lRect.left,(int)lRect.top+1 ,(int)(lRect.Width()/2-x/2+1),(int)lRect.Height()-1, RGB(255, 255, 255));//左
				pStatic->GetDC()->FillSolidRect((int)(lRect.Width()/2+x/2) ,(int)lRect.top+1 ,(int)(lRect.Width()/2-x/2+2),(int)lRect.Height()-1, RGB(255, 255, 255));//右

				grp.DrawImage(&b,0,0,(int)x,(int)y);
				grphics.DrawImage(&bitmap,(int)(50-x/2),0);	
			}
			/*CString pice;
			pice.Format("%.2f",pinfo[i+(page-1)*12].price);
			Gdiplus::Font f(L"幼圆", 10);
			SolidBrush blackBrush(Color(100, 255, 0, 0));
			WCHAR *string;
			pice="￥"+pice;	
			Color cOloR(100,230,230,230);
			SolidBrush sb(cOloR);
			grphics.FillRectangle(&sb,RectF(rect.left,rect.top,rect.Width(),20));
			grphics.FillRectangle(&sb,RectF(rect.left,rect.bottom-20,rect.Width(),20));
					
			SolidBrush sbs(Color(120,0,0,0));
			grphics.FillRectangle(&sbs,RectF(rect.left+10,rect.bottom-40,75,20));
			grphics.FillRectangle(&sbs,RectF(rect.Width()/2+10,rect.bottom-40,75,20));
					
			string = T2W((LPCTSTR)pinfo[i+(page-1)*12].name);
			grphics.DrawString(string,-1,&f,PointF(0.0f, 5.0f),&SolidBrush(Color(100,0,0,0)));
			string = T2W((LPCTSTR)pice);
			grphics.DrawString(string,-1,&f,PointF(0.0f, 180.0f),&blackBrush);

			SolidBrush blackBrushs(Color(100, 230, 230, 230));
			string = T2W((LPCTSTR)"编辑");
			grphics.DrawString(string,-1,&f,PointF(30.0f, 160.0f),&blackBrushs);

			string = T2W((LPCTSTR)"删除");
			grphics.DrawString(string,-1,&f,PointF(130.0f, 160.0f),&blackBrushs);*/

		}else{
			    CStatic* pStatic = (CStatic*)GetDlgItem(IDC_MYPICTURE+i);
				CRect lRect;
				pStatic->GetClientRect(&lRect);
				pStatic->GetDC()->FillSolidRect(lRect.left,lRect.top,lRect.Width(),lRect.Height(), RGB(231, 243, 229));	
				pStatic->GetDC()->FillSolidRect(lRect.left+1,lRect.top+2,lRect.Width()-2,lRect.Height()-2, RGB(255, 255, 255));
				pStatic->GetDC()->TextOutA( (lRect.left+lRect.Width()/2)-30 , (lRect.top+lRect.Height()/2)-5 , "暂无图片" );
				
		}
	}
	m_list.Invalidate();
	//绘图完成后的清理  
	m_Back.DeleteObject();  
	mdc.DeleteDC();
	// 不为绘图消息调用 CDialogEx::OnPaint()
}





void M_I_io::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_LISTVIEW* pNMListView=(NM_LISTVIEW*)pNMHDR;
	CRect rc;
	m_Row = pNMListView->iItem;//获得选中的行
	m_Col = pNMListView->iSubItem;//获得选中列

	/*if   (pNMListView->iSubItem != 0)
	{*/
		m_list.GetSubItemRect(m_Row,m_Col,LVIR_LABEL,rc);//获得子项的RECT；
		/*if   (pNMListView->iSubItem == 0)
		{
		}else{
			rc.left=rc.left+17;
		}*/
		rc.bottom=rc.bottom-1;
		m_edit.SetParent(&m_list);//转换坐标为列表框中的坐标
		m_edit.MoveWindow(rc);//移动Edit到RECT坐在的位置;
		m_edit.SetWindowText(m_list.GetItemText(m_Row,m_Col));//将该子项中的值放在Edit控件中；
		m_edit.ShowWindow(SW_SHOW);//显示Edit控件；
		m_edit.SetFocus();//设置Edit焦点
		m_edit.ShowCaret();//显示光标
		m_edit.SetSel(-1);//将光标移动到最后
		//start_date=m_list.GetItemText(m_Row,m_Col);//还原初始数据
	//}

	*pResult = 0;
}


void M_I_io::OnEnKillfocusEdit1()
{
	CString tem;
	m_edit.GetWindowText(tem);    //得到用户输入的新的内容
	m_list.SetItemText(m_Row,m_Col,tem);   //设置编辑框的新内容
	m_edit.ShowWindow(SW_HIDE); //应藏编辑框
	//自动添加数据
	if(!tem.IsEmpty())
	{
		CString name;
		name=tem;
		name=m_list.GetItemText(m_Row,0);
		CString sql;
		sql.Format("SELECT G_kc,G_image FROM tally.goods where G_name='%s';",name);
		//执行查询
		MYSQL_RES *m_result;
		mysql_query(&m_sqlCons,sql);
		m_result=mysql_use_result(&m_sqlCons);
		CString data[2]={};
		int i=0;
		MYSQL_ROW row;
		m_list.SetItemText(m_Row, 3,"" );
		image[m_Row]="";
		if((row=mysql_fetch_row(m_result)))
		{
			//获取数据
			data[0]=row[0];
			data[1]=row[1];
			i++;
			image[m_Row]=data[1];
			m_list.SetItemText(m_Row, 3,data[0] );
				
		}else{
			MessageBox(name+"此产品未录入","提示",MB_ICONEXCLAMATION);
			m_list.SetItemText(m_Row,0,"");
		}
		CRect cpic;
		pic[m_Row].GetClientRect(cpic);
		if(m_Col==0)
			InvalidateRect(cpic,0);

		mysql_free_result(m_result); //关联的内存会释放
	}
	CString num1,num2,num3;
	double Num1,Num2,Num3;

	num1=m_list.GetItemText(m_Row,1);
	num2=m_list.GetItemText(m_Row,2);
	num3=m_list.GetItemText(m_Row,3);
	if(!num1.IsEmpty()&&!num2.IsEmpty()&&!num3.IsEmpty())
	{
		Num1=atof(num1);
		Num2=atof(num2);
		Num3=atof(num3);
		Num3=Num1-Num2+Num3;
		num3.Format("%.2f",Num3);
		if(Num3<0)
		{
			m_list.SetItemText(m_Row,1,"");
			m_list.SetItemText(m_Row,2,"");
			MessageBox("已超出库存量","提示",MB_ICONEXCLAMATION);
		}
		else
			m_list.SetItemText(m_Row,3,num3);
	}
}


void M_I_io::OnOk()
{
	CString name;
	CString Rk,Ck,Kc,ID;
	CString start_kc;
	CRect cpic;
	for(int i=0;i<6;i++)
	{
		if( !( name=m_list.GetItemText(i,0) ).IsEmpty() )
		{
			product.name=name;
			product=product.select(product);
			inventory.goodsId=product.id;
			start_kc.Format("%.2f",product.kc);
			Rk=m_list.GetItemText(i,1);
			Ck=m_list.GetItemText(i,2);
			Kc=m_list.GetItemText(i,3);
			inventory.rk=atof(Rk);
			inventory.ck=atof(Ck);
			inventory.kc=atof(Kc);
			inventory.remark=m_list.GetItemText(i,4);
			if(! (Rk.SpanIncluding(_T("0123456789.")) == Rk) || ! (Ck.SpanIncluding(_T("0123456789.")) == Ck) )
			{
				CString strerror="";
				if(! (Rk.SpanIncluding(_T("0123456789.")) == Rk) )
					strerror+="入库数据不是纯数字、";
				if(! (Ck.SpanIncluding(_T("0123456789.")) == Ck) )
					strerror+="出库数据不是纯数字、";
				MessageBox(name+strerror,"提示",MB_ICONEXCLAMATION);
			}else{
			    if(inventory.add(inventory))
				{
					ID.Format("%d",product.id);
					product.updateKc(m_list.GetItemText(i,3),ID);
					inventory=inventory.searchAuto(inventory,h_Itime);
					//1.获取当前时间,插入历史记录
					GetLocalTime(&CurTime);////获取本地时间 
					h.time.Format("%d:%d:%d",CurTime.wHour,CurTime.wMinute,CurTime.wSecond);
					h.content="出入库操作\n变更产品"+product.name+"的库存\n"+start_kc+"→"+m_list.GetItemText(i,3);
					h.table="inventory";
					h.tableId=inventory.id;
					h.add();
					//2.插入listcontrol
					m_ListCtrl.InsertItem(0,h.time);
					m_ListCtrl.SetItemText(0,1,h.content);
					//清空表
					m_list.SetItemText(i,0,"");
					m_list.SetItemText(i,1,"");
					m_list.SetItemText(i,2,"");
					m_list.SetItemText(i,3,"");
					m_list.SetItemText(i,4,"");
					//m_list.DeleteItem(i);
					image[i]="";
					pic[i].GetClientRect(cpic);
					InvalidateRect(cpic,0);
				}else{
					MessageBox(name+"添加失败","提示",MB_ICONEXCLAMATION);
				}
			}
		}
	}
	
}


void M_I_io::OnTimer(UINT_PTR nIDEvent)
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


void M_I_io::OnCancel()
{
	m_list.DeleteAllItems();
	CRect cpic;
	for(int i=0;i<6;i++)
	{
		image[i]="";
		pic[i].GetClientRect(cpic);
		InvalidateRect(cpic,0);
	}
}
