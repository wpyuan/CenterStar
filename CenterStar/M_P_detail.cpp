// M_P_detail.cpp : 实现文件
//

#include "stdafx.h"
#include "CenterStar.h"
#include "M_P_detail.h"
#include "afxdialogex.h"


// M_P_detail 对话框

IMPLEMENT_DYNAMIC(M_P_detail, CDialogEx)

M_P_detail::M_P_detail(CWnd* pParent /*=NULL*/)
	: CDialogEx(M_P_detail::IDD, pParent)
{

}

M_P_detail::~M_P_detail()
{
}

void M_P_detail::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_ok);
	DDX_Control(pDX, IDCANCEL, m_cancel);
	DDX_Control(pDX, IDC_information, m_info);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
	DDX_Control(pDX, IDC_lastpage, m_lastpage);
	DDX_Control(pDX, IDC_nextpage, m_nextpage);
	DDX_Control(pDX, IDC_edit, b_edit);
	DDX_Control(pDX, IDC_delete, b_delete);
	DDX_Control(pDX, IDC_EDIT2, e_name);
	DDX_Control(pDX, IDC_EDIT3, e_price);
	DDX_Control(pDX, IDC_EDIT4, e_kc);
	DDX_Control(pDX, IDC_EDIT5, e_unit);
	DDX_Control(pDX, IDC_EDIT6, e_content);
}


BEGIN_MESSAGE_MAP(M_P_detail, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDCANCEL, &M_P_detail::OnCancel)
	ON_BN_CLICKED(IDC_information, &M_P_detail::Oninfo)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDOK, &M_P_detail::OnSearchText)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_lastpage, &M_P_detail::OnBnClickedlastpage)
	ON_BN_CLICKED(IDC_nextpage, &M_P_detail::OnBnClickednextpage)
	ON_EN_KILLFOCUS(IDC_EDIT2, &M_P_detail::OnEnKillfocusEdit2)
	ON_EN_KILLFOCUS(IDC_EDIT3, &M_P_detail::OnEnKillfocusEdit3)
	ON_EN_KILLFOCUS(IDC_EDIT4, &M_P_detail::OnEnKillfocusEdit4)
	ON_EN_KILLFOCUS(IDC_EDIT5, &M_P_detail::OnEnKillfocusEdit5)
	ON_EN_KILLFOCUS(IDC_EDIT6, &M_P_detail::OnEnKillfocusEdit6)
//	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// M_P_detail 消息处理程序


void M_P_detail::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CBitmap m_Back;
	m_Back.LoadBitmap(IDB_BITMAP52);
	CDC mdc;
	mdc.CreateCompatibleDC(&dc); 
	mdc.SelectObject(&m_Back);
	
	if(infoNum==0)
	{
		CFont f;
		f.CreatePointFont(250,"幼圆");
		mdc.SelectObject(f);	  
		mdc.TextOutA(250,293,"0条相关记录");
		f.DeleteObject();
	}else{
		if(infoNum>12)
		{
			m_lastpage.ShowWindow(1);
			m_nextpage.ShowWindow(1);
		}

		CFont f;
		f.CreatePointFont(140,"幼圆");
		mdc.SelectObject(f);	  
		CString pageNow;
		pageNow.Format("%d",page);
		CString nUM;
		nUM.Format("%d",infoNum);
		mdc.TextOutA(20,680,"共"+nUM+"件产品");
		mdc.TextOutA(700,680,pageNow+"/"+pageAll);
		f.DeleteObject();
	}
	dc.BitBlt(0,0,850,712,&mdc,0,0,SRCCOPY);

	USES_CONVERSION;
	WCHAR* pBuf;
	if(infoNum>0)
	{		
		for(int i=0;i<12;i++)
		{	
			if(i+(page-1)*12<infoNum)
			{
				if(!pinfo[i+(page-1)*12].image.IsEmpty())
				{
					pBuf = T2W((LPCTSTR)pinfo[i+(page-1)*12].image);
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
						pStatic->GetDC()->FillSolidRect(lRect.left ,(int)(lRect.Height()/2+y/2) ,(int)lRect.Width(),(int)(lRect.Height()/2+1-y/2), RGB(255, 255, 255));//下		
					
						grp.DrawImage(&b,0,0,(int)x,(int)y);
						grphics.DrawImage(&bitmap,0,(int)(100-y/2));	
					}else	{
						double IndexWH=(double)b.GetHeight()/(double)200;
						y=200;
						x=(double)b.GetWidth()/(double)IndexWH;
					
						CStatic* pStatic = (CStatic*)GetDlgItem(IDC_MYPICTURE+i);
						CRect lRect;
						pStatic->GetClientRect(&lRect);
						pStatic->GetDC()->FillSolidRect(lRect.left,lRect.top+1 ,(int)(lRect.Width()/2-x/2+1),(int)(lRect.Height()-1), RGB(255, 255, 255));//左
						pStatic->GetDC()->FillSolidRect((int)(lRect.Width()/2+x/2) ,lRect.top+1 ,(int)(lRect.Width()/2-x/2+2),lRect.Height()-1, RGB(255, 255, 255));//右

						grp.DrawImage(&b,0,0,(int)x,(int)y);
						grphics.DrawImage(&bitmap,(int)(100-x/2),0);	
					}
					CString pIce;
					pIce.Format("%.2f",pinfo[i+(page-1)*12].price);
					Gdiplus::Font f(L"幼圆", 10);
					SolidBrush blackBrush(Color(200, 255, 0, 0));
					WCHAR *string;
					pIce="￥"+pIce;	
					Color cOloR(100,230,230,230);
					SolidBrush sb(cOloR);
					grphics.FillRectangle(&sb,RectF((REAL)rect.left,(REAL)rect.top,(REAL)rect.Width(),20));
					grphics.FillRectangle(&sb,RectF((REAL)rect.left,(REAL)rect.bottom-20,(REAL)rect.Width(),20));
					
					SolidBrush sbs(Color(120,0,0,0));
					grphics.FillRectangle(&sbs,RectF((REAL)rect.left+10,(REAL)rect.bottom-40,75,20));
					grphics.FillRectangle(&sbs,RectF((REAL)rect.Width()/2+10,(REAL)rect.bottom-40,75,20));
					
					string = T2W((LPCTSTR)pinfo[i+(page-1)*12].name);
					grphics.DrawString(string,-1,&f,PointF(0.0f, 5.0f),&SolidBrush(Color(200,0,0,0)));
					string = T2W((LPCTSTR)pIce);
					grphics.DrawString(string,-1,&f,PointF(0.0f, 180.0f),&blackBrush);

					SolidBrush blackBrushs(Color(200, 230, 230, 230));
					string = T2W((LPCTSTR)"编辑");
					grphics.DrawString(string,-1,&f,PointF(30.0f, 160.0f),&blackBrushs);

					string = T2W((LPCTSTR)"删除");
					grphics.DrawString(string,-1,&f,PointF(130.0f, 160.0f),&blackBrushs);

				}else{		
					if(!pinfo[i+(page-1)*12].name.IsEmpty())  
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
						pIce.Format("%.2f",pinfo[i+(page-1)*12].price);
						Gdiplus::Font f(L"幼圆", 10);
						SolidBrush blackBrush(Color(200, 255, 0, 0));
						WCHAR *string;
						pIce="￥"+pIce;	
						Color cOloR(100,230,230,230);
						SolidBrush sb(cOloR);
						grphics.FillRectangle(&sb,RectF((REAL)rect.left,(REAL)rect.bottom-20,(REAL)rect.Width(),(REAL)rect.bottom));
						grphics.FillRectangle(&sb,RectF((REAL)rect.left,(REAL)rect.top,(REAL)rect.Width(),(REAL)rect.top+20));
						
						SolidBrush sbs(Color(120,0,0,0));
						grphics.FillRectangle(&sbs,RectF((REAL)rect.left+10,(REAL)rect.bottom-40,75,20));
						grphics.FillRectangle(&sbs,RectF((REAL)rect.Width()/2+10,(REAL)rect.bottom-40,75,20));

						string = T2W((LPCTSTR)pinfo[i+(page-1)*12].name);
						grphics.DrawString(string,-1,&f,PointF(0.0f, 0.0f),&SolidBrush(Color(200,0,0,0)));
						string = T2W((LPCTSTR)pIce);
						grphics.DrawString(string,-1,&f,PointF(0.0f, 180.0f),&blackBrush);
			
						SolidBrush blackBrushs(Color(200, 230, 230, 230));
						string = T2W((LPCTSTR)"编辑");
						grphics.DrawString(string,-1,&f,PointF(30.0f, 160.0f),&blackBrushs);

						string = T2W((LPCTSTR)"删除");
						grphics.DrawString(string,-1,&f,PointF(130.0f, 160.0f),&blackBrushs);
					}
				}
			}
		}
	}


	//绘图完成后的清理  
	m_Back.DeleteObject();  
	mdc.DeleteDC();
	// 不为绘图消息调用 CDialogEx::OnPaint()
}


BOOL M_P_detail::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化.
	_initButton();
	_initPicture();
	page=1;
	sx=0;
	isEdit=false;
	EnableToolTips(TRUE);
	m_Mytip.Create(this);
	m_Mytip.SetDelayTime(50); //设置延迟
	m_Mytip.SetTipTextColor( RGB(0,0,0) ); //设置提示文本的颜色
	m_Mytip.SetTipBkColor( RGB(199,237,204)); //设置提示框的背景颜色
	m_Mytip.SetMaxTipWidth(200);  //设置宽度
	m_Mytip.Activate(true); //设置是否启用提示
	SetTimer(1,200,NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
void M_P_detail::_initButton()
{
	GetDlgItem(IDOK)->MoveWindow(665,9,36,33);
	m_ok.LoadBitmaps(IDB_BITMAP53);
	GetDlgItem(IDCANCEL)->MoveWindow(152,12,50,27);
	m_cancel.LoadBitmaps(IDB_BITMAP54);
	GetDlgItem(IDC_information)->MoveWindow(152,12,50,27);
	m_info.LoadBitmaps(IDB_BITMAP55);

	m_lastpage.LoadBitmaps(IDB_BITMAP44,IDB_BITMAP46,IDB_BITMAP45,IDB_BITMAP47);
	m_lastpage.MoveWindow(760,670,32,32);

	m_nextpage.LoadBitmaps(IDB_BITMAP48,IDB_BITMAP50,IDB_BITMAP49,IDB_BITMAP51);
	m_nextpage.MoveWindow(800,670,32,32);

	b_edit.LoadBitmaps(IDB_BITMAP56);
	b_edit.SizeToContent();  

	b_delete.LoadBitmaps(IDB_BITMAP42);
	b_delete.SizeToContent();  
	b_edit.MoveWindow(0,0,32,32);
	b_delete.MoveWindow(800,0,32,32);
	/*b_edit.ShowWindow(1);
	b_delete.ShowWindow(1);*/
}
void M_P_detail::_initPicture()
{
	int j=0,k=0;
	for(int i=0;i<12;i++)
	{
		//picUD[i]=false;
		if(NULL==pic[i].GetSafeHwnd())
				pic[i].Create(_T( "" ), WS_BORDER | WS_EX_TRANSPARENT|WS_CHILD | WS_VISIBLE  | SS_BITMAP| SS_CENTERIMAGE | SS_NOTIFY, CRect (20+205*j,50+205*k,221+205*j,251+205*k), this,IDC_MYPICTURE+i);				
		j++;
		if(i==3||i==7)
		{
			j=0;
			k++;
		}
	}
}
void M_P_detail::OnCancel()
{
	m_info.ShowWindow(1);
	m_cancel.ShowWindow(0);
}


void M_P_detail::Oninfo()
{
	m_info.ShowWindow(0);
	m_cancel.ShowWindow(1);
}


void M_P_detail::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect text(201,18,663,38);
	CString str;
	m_edit.GetWindowText(str);

	if (text.PtInRect(point))       
	{
		m_edit.MoveWindow(text);
		if(str.IsEmpty())
			m_edit.SetWindowText("");
		else
			m_edit.SetWindowText(str);//将该子项中的值放在Edit控件中；

		m_edit.ShowWindow(SW_SHOW);//显示Edit控件；
		m_edit.SetFocus();//设置Edit焦点
		m_edit.ShowCaret();//显示光标
		m_edit.SetSel(-1);//将光标移动到最后
	}else{
		if(str.IsEmpty())
			m_edit.ShowWindow(0);
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}


BOOL M_P_detail::PreTranslateMessage(MSG* pMsg)
{
	if (NULL != m_Mytip.GetSafeHwnd())
    {
        m_Mytip.RelayEvent(pMsg);
    }
	if(pMsg->message==WM_LBUTTONDOWN)
	{
		GetDlgItem(IDOK)->SetFocus();      //这里的IDOK为想跳转到的控件ID号
		CRect p[12];
		CRect pPoint[12];
		CRect dPoint[12];
		CRect cPoint[12];

		for(int j=0; j<12; j++)
		{
			pic[j].GetWindowRect(p[j]);
			pPoint[j].left=p[j].left+10;
			pPoint[j].top=p[j].bottom-40;
			pPoint[j].right=p[j].left+85;
			pPoint[j].bottom=p[j].bottom-20;

			dPoint[j].left=p[j].right-95;
			dPoint[j].top=p[j].bottom-40;
			dPoint[j].right=p[j].right-20;
			dPoint[j].bottom=p[j].bottom-20;

			cPoint[j].left=p[j].right-85;
			cPoint[j].top=p[j].top+3;
			cPoint[j].right=p[j].right;
			cPoint[j].bottom=p[j].top+20;

			if(cPoint[j].PtInRect(pMsg->pt))
			{
				if(j==sx&&isEdit)
				{
					isEdit=false;//更换图片成功

					CString str;
					strFilePath=pinfo[j+(page-1)*12].image;
					str=strFilePath;
					/*CFileDialog */fileDlg=new CFileDialog(TRUE, _T("image"), NULL, 0, _T("图片(*.png;*.jpg;*.bmp;*.jpeg)|*.png;*.jpg;*.bmp;*.jpeg||"), this);//文本文件(*.txt)|*.txt|所有文件(*.*)|*.*||
					fileDlg->DoModal();
					strFilePath = fileDlg->GetPathName();
					delete fileDlg;
					if (strFilePath == _T(""))
					{
						MessageBox("无效文件路径","提示");
						strFilePath=str;
						break;
					}
					CImage image;
					image.Load(strFilePath); //图片文件路径

					if(image.GetWidth()<200||image.GetHeight()<200){
						MessageBox("图片小于200X200，请重新添加另张","提示");
					}else{
						CString strid;
						strid.Format("%d", pinfo[j+(page-1)*12].id);
						product.updateImage(strFilePath,strid);
						product.selectInfor();

						e_name.ShowWindow(0);
						e_price.ShowWindow(0);
						e_kc.ShowWindow(0);
						e_unit.ShowWindow(0);
						e_content.ShowWindow(0);

						InvalidateRect(CRect(20,680,760,714),0);

						//1.获取当前时间,插入历史记录
						GetLocalTime(&CurTime);////获取本地时间 
						h.time.Format("%d:%d:%d",CurTime.wHour,CurTime.wMinute,CurTime.wSecond);
						h.content="更换产品\n"+pinfo[sx+(page-1)*12].name+"的图片";
						h.table="goods";
						h.tableId=pinfo[sx+(page-1)*12].id;
						h.add();
						//2.插入listcontrol
						m_ListCtrl.InsertItem(0,h.time);
						m_ListCtrl.SetItemText(0,1,h.content);
					}

				}
			}
			//删除 
			if(pic[j].IsWindowVisible())
			{
				if(j!=sx)
				{
					if(dPoint[j].PtInRect(pMsg->pt))
					{
						CString strid;
						strid.Format("%d", pinfo[j+(page-1)*12].id);
						CString startName;
						startName=pinfo[j+(page-1)*12].name;
						if(product.delet(strid))
						{
							CString text;
							m_edit.GetWindowTextA(text);
							//更新信息显示
							if(m_cancel.IsWindowVisible())
							{
								product.selectText(text);
							}
							if(m_info.IsWindowVisible())
							{
								product.selectContent(text);
							}
							
							//更新布局
							for(int i=0;i<12;i++)
							{	
								if( i >= ( infoNum-(page-1)*12) )
									pic[i].ShowWindow(0);
								else
									pic[i].ShowWindow(1);
							}
							//更新页数
							if(infoNum%12==0)
								pageAll.Format("%d",infoNum/12);
							else
								pageAll.Format("%d",infoNum/12+1);
							//更新按钮状态
							if(infoNum>12)
							{
								m_lastpage.ShowWindow(1);
								m_nextpage.ShowWindow(1);
								if(page==1)
									m_lastpage.EnableWindow(0);
								else
									m_lastpage.EnableWindow(1);
								int paGeAll;
								paGeAll=atoi(pageAll);
								if(page==paGeAll)
									m_nextpage.EnableWindow(0);
								else
									m_nextpage.EnableWindow(1);
							}else{
								m_lastpage.ShowWindow(0);
								m_nextpage.ShowWindow(0);
							}
							//更新提示标签
							for(int i=0;i<12;i++)
							{
								if(pic[i].IsWindowVisible())
								{
									CString strKc;
									strKc.Format("%.2f",pinfo[i+(page-1)*12].kc);
									if(!pinfo[i+(page-1)*12].content.IsEmpty())
										m_Mytip.AddTool( GetDlgItem(IDC_MYPICTURE+i), _T("库存:"+strKc+"("+pinfo[i+(page-1)*12].unit+")"+"\n详细信息:\n      "+pinfo[i+(page-1)*12].content) );
									else
										m_Mytip.AddTool( GetDlgItem(IDC_MYPICTURE+i), _T("库存:"+strKc+"("+pinfo[i+(page-1)*12].unit+")"+"\n详细信息:无"));

								}else{
									break;
								}
							}
							InvalidateRect(CRect(20,680,760,714),0);
							//1.获取当前时间,插入历史记录	
							GetLocalTime(&CurTime);////获取本地时间 
							h.time.Format("%d:%d:%d",CurTime.wHour,CurTime.wMinute,CurTime.wSecond);
							h.content="删除产品\n"+startName;
							h.table="goods";
							h.tableId=atoi(strid);
							h.add();

							//2.插入listcontrol
							m_ListCtrl.InsertItem(0,h.time);
							m_ListCtrl.SetItemText(0,1,h.content);
						}else{
							MessageBox("删除失败","提示",MB_ICONEXCLAMATION);
						}
					}
				}else{
					if(!isEdit)
					{
						if(dPoint[j].PtInRect(pMsg->pt))
						{
							CString strid;
							strid.Format("%d", pinfo[j+(page-1)*12].id);
							if(product.delet(strid))
							{
								//1.获取当前时间,插入历史记录
								GetLocalTime(&CurTime);////获取本地时间 
								h.time.Format("%d:%d:%d",CurTime.wHour,CurTime.wMinute,CurTime.wSecond);
								h.content="删除产品\n"+pinfo[j+(page-1)*12].name;
								h.table="goods";
								h.tableId=pinfo[sx+(page-1)*12].id;
								h.add();

								//2.插入listcontrol
								m_ListCtrl.InsertItem(0,h.time);
								m_ListCtrl.SetItemText(0,1,h.content);

								//更新信息显示
								product.selectInfor();
								//更新布局
								for(int i=0;i<12;i++)
								{	
									if( i >= ( infoNum-(page-1)*12) )
										pic[i].ShowWindow(0);
									else
										pic[i].ShowWindow(1);
								}
								//更新页数
								if(infoNum%12==0)
									pageAll.Format("%d",infoNum/12);
								else
									pageAll.Format("%d",infoNum/12+1);
								//更新按钮状态
								if(infoNum>12)
								{
									m_lastpage.ShowWindow(1);
									m_nextpage.ShowWindow(1);
									if(page==1)
										m_lastpage.EnableWindow(0);
									else
										m_lastpage.EnableWindow(1);
									int paGeAll;
									paGeAll=atoi(pageAll);
									if(page==paGeAll)
										m_nextpage.EnableWindow(0);
									else
										m_nextpage.EnableWindow(1);
								}else{
									m_lastpage.ShowWindow(0);
									m_nextpage.ShowWindow(0);
								}
								//更新提示标签
								for(int i=0;i<12;i++)
								{
									if(pic[i].IsWindowVisible())
									{
										CString strKc;
										strKc.Format("%.2f",pinfo[i+(page-1)*12].kc);
										if(!pinfo[i+(page-1)*12].content.IsEmpty())
											m_Mytip.AddTool( GetDlgItem(IDC_MYPICTURE+i), _T("库存:"+strKc+"("+pinfo[i+(page-1)*12].unit+")"+"\n详细信息:\n      "+pinfo[i+(page-1)*12].content) );
										else
											m_Mytip.AddTool( GetDlgItem(IDC_MYPICTURE+i), _T("库存:"+strKc+"("+pinfo[i+(page-1)*12].unit+")"+"\n详细信息:无"));

									}else{
										break;
									}
								}
								InvalidateRect(CRect(20,680,760,714),0);

							}else{
								MessageBox("删除失败","提示",MB_ICONEXCLAMATION);
							}
						}
					}
				}
			}
			//编辑
			if(pic[j].IsWindowVisible())
			{
				if(pPoint[j].PtInRect(pMsg->pt))
				{		
					USES_CONVERSION;
					WCHAR* pBuf;
					if(infoNum>0)
					{	
							int i=sx;
							if(i+(page-1)*12<infoNum)
							{
								if(!pinfo[i+(page-1)*12].image.IsEmpty())
								{
									pBuf = T2W((LPCTSTR)pinfo[i+(page-1)*12].image);
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
										pStatic->GetDC()->FillSolidRect((int)lRect.left ,(int)lRect.top ,(int)lRect.Width(),(int)(lRect.Height()/2-(int)y/2+1), RGB(255, 255, 255));//上
										pStatic->GetDC()->FillSolidRect((int)lRect.left ,(int)(lRect.Height()/2+y/2) ,(int)lRect.Width(),(int)(lRect.Height()/2+1-y/2), RGB(255, 255, 255));//下		
					
										grp.DrawImage(&b,0,0,(int)x,(int)y);
										grphics.DrawImage(&bitmap,0,(int)(100-y/2));	
									}else	{
											double IndexWH=(double)b.GetHeight()/(double)200;
											y=200;
											x=(double)b.GetWidth()/(double)IndexWH;
					
											CStatic* pStatic = (CStatic*)GetDlgItem(IDC_MYPICTURE+i);
											CRect lRect;
											pStatic->GetClientRect(&lRect);
											pStatic->GetDC()->FillSolidRect((int)lRect.left,(int)lRect.top ,(int)(lRect.Width()/2-x/2+1),(int)(lRect.Height()-1), RGB(255, 255, 255));//左
											pStatic->GetDC()->FillSolidRect((int)(lRect.Width()/2+x/2) ,(int)lRect.top ,(int)(lRect.Width()/2-x/2+2),(int)(lRect.Height()-1), RGB(255, 255, 255));//右

											grp.DrawImage(&b,0,0,(int)x,(int)y);
											grphics.DrawImage(&bitmap,(int)(100-x/2),0);	
										}
										CString pIce;
										pIce.Format("%.2f",pinfo[i+(page-1)*12].price);
										Gdiplus::Font f(L"幼圆", 10);
										SolidBrush blackBrush(Color(200, 255, 0, 0));
										WCHAR *string;
										pIce="￥"+pIce;	
										Color cOloR(100,230,230,230);
										SolidBrush sb(cOloR);
										grphics.FillRectangle(&sb,RectF((REAL)rect.left,(REAL)rect.top,(REAL)rect.Width(),20));
										grphics.FillRectangle(&sb,RectF((REAL)rect.left,(REAL)rect.bottom-20,(REAL)rect.Width(),20));
					
										SolidBrush sbs(Color(120,0,0,0));
										grphics.FillRectangle(&sbs,RectF((REAL)rect.left+10,(REAL)rect.bottom-40,75,20));
										grphics.FillRectangle(&sbs,RectF((REAL)rect.Width()/2+10,(REAL)rect.bottom-40,75,20));
					
										string = T2W((LPCTSTR)pinfo[i+(page-1)*12].name);
										grphics.DrawString(string,-1,&f,PointF(0.0f, 5.0f),&SolidBrush(Color(200,0,0,0)));
										string = T2W((LPCTSTR)pIce);
										grphics.DrawString(string,-1,&f,PointF(0.0f, 180.0f),&blackBrush);

										SolidBrush blackBrushs(Color(200, 230, 230, 230));
										string = T2W((LPCTSTR)"编辑");
										grphics.DrawString(string,-1,&f,PointF(30.0f, 160.0f),&blackBrushs);

										string = T2W((LPCTSTR)"删除");
										grphics.DrawString(string,-1,&f,PointF(130.0f, 160.0f),&blackBrushs);

									}else{		
										if(!pinfo[i+(page-1)*12].name.IsEmpty())  
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
											pIce.Format("%.2f",pinfo[i+(page-1)*12].price);
											Gdiplus::Font f(L"幼圆", 10);
											SolidBrush blackBrush(Color(200, 255, 0, 0));
											WCHAR *string;
											pIce="￥"+pIce;	
											Color cOloR(100,230,230,230);
											SolidBrush sb(cOloR);
											grphics.FillRectangle(&sb,RectF((REAL)rect.left,(REAL)rect.bottom-20,(REAL)rect.Width(),(REAL)rect.bottom));
											grphics.FillRectangle(&sb,RectF((REAL)rect.left,(REAL)rect.top,(REAL)rect.Width(),(REAL)rect.top+20));
						
											SolidBrush sbs(Color(120,0,0,0));
											grphics.FillRectangle(&sbs,RectF((REAL)rect.left+10,(REAL)rect.bottom-40,75,20));
											grphics.FillRectangle(&sbs,RectF((REAL)rect.Width()/2+10,(REAL)rect.bottom-40,75,20));

											string = T2W((LPCTSTR)pinfo[i+(page-1)*12].name);
											grphics.DrawString(string,-1,&f,PointF(0.0f, 0.0f),&SolidBrush(Color(200,0,0,0)));
											string = T2W((LPCTSTR)pIce);
											grphics.DrawString(string,-1,&f,PointF(0.0f, 180.0f),&blackBrush);
			
											SolidBrush blackBrushs(Color(200, 230, 230, 230));
											string = T2W((LPCTSTR)"编辑");
											grphics.DrawString(string,-1,&f,PointF(30.0f, 160.0f),&blackBrushs);

											string = T2W((LPCTSTR)"删除");
											grphics.DrawString(string,-1,&f,PointF(130.0f, 160.0f),&blackBrushs);
										}
									}
								}
								
	
						}

                    isEdit=true;//打开编辑成功
					sx=j;//记录刷新控件

					CDC *pCDC = GetDlgItem(IDC_MYPICTURE+j)->GetDC();
					HDC hdc = pCDC->GetSafeHdc();
					Graphics grphics(hdc);
					CRect rect;
					GetDlgItem(IDC_MYPICTURE+j)->GetClientRect(&rect);
					Color cOloR(200,0,0,0);
					SolidBrush sb(cOloR);
					grphics.FillRectangle(&sb,RectF((REAL)rect.left,(REAL)rect.top,(REAL)rect.Width(),(REAL)rect.Height()));
				
					WCHAR *string;
					
					Gdiplus::Font f(L"幼圆", 10);
					SolidBrush blackBrushs(Color(200, 255, 255, 255));
					
					grphics.DrawString(L"『更换图片』",-1,&f,PointF(110.0f, 3.0f),&blackBrushs);
					
					string = T2W((LPCTSTR)"品名: "+pinfo[j+(page-1)*12].name);
					grphics.DrawString(string,-1,&f,PointF(0.0f, 20.0f),&blackBrushs);
					CString pIce;
					pIce.Format("%.2f",pinfo[j+(page-1)*12].price);
					string = T2W((LPCTSTR)"单价: "+pIce);
					grphics.DrawString(string,-1,&f,PointF(0.0f, 40.0f),&blackBrushs);
					CString Kc;
					Kc.Format("%.2f",pinfo[j+(page-1)*12].kc);
					string = T2W((LPCTSTR)"库存: "+Kc);
					grphics.DrawString(string,-1,&f,PointF(0.0f, 60.0f),&blackBrushs);
					string = T2W((LPCTSTR)"单位: "+pinfo[j+(page-1)*12].unit);
					grphics.DrawString(string,-1,&f,PointF(0.0f, 80.0f),&blackBrushs);
					//限制输出47字
					CString pwords;
					pwords=pinfo[j+(page-1)*12].content;
					if(pwords.GetLength()>94)
					{
						pwords=pwords.Left(94)+"...";
					}
					string = T2W((LPCTSTR)"详细: ");
					grphics.DrawString(string,-1,&f,PointF(0.0f, 100.0f),&blackBrushs);

					string = T2W((LPCTSTR)pwords);
					StringFormat stringFormat;
					RectF rectf(0.0f,120.0f,200.0f,80.0f);
					grphics.DrawString(string,-1,&f,rectf,&stringFormat,&blackBrushs);


					e_name.SetWindowTextA(pinfo[j+(page-1)*12].name);
					e_price.SetWindowTextA(pIce);
					e_kc.SetWindowTextA(Kc);
					e_unit.SetWindowTextA(pinfo[j+(page-1)*12].unit);
					e_content.SetWindowTextA(pinfo[j+(page-1)*12].content);

					CString str_name;
					e_name.GetWindowTextA(str_name);
					str_start[0]=str_name;
					e_price.GetWindowTextA(pIce);
					str_start[1]=pIce;
					e_kc.GetWindowTextA(Kc);
					str_start[2]=Kc;
					e_unit.GetWindowTextA(str_name);
					str_start[3]=str_name;
					e_content.GetWindowTextA(str_name);
					str_start[4]=str_name;

					//显示控件
					int k=0,o=0;
					if(j<=3)
					{
						o=j;
					}else if(j>3&&j<=7){
						o=j-4;
					}else{
						o=j-8;
					}
					if(j>3)
					{
						k=1;
					}
					if(j>7)
					{
						k=2;
					}

					
				
					SetRedraw(0);
					e_name.ShowWindow(SW_SHOW);//显示Edit控件；
					e_name.SetFocus();//设置Edit焦点
					e_name.ShowCaret();//显示光标
					e_name.SetSel(-1);//将光标移动到最后
					e_name.MoveWindow(60+205*o,70+205*k,150,20);

					

					e_price.ShowWindow(SW_SHOW);
					e_price.MoveWindow(60+205*o,90+205*k,150,20);
					e_kc.ShowWindow(SW_SHOW);
					e_kc.MoveWindow(60+205*o,110+205*k,150,20);
					e_unit.ShowWindow(SW_SHOW);
					e_unit.MoveWindow(60+205*o,130+205*k,150,20);
					e_content.ShowWindow(SW_SHOW);
					e_content.MoveWindow(21+205*o,170+205*k,199,70);

					SetRedraw(1);
					pic[j].Invalidate();
					

				}else{ 
					pic[j].Invalidate();
                }
			}
		}	
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void M_P_detail::OnSearchText()
{
	page=1;
	if(m_cancel.IsWindowVisible())
	{
		m_edit.GetWindowTextA(product.name);
		product.selectText(product.name);
	}else{
		m_edit.GetWindowTextA(product.content);
		product.selectContent(product.content);
	}
	for(int i=0;i<12;i++)
	{
		pic[i].ShowWindow(1);
		pic[i].Invalidate();
		if(i>=infoNum)
			pic[i].ShowWindow(0);
	}
	if(infoNum>12)
	{
		m_lastpage.ShowWindow(1);
		m_nextpage.ShowWindow(1);
		m_lastpage.EnableWindow(0);
		m_nextpage.EnableWindow(1);
	}else{
		m_lastpage.ShowWindow(0);
		m_nextpage.ShowWindow(0);
	}
	//页数计算
	if(infoNum%12==0)
		pageAll.Format("%d",infoNum/12);
	else
		pageAll.Format("%d",infoNum/12+1);

	InvalidateRect(CRect(20,680,760,714),0);

	for(int i=0;i<12;i++)
	{
		if(pic[i].IsWindowVisible())
		{
			CString strKc;
			strKc.Format("%.2f",pinfo[i+(page-1)*12].kc);
			if(!pinfo[i+(page-1)*12].content.IsEmpty())
				m_Mytip.AddTool( GetDlgItem(IDC_MYPICTURE+i), _T("库存:"+strKc+"("+pinfo[i+(page-1)*12].unit+")"+"\n详细信息:\n      "+pinfo[i+(page-1)*12].content) );
			else
				m_Mytip.AddTool( GetDlgItem(IDC_MYPICTURE+i), _T("库存:"+strKc+"("+pinfo[i+(page-1)*12].unit+")"+"\n详细信息:无"));

		}else{
			break;
		}
	}
	e_name.ShowWindow(0);
	e_price.ShowWindow(0);
	e_kc.ShowWindow(0);
	e_unit.ShowWindow(0);
	e_content.ShowWindow(0);
}


void M_P_detail::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (1==nIDEvent)  
	{  
		 POINT p;  
		 GetCursorPos(&p);     
		 CWnd *hwnd;  
		 hwnd=WindowFromPoint(p);        //检索窗口中包含指定的点;点必须指定屏幕坐标在屏幕上的一个点。     
		 CWnd *hwnd2=GetDlgItem(IDC_lastpage);  
		 CWnd *hwnd3=GetDlgItem(IDC_nextpage);  
		
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
		 if (hwnd3 == hwnd)        
		 {  
			 if (GetFocus()!=hwnd3)      
				 hwnd3->SetFocus() ;  
		 }  
		 else         
		 {  
			 if (GetFocus() == hwnd3 )                 
				 GetDlgItem(IDOK)->SetFocus();      
		 } 
	}
	CDialogEx::OnTimer(nIDEvent);
}


void M_P_detail::OnBnClickedlastpage()
{
	page--;
	m_nextpage.EnableWindow(1);
	if(page==1)
		m_lastpage.EnableWindow(0);

	InvalidateRect(CRect(20,680,760,714),0);
	
	for(int i=0;i<12;i++)
	{	
		if( i >= ( infoNum-(page-1)*12) )
			pic[i].ShowWindow(0);
		else
			pic[i].ShowWindow(1);
	}
	for(int i=0;i<12;i++)
	{
		if(pic[i].IsWindowVisible())
		{
			CString strKc;
			strKc.Format("%.2f",pinfo[i+(page-1)*12].kc);
			if(!pinfo[i+(page-1)*12].content.IsEmpty())
				m_Mytip.AddTool( GetDlgItem(IDC_MYPICTURE+i), _T("库存:"+strKc+"("+pinfo[i+(page-1)*12].unit+")"+"\n详细信息:\n      "+pinfo[i+(page-1)*12].content) );
			else
				m_Mytip.AddTool( GetDlgItem(IDC_MYPICTURE+i), _T("库存:"+strKc+"("+pinfo[i+(page-1)*12].unit+")"+"\n详细信息:无"));

		}else{
			break;
		}
	}
	//可优化，出白色区域
	e_name.ShowWindow(0);
	e_price.ShowWindow(0);
	e_kc.ShowWindow(0);
	e_unit.ShowWindow(0);
	e_content.ShowWindow(0);
}


void M_P_detail::OnBnClickednextpage()
{
	m_lastpage.EnableWindow(1);
	int paGeaLL;
	paGeaLL=atoi(pageAll);
	if(page<paGeaLL)
		page++;
	if(page==paGeaLL)
		m_nextpage.EnableWindow(0);
	for(int i=0;i<12;i++)
	{	
		if( i >= ( infoNum-(page-1)*12) )
			pic[i].ShowWindow(0);
		else 
		{
			pic[i].ShowWindow(1);
			pic[i].Invalidate();
		}
	}
	InvalidateRect(CRect(20,680,760,714),0);
	for(int i=0;i<12;i++)
	{
		if(pic[i].IsWindowVisible())
		{
			CString strKc;
			strKc.Format("%.2f",pinfo[i+(page-1)*12].kc);
			if(!pinfo[i+(page-1)*12].content.IsEmpty())
				m_Mytip.AddTool( GetDlgItem(IDC_MYPICTURE+i), _T("库存:"+strKc+"("+pinfo[i+(page-1)*12].unit+")"+"\n详细信息:\n      "+pinfo[i+(page-1)*12].content) );
			else
				m_Mytip.AddTool( GetDlgItem(IDC_MYPICTURE+i), _T("库存:"+strKc+"("+pinfo[i+(page-1)*12].unit+")"+"\n详细信息:无"));
		}else{
			break;
		}
	}
	//可优化，出白色区域
	e_name.ShowWindow(0);
	e_price.ShowWindow(0);
	e_kc.ShowWindow(0);
	e_unit.ShowWindow(0);
	e_content.ShowWindow(0);
}


void M_P_detail::OnEnKillfocusEdit2()
{
	CString tem;
	e_name.GetWindowText(tem);    //得到用户输入的新的内容
	CString lastName;
	lastName = pinfo[sx+(page-1)*12].name;
	CString strsx;
	strsx.Format("%d", pinfo[sx+(page-1)*12].id);

	if(str_start[0]!=tem&&lastName!=tem)
	{
		if(product.update(tem,strsx))
		{
			//AfxMessageBox("修改成功");
			product.selectInfor();
			//1.获取当前时间,插入历史记录
			GetLocalTime(&CurTime);////获取本地时间 
			h.time.Format("%d:%d:%d",CurTime.wHour,CurTime.wMinute,CurTime.wSecond);
			h.content="编辑产品\n"+tem+"的品名\n"+lastName+"→"+tem;
			h.table="goods";
			h.tableId=pinfo[sx+(page-1)*12].id;
			h.add();
			//2.插入listcontrol
			m_ListCtrl.InsertItem(0,h.time);
			m_ListCtrl.SetItemText(0,1,h.content);
		}else{
			MessageBox("修改失败，重名","提示",MB_ICONEXCLAMATION);
			
		}
	}else{
		//MessageBox("no");
	}
}


void M_P_detail::OnEnKillfocusEdit3()
{
	CString tem;
	e_price.GetWindowText(tem);    //得到用户输入的新的内容
	double lastPrice;
	lastPrice=pinfo[sx+(page-1)*12].price;
	CString strsx;
	strsx.Format("%d", pinfo[sx+(page-1)*12].id);

	if( str_start[1]!=tem && lastPrice!=atof(tem) )
	{
		if(product.updatePrcie(tem,strsx))
		{
			//AfxMessageBox("修改成功");
			product.selectInfor();
			//1.获取当前时间,插入历史记录
			GetLocalTime(&CurTime);////获取本地时间 
			h.time.Format("%d:%d:%d",CurTime.wHour,CurTime.wMinute,CurTime.wSecond);
			CString LP;
			LP.Format("%.2f",lastPrice);
			h.content="编辑产品\n"+pinfo[sx+(page-1)*12].name+"的单价\n"+LP+"→"+tem;
			h.table="goods";
			h.tableId=pinfo[sx+(page-1)*12].id;
			h.add();
			//2.插入listcontrol
			m_ListCtrl.InsertItem(0,h.time);
			m_ListCtrl.SetItemText(0,1,h.content);

		}else{
			MessageBox("修改失败，非纯数字","提示",MB_ICONEXCLAMATION);
		}
	}else{
		//MessageBox("no");
	}
}


void M_P_detail::OnEnKillfocusEdit4()
{
	CString tem;
	e_kc.GetWindowText(tem);    //得到用户输入的新的内容
	double lastKc;
	lastKc=pinfo[sx+(page-1)*12].kc;
	CString strsx;
	strsx.Format("%d", pinfo[sx+(page-1)*12].id);

	if( str_start[2]!=tem && lastKc!=atof(tem) )
	{
		if(product.updateKc(tem,strsx))
		{
			//AfxMessageBox("修改成功");
			product.selectInfor();

			//1.获取当前时间,插入历史记录
			GetLocalTime(&CurTime);////获取本地时间 
			h.time.Format("%d:%d:%d",CurTime.wHour,CurTime.wMinute,CurTime.wSecond);
			CString Lk;
			Lk.Format("%.2f",lastKc);
			h.content="编辑产品\n"+pinfo[sx+(page-1)*12].name+"的库存\n"+Lk+"→"+tem;
			h.table="goods";
			h.tableId=pinfo[sx+(page-1)*12].id;
			h.add();
			//2.插入listcontrol
			m_ListCtrl.InsertItem(0,h.time);
			m_ListCtrl.SetItemText(0,1,h.content);

			for(int i=0;i<12;i++)
			{
				if(pic[i].IsWindowVisible())
				{
					CString strKc;
					strKc.Format("%.2f",pinfo[i+(page-1)*12].kc);
					if(!pinfo[i+(page-1)*12].content.IsEmpty())
						m_Mytip.AddTool( GetDlgItem(IDC_MYPICTURE+i), _T("库存:"+strKc+"("+pinfo[i+(page-1)*12].unit+")"+"\n详细信息:\n      "+pinfo[i+(page-1)*12].content) );
					else
						m_Mytip.AddTool( GetDlgItem(IDC_MYPICTURE+i), _T("库存:"+strKc+"("+pinfo[i+(page-1)*12].unit+")"+"\n详细信息:无"));

				}else{
					break;
				}
			}
		}else{
			MessageBox("修改失败，非纯数字","提示",MB_ICONEXCLAMATION);
		}
	}else{
		//MessageBox("no");
	}
}


void M_P_detail::OnEnKillfocusEdit5()
{
	CString tem;
	e_unit.GetWindowText(tem);    //得到用户输入的新的内容
	CString lastUnit;
	lastUnit=pinfo[sx+(page-1)*12].unit;
	CString strsx;
	strsx.Format("%d", pinfo[sx+(page-1)*12].id);

	if(str_start[3]!=tem)
	{
		if( product.updateUnit(tem,strsx) && lastUnit!=tem )
		{
			//AfxMessageBox("修改成功");
			product.selectInfor();
			//1.获取当前时间,插入历史记录
			GetLocalTime(&CurTime);////获取本地时间 
			h.time.Format("%d:%d:%d",CurTime.wHour,CurTime.wMinute,CurTime.wSecond);
			h.content="编辑产品\n"+pinfo[sx+(page-1)*12].name+"的库存单位\n"+lastUnit+"→"+tem;
			h.table="goods";
			h.tableId=pinfo[sx+(page-1)*12].id;
			h.add();
			//2.插入listcontrol
			m_ListCtrl.InsertItem(0,h.time);
			m_ListCtrl.SetItemText(0,1,h.content);

			for(int i=0;i<12;i++)
			{
				if(pic[i].IsWindowVisible())
				{
					CString strKc;
					strKc.Format("%.2f",pinfo[i+(page-1)*12].kc);
					if(!pinfo[i+(page-1)*12].content.IsEmpty())
						m_Mytip.AddTool( GetDlgItem(IDC_MYPICTURE+i), _T("库存:"+strKc+"("+pinfo[i+(page-1)*12].unit+")"+"\n详细信息:\n      "+pinfo[i+(page-1)*12].content) );
					else
						m_Mytip.AddTool( GetDlgItem(IDC_MYPICTURE+i), _T("库存:"+strKc+"("+pinfo[i+(page-1)*12].unit+")"+"\n详细信息:无"));

				}else{
					break;
				}
			}
		}else{
			MessageBox("修改失败，非纯数字","提示",MB_ICONEXCLAMATION);
		}
	}else{
		//MessageBox("no");
	}
}


void M_P_detail::OnEnKillfocusEdit6()
{
	CString tem;
	e_content.GetWindowText(tem);    //得到用户输入的新的内容
	CString lastContent;
	lastContent=pinfo[sx+(page-1)*12].content;
	CString strsx;
	strsx.Format("%d", pinfo[sx+(page-1)*12].id);

	if( str_start[4]!=tem && lastContent!=tem )
	{
		if(product.updateContent(tem,strsx))
		{
			//AfxMessageBox("修改成功");
			product.selectInfor();

			//1.获取当前时间,插入历史记录
			GetLocalTime(&CurTime);////获取本地时间 
			h.time.Format("%d:%d:%d",CurTime.wHour,CurTime.wMinute,CurTime.wSecond);
			h.content="编辑产品\n"+pinfo[sx+(page-1)*12].name+"的详细\n"+lastContent+"→"+tem;
			h.table="goods";
			h.tableId=pinfo[sx+(page-1)*12].id;
			h.add();
			//2.插入listcontrol
			m_ListCtrl.InsertItem(0,h.time);
			m_ListCtrl.SetItemText(0,1,h.content);

			for(int i=0;i<12;i++)
			{
				if(pic[i].IsWindowVisible())
				{
					CString strKc;
					strKc.Format("%.2f",pinfo[i+(page-1)*12].kc);
					if(!pinfo[i+(page-1)*12].content.IsEmpty())
						m_Mytip.AddTool( GetDlgItem(IDC_MYPICTURE+i), _T("库存:"+strKc+"("+pinfo[i+(page-1)*12].unit+")"+"\n详细信息:\n      "+pinfo[i+(page-1)*12].content) );
					else
						m_Mytip.AddTool( GetDlgItem(IDC_MYPICTURE+i), _T("库存:"+strKc+"("+pinfo[i+(page-1)*12].unit+")"+"\n详细信息:无"));

				}else{
					break;
				}
			}
		}else{
			MessageBox("修改失败，非纯数字","提示",MB_ICONEXCLAMATION);
		}
	}else{
		//MessageBox("no");
	}
}

