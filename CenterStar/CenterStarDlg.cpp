
// CenterStarDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CenterStar.h"
#include "CenterStarDlg.h"
#include "afxdialogex.h"
#include "Inventory.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCenterStarDlg 对话框




CCenterStarDlg::CCenterStarDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCenterStarDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	/////////////////2.GDI+
	 Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	 Gdiplus::GdiplusStartup(&gdiplustoken, &gdiplusStartupInput, NULL);
	////////////////

	 //库存不足预警
	 product.selectIndex();
	 //页数计算
	 if(indexNum%4==0)
		pageAll.Format("%d",indexNum/4);
	else
		pageAll.Format("%d",indexNum/4+1);
}

void CCenterStarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
	DDX_Control(pDX, IDCANCEL, m_close);
	DDX_Control(pDX, IDC_Min, m_min);
	DDX_Control(pDX, IDC_Test, m_test);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
	DDX_Control(pDX, IDC_ChangeKC, m_changekc);
	DDX_Control(pDX, IDC_KcDetail, m_kcdetail);
	DDX_Control(pDX, IDC_history, m_kchistory);
	DDX_Control(pDX, IDC_Product, m_product);
	DDX_Control(pDX, IDC_addproduct, m_addproduct);
	DDX_Control(pDX, IDC_productDetail, m_P_Detail);
	DDX_Control(pDX, IDC_order, m_order);
	DDX_Control(pDX, IDC_O_add, m_O_add);
	DDX_Control(pDX, IDC_O_Detail, m_O_detail);
	DDX_Control(pDX, IDC_Customer, m_customer);
	DDX_Control(pDX, IDC_c_add, m_C_add);
	DDX_Control(pDX, IDC_c_search, m_C_search);
	DDX_Control(pDX, IDC_lastpage, m_lastpage);
	DDX_Control(pDX, IDC_nextpage, m_nextpage);
	DDX_Control(pDX, IDC_LIST2, m_lists);
}

BEGIN_MESSAGE_MAP(CCenterStarDlg, CDialogEx)
	ON_WM_QUERYDRAGICON()
	ON_WM_NCHITTEST()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_Test, &CCenterStarDlg::OnBnClickedTest)
	ON_BN_CLICKED(IDC_addproduct, &CCenterStarDlg::OnM_P_add)
	ON_BN_CLICKED(IDC_nextpage, &CCenterStarDlg::OnBnClickednextpage)
	ON_BN_CLICKED(IDC_lastpage, &CCenterStarDlg::OnBnClickedlastpage)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_productDetail, &CCenterStarDlg::OnM_Pdeai)
	ON_BN_CLICKED(IDOK, &CCenterStarDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_ChangeKC, &CCenterStarDlg::OnM_I_io)
	ON_BN_CLICKED(IDC_KcDetail, &CCenterStarDlg::OnM_I_detail)
	ON_BN_CLICKED(IDC_history, &CCenterStarDlg::OnM_I_history)
	ON_BN_CLICKED(IDC_O_add, &CCenterStarDlg::OnM_O_add)
	ON_BN_CLICKED(IDC_c_add, &CCenterStarDlg::OnM_C_add)
	ON_BN_CLICKED(IDC_c_search, &CCenterStarDlg::OnM_C_detail)
	ON_BN_CLICKED(IDC_O_Detail, &CCenterStarDlg::OnM_O_Detail)
	ON_BN_CLICKED(IDC_Min, &CCenterStarDlg::OnMin)
END_MESSAGE_MAP()


// CCenterStarDlg 消息处理程序

BOOL CCenterStarDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	
	// TODO: 在此添加额外的初始化代码
	f_M_P_add=false;
	page=1;
	//m_edit.MoveWindow(300,10,400,30);
	//m_edit.SetWindowTextA("搜索内容、功能");

	   CRect clist(1050,54,1366,766);
	   m_ListCtrl.MoveWindow(clist);
	   m_ListCtrl.SetRowHeight(60);
	    // 为列表视图控件添加3列       
	    m_ListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT| LVS_EX_GRIDLINES| LVS_EX_TWOCLICKACTIVATE | LVS_EX_TRACKSELECT /*自动换行*/| LVS_EX_FLATSB/*扁平滚动条*/);
	    m_ListCtrl.InsertColumn(0,_T("时间"),LVCFMT_CENTER,clist.Width()/6+30,0); 
		m_ListCtrl.InsertColumn(1,_T("简略信息"),LVCFMT_LEFT,clist.Width()*5/6-30,1); 
		
	CRect clists(200,450,1050,766);
	m_lists.MoveWindow(clists);
	// 为列表视图控件添加3列       
	m_lists.SetExtendedStyle(LVS_EX_FULLROWSELECT| LVS_EX_GRIDLINES| LVS_EX_TWOCLICKACTIVATE | LVS_EX_TRACKSELECT /*自动换行*/| LVS_EX_FLATSB/*扁平滚动条*/);
	m_lists.InsertColumn(0,_T(""),LVCFMT_CENTER,clists.Width()/12,0); 
	m_lists.InsertColumn(1,_T("简略信息"),LVCFMT_CENTER,clists.Width()*9/12,1); 
	m_lists.InsertColumn(2,_T("时间"),LVCFMT_LEFT,clists.Width()/6,2); 
	history();

	//按分辨率调窗口自适应分布
	cx=GetSystemMetrics(SM_CXSCREEN);
	cy=GetSystemMetrics(SM_CYSCREEN);
	if(cx>=1366)
	{
		CRect   temprect(0,0,1366,768);
		CWnd::SetWindowPos(NULL,0,0,temprect.Width(),temprect.Height(),SWP_NOZORDER|SWP_NOMOVE);
	}else{
		//再用MoveWindow
		CWnd::SetWindowPos(NULL,0,0,cx,cy,SWP_NOZORDER|SWP_NOMOVE);
	}
	/*Database database;
	database.linkSql(database);*/
	//f_close=false;
	 _initPictrue();
	 _initDialog();
	SetTimer(1,200,NULL);
	 _initButton();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。



//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCenterStarDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



LRESULT CCenterStarDlg::OnNcHitTest(CPoint point)
{
	CRect rect(0,0,cx,10);
	ClientToScreen(rect);
	if(rect.PtInRect(point))
		return HTCAPTION;
	return CDialogEx::OnNcHitTest(point);
}


void CCenterStarDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	//定义一个位图对象 
	CBitmap m_Back,m_register;
	m_Back.LoadBitmap(IDB_BITMAP1);
	m_register.LoadBitmapA(IDB_BITMAP6);
	//定义一个内存设备描述表对象（即后备缓冲区）  
	CDC mdc;
	//建立与屏幕设备描述表（前端缓冲区）兼容的内存设备描述表句柄（后备缓冲区）  
    mdc.CreateCompatibleDC(&dc); 
	//绘图
	mdc.SelectObject(&m_Back);
	//将后备缓冲区中的图形拷贝到前端缓冲区  
	dc.StretchBlt(0,0,cx,cy,&mdc,0,0,1366,768,SRCCOPY);	

	mdc.SelectObject(&m_register);

	if(indexNum>4&&!f_M_P_add)
	{
		m_lastpage.ShowWindow(1);
		CFont f,f0;
		f.CreatePointFont(140,"幼圆");
		mdc.SelectObject(f);	  
		CString pageNow;
		pageNow.Format("%d",page);
		CString nUM;
		nUM.Format("%d",indexNum);
		mdc.TextOutA(220,293,"共"+nUM+"件产品");
		mdc.TextOutA(900,293,pageNow+"/"+pageAll);
		f0.CreatePointFont(180,"幼圆");
		mdc.SelectObject(f0);	 
		mdc.SetTextColor(RGB(217,194,116));
		mdc.TextOutA(220,10,"库存不足提醒");

		mdc.SetTextColor(RGB(112,112,112));
		mdc.TextOutA(200,340,"今天我的操作");
		f.DeleteObject();
	}
	dc.StretchBlt(0,54,cx,cy,&mdc,0,0,1366,712,SRCCOPY);

	//***//
	if(!f_M_P_add)
	{
		    m_addproduct.EnableWindow(1);
			m_P_Detail.EnableWindow(1);
			m_lastpage.ShowWindow(1);
			m_nextpage.ShowWindow(1);

			USES_CONVERSION;
			WCHAR* pBuf;
			if(indexNum>0)
			{
				for(int i=0;i<4;i++)
				{	
					//刷白
					CStatic* pStatics = (CStatic*)GetDlgItem(IDC_MYPICTURE+i);
					CRect lRect;
					pStatics->GetClientRect(&lRect);
					pStatics->GetDC()->FillSolidRect(lRect.left,lRect.top ,lRect.Width(),lRect.Height(), RGB(255, 255, 255));		
					
					if(!pindex[i+(page-1)*4].image.IsEmpty())
					{
						pBuf = T2W((LPCTSTR)pindex[i+(page-1)*4].image);
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
							double IndexWH=(double)b.GetWidth()/(double)200;
							x=200;
							y=(double)b.GetHeight()/(double)IndexWH;
					
							CStatic* pStatic = (CStatic*)GetDlgItem(IDC_MYPICTURE+i);
							CRect lRect;
							pStatic->GetClientRect(&lRect);
							pStatic->GetDC()->FillSolidRect(lRect.left ,lRect.top ,lRect.Width(),lRect.Height()/2-(int)y/2+1, RGB(255, 255, 255));//上
							pStatic->GetDC()->FillSolidRect(lRect.left ,lRect.Height()/2+y/2 ,lRect.Width(),lRect.Height()/2+1-y/2, RGB(255, 255, 255));//下		
					
							grp.DrawImage(&b,0,0,x,y);
							grphics.DrawImage(&bitmap,0,100-y/2);	
						}else	{
							double IndexWH=(double)b.GetHeight()/(double)200;
							y=200;
							x=(double)b.GetWidth()/(double)IndexWH;
					
							CStatic* pStatic = (CStatic*)GetDlgItem(IDC_MYPICTURE+i);
							CRect lRect;
							pStatic->GetClientRect(&lRect);
							pStatic->GetDC()->FillSolidRect(lRect.left,lRect.top+1 ,lRect.Width()/2-x/2+1,lRect.Height()-1, RGB(255, 255, 255));//左
							pStatic->GetDC()->FillSolidRect(lRect.Width()/2+x/2 ,lRect.top+1 ,lRect.Width()/2-x/2+2,lRect.Height()-1, RGB(255, 255, 255));//右

							grp.DrawImage(&b,0,0,x,y);
							grphics.DrawImage(&bitmap,100-x/2,0);	
						}
						CString pIce;
						pIce.Format("%.2f",pindex[i+(page-1)*4].price);
						Gdiplus::Font f(L"幼圆", 10);
						SolidBrush blackBrush(Color(255, 255, 0, 0));
						WCHAR *string;
						pIce="￥"+pIce;
						string = T2W((LPCTSTR)pIce);
						Color cOloR(200,230,230,230);
						SolidBrush sb(cOloR);
						grphics.FillRectangle(&sb,RectF(rect.left,rect.bottom-20,rect.right,rect.bottom));
						grphics.DrawString(string,-1,&f,PointF(0.0f, 180.0f),&blackBrush);

						dc.SetBkColor(RGB(255,255,255));
						dc.SetTextColor(RGB(112,112,112));
				
						dc.TextOutA(220+205*i,300,pindex[i+(page-1)*4].name);
						CString kC;
						kC.Format("%.2f",pindex[i+(page-1)*4].kc);
						dc.TextOutA(220+205*i,320,"库存("+pindex[i+(page-1)*4].unit+")"+kC);
						if(pindex[i+(page-1)*4].content.GetLength()>12)
							pindex[i+(page-1)*4].content=pindex[i+(page-1)*4].content.Left(12)+"...";
						dc.TextOutA(220+205*i,340,pindex[i+(page-1)*4].content);	
					}
					else if(!pindex[i+(page-1)*4].name.IsEmpty())
					{
							CStatic* pStatic = (CStatic*)GetDlgItem(IDC_MYPICTURE+i);
							CRect lRect;
							pStatic->GetClientRect(&lRect);
							pStatic->GetDC()->FillSolidRect(lRect.left,lRect.top ,lRect.Width(),lRect.Height(), RGB(255, 255, 255));		
					
							CDC *pCDC = GetDlgItem(IDC_MYPICTURE+i)->GetDC();
							HDC hdc = pCDC->GetSafeHdc();
							Graphics grphics(hdc);

							CRect rect;
							GetDlgItem(IDC_MYPICTURE+i)->GetClientRect(&rect);

							CString pIce;
							pIce.Format("%.2f",pindex[i+(page-1)*4].price);
							Gdiplus::Font f(L"幼圆", 10);
							SolidBrush blackBrush(Color(255, 255, 0, 0));
							WCHAR *string;
							pIce="￥"+pIce;
							string = T2W((LPCTSTR)pIce);
							Color cOloR(200,230,230,230);
							SolidBrush sb(cOloR);
							grphics.FillRectangle(&sb,RectF(rect.left,rect.bottom-20,rect.right,rect.bottom));
							grphics.DrawString(string,-1,&f,PointF(0.0f, 180.0f),&blackBrush);

							dc.SetBkColor(RGB(255,255,255));
							dc.SetTextColor(RGB(112,112,112));
				
							dc.TextOutA(220+205*i,300,pindex[i+(page-1)*4].name);
							CString kC;
							kC.Format("%.2f",pindex[i+(page-1)*4].kc);
							dc.TextOutA(220+205*i,320,"库存("+pindex[i+(page-1)*4].unit+")"+kC);
							if(pindex[i+(page-1)*4].content.GetLength()>12)
								pindex[i+(page-1)*4].content=pindex[i+(page-1)*4].content.Left(12)+"...";
							dc.TextOutA(220+205*i,340,pindex[i+(page-1)*4].content);	
					}
				}
			}
	}
	//****//
	//绘图完成后的清理  
	m_Back.DeleteObject();  
	mdc.DeleteDC();
	
	// 不为绘图消息调用 CDialogEx::OnPaint()
}


void CCenterStarDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//CString x;
	//x.Format("%d %d",point.x,point.y);
	//MessageBox(x);

	CRect picture1;
	GetDlgItem(IDC_MYPICTURE)->GetWindowRect(picture1);
	//CRect password(550,168,650,185);
	if(point.x<=193&&point.y>=10&&point.y<=50)
	{
		f_M_P_add=false;
		m_addproduct.EnableWindow(1);
		m_P_Detail.EnableWindow(1);
		m_changekc.EnableWindow(1);
		m_kcdetail.EnableWindow(1);
		m_kchistory.EnableWindow(1);
		m_O_add.EnableWindow(1);
		m_C_add.EnableWindow(1);
		m_C_search.EnableWindow(1);
		m_O_detail.EnableWindow(1);

		c_cpadd.ShowWindow(0);
		c_cpdeai.ShowWindow(0);
		c_kcio.ShowWindow(0);
		c_kcdt.ShowWindow(0);
		c_kcls.ShowWindow(0);
		c_ddadd.ShowWindow(0);
		c_khadd.ShowWindow(0);
		c_khdt.ShowWindow(0);
		c_dddt.ShowWindow(0);
		history();
		m_lists.ShowWindow(1);
		
	}
	if(picture1.PtInRect(point))
	{
		/*int row=m_ListCtrl.GetItemCount();
		CString name;
		GetDlgItem(IDC_MYPICTURE)->GetWindowTextA(name);
		
		m_ListCtrl.InsertItem(row,name);
		m_ListCtrl.SetItemText(row,1,"1");*/
	}
	//if(password.PtInRect(point))
	//{
	//	m_edit.MoveWindow(password);//移动Edit到RECT坐在的位置;
	//	m_edit.SetPasswordChar(7);
	//	
	//	m_edit.SetWindowText("");//将该子项中的值放在Edit控件中；
	//	m_edit.ShowWindow(SW_SHOW);//显示Edit控件；
	//	m_edit.SetFocus();//设置Edit焦点
	//	m_edit.ShowCaret();//显示光标
	//	m_edit.SetSel(-1);//将光标移动到最后
	//}
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CCenterStarDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	/*CRect close(1320,10,1352,42);
	if(close.PtInRect(point))
	{
		InvalidateRect(close,0);
		f_close=true;
	}else{
		InvalidateRect(close,0);
		f_close=false;
	}*/
	/*p_picindex[0].SetRedraw(0);
	p_picindex[1].SetRedraw(0);
	p_picindex[2].SetRedraw(0);
	p_picindex[3].SetRedraw(0);*/

	CDialogEx::OnMouseMove(nFlags, point);
}


void CCenterStarDlg::OnTimer(UINT_PTR nIDEvent)
{
	
	//页数计算
	if(indexNum%4==0)
		pageAll.Format("%d",indexNum/4);
	else
		pageAll.Format("%d",indexNum/4+1);

    if (1==nIDEvent)  
     {  
		 POINT p;  
		 GetCursorPos(&p);     
		 CWnd *hwnd;  
		 hwnd=WindowFromPoint(p);        //检索窗口中包含指定的点;点必须指定屏幕坐标在屏幕上的一个点。     
		 CWnd *hwnd2=GetDlgItem(IDCANCEL);  
		 CWnd *hwnd3=GetDlgItem(IDC_Min);  
		 CWnd *hwnd4=GetDlgItem(IDC_Test);
		 CWnd *hwnd5=GetDlgItem(IDC_ChangeKC);
		 CWnd *hwnd6=GetDlgItem(IDC_KcDetail);
		 CWnd *hwnd7=GetDlgItem(IDC_history);
		 CWnd *hwnd8=GetDlgItem(IDC_Product);
		 CWnd *hwnd9=GetDlgItem(IDC_addproduct);
		 CWnd *hwnd10=GetDlgItem(IDC_productDetail);
		 CWnd *hwnd11=GetDlgItem(IDC_O_add);
		 CWnd *hwnd12=GetDlgItem(IDC_O_Detail);
		 CWnd *hwnd13=GetDlgItem(IDC_lastpage);
		 CWnd *hwnd14=GetDlgItem(IDC_nextpage);
		 if (hwnd2 == hwnd)         //如果鼠标在按钮上  
		 {  
			 if (GetFocus()!=hwnd2)        //如果按钮无焦点，那么设置焦点  
				 hwnd2->SetFocus() ;  
		 }  
		 else          //如果鼠标不在按钮上；  
		 {  
			 if (GetFocus() == hwnd2 )                  //如果按钮有焦点，那么去焦点；  
				 GetDlgItem(IDOK)->SetFocus();      //这里的IDOK为想跳转到的控件ID号
		 } 
		 if(hwnd3==hwnd)
		 {
			  if (GetFocus()!=hwnd3)      
				 hwnd3->SetFocus() ;  
		 }else            
		 {  
			 if (GetFocus() == hwnd3 )                  
				 GetDlgItem(IDOK)->SetFocus();      
		 } 
		 if(hwnd4==hwnd)
		 {
			  if (GetFocus()!=hwnd4)        
				 hwnd4->SetFocus() ;  
		 }else         
		 {  
			 if (GetFocus() == hwnd4 )                 
				 GetDlgItem(IDOK)->SetFocus();    
		 } 
		 if(hwnd5==hwnd)
		 {
			  if (GetFocus()!=hwnd5)        
				 hwnd5->SetFocus() ;  
		 }else         
		 {  
			 if (GetFocus() == hwnd5)                 
				 GetDlgItem(IDOK)->SetFocus();    
		 } 
		 if(hwnd6==hwnd)
		 {
			  if (GetFocus()!=hwnd6)        
				 hwnd6->SetFocus() ;  
		 }else         
		 {  
			 if (GetFocus() == hwnd6)                 
				 GetDlgItem(IDOK)->SetFocus();    
		 } 
		 if(hwnd7==hwnd)
		 {
			  if (GetFocus()!=hwnd7)        
				 hwnd7->SetFocus() ;  
		 }else         
		 {  
			 if (GetFocus() == hwnd7)                 
				 GetDlgItem(IDOK)->SetFocus();    
		 }
		 if(hwnd8==hwnd)
		 {
			  if (GetFocus()!=hwnd8)        
				 hwnd8->SetFocus() ;  
		 }else         
		 {  
			 if (GetFocus() == hwnd8)                 
				 GetDlgItem(IDOK)->SetFocus();    
		 } 
		 if(hwnd9==hwnd)
		 {
			  if (GetFocus()!=hwnd9)        
				 hwnd9->SetFocus() ;  
		 }else         
		 {  
			/* if (GetFocus() == hwnd9)                 
				 GetDlgItem(IDOK)->SetFocus();    */
		 } 
		 if(hwnd10==hwnd)
		 {
			  if (GetFocus()!=hwnd10)        
				 hwnd10->SetFocus() ;  
		 }else         
		 {  
			 if (GetFocus() == hwnd10)                 
				 GetDlgItem(IDOK)->SetFocus();    
		 } 
		 if(hwnd11==hwnd)
		 {
			  if (GetFocus()!=hwnd11)        
				 hwnd11->SetFocus() ;  
		 }else         
		 {  
			 if (GetFocus() == hwnd11)                 
				 GetDlgItem(IDOK)->SetFocus();    
		 } 
		 if(hwnd12==hwnd)
		 {
			  if (GetFocus()!=hwnd12)        
				 hwnd12->SetFocus() ;  
		 }else         
		 {  
			 if (GetFocus() == hwnd12)                 
				 GetDlgItem(IDOK)->SetFocus();    
		 } 
		 if(hwnd13==hwnd)
		 {
			  if (GetFocus()!=hwnd13)        
				 hwnd13->SetFocus() ;  
		 }else         
		 {  
			 if (GetFocus() == hwnd13)                 
				 GetDlgItem(IDOK)->SetFocus();    
		 } 
		 if(hwnd14==hwnd)
		 {
			  if (GetFocus()!=hwnd14)        
				 hwnd14->SetFocus() ;  
		 }else         
		 {  
			 if (GetFocus() == hwnd14)                 
				 GetDlgItem(IDOK)->SetFocus();    
		 } 
	}  
	CDialogEx::OnTimer(nIDEvent);
}


void CCenterStarDlg::OnBnClickedTest()
{
	
	    
	
}
void CCenterStarDlg::_initPictrue()
{
	
	
	for(int i=0;i<4;i++)
	{
		if(NULL==p_picindex[i].GetSafeHwnd())
				p_picindex[i].Create(_T( "" ), WS_BORDER | WS_EX_TRANSPARENT|WS_CHILD | WS_VISIBLE  | SS_BITMAP| SS_CENTERIMAGE, CRect (220+205*i,100,421+205*i,301), this,IDC_MYPICTURE+i);					
	}
}
void CCenterStarDlg::_initButton()
{
	m_close.LoadBitmaps(IDB_BITMAP2,IDB_BITMAP3,IDB_BITMAP3);   //载入
	m_close.SizeToContent();  //使按钮适应图片大小
	m_close.MoveWindow(cx-46,10,32,32);

	m_min.LoadBitmaps(IDB_BITMAP4,IDB_BITMAP5,IDB_BITMAP5);
	m_min.SizeToContent(); 
	m_min.MoveWindow(cx-86,10,32,32);

	m_test.LoadBitmaps(IDB_BITMAP8,IDB_BITMAP9,IDB_BITMAP9);
	m_test.SizeToContent(); 
	m_test.MoveWindow(10,74,156,32);

	m_changekc.LoadBitmaps(IDB_BITMAP10,IDB_BITMAP14,IDB_BITMAP11,IDB_BITMAP14);
	m_changekc.SizeToContent();  
	m_changekc.MoveWindow(0,120,200,25);

	m_kcdetail.LoadBitmaps(IDB_BITMAP12,IDB_BITMAP15,IDB_BITMAP13,IDB_BITMAP15);
	m_kcdetail.SizeToContent();  
	m_kcdetail.MoveWindow(0,150,200,24);

	m_kchistory.LoadBitmaps(IDB_BITMAP16,IDB_BITMAP18,IDB_BITMAP17,IDB_BITMAP18);
	m_kchistory.SizeToContent();  
	m_kchistory.MoveWindow(0,180,200,25);

	m_product.LoadBitmaps(IDB_BITMAP19,IDB_BITMAP19,IDB_BITMAP19);
	m_product.SizeToContent();  
	m_product.MoveWindow(0,230,170,36);

	m_addproduct.LoadBitmaps(IDB_BITMAP21,IDB_BITMAP23,IDB_BITMAP22,IDB_BITMAP23);
	m_addproduct.SizeToContent();  
	m_addproduct.MoveWindow(0,280,200,25);

	m_P_Detail.LoadBitmaps(IDB_BITMAP24,IDB_BITMAP26,IDB_BITMAP25,IDB_BITMAP26);
	m_P_Detail.SizeToContent();  
	m_P_Detail.MoveWindow(0,310,200,26);

	m_order.LoadBitmaps(IDB_BITMAP27);
	m_order.SizeToContent();  
	m_order.MoveWindow(0,360,170,37);

	m_O_add.LoadBitmaps(IDB_BITMAP28,IDB_BITMAP30,IDB_BITMAP29,IDB_BITMAP30);
	m_O_add.SizeToContent();  
	m_O_add.MoveWindow(0,410,200,26);

	m_O_detail.LoadBitmaps(IDB_BITMAP31,IDB_BITMAP33,IDB_BITMAP32,IDB_BITMAP33);
	m_O_detail.SizeToContent();  
	m_O_detail.MoveWindow(0,440,200,26);

	m_customer.LoadBitmaps(IDB_BITMAP34);
	m_customer.SizeToContent();  
	m_customer.MoveWindow(0,490,170,37);

	m_C_add.LoadBitmaps(IDB_BITMAP35);
	m_C_add.SizeToContent();  
	m_C_add.MoveWindow(30,540,32,32);

	m_C_search.LoadBitmaps(IDB_BITMAP36);
	m_C_search.SizeToContent();  
	m_C_search.MoveWindow(100,540,32,32);
	
	m_lastpage.LoadBitmaps(IDB_BITMAP44,IDB_BITMAP46,IDB_BITMAP45,IDB_BITMAP47);
	m_lastpage.MoveWindow(960,363,32,32);

	m_nextpage.LoadBitmaps(IDB_BITMAP48,IDB_BITMAP50,IDB_BITMAP49,IDB_BITMAP51);
	m_nextpage.MoveWindow(1000,363,32,32);

	GetDlgItem(IDOK)->MoveWindow(50,cy-70,100,30);
}
void CCenterStarDlg::_initDialog()
{
	CRect clist0(200,54,1050,766);
	GetDlgItem(IDC_chirld)->MoveWindow(clist0);
	//录入产品
	c_cpadd.Create(IDD_M_P_add,this);
	GetDlgItem(IDC_chirld)->GetWindowRect(&m_c);  
    ScreenToClient(m_c);
	c_cpadd.MoveWindow(m_c);
	c_cpadd.ShowWindow(0);
	//产品信息
	c_cpdeai.Create(IDD_M_P_detail,this);
	//我的库存-出入库
	c_kcio.Create(IDD_IO,this);
	//我的库存-库存明细
	c_kcdt.Create(IDD_KCDetail,this);
	//我的库存-历史记录
	c_kcls.Create(IDD_KChistory,this);
	//我的订单-生成订单
	c_ddadd.Create(IDD_M_O_add,this);
	//我的客户-添加
	c_khadd.Create(IDD_M_C_add,this);
	//我的客户-详细
	c_khdt.Create(IDD_M_C_detail,this);
	//我的订单-详细
	c_dddt.Create(IDD_M_O_detail,this);
}

void CCenterStarDlg::OnM_P_add()
{
	m_lastpage.ShowWindow(0);
	m_nextpage.ShowWindow(0);
	m_lists.ShowWindow(0);
	f_M_P_add=true;
	m_addproduct.EnableWindow(0);
	m_P_Detail.EnableWindow(1);
	m_changekc.EnableWindow(1);
	m_kcdetail.EnableWindow(1);
	m_kchistory.EnableWindow(1);
	m_O_add.EnableWindow(1);
	m_C_add.EnableWindow(1);
	m_C_search.EnableWindow(1);
	m_O_detail.EnableWindow(1);

	c_cpadd.ShowWindow(1);
	c_cpdeai.ShowWindow(0);
	c_kcdt.ShowWindow(0);
	c_kcio.ShowWindow(0);
	c_kcls.ShowWindow(0);
	c_ddadd.ShowWindow(0);
	c_khadd.ShowWindow(0);
	c_khdt.ShowWindow(0);
	c_dddt.ShowWindow(0);
}


BOOL CCenterStarDlg::DestroyWindow()
{
	//释放指针回收资源
	delete[indexNum] pindex;
	delete[indexNum] pinfo;
	delete[indexNum] kcindex;
	if(c_kcdt.pageMax!=0)
		delete[c_kcdt.pageMax] c_kcdt.pageIDs;
	delete[kclsNum] kchistory;
	database.CloseMySQLConn();
	if(c_dddt.orderNum!=0)
		delete [c_dddt.orderNum] c_dddt.oder;
	return CDialogEx::DestroyWindow();
}


void CCenterStarDlg::OnBnClickednextpage()
{
	m_lastpage.EnableWindow(1);
	int pageALL;
	pageALL=atoi(pageAll);
	if(page<pageALL)
		page++;
	if(page==pageALL)
		m_nextpage.EnableWindow(0);

	for(int i=0;i<4;i++)
	{
		p_picindex[i].ShowWindow(1);
		if( i >= (indexNum-(page-1)*4) )
			p_picindex[i].ShowWindow(0);
	}

	InvalidateRect(CRect(900,365,960,400),0);
	InvalidateRect(CRect(201,301,1049,365),0);
}


void CCenterStarDlg::OnBnClickedlastpage()
{
	page--;
	InvalidateRect(CRect(900,365,960,400),0);
	InvalidateRect(CRect(201,301,1049,365),0);
	m_nextpage.EnableWindow(1);
	if(page==1)
		m_lastpage.EnableWindow(0);
	for(int i=0;i<4;i++)
	{
		p_picindex[i].ShowWindow(1);
		if( i >= (indexNum-(page-1)*4) )
			p_picindex[i].ShowWindow(0);
	}
}


BOOL CCenterStarDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	return TRUE; 
	//return CDialogEx::OnEraseBkgnd(pDC);
}


void CCenterStarDlg::OnM_Pdeai()
{
	m_lastpage.ShowWindow(0);
	m_nextpage.ShowWindow(0);
	m_lists.ShowWindow(0);
	f_M_P_add=true;
	m_addproduct.EnableWindow(1);
	m_changekc.EnableWindow(1);
	m_kcdetail.EnableWindow(1);
	m_kchistory.EnableWindow(1);
	m_O_add.EnableWindow(1);
	m_C_add.EnableWindow(1);
	m_C_search.EnableWindow(1);
	m_O_detail.EnableWindow(1);
	m_P_Detail.EnableWindow(0);
	
	c_cpdeai.ShowWindow(1);
	c_cpdeai.MoveWindow(m_c);
	c_cpadd.ShowWindow(0);
	c_kcio.ShowWindow(0);
	c_kcdt.ShowWindow(0);
	c_kcls.ShowWindow(0);
	c_ddadd.ShowWindow(0);
	c_khadd.ShowWindow(0);
	c_khdt.ShowWindow(0);
	c_dddt.ShowWindow(0);
	//产品信息
	product.selectInfor();
	c_cpdeai.m_edit.SetWindowTextA("");
	c_cpdeai.m_edit.ShowWindow(0);
	//页数计算
	if(infoNum%12==0)
		c_cpdeai.pageAll.Format("%d",infoNum/12);
	else
		c_cpdeai.pageAll.Format("%d",infoNum/12+1);
	for(int i=0;i<12;i++)
	{	
		c_cpdeai.pic[i].ShowWindow(1);
		c_cpdeai.pic[i].Invalidate();
		if(i>=infoNum)
			c_cpdeai.pic[i].ShowWindow(0);
	}
	if(infoNum>12)
	{
		c_cpdeai.m_lastpage.ShowWindow(1);
		c_cpdeai.m_nextpage.ShowWindow(1);
	}else{
		c_cpdeai.m_lastpage.ShowWindow(0);
		c_cpdeai.m_nextpage.ShowWindow(0);
	}
	c_cpdeai.page=1;
	for(int i=0;i<12;i++)
	{
		if(c_cpdeai.pic[i].IsWindowVisible())
		{
			CString strKc;
			strKc.Format("%.2f",pinfo[i+(c_cpdeai.page-1)*12].kc);
			if(!pinfo[i+(c_cpdeai.page-1)*12].content.IsEmpty())
				c_cpdeai.m_Mytip.AddTool( c_cpdeai.GetDlgItem(IDC_MYPICTURE+i), _T("库存:"+strKc+"("+pinfo[i+(c_cpdeai.page-1)*12].unit+")"+"\n详细信息:\n      "+pinfo[i+(c_cpdeai.page-1)*12].content) );
			else
				c_cpdeai.m_Mytip.AddTool( c_cpdeai.GetDlgItem(IDC_MYPICTURE+i), _T("库存:"+strKc+"("+pinfo[i+(c_cpdeai.page-1)*12].unit+")"+"\n详细信息:无"));

		}else{
			break;
		}
	}
	//产品详细页控件处理
	c_cpdeai.e_name.ShowWindow(0);
	c_cpdeai.e_price.ShowWindow(0);
	c_cpdeai.e_kc.ShowWindow(0);
	c_cpdeai.e_unit.ShowWindow(0);
	c_cpdeai.e_content.ShowWindow(0);
}


void CCenterStarDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	
}


void CCenterStarDlg::OnM_I_io()
{
	m_lastpage.ShowWindow(0);
	m_nextpage.ShowWindow(0);
	m_lists.ShowWindow(0);
	f_M_P_add=true;
	m_addproduct.EnableWindow(1);
	m_P_Detail.EnableWindow(1);
	m_kcdetail.EnableWindow(1);
	m_kchistory.EnableWindow(1);
	m_O_add.EnableWindow(1);
	m_C_add.EnableWindow(1);
	m_C_search.EnableWindow(1);
	m_O_detail.EnableWindow(1);
	m_changekc.EnableWindow(0);

	c_cpadd.ShowWindow(0);
	c_cpdeai.ShowWindow(0);
	c_kcdt.ShowWindow(0);
	c_kcls.ShowWindow(0);
	c_ddadd.ShowWindow(0);
	c_khadd.ShowWindow(0);
	c_khdt.ShowWindow(0);
	c_dddt.ShowWindow(0);
	c_kcio.ShowWindow(1);
	c_kcio.MoveWindow(m_c);
}


void CCenterStarDlg::OnM_I_detail()
{
	m_lastpage.ShowWindow(0);
	m_nextpage.ShowWindow(0);
	m_lists.ShowWindow(0);
	f_M_P_add=true;
	m_addproduct.EnableWindow(1);
	m_P_Detail.EnableWindow(1);
	m_changekc.EnableWindow(1);
	m_kchistory.EnableWindow(1);
	m_O_add.EnableWindow(1);
	m_C_add.EnableWindow(1);
	m_C_search.EnableWindow(1);
	m_O_detail.EnableWindow(1);
	m_kcdetail.EnableWindow(0);

	c_cpadd.ShowWindow(0);
	c_cpdeai.ShowWindow(0);
	c_kcio.ShowWindow(0);
	c_kcls.ShowWindow(0);
	c_ddadd.ShowWindow(0);
	c_khadd.ShowWindow(0);
	c_khdt.ShowWindow(0);
	c_dddt.ShowWindow(0);
	c_kcdt.ShowWindow(1);
	c_kcdt.MoveWindow(m_c);
	c_kcdt.penPic=true;
	c_kcdt.barchart=true;
	c_kcdt.fanchart=false;
	if(c_kcdt.pc->GetCheck())
	{
		c_kcdt.pc->SetCheck(0);
	}
	if(c_kcdt.pr->GetCheck())
	{
		c_kcdt.pr->SetCheck(0);
	}
	c_kcdt.m_changePic.ShowWindow(1);
	c_kcdt.m_changePics.ShowWindow(0);
	c_kcdt.pc->ShowWindow(1);
	c_kcdt.pr->ShowWindow(1);
	c_kcdt.m_lastpage.ShowWindow(1);
	c_kcdt.m_nextpage.ShowWindow(1);
	c_kcdt.Fcdetail=false;
	c_kcdt.FcMonth=-1;
	c_kcdt.show();
	c_kcdt.tally();
	c_kcdt.m_d1.ShowWindow(0);
	c_kcdt.m_d2.ShowWindow(0);
}


void CCenterStarDlg::OnM_I_history()
{
	m_lastpage.ShowWindow(0);
	m_nextpage.ShowWindow(0);
	m_lists.ShowWindow(0);
	f_M_P_add=true;
	m_addproduct.EnableWindow(1);
	m_P_Detail.EnableWindow(1);
	m_kcdetail.EnableWindow(1);
	m_changekc.EnableWindow(1);
	m_O_add.EnableWindow(1);
	m_C_add.EnableWindow(1);
	m_C_search.EnableWindow(1);
	m_O_detail.EnableWindow(1);
	m_kchistory.EnableWindow(0);

	c_cpadd.ShowWindow(0);
	c_cpdeai.ShowWindow(0);
	c_kcdt.ShowWindow(0);
	c_kcio.ShowWindow(0);
	c_ddadd.ShowWindow(0);
	c_khadd.ShowWindow(0);
	c_khdt.ShowWindow(0);
	c_dddt.ShowWindow(0);
	c_kcls.ShowWindow(1);
	c_kcls.MoveWindow(m_c);
	c_kcls.show();
}


void CCenterStarDlg::OnM_O_add()
{
	m_lastpage.ShowWindow(0);
	m_nextpage.ShowWindow(0);
	m_lists.ShowWindow(0);
	f_M_P_add=true;
	m_addproduct.EnableWindow(1);
	m_P_Detail.EnableWindow(1);
	m_kcdetail.EnableWindow(1);
	m_changekc.EnableWindow(1);
	m_kchistory.EnableWindow(1);
	m_C_add.EnableWindow(1);
	m_C_search.EnableWindow(1);
	m_O_detail.EnableWindow(1);
	m_O_add.EnableWindow(0);

	c_cpadd.ShowWindow(0);
	c_cpdeai.ShowWindow(0);
	c_kcdt.ShowWindow(0);
	c_kcio.ShowWindow(0);
	c_kcls.ShowWindow(0);
	c_khadd.ShowWindow(0);
	c_khdt.ShowWindow(0);
	c_dddt.ShowWindow(0);
	c_ddadd.ShowWindow(1);
	c_ddadd.MoveWindow(m_c);
}


void CCenterStarDlg::OnM_C_add()
{
	m_lastpage.ShowWindow(0);
	m_nextpage.ShowWindow(0);
	m_lists.ShowWindow(0);
	f_M_P_add=true;
	m_addproduct.EnableWindow(1);
	m_P_Detail.EnableWindow(1);
	m_kcdetail.EnableWindow(1);
	m_changekc.EnableWindow(1);
	m_kchistory.EnableWindow(1);
	m_O_add.EnableWindow(1);
	m_C_search.EnableWindow(1);
	m_O_detail.EnableWindow(1);
	m_C_add.EnableWindow(0);

	c_cpadd.ShowWindow(0);
	c_cpdeai.ShowWindow(0);
	c_kcdt.ShowWindow(0);
	c_kcio.ShowWindow(0);
	c_kcls.ShowWindow(0);
	c_ddadd.ShowWindow(0);
	c_khdt.ShowWindow(0);
	c_dddt.ShowWindow(0);
	c_khadd.ShowWindow(1);
	c_khadd.MoveWindow(m_c);
}


void CCenterStarDlg::OnM_C_detail()
{
	m_lastpage.ShowWindow(0);
	m_nextpage.ShowWindow(0);
	m_lists.ShowWindow(0);
	f_M_P_add=true;
	m_addproduct.EnableWindow(1);
	m_P_Detail.EnableWindow(1);
	m_kcdetail.EnableWindow(1);
	m_changekc.EnableWindow(1);
	m_kchistory.EnableWindow(1);
	m_O_add.EnableWindow(1);
	m_C_add.EnableWindow(1);
	m_O_detail.EnableWindow(1);
	m_C_search.EnableWindow(0);

	c_cpadd.ShowWindow(0);
	c_cpdeai.ShowWindow(0);
	c_kcdt.ShowWindow(0);
	c_kcio.ShowWindow(0);
	c_kcls.ShowWindow(0);
	c_ddadd.ShowWindow(0);
	c_khadd.ShowWindow(0);
	c_dddt.ShowWindow(0);
	c_khdt.ShowWindow(1);
	c_khdt.MoveWindow(m_c);
	c_khdt.show();
}


void CCenterStarDlg::OnM_O_Detail()
{
	m_lastpage.ShowWindow(0);
	m_nextpage.ShowWindow(0);
	m_lists.ShowWindow(0);
	f_M_P_add=true;
	m_addproduct.EnableWindow(1);
	m_P_Detail.EnableWindow(1);
	m_kcdetail.EnableWindow(1);
	m_changekc.EnableWindow(1);
	m_kchistory.EnableWindow(1);
	m_O_add.EnableWindow(1);
	m_C_add.EnableWindow(1);
	m_C_search.EnableWindow(1);
	m_O_detail.EnableWindow(0);

	c_cpadd.ShowWindow(0);
	c_cpdeai.ShowWindow(0);
	c_kcdt.ShowWindow(0);
	c_kcio.ShowWindow(0);
	c_kcls.ShowWindow(0);
	c_ddadd.ShowWindow(0);
	c_khadd.ShowWindow(0);
	c_khdt.ShowWindow(0);
	c_dddt.ShowWindow(1);
	c_dddt.MoveWindow(m_c);
	c_dddt.show();
}
void CCenterStarDlg::history()
{
	CString sql;
	GetLocalTime(&CurTime);////获取本地时间 
	CString y,m,d;
	y.Format("%d",CurTime.wYear);
	if(CurTime.wMonth<10)
		m.Format("0%d",CurTime.wMonth);
	else
		m.Format("%d",CurTime.wMonth);
	if(CurTime.wDay<10)
		d.Format("0%d",CurTime.wDay);
	else
		d.Format("%d",CurTime.wDay);
	sql.Format("SELECT * FROM tally.history where H_time>='%s' and H_time<=now();",y+"-"+m+"-"+d);
	h.search(sql);
	m_lists.SetRedraw(0);
	m_lists.DeleteAllItems();

	if(kclsNum>0)
	{
		CString stri,rk,ck,kc;
		for(int i=0;i<kclsNum;i++)
		{
			stri.Format("%d",i+1);
			m_lists.InsertItem(i,stri);
			m_lists.SetItemText(i,1,kchistory[i].content);
			m_lists.SetItemText(i,2,kchistory[i].time);
		}
	}
	m_lists.SetRedraw(1);
	m_lists.Invalidate();
}

void CCenterStarDlg::OnMin()
{
	ShowWindow(SW_SHOWMINIMIZED);
} 
