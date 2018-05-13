// M_I_detail.cpp : 实现文件
//

#include "stdafx.h"
#include "CenterStar.h"
#include "M_I_detail.h"
#include "afxdialogex.h"
// M_I_detail 对话框

IMPLEMENT_DYNAMIC(M_I_detail, CDialogEx)

M_I_detail::M_I_detail(CWnd* pParent /*=NULL*/)
	: CDialogEx(M_I_detail::IDD, pParent)
{

}

M_I_detail::~M_I_detail()
{
}

void M_I_detail::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDOK, m_ok);
	DDX_Control(pDX, IDC_date, m_startDate);
	DDX_Control(pDX, IDC_start_date, m_d1);
	DDX_Control(pDX, IDC_end_date, m_d2);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
	DDX_Control(pDX, IDC_EDIT2, m_edit1);
	DDX_Control(pDX, IDCANCEL, m_cancel);
	DDX_Control(pDX, IDC_lastpage, m_lastpage);
	DDX_Control(pDX, IDC_nextpage, m_nextpage);
	DDX_Control(pDX, IDC_changePic, m_changePic);
	DDX_Control(pDX, IDC_changePics, m_changePics);
}


BEGIN_MESSAGE_MAP(M_I_detail, CDialogEx)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_NOTIFY(DTN_CLOSEUP, IDC_start_date, &M_I_detail::OnDtnCloseupstartdate)
	ON_NOTIFY(NM_KILLFOCUS, IDC_start_date, &M_I_detail::OnNMKillfocusstartdate)
	ON_NOTIFY(DTN_CLOSEUP, IDC_end_date, &M_I_detail::OnDtnCloseupenddate)
	ON_WM_LBUTTONDOWN()
	ON_NOTIFY(HDN_ITEMCLICK, 0, &M_I_detail::OnHdnItemclickList1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &M_I_detail::OnNMDblclkList1)
//	ON_EN_KILLFOCUS(IDC_EDIT1, &M_I_detail::OnEnKillfocusEdit1)
	ON_EN_KILLFOCUS(IDC_EDIT2, &M_I_detail::OnEnKillfocusEdit2)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &M_I_detail::OnNMRClickList1)
	ON_COMMAND(ID_32772, &M_I_detail::On32772)
	ON_BN_CLICKED(IDCANCEL, &M_I_detail::OnCancel)
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_lastpage, &M_I_detail::Onlastpage)
	ON_BN_CLICKED(IDC_nextpage, &M_I_detail::Onnextpage)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CK, &M_I_detail::OnBnClickedCk)
	ON_BN_CLICKED(IDC_RK, &M_I_detail::OnBnClickedRk)
	ON_BN_CLICKED(IDC_changePic, &M_I_detail::OnFanchart)
	ON_BN_CLICKED(IDC_changePics, &M_I_detail::OnBarchart)
	ON_BN_CLICKED(IDOK, &M_I_detail::OnOk)
	ON_NOTIFY(NM_KILLFOCUS, IDC_end_date, &M_I_detail::OnNMKillfocusenddate)
END_MESSAGE_MAP()


// M_I_detail 消息处理程序


BOOL M_I_detail::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_Row=0;
	m_Col=0;
	penPic=false;
	page=0;
	pageMax=0;
	isChoose0=false;
	isChoose1=false;
	isChoose3=false;
	isChoose4=false;
	chooseMonth=-1;
	chooseDay=-1;
	picMonth=false;
	dmax=0;
	changeColor=false;
	fanchart=false;
	barchart=false;
	FcMonth=-1;
	Fcdetail=false;
	PanPie=-1;
	isPanrk=false;
	Fcpage=1;
	FcpageMax=1;

	static CFont   font1;
	font1.CreatePointFont(150,"宋体");
	m_edit1.SetFont(&font1);
	m_edit1.LimitText(100);

	CRect rect(0,43,850,340);
	m_list.MoveWindow(rect);
	m_list.SetRowHeight(20);
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT| LVS_EX_GRIDLINES| LVS_EX_TWOCLICKACTIVATE | LVS_EX_TRACKSELECT /*自动换行*/| LVS_EX_FLATSB/*扁平滚动条*/ );
	m_list.InsertColumn(0,"◢筛选",LVCFMT_CENTER,rect.Width()/7-40,0);
	m_list.InsertColumn(1,"品名",LVCFMT_CENTER,rect.Width()/7,1);
	m_list.InsertColumn(2,"入库",LVCFMT_CENTER,rect.Width()/7-20,2);
	m_list.InsertColumn(3,"出库",LVCFMT_CENTER,rect.Width()/7-20,3);
	m_list.InsertColumn(4,"库存",LVCFMT_CENTER,rect.Width()/7-20,4);
	m_list.InsertColumn(5,"时间",LVCFMT_CENTER,rect.Width()/7+80,5);
	m_list.InsertColumn(6,"备注",LVCFMT_CENTER,rect.Width()/7+20,6);

	GetDlgItem(IDOK)->MoveWindow(800,1,36,33);
	m_ok.LoadBitmaps(IDB_BITMAP53);
	m_cancel.MoveWindow(0,342,850,25);
	m_cancel.LoadBitmaps(IDB_BITMAP59);
	m_lastpage.LoadBitmaps(IDB_BITMAP44,IDB_BITMAP46,IDB_BITMAP45,IDB_BITMAP47);
	m_lastpage.MoveWindow(20,620,32,32);
	m_nextpage.LoadBitmaps(IDB_BITMAP48,IDB_BITMAP50,IDB_BITMAP49,IDB_BITMAP51);
	m_nextpage.MoveWindow(590,620,32,32);
	m_changePic.LoadBitmaps(IDB_BITMAP60);
	m_changePic.MoveWindow(745,368,105,346);
	m_changePics.LoadBitmaps(IDB_BITMAP61);
	m_changePics.MoveWindow(0,368,105,346);
	/*Rect(630,390,50,5);	
	Rect(630,420,50,5);*/
	GetDlgItem(IDC_CK)->MoveWindow(682,387,14,14);
	GetDlgItem(IDC_RK)->MoveWindow(682,417,14,14);
	CFont f;
	f.CreateFont(25, 0, 0, 0, 0 ,0, 0, 0, GB2312_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH ,"宋体");
	m_startDate.SetFont(&f);
	m_startDate.SetWindowTextA("库存明细2017/05/10 - 2017/05/14");
	SetTimer(1,200,NULL);

	pc=(CButton *)GetDlgItem(IDC_CK);
	pr=(CButton *)GetDlgItem(IDC_RK);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
void M_I_detail::show()
{
	m_list.SetRedraw(0);
	m_list.DeleteAllItems();
	while(m_list.DeleteColumn(0));
	CRect rect(0,43,850,340);
	m_list.MoveWindow(rect);
	m_list.InsertColumn(0,"◢筛选",LVCFMT_CENTER,rect.Width()/7-40,0);
	m_list.InsertColumn(1,"品名",LVCFMT_CENTER,rect.Width()/7,1);
	m_list.InsertColumn(2,"入库",LVCFMT_CENTER,rect.Width()/7-20,2);
	m_list.InsertColumn(3,"出库",LVCFMT_CENTER,rect.Width()/7-20,3);
	m_list.InsertColumn(4,"库存",LVCFMT_CENTER,rect.Width()/7-20,4);
	m_list.InsertColumn(5,"时间",LVCFMT_CENTER,rect.Width()/7+100,5);
	m_list.InsertColumn(6,"备注",LVCFMT_CENTER,rect.Width()/7+20,6);

	CRect lrect;
	m_list.GetSubItemRect(0,5,LVIR_LABEL,lrect);// 
	m_d1.SetParent(&m_list);//转换坐标为列表框中的坐标
	m_d1.MoveWindow(lrect.left,lrect.top-22,lrect.Width()/2-20,lrect.Height());
	m_d2.SetParent(&m_list);//转换坐标为列表框中的坐标
	m_d2.MoveWindow(lrect.right-lrect.Width()/2+20,lrect.top-22,lrect.Width()/2-20,lrect.Height());

	inventory.selectKcIndex();
	if(kcdtNum>0)
	{
		m_startDate.SetWindowTextA("库存明细"+kcindex[0].time.Left(10)+" - "+kcindex[kcdtNum-1].time.Left(10));
		m_d1.SetWindowTextA(kcindex[0].time.Left(10));
		m_d2.SetWindowTextA(kcindex[kcdtNum-1].time.Left(10));
		CString stri,rk,ck,kc;
		for(int i=0;i<kcdtNum;i++)
		{
			/*product.id=kcindex[i].goodsId;
			product=product.selectId(product);*/
			product.id=kcindex[i].goodsId;
			product=product.selectId(product);

			stri.Format("%d",i+1);
			rk.Format("%.2f",kcindex[i].rk);
			ck.Format("%.2f",kcindex[i].ck);
			kc.Format("%.2f",kcindex[i].kc);
			m_list.InsertItem(i,stri);
			m_list.SetItemText(i,1,product.name);
			m_list.SetItemText(i,2,rk);
			m_list.SetItemText(i,3,ck);
			m_list.SetItemText(i,4,kc);
			m_list.SetItemText(i,5,kcindex[i].time);
			m_list.SetItemText(i,6,kcindex[i].remark);
		}
	}
	m_list.SetRedraw(1);
	m_list.Invalidate();
}
void M_I_detail::tally()
{
	if(pageMax!=0)
		delete[pageMax] pageIDs;
	CString title;
	m_startDate.GetWindowTextA(title);
	year=title.Mid(21,4);
	//初始化
	rkMax=kcindex[0].rk;
	rkMin=kcindex[0].rk;
	ckMax=kcindex[0].ck;
	ckMin=kcindex[0].ck;
	isShowck=false;
	isShowrk=false;
	for(int i=0;i<12;i++)
	{
		rk[i]=0;
		ck[i]=0;
	}
	if(kcdtNum>0)
	{
		//计算最大页数
		pageMax=0;
		CString s="",s0="";
		for(int i=0;i<kcdtNum;i++)
		{
			s0.Format("%d",kcindex[i].goodsId);
			if( s.Find(_T(s0),0)==-1 || s.IsEmpty() )
			{
				s=s+s0+" ";
				pageMax++;
			}
		}
		pageName=s;
		//拆分
		CString space=" ";
		pageIDs = new CString[pageMax];
		int i=0;
		while( i<pageMax )
		{
			if( !pageName.Left( pageName.Find(_T(space),0) ).IsEmpty() )
			{
				pageIDs[i]=pageName.Left( pageName.Find(_T(space),0) );
				pageName.Delete(0,pageName.Find(_T(space),0)+1);
			}
			i++;
		}
		int typeId;
		int pageId;
		pageId=atoi(pageIDs[page]);

		typeId=pageId;
		product.id=pageId;
		product=product.selectId(product);
		unit=product.unit;
		for(int i=0;i<kcdtNum;i++)
		{		
			if(kcindex[i].goodsId==typeId)
			{	
				if(kcindex[i].time.Find(year+"-"+"01",0)==0)
				{
					rk[0]=rk[0]+kcindex[i].rk;
					ck[0]=ck[0]+kcindex[i].ck;
				}
				if(kcindex[i].time.Find(year+"-"+"02",0)==0)
				{
					rk[1]=rk[1]+kcindex[i].rk;
					ck[1]=ck[1]+kcindex[i].ck;
				}
				if(kcindex[i].time.Find(year+"-"+"03",0)==0)
				{
					rk[2]=rk[2]+kcindex[i].rk;
					ck[2]=ck[2]+kcindex[i].ck;
				}
				if(kcindex[i].time.Find(year+"-"+"04",0)==0)
				{
					rk[3]=rk[3]+kcindex[i].rk;
					ck[3]=ck[3]+kcindex[i].ck;
				}
				if(kcindex[i].time.Find(year+"-"+"05",0)==0)
				{
					rk[4]=rk[4]+kcindex[i].rk;
					ck[4]=ck[4]+kcindex[i].ck;
				}
				if(kcindex[i].time.Find(year+"-"+"06",0)==0)
				{
					rk[5]=rk[5]+kcindex[i].rk;
					ck[5]=ck[5]+kcindex[i].ck;
				}
				if(kcindex[i].time.Find(year+"-"+"07",0)==0)
				{
					rk[6]=rk[6]+kcindex[i].rk;
					ck[6]=ck[6]+kcindex[i].ck;
				}
				if(kcindex[i].time.Find(year+"-"+"08",0)==0)
				{
					rk[7]=rk[7]+kcindex[i].rk;
					ck[7]=ck[7]+kcindex[i].ck;
				}
				if(kcindex[i].time.Find(year+"-"+"09",0)==0)
				{
					rk[8]=rk[8]+kcindex[i].rk;
					ck[8]=ck[8]+kcindex[i].ck;
				}
				if(kcindex[i].time.Find(year+"-"+"10",0)==0)
				{
					rk[9]=rk[9]+kcindex[i].rk;
					ck[9]=ck[9]+kcindex[i].ck;
				}
				if(kcindex[i].time.Find(year+"-"+"11",0)==0)
				{
					rk[10]=rk[10]+kcindex[i].rk;
					ck[10]=ck[10]+kcindex[i].ck;
				}
				if(kcindex[i].time.Find(year+"-"+"12",0)==0)
				{
					rk[11]=rk[11]+kcindex[i].rk;
					ck[11]=ck[11]+kcindex[i].ck;
				}
				for(int i=0;i<12;i++)
				{
					if(rk[i]>rkMax)
						rkMax=rk[i];
					if(rk[i]<rkMin)
						rkMin=rk[i];
					if(ck[i]>ckMax)
						ckMax=ck[i];
					if(ck[i]<ckMin)
						ckMin=ck[i];
				}
			}
		}
		
	}
}
void M_I_detail::tallyFanchart()
{
	/*if(rksum!=NULL)
		delete rksum;
	if(cksum!=NULL)
		delete cksum;*/
	//1. 每月份的出入库总和数据 rk[12] ck[12]
	//2. 每月份的产品出入库之和 double rksum cksum
	//3. 算占比double rkzb ckzb
	CString strMonth;
	/*rksum=new double[pageMax*12];
	cksum=new double[pageMax*12];*/
	for(int m=0;m<12;m++)
	{
		rk[m]=0;
		ck[m]=0;
	}
	for(int i=0;i<kcdtNum;i++)
	{		
		for(int m=0;m<12;m++)
		{
			if(m<9)
				strMonth.Format("0%d",m+1);
			else
				strMonth.Format("%d",m+1);
			if(kcindex[i].time.Find(year+"-"+strMonth,0)==0)
			{
				rk[m]=rk[m]+kcindex[i].rk;
				ck[m]=ck[m]+kcindex[i].ck;
			}
	   }
	}
	/*for(int i=0;i<12;i++)
	{
		strMonth.Format("%d  %d %.2f %.2f",i+1,pageMax,rk[i],ck[i]);
		MessageBox(strMonth);
	}*/
}
double M_I_detail::Sumck(int month,int goodsid)
{
	CString strmonth;
	if(month<10)
		strmonth.Format("0%d",month);
	else
		strmonth.Format("%d",month);
	double cksum=0;
	for(int i=0;i<kcdtNum;i++)
	{	
		if(kcindex[i].goodsId==goodsid)
		{
			if(kcindex[i].time.Find(year+"-"+strmonth,0)==0)
			{
				cksum=cksum+kcindex[i].ck;			
			}
		}
	}
	return cksum;
}
double M_I_detail::Sumrk(int month,int goodsid)
{
	CString strmonth;
	if(month<10)
		strmonth.Format("0%d",month);
	else
		strmonth.Format("%d",month);
	double rksum=0;
	for(int i=0;i<kcdtNum;i++)
	{	
		if(kcindex[i].goodsId==goodsid)
		{
			if(kcindex[i].time.Find(year+"-"+strmonth,0)==0)
			{
				rksum=rksum+kcindex[i].rk;
			}
		}
	}
	return rksum;
}
void M_I_detail::tallyMonth(int month)
{
	//型号 、年份、月份
	/*CString s;
	s.Format("%d",month);
	MessageBox(pageIDs[page]+"、"+year+"、"+s);*/
	//初始化
	for(int i=0;i<31;i++)
	{
		rkMonth[i]=0;
		ckMonth[i]=0;
	}
	//统计数据
	int typeId;
	int pageId;
	pageId=atoi(pageIDs[page]);
	typeId=pageId;
	product.id=pageId;
	product=product.selectId(product);
	unit=product.unit;
	CString strMonth;
	if(month<10)
		strMonth.Format("0%d",month);
	else
		strMonth.Format("%d",month);
	CString strDay;
	if(kcdtNum>0)
	{
		for(int i=0;i<kcdtNum;i++)
		{		
			if(kcindex[i].goodsId==typeId)//找到型号
			{
				if(kcindex[i].time.Find(year+"-"+strMonth,0)==0)//找到月份
				{
					for(int d=0;d<31;d++)
					{
						if(d<9)
							strDay.Format("0%d",d+1);
						else
							strDay.Format("%d",d+1);
						if(kcindex[i].time.Find(year+"-"+strMonth+"-"+strDay,0)==0)
						{
							//MessageBox(kcindex[i].time);//2017-5-20
							rkMonth[d]=rkMonth[d]+kcindex[i].rk;
							ckMonth[d]=ckMonth[d]+kcindex[i].ck;
						}
					}
				}		
			}
		}
		/*for(int i=0;i<31;i++)
		{
			strDay.Format("%d  rk%.2f  ck%.2f",i+1,rkMonth[i],ckMonth[i]);
			MessageBox(strDay);
			
		}*/
		//初始化
		rkMonthMax=rkMonth[0];
		rkMonthMin=rkMonth[0];
		ckMonthMax=ckMonth[0];
		ckMonthMin=ckMonth[0];
		//计算最大值
		for(int i=0;i<31;i++)
		{
			if(rkMonth[i]>rkMonthMax)
				rkMonthMax=rkMonth[i];
			if(rkMonth[i]<rkMonthMin)
				rkMonthMin=rkMonth[i];
			if(ckMonth[i]>ckMonthMax)
				ckMonthMax=ckMonth[i];
			if(ckMonth[i]<ckMonthMin)
				ckMonthMin=ckMonth[i];
		}
	}
	
}
void M_I_detail::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CBitmap m_Back;
	m_Back.LoadBitmap(IDB_BITMAP58);
	CDC mdc;
	mdc.CreateCompatibleDC(&dc); 
	mdc.SelectObject(&m_Back);
	if(penPic)
	{
		USES_CONVERSION;
		WCHAR *string;
		HDC hdc = mdc.GetSafeHdc();
		Graphics grphics(hdc);
		grphics.SetSmoothingMode(SmoothingModeHighQuality); //设置平滑画线 
		Gdiplus::Font f(L"幼圆", 10);
		Gdiplus::Font fjd(L"幼圆", 8);
		Gdiplus::Font fjdM(L"幼圆", 7);
		Gdiplus::Font fbig(L"幼圆", 14);
		Gdiplus::Font fsmall(L"幼圆", 12);
		if(barchart)
		{
			Pen p(Color(100,0,0,0));
			Pen pYLine(Color(30,0,0,0));
			
			//Y轴
			grphics.DrawLine(&p,Point(20,390),Point(20,590));
			grphics.DrawLine(&p,Point(20,390),Point(10,400));
			grphics.DrawLine(&p,Point(20,390),Point(30,400));
			string = T2W((LPCTSTR)"0");
			grphics.DrawString(string,-1,&f,PointF(8.0f, 585.0f),&SolidBrush(Color(100,0,0,0)));
			////单位
			string = T2W((LPCTSTR)unit);
			grphics.DrawString(string,-1,&f,PointF(0.0f, 378.0f),&SolidBrush(Color(100,0,0,0)));
			if(!picMonth)
			{
				for(int i=0;i<12;i++)          
					grphics.DrawLine(&pYLine,Point(55+50*i,390),Point(55+50*i,590));
			}
			//X轴
			grphics.DrawLine(&p,Point(20,590),Point(640,590));
			grphics.DrawLine(&p,Point(630,580),Point(640,590));
			grphics.DrawLine(&p,Point(630,600),Point(640,590));
			//X轴坐标	
			CString str;
			CString jd;
			if(picMonth)
			{
				str.Format("%d",chooseMonth+1);
				string = T2W((LPCTSTR)"日/"+str+"月");
				grphics.DrawString(string,-1,&f,PointF(604.0f, 602.0f),&SolidBrush(Color(100,0,0,0)));
			}else{
				string = T2W((LPCTSTR)"月份/"+year);
				grphics.DrawString(string,-1,&f,PointF(604.0f, 602.0f),&SolidBrush(Color(100,0,0,0)));
			}
			if(picMonth)
			{
				//天数
				int d=0;
				if(chooseMonth==0||chooseMonth==2||chooseMonth==4||chooseMonth==6||chooseMonth==7||chooseMonth==9||chooseMonth==11)
					dmax=31;
				else if(chooseMonth!=1)
					dmax=30;
				else{
					//2月
					if( atoi(year)%400==0 || (atoi(year)%4==0&&atoi(year)%100!=0) )//闰年
					{
						dmax=29;
					}else{
						dmax=28;
					}
				}
				for(d=0;d<dmax;d++)
				{   
					//20---670
					str.Format("%d",d+1);
					string = T2W((LPCTSTR)str);
					if(chooseDay==d)
						grphics.DrawString(string,-1,&f,PointF(22.0f+d*(590/dmax), 600.0f),&SolidBrush(Color(255,0,0,0)));
					else
						grphics.DrawString(string,-1,&f,PointF(22.0f+d*(590/dmax), 600.0f),&SolidBrush(Color(100,0,0,0)));
					//辅助竖线                                               
					//grphics.DrawLine(&pYLine,Point( 40+d*(590/dmax),390),Point(40+d*(590/dmax),590));//字30.0f+i*50.0f, 线55+50*i,
				}
			}
			if(!picMonth)
			{
				for(int i=0;i<12;i++)
				{
					//月份数
					str.Format("%d",i+1);
					string = T2W((LPCTSTR)str);
					if(chooseMonth==i)
						grphics.DrawString(string,-1,&f,PointF(30.0f+i*50.0f, 600.0f),&SolidBrush(Color(255,0,0,0)));
					else
						grphics.DrawString(string,-1,&f,PointF(30.0f+i*50.0f, 600.0f),&SolidBrush(Color(100,0,0,0)));
	
					//画圆点
					//出库数据色 RGB(79,22,29)
					//入库数据色 RGB(217,194,116)
					if(isShowck || (chooseMonth==i))
						grphics.FillEllipse(&SolidBrush(Color(200,79,22,29)),Rect(21+50*i,590-(ck[i]/ckMax)*200-2,5,5));	
					if(isShowrk || (chooseMonth==i))
						grphics.FillEllipse(&SolidBrush(Color(200,217,194,116)),Rect(41+50*i,590-(rk[i]/rkMax)*200-2,5,5));
					//显示数据在对应圆点
					//入库
					if(isShowrk || (chooseMonth==i))
					{
						jd.Format("%.2f",rk[i]);
						string = T2W((LPCTSTR)jd);
						if(rkMax==0)
							grphics.DrawString(string,-1,&fjd,PointF(41+50*i,590),&SolidBrush(Color(255,211,85,45)));
						else
							grphics.DrawString(string,-1,&fjd,PointF(41+50*i,590-(rk[i]/rkMax)*200),&SolidBrush(Color(255,211,85,45)));
					}
					//出库
					if(isShowck || (chooseMonth==i))
					{
						jd.Format("%.2f",ck[i]);
						string = T2W((LPCTSTR)jd);
						if(ckMax==0)
							grphics.DrawString(string,-1,&fjd,PointF(21+50*i,580),&SolidBrush(Color(255,45,85,211)));
						else
							grphics.DrawString(string,-1,&fjd,PointF(21+50*i,590-(ck[i]/ckMax)*200-10),&SolidBrush(Color(255,45,85,211)));
					}
				}
			}else{
				for(int i=0;i<dmax;i++)
				{
					//画圆点
					//出库数据色 RGB(79,22,29)
					//入库数据色 RGB(217,194,116)
					if(isShowck )                                     //22.0f+d*(590/dmax)
						grphics.FillEllipse(&SolidBrush(Color(200,79,22,29)),Rect(24.0f+i*(590/dmax),590-(ckMonth[i]/ckMonthMax)*200-2,5,5));	
					if(isShowrk )
						grphics.FillEllipse(&SolidBrush(Color(200,217,194,116)),Rect(30.0f+i*(590/dmax),590-(rkMonth[i]/rkMonthMax)*200-2,5,5));
					//显示数据在对应圆点
					//入库
					if(isShowrk || (chooseDay==i))
					{
						jd.Format("%.2f",rkMonth[i]);
						string = T2W((LPCTSTR)jd);
						if(rkMonthMax==0)
							grphics.DrawString(string,-1,&fjdM,PointF(30.0f+i*(590/dmax),590),&SolidBrush(Color(255,211,85,45)));
						else
							grphics.DrawString(string,-1,&fjdM,PointF(30.0f+i*(590/dmax),590-(rkMonth[i]/rkMonthMax)*200),&SolidBrush(Color(255,211,85,45)));
					}
					//出库
					if(isShowck || (chooseDay==i))
					{
						jd.Format("%.2f",ckMonth[i]);
						string = T2W((LPCTSTR)jd);
						if(ckMonthMax==0)
							grphics.DrawString(string,-1,&fjdM,PointF(24.0f+i*(590/dmax),580),&SolidBrush(Color(255,45,85,211)));
						else
							grphics.DrawString(string,-1,&fjdM,PointF(24.0f+i*(590/dmax),590-(ckMonth[i]/ckMonthMax)*200-10),&SolidBrush(Color(255,45,85,211)));
					}
				}
				Pen p1m(Color(100,45,85,211),2.0f);
				Pen p2m(Color(100,211,85,45),2.0f);
				//画折线
				for(int i=0;i<dmax-1;i++)
				{
					if(chooseDay==i)
					{
						p1m.SetWidth(5.0f);
						p2m.SetWidth(5.0f);
					}else{
						if(isShowck)
							p1m.SetWidth(3.0f);
						else
							p1m.SetWidth(2.0f);
						if(isShowrk)
							p2m.SetWidth(3.0f);
						else
							p2m.SetWidth(2.0f);
					}
					//出库
					if(ckMonthMax==0)                           
						grphics.DrawLine(&p1m,Point((int)(26.0f+i*(590/dmax)),(int)(590)),Point((int)(26.0f+i*(590/dmax)),(int)(590)));
					else
						grphics.DrawLine(&p1m,Point((int)(26.0f+i*(590/dmax)),(int)(590-(ckMonth[i]/ckMonthMax)*200)),Point((int)(26.0f+(i+1)*(590/dmax)),(int)(590-(ckMonth[i+1]/ckMonthMax)*200)));
					//入库                                     
					if(rkMonthMax==0)                           //,
						grphics.DrawLine(&p2m,Point((int)(32.0f+i*(590/dmax)),(int)(590)),Point((int)(32.0f+(i+1)*(590/dmax)),(int)(590)));
					else
						grphics.DrawLine(&p2m,Point((int)(32.0f+i*(590/dmax)),(int)(590-(rkMonth[i]/rkMonthMax)*200)),Point((int)(32.0f+(i+1)*(590/dmax)),(int)(590-(rkMonth[i+1]/rkMonthMax)*200)));
			
				}
			}
			Pen p1(Color(100,45,85,211),2.0f);
			Pen p2(Color(100,211,85,45),2.0f);
			//画折线
			if(!picMonth)
			{
				for(int i=0;i<11;i++)
				{
					if(chooseMonth==i)
					{
						p1.SetWidth(5.0f);
						p2.SetWidth(5.0f);
					}else{
						if(isShowck)
						{
							p1.SetWidth(3.0f);
						}else{
							p1.SetWidth(2.0f);
						}
						if(isShowrk)
						{
							p2.SetWidth(3.0f);
						}else{
							p2.SetWidth(2.0f);
						}
					}
					//出库
					if(ckMax==0)
						grphics.DrawLine(&p1,Point((int)(23+50*i),(int)(590)),Point((int)(23+50*(i+1)),(int)(590)));
					else
						grphics.DrawLine(&p1,Point((int)(23+50*i),(int)(590-(ck[i]/ckMax)*200)),Point((int)(23+50*(i+1)),(int)(590-(ck[i+1]/ckMax)*200)));
					//入库                                     
					if(rkMax==0)
						grphics.DrawLine(&p2,Point((int)(43+50*i),(int)(590)),Point((int)(43+50*(i+1)),(int)(590)));
					else
						grphics.DrawLine(&p2,Point((int)(43+50*i),(int)(590-(rk[i]/rkMax)*200)),Point((int)(43+50*(i+1)),(int)(590-(rk[i+1]/rkMax)*200)));
			
				}
			}
			//指示标
			grphics.FillRectangle(&SolidBrush(Color(100,45,85,211)),Rect(630,390,50,5));	
			grphics.FillRectangle(&SolidBrush(Color(100,211,85,45)),Rect(630,420,50,5));
			string = T2W((LPCTSTR)"出库");
			grphics.DrawString(string,-1,&f,PointF(635.0f,385.0f),&SolidBrush(Color(200,45,85,211)));
			string = T2W((LPCTSTR)"入库");
			grphics.DrawString(string,-1,&f,PointF(635.0f,415.0f),&SolidBrush(Color(200,211,85,45)));
			if(picMonth)
			{
				grphics.DrawRectangle(&p1,Rect(630,540,58,20));//100,45,85,211
				if(changeColor)
					grphics.FillRectangle(&SolidBrush(Color(200,45,85,211)),Rect(631,541,56,18));
				else
					grphics.FillRectangle(&SolidBrush(Color(100,45,85,211)),Rect(631,541,56,18));
				string = T2W((LPCTSTR)"返回");
				grphics.DrawString(string,-1,&f,PointF(641.0f,543.0f),&SolidBrush(Color(200,0,255,255)));
			}
			///////图名
			//当前图名
			int pageId;
			pageId=atoi(pageIDs[page]);
			product.id=pageId;
			product=product.selectId(product);

			string = T2W((LPCTSTR)product.name);
			grphics.DrawString(string,-1,&fbig,PointF((70.0f+2*110.0f),625.0f),&SolidBrush(Color(200,0,0,0)));
			//左
			for(int i=0;i<2;i++)
			{
				if(page>=2)
				{
					pageId=atoi(pageIDs[page-2+i]);
					/*product.id=pageId;
					product=product.selectId(product);*/
					product.id=pageId;
					product=product.selectId(product);

					string = T2W((LPCTSTR)product.name);
					if( ( i==0&&isChoose0 ) || ( i==1&&isChoose1) )
						grphics.DrawString(string,-1,&fsmall,PointF((70.0f+i*110.0f),620.0f),&SolidBrush(Color(100,0,0,0)));
					else
						grphics.DrawString(string,-1,&fsmall,PointF((70.0f+i*110.0f),625.0f),&SolidBrush(Color(100,0,0,0)));
			
				}
				else if(page==1)
				{
					if(i==1)
					{
						pageId=atoi(pageIDs[0]);
						/*product.id=pageId;
						product=product.selectId(product);*/
						product.id=pageId;
						product=product.selectId(product);

						string = T2W((LPCTSTR)product.name);
						if( i==1&&isChoose1 )
							grphics.DrawString(string,-1,&fsmall,PointF((70.0f+i*110.0f),620.0f),&SolidBrush(Color(100,0,0,0)));
						else
							grphics.DrawString(string,-1,&fsmall,PointF((70.0f+i*110.0f),625.0f),&SolidBrush(Color(100,0,0,0)));
					}
				}
			}
			//右
			for(int i=0;i<2;i++)
			{
				if(page<=pageMax-3)
				{
					pageId=atoi(pageIDs[page+i+1]);
					/*product.id=pageId;
					product=product.selectId(product);*/
					product.id=pageId;
					product=product.selectId(product);

					string = T2W((LPCTSTR)product.name);
					if( (i==0&&isChoose3) || (i==1&&isChoose4) )
						grphics.DrawString(string,-1,&fsmall,PointF((70.0f+(i+3)*110.0f),620.0f),&SolidBrush(Color(100,0,0,0)));
					else
						grphics.DrawString(string,-1,&fsmall,PointF((70.0f+(i+3)*110.0f),625.0f),&SolidBrush(Color(100,0,0,0)));
				}
				else if(page==pageMax-2)
				{
					if(i==0)
					{
						pageId=atoi(pageIDs[page+1]);
						/*product.id=pageId;
						product=product.selectId(product);*/
						product.id=pageId;
						product=product.selectId(product);
						string = T2W((LPCTSTR)product.name);
						if( (i==0&&isChoose3) )
							grphics.DrawString(string,-1,&fsmall,PointF((70.0f+(i+3)*110.0f),620.0f),&SolidBrush(Color(100,0,0,0)));
						else
							grphics.DrawString(string,-1,&fsmall,PointF((70.0f+(i+3)*110.0f),625.0f),&SolidBrush(Color(100,0,0,0)));
					}
				}
			}
		}
		if(fanchart)
		{
			//105-850 宽度745 ; 120一个, r=60
			Pen p1(Color(100,45,85,211),2.0f);//出库
			Pen p1c(Color(155,45,85,211),2.0f);//出库
			Pen pPieck(Color(100,45,85,211),6.0f);//出库
			Pen p2(Color(100,211,85,45),2.0f);//入库
			Pen p2c(Color(155,211,85,45),2.0f);//入库
			Pen pPie(Color(100,211,85,45),6.0f);//入库
			for(int i=0;i<6;i++)
			{
				if(FcMonth<6)
				{
					if(i==FcMonth)
						grphics.DrawEllipse(&p2c,Rect(105+i*120,368+20,70,70));
				}
				else if(FcMonth<12)
				{
					if(i==FcMonth-6)
						grphics.DrawEllipse(&p2c,Rect(105+i*120,368+100,70,70));
				}
				else if(FcMonth<18)
				{
					if(i==FcMonth-12)
						grphics.DrawEllipse(&p1c,Rect(105+i*120,368+190,70,70));
				}
				else
				{
					if(i==FcMonth-18)
						grphics.DrawEllipse(&p1c,Rect(105+i*120,368+270,70,70));
				}
				//入库圆形  
				grphics.DrawEllipse(&p2,Rect(105+i*120,368+20,70,70));
				grphics.DrawEllipse(&p2,Rect(105+i*120,368+100,70,70));
				//出库圆形                      
				grphics.DrawEllipse(&p1,Rect(105+i*120,368+190,70,70));
				grphics.DrawEllipse(&p1,Rect(105+i*120,368+270,70,70));
			}
			//画比例文字
			for(int i=0;i<150;i++)
			{
				grphics.FillRectangle(&SolidBrush(Color(150-i,211,85,45)),Rect(105+i,368,1,18));
				grphics.FillRectangle(&SolidBrush(Color(150-i,45,85,211)),Rect(105+i,370+170,1,16));
			}
			string = T2W((LPCTSTR)"入库(占比25%以上)");
			grphics.DrawString(string,-1,&fjd,PointF(105,370),&SolidBrush(Color(100,0,0,0)));
			string = T2W((LPCTSTR)"出库(占比25%以上)");
			grphics.DrawString(string,-1,&fjd,PointF(105,372+170),&SolidBrush(Color(100,0,0,0)));
			double rksum,cksum;
			int rkPie[12],ckPie[12];
			for(int i=0;i<12;i++)
			{
				jrkPie[i]=0;
				rkPie[i]=0;
				ckPie[i]=0;
				jckPie[i]=0;
			}
			for(int i=0;i<pageMax;i++)
			{		
				product.id=0;
				product.id=atoi(pageIDs[i]);
				product=product.selectId(product);
				string = T2W((LPCTSTR)product.name);
				for(int m=0;m<12;m++)
				{
					rksum=Sumrk(m+1,atoi(pageIDs[i]));	
					if(rksum/rk[m]>=0.25)
					{
						if(m<6)
						{
							//grphics.FillPie(&SolidBrush(Color(100,211,85,45)),Rect(115+m*120,368+30,50,50),rkPie[m],360*(rksum/rk[m]));
							grphics.DrawString(string,-1,&fjd,PointF(105+(m*120)+70.0f,388.0f+10.0f*jrkPie[m]),&SolidBrush(Color(100,0,0,0)));
							if(rksum/rk[m]==1)
							{			
								grphics.DrawEllipse(&pPie,Rect(115+m*120,368+30,50,50));
							}
							else 
							{
								grphics.DrawPie(&pPie,Rect(115+m*120,368+30,50,50),rkPie[m],360*(rksum/rk[m]));
							}
							rkPie[m]=rkPie[m]+360*(rksum/rk[m]);
						}
						else
						{
							if(rksum/rk[m]==1)
							{
								grphics.DrawEllipse(&pPie,Rect(115+(m-6)*120,368+110,50,50));
							}
							else 
							{
								grphics.DrawPie(&pPie,Rect(115+(m-6)*120,368+110,50,50),rkPie[m],360*(rksum/rk[m]));
							}
							rkPie[m]=rkPie[m]+360*(rksum/rk[m]);
							grphics.DrawString(string,-1,&fjd,PointF(105+((m-6)*120)+70.0f,468.0f+10.0f*jrkPie[m]),&SolidBrush(Color(100,0,0,0)));
						}
						jrkPie[m]++;
					}

					cksum=Sumck(m+1,atoi(pageIDs[i]));
					if(cksum/ck[m]>=0.25)
					{
						if(m<6)
						{                                                                                             
							//grphics.FillPie(&SolidBrush(Color(100,211,85,45)),Rect(115+m*120,368+30,50,50),rkPie[m],360*(rksum/rk[m]));
							grphics.DrawString(string,-1,&fjd,PointF(105+(m*120)+70.0f,368+190.0f+10.0f*jckPie[m]),&SolidBrush(Color(100,0,0,0)));
							if(cksum/ck[m]==1)                              
							{			                                         
								grphics.DrawEllipse(&pPieck,Rect(115+m*120,368+200,50,50));
							}
							else 
							{
								grphics.DrawPie(&pPieck,Rect(115+m*120,368+200,50,50),ckPie[m],360*(cksum/ck[m]));
							}
							ckPie[m]=ckPie[m]+360*(cksum/ck[m]);
						}
						else
						{
							if(cksum/ck[m]==1)
							{
								grphics.DrawEllipse(&pPieck,Rect(115+(m-6)*120,368+280,50,50));
							}
							else 
							{
								grphics.DrawPie(&pPieck,Rect(115+(m-6)*120,368+280,50,50),ckPie[m],360*(cksum/ck[m]));
							}
							ckPie[m]=ckPie[m]+360*(cksum/ck[m]);                                      
							grphics.DrawString(string,-1,&fjd,PointF(105+((m-6)*120)+70.0f,368+270.0f+10.0f*jckPie[m]),&SolidBrush(Color(100,0,0,0)));
						}
						jckPie[m]++;
					}
				}
			}
			CString monthl;
			for(int m=0;m<12;m++)
			{
				//标月份                       
				monthl.Format("%d",m+1);
				string = T2W((LPCTSTR)monthl);
				if(m<6)
				{                                                                        
					grphics.DrawString(string,-1,&fjd,PointF(135+m*120.0f,368+50.0f),&SolidBrush(Color(100,0,0,0)));
					grphics.DrawString(string,-1,&fjd,PointF(135+m*120.0f,368+220.0f),&SolidBrush(Color(100,0,0,0)));
				}
				else
				{
					if(m<9)        
					{                                                                       
						grphics.DrawString(string,-1,&fjd,PointF(135+(m-6)*120.0f,468+30.0f),&SolidBrush(Color(100,0,0,0)));
						grphics.DrawString(string,-1,&fjd,PointF(135+(m-6)*120.0f,368+300.0f),&SolidBrush(Color(100,0,0,0)));
					}
					else
					{
						grphics.DrawString(string,-1,&fjd,PointF(132+(m-6)*120.0f,468+30.0f),&SolidBrush(Color(100,0,0,0)));
						grphics.DrawString(string,-1,&fjd,PointF(132+(m-6)*120.0f,368+300.0f),&SolidBrush(Color(100,0,0,0)));
					}
				}
			}
		}else if(!barchart){
			//返回
			for(int i=0;i<100;i++)
			{
				if(FcMonth<12)
					grphics.FillRectangle(&SolidBrush(Color(100-i,211,85,45)),Rect(105+i,368,1,18));
				else
					grphics.FillRectangle(&SolidBrush(Color(100-i,45,85,211)),Rect(105+i,368,1,16));
			}
			string = T2W((LPCTSTR)"返回");
			grphics.DrawString(string,-1,&fjd,PointF(105,370),&SolidBrush(Color(100,0,0,0)));

			grphics.FillRectangle(&SolidBrush(Color(200,217,194,116)),Rect(305,368,500,18));
			string = T2W((LPCTSTR)"序号");
			grphics.DrawString(string,-1,&fjd,PointF(305,370),&SolidBrush(Color(100,0,0,0)));
			string = T2W((LPCTSTR)"名称");
			grphics.DrawString(string,-1,&fjd,PointF(355,370),&SolidBrush(Color(100,0,0,0)));
			string = T2W((LPCTSTR)"占比");
			grphics.DrawString(string,-1,&fjd,PointF(505,370),&SolidBrush(Color(100,0,0,0)));
			string = T2W((LPCTSTR)"数量");
			grphics.DrawString(string,-1,&fjd,PointF(585,370),&SolidBrush(Color(100,0,0,0)));
			if(FcMonth<12)
			{
				CString strF;
				//105,368+20,200,200
				strF.Format("总和:%.2f",rk[FcMonth]);
				string = T2W((LPCTSTR)strF);
				grphics.DrawString(string,-1,&f,PointF(140.0f,588.0f),&SolidBrush(Color(100,0,0,0)));	
				strF.Format("%s年%d月",year,FcMonth+1);
				string = T2W((LPCTSTR)strF);
				grphics.DrawString(string,-1,&f,PointF(155.0f,608.0f),&SolidBrush(Color(100,0,0,0)));	
								
			}else{
				CString strF;
				strF.Format("总和:%.2f",ck[FcMonth-12]);
				string = T2W((LPCTSTR)strF);
				grphics.DrawString(string,-1,&f,PointF(140.0f,588.0f),&SolidBrush(Color(100,0,0,0)));	
				strF.Format("%s年%d月",year,FcMonth-12+1);
				string = T2W((LPCTSTR)strF);
				grphics.DrawString(string,-1,&f,PointF(165.0f,608.0f),&SolidBrush(Color(100,0,0,0)));	
			}
			//画圆圈
			if(FcMonth<=11)
			{
				Pen p2(Color(25,211,85,45),2.0f);//入库
				grphics.DrawEllipse(&p2,Rect(105,368+20,200,200));
			}
			else
			{
				Pen p1(Color(25,45,85,211),2.0f);//出库
				grphics.DrawEllipse(&p1,Rect(105,368+20,200,200));
			}		
			//画文字
			double sum;
			int Pie[12],ckPie[12];
			CString strcount;
			CString zb,nums;
			for(int i=0;i<12;i++)
			{
				jrkPie[i]=0;
				Pie[i]=0;
				ckPie[i]=0;
				jckPie[i]=0;
			}
			for(int i=0;i<pageMax;i++)
			{		
				product.id=0;
				product.id=atoi(pageIDs[i]);
				product=product.selectId(product);
				int m;
				if(FcMonth<12)
				{
					m=FcMonth;
					sum=Sumrk(m+1,atoi(pageIDs[i]));	
				}
				else 
				{
					m=FcMonth-12;
					sum=Sumck(m+1,atoi(pageIDs[i]));	
				}	
				if(FcMonth<12)
				{
					if(sum/rk[m]>0)
					{
						if(sum/rk[m]==1)
						{			
							grphics.FillEllipse(&SolidBrush(Color(100,211,85,45)),Rect(105,368+20,200,200));
						}
						else 
						{
							Pen p1(Color(100,211,85,45));
							grphics.DrawPie(&p1,Rect(105,368+20,200,200),Pie[m],360*(sum/rk[m]));	
							if(PanPie==(jrkPie[m]-(Fcpage-1)*15)&&isPanrk)
								grphics.FillPie(&SolidBrush(Color(100,211,85,45)),Rect(105,368+20,200,200),Pie[m],360*(sum/rk[m]));
						}
						Pie[m]=Pie[m]+360*(sum/rk[m]); 
						if( (jrkPie[m]-(Fcpage-1)*15)<15 )
						{
							if(jrkPie[m]%2==0)
							{
								grphics.FillRectangle(&SolidBrush(Color(100,229,232,177)),Rect(305,388+15*(jrkPie[m]-(Fcpage-1)*15),500,15));
							}else{
								grphics.FillRectangle(&SolidBrush(Color(100,217,194,116)),Rect(305,388+15*(jrkPie[m]-(Fcpage-1)*15),500,15));
							}
							if(isPanrk)
							{
								if(PanPie==(jrkPie[m]-(Fcpage-1)*15))
								{
									strcount.Format("%d",jrkPie[m]+1);
									string = T2W((LPCTSTR)strcount);
									grphics.DrawString(string,-1,&f,PointF(305,388.0f+15.0f*((jrkPie[m]-(Fcpage-1)*15))),&SolidBrush(Color(255,255,0,0)));
									string = T2W((LPCTSTR)product.name);
									grphics.DrawString(string,-1,&f,PointF(355,388.0f+15.0f*((jrkPie[m]-(Fcpage-1)*15))),&SolidBrush(Color(255,255,0,0)));
									zb.Format("%.2f%s",sum/rk[m]*100,"%");
									string = T2W((LPCTSTR)zb);
									grphics.DrawString(string,-1,&f,PointF(505,388.0f+15.0f*((jrkPie[m]-(Fcpage-1)*15))),&SolidBrush(Color(255,255,0,0)));
									nums.Format("%.2f",sum);
									string = T2W((LPCTSTR)nums);
									grphics.DrawString(string,-1,&f,PointF(585,388.0f+15.0f*((jrkPie[m]-(Fcpage-1)*15))),&SolidBrush(Color(255,255,0,0)));	
								}else{
									strcount.Format("%d",jrkPie[m]+1);
									string = T2W((LPCTSTR)strcount);
									grphics.DrawString(string,-1,&f,PointF(305,388.0f+15.0f*((jrkPie[m]-(Fcpage-1)*15))),&SolidBrush(Color(255,0,0,0)));
									string = T2W((LPCTSTR)product.name);
									grphics.DrawString(string,-1,&f,PointF(355,388.0f+15.0f*((jrkPie[m]-(Fcpage-1)*15))),&SolidBrush(Color(255,0,0,0)));
									zb.Format("%.2f%s",sum/rk[m]*100,"%");
									string = T2W((LPCTSTR)zb);
									grphics.DrawString(string,-1,&f,PointF(505,388.0f+15.0f*((jrkPie[m]-(Fcpage-1)*15))),&SolidBrush(Color(255,0,0,0)));
									nums.Format("%.2f",sum);
									string = T2W((LPCTSTR)nums);
									grphics.DrawString(string,-1,&f,PointF(585,388.0f+15.0f*((jrkPie[m]-(Fcpage-1)*15))),&SolidBrush(Color(255,0,0,0)));				
								}
							}else
							{
								strcount.Format("%d",jrkPie[m]+1);
								string = T2W((LPCTSTR)strcount);
								grphics.DrawString(string,-1,&f,PointF(305,388.0f+15.0f*((jrkPie[m]-(Fcpage-1)*15))),&SolidBrush(Color(255,0,0,0)));
								string = T2W((LPCTSTR)product.name);
								grphics.DrawString(string,-1,&f,PointF(355,388.0f+15.0f*((jrkPie[m]-(Fcpage-1)*15))),&SolidBrush(Color(255,0,0,0)));
								zb.Format("%.2f%s",sum/rk[m]*100,"%");
								string = T2W((LPCTSTR)zb);
								grphics.DrawString(string,-1,&f,PointF(505,388.0f+15.0f*((jrkPie[m]-(Fcpage-1)*15))),&SolidBrush(Color(255,0,0,0)));
								nums.Format("%.2f",sum);
								string = T2W((LPCTSTR)nums);
								grphics.DrawString(string,-1,&f,PointF(585,388.0f+15.0f*((jrkPie[m]-(Fcpage-1)*15))),&SolidBrush(Color(255,0,0,0)));				
							}
						}
						jrkPie[m]++;
						if(jrkPie[m]!=0)
						{
							if((jrkPie[m]+1)%15==0)
							{
								FcpageMax=(jrkPie[m]+1)/15;
							}else{
								FcpageMax=(jrkPie[m]+1)/15+1;
							}
						}
					}
				}else{
					if(sum/ck[m]>0)
					{	
						if(sum/ck[m]==1)
						{			
							grphics.FillEllipse(&SolidBrush(Color(100,45,85,211)),Rect(105,368+20,200,200));
						}
						else 
						{
							Pen p1(Color(100,45,85,211));
							grphics.DrawPie(&p1,Rect(105,368+20,200,200),ckPie[m],360*(sum/ck[m]));	
							if(PanPie==(jckPie[m]-(Fcpage-1)*15)&&!isPanrk)
								grphics.FillPie(&SolidBrush(Color(100,45,85,211)),Rect(105,368+20,200,200),ckPie[m],360*(sum/ck[m]));
						}
						ckPie[m]=ckPie[m]+360*(sum/ck[m]); 
						if( (jckPie[m]-(Fcpage-1)*15)<15)
						{
							if(jckPie[m]%2==0)
							{
								grphics.FillRectangle(&SolidBrush(Color(100,229,232,177)),Rect(305,388+15*(jckPie[m]-(Fcpage-1)*15),500,15));
							}else{
								grphics.FillRectangle(&SolidBrush(Color(100,217,194,116)),Rect(305,388+15*(jckPie[m]-(Fcpage-1)*15),500,15));
							}
							if(!isPanrk)
							{
								if(PanPie==(jckPie[m]-(Fcpage-1)*15))
								{
									strcount.Format("%d",jckPie[m]+1);
									string = T2W((LPCTSTR)strcount);
									grphics.DrawString(string,-1,&f,PointF(305,388.0f+15.0f*(jckPie[m]-(Fcpage-1)*15)),&SolidBrush(Color(255,0,0,255)));
									string = T2W((LPCTSTR)product.name);
									grphics.DrawString(string,-1,&f,PointF(355,388.0f+15.0f*(jckPie[m]-(Fcpage-1)*15)),&SolidBrush(Color(255,0,0,255)));
									zb.Format("%.2f%s",sum/ck[m]*100,"%");
									string = T2W((LPCTSTR)zb);
									grphics.DrawString(string,-1,&f,PointF(505,388.0f+15.0f*(jckPie[m]-(Fcpage-1)*15)),&SolidBrush(Color(255,0,0,255)));
									nums.Format("%.2f",sum);
									string = T2W((LPCTSTR)nums);
									grphics.DrawString(string,-1,&f,PointF(585,388.0f+15.0f*(jckPie[m]-(Fcpage-1)*15)),&SolidBrush(Color(255,0,0,255)));	
								}else{
									strcount.Format("%d",jckPie[m]+1);
									string = T2W((LPCTSTR)strcount);
									grphics.DrawString(string,-1,&f,PointF(305,388.0f+15.0f*(jckPie[m]-(Fcpage-1)*15)),&SolidBrush(Color(255,0,0,0)));
									string = T2W((LPCTSTR)product.name);
									grphics.DrawString(string,-1,&f,PointF(355,388.0f+15.0f*(jckPie[m]-(Fcpage-1)*15)),&SolidBrush(Color(255,0,0,0)));
									zb.Format("%.2f%s",sum/ck[m]*100,"%");
									string = T2W((LPCTSTR)zb);
									grphics.DrawString(string,-1,&f,PointF(505,388.0f+15.0f*(jckPie[m]-(Fcpage-1)*15)),&SolidBrush(Color(255,0,0,0)));
									nums.Format("%.2f",sum);
									string = T2W((LPCTSTR)nums);
									grphics.DrawString(string,-1,&f,PointF(585,388.0f+15.0f*(jckPie[m]-(Fcpage-1)*15)),&SolidBrush(Color(255,0,0,0)));	
								}
							}
							else
							{
								strcount.Format("%d",jckPie[m]+1);
								string = T2W((LPCTSTR)strcount);
								grphics.DrawString(string,-1,&f,PointF(305,388.0f+15.0f*(jckPie[m]-(Fcpage-1)*15)),&SolidBrush(Color(255,0,0,0)));
								string = T2W((LPCTSTR)product.name);
								grphics.DrawString(string,-1,&f,PointF(355,388.0f+15.0f*(jckPie[m]-(Fcpage-1)*15)),&SolidBrush(Color(255,0,0,0)));
								zb.Format("%.2f%s",sum/ck[m]*100,"%");
								string = T2W((LPCTSTR)zb);
								grphics.DrawString(string,-1,&f,PointF(505,388.0f+15.0f*(jckPie[m]-(Fcpage-1)*15)),&SolidBrush(Color(255,0,0,0)));
								nums.Format("%.2f",sum);
								string = T2W((LPCTSTR)nums);
								grphics.DrawString(string,-1,&f,PointF(585,388.0f+15.0f*(jckPie[m]-(Fcpage-1)*15)),&SolidBrush(Color(255,0,0,0)));	
							}
						}
						jckPie[m]++;
						if(jckPie[m]!=0)
						{
							if((jckPie[m]+1)%15==0)
							{
								FcpageMax=(jckPie[m]+1)/15;
							}else{
								FcpageMax=(jckPie[m]+1)/15+1;
							}
						}
					}
				}
				
			}
			////详情翻页
			string = T2W((LPCTSTR)"上一页");
			grphics.FillRectangle(&SolidBrush(Color(255,217,194,116)),Rect(550,620,40,15));
			grphics.DrawString(string,-1,&fjd,PointF(550,620),&SolidBrush(Color(200,255,255,255)));
			//当前页数
			CString strpage;
			strpage.Format("%d",Fcpage);
			string = T2W((LPCTSTR)strpage);
			grphics.DrawString(string,-1,&fjd,PointF(670,620),&SolidBrush(Color(100,0,0,0)));
			//最大页数
			strpage.Format("共%d页",FcpageMax);
			string = T2W((LPCTSTR)strpage);
			grphics.DrawString(string,-1,&fjd,PointF(720,620),&SolidBrush(Color(100,0,0,0)));

			string = T2W((LPCTSTR)"下一页");    
			grphics.FillRectangle(&SolidBrush(Color(255,217,194,116)),Rect(770,620,40,15));
			grphics.DrawString(string,-1,&fjd,PointF(770,620),&SolidBrush(Color(200,255,255,255)));
			
		}
	}
	dc.StretchBlt(0,0,850,712,&mdc,0,0,850,712,SRCCOPY);

	//绘图完成后的清理  
	m_Back.DeleteObject();  
	mdc.DeleteDC();
	// 不为绘图消息调用 CDialogEx::OnPaint()
}
HBRUSH M_I_detail::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	 if ((pWnd->GetDlgCtrlID() == (IDC_date))||(pWnd->GetDlgCtrlID() == (IDC_line)) )
	 {
		  pDC->SetBkMode(TRANSPARENT);
		  pDC->SetTextColor(RGB(0,0,0));
		  CFont f;
		  f.CreatePointFont(140,"宋体");
		  pDC->SelectObject(&f);
		  return HBRUSH(GetStockObject(HOLLOW_BRUSH));
	 }
	return hbr;
}
//1.1
void M_I_detail::OnDtnCloseupstartdate(NMHDR *pNMHDR, LRESULT *pResult)
{
	CTime tm;
	m_d1.GetTime(tm);
	stime=tm.Format("%Y-%m-%d");
	m_d2.GetTime(tm);
	etime=tm.Format("%Y-%m-%d");
	CString SQL;
	SQL.Format("SELECT * FROM tally.inventory where I_time>='%s' and I_time<='%s' order by I_time asc;",stime,etime);
	inventory.selectSql(SQL);
	m_list.SetRedraw(0);
	m_list.DeleteAllItems();

	if(kcdtNum>0)
	{
		m_d1.SetWindowTextA(kcindex[0].time.Left(10));
		m_d2.SetWindowTextA(kcindex[kcdtNum-1].time.Left(10));
		CString stri,rk,ck,kc;
		for(int i=0;i<kcdtNum;i++)
		{
			product.id=kcindex[i].goodsId;
			product=product.selectId(product);

			stri.Format("%d",i+1);
			rk.Format("%.2f",kcindex[i].rk);
			ck.Format("%.2f",kcindex[i].ck);
			kc.Format("%.2f",kcindex[i].kc);
			m_list.InsertItem(i,stri);
			m_list.SetItemText(i,1,product.name);
			m_list.SetItemText(i,2,rk);
			m_list.SetItemText(i,3,ck);
			m_list.SetItemText(i,4,kc);
			m_list.SetItemText(i,5,kcindex[i].time);
			m_list.SetItemText(i,6,kcindex[i].remark);
		}
	}
	m_list.SetRedraw(1);
	m_list.Invalidate();

	*pResult = 0;
}

//1.2
void M_I_detail::OnNMKillfocusstartdate(NMHDR *pNMHDR, LRESULT *pResult)
{
	CTime tm;
	m_d1.GetTime(tm);
	stime=tm.Format("%Y-%m-%d");
	m_d2.GetTime(tm);
	etime=tm.Format("%Y-%m-%d");
	CString SQL;
	SQL.Format("SELECT * FROM tally.inventory where I_time>='%s' and I_time<='%s' order by I_time asc;",stime,etime);
	inventory.selectSql(SQL);
	m_list.SetRedraw(0);
	m_list.DeleteAllItems();

	if(kcdtNum>0)
	{
		m_d1.SetWindowTextA(kcindex[0].time.Left(10));
		m_d2.SetWindowTextA(kcindex[kcdtNum-1].time.Left(10));
		CString stri,rk,ck,kc;
		for(int i=0;i<kcdtNum;i++)
		{
			product.id=kcindex[i].goodsId;
			product=product.selectId(product);

			stri.Format("%d",i+1);
			rk.Format("%.2f",kcindex[i].rk);
			ck.Format("%.2f",kcindex[i].ck);
			kc.Format("%.2f",kcindex[i].kc);
			m_list.InsertItem(i,stri);
			m_list.SetItemText(i,1,product.name);
			m_list.SetItemText(i,2,rk);
			m_list.SetItemText(i,3,ck);
			m_list.SetItemText(i,4,kc);
			m_list.SetItemText(i,5,kcindex[i].time);
			m_list.SetItemText(i,6,kcindex[i].remark);
		}
	}
	m_list.SetRedraw(1);
	m_list.Invalidate();

	*pResult = 0;
}

//2.1
void M_I_detail::OnDtnCloseupenddate(NMHDR *pNMHDR, LRESULT *pResult)
{
	CTime tm;
	m_d1.GetTime(tm);
	stime=tm.Format("%Y-%m-%d");
	m_d2.GetTime(tm);
	etime=tm.Format("%Y-%m-%d");
	CString SQL;
	SQL.Format("SELECT * FROM tally.inventory where I_time>='%s' and I_time<='%s' order by I_time asc;",stime,etime);
	inventory.selectSql(SQL);
	m_list.SetRedraw(0);
	m_list.DeleteAllItems();

	if(kcdtNum>0)
	{
		m_d1.SetWindowTextA(kcindex[0].time.Left(10));
		m_d2.SetWindowTextA(kcindex[kcdtNum-1].time.Left(10));
		CString stri,rk,ck,kc;
		for(int i=0;i<kcdtNum;i++)
		{
			product.id=kcindex[i].goodsId;
			product=product.selectId(product);

			stri.Format("%d",i+1);
			rk.Format("%.2f",kcindex[i].rk);
			ck.Format("%.2f",kcindex[i].ck);
			kc.Format("%.2f",kcindex[i].kc);
			m_list.InsertItem(i,stri);
			m_list.SetItemText(i,1,product.name);
			m_list.SetItemText(i,2,rk);
			m_list.SetItemText(i,3,ck);
			m_list.SetItemText(i,4,kc);
			m_list.SetItemText(i,5,kcindex[i].time);
			m_list.SetItemText(i,6,kcindex[i].remark);
		}
	}
	m_list.SetRedraw(1);
	m_list.Invalidate();

	*pResult = 0;
}

//2.2
void M_I_detail::OnNMKillfocusenddate(NMHDR *pNMHDR, LRESULT *pResult)
{
	CTime tm;
	m_d1.GetTime(tm);
	stime=tm.Format("%Y-%m-%d");
	m_d2.GetTime(tm);
	etime=tm.Format("%Y-%m-%d");
	CString SQL;
	SQL.Format("SELECT * FROM tally.inventory where I_time>='%s' and I_time<='%s' order by I_time asc;",stime,etime);
	inventory.selectSql(SQL);
	m_list.SetRedraw(0);
	m_list.DeleteAllItems();

	if(kcdtNum>0)
	{
		m_d1.SetWindowTextA(kcindex[0].time.Left(10));
		m_d2.SetWindowTextA(kcindex[kcdtNum-1].time.Left(10));
		CString stri,rk,ck,kc;
		for(int i=0;i<kcdtNum;i++)
		{
			product.id=kcindex[i].goodsId;
			product=product.selectId(product);

			stri.Format("%d",i+1);
			rk.Format("%.2f",kcindex[i].rk);
			ck.Format("%.2f",kcindex[i].ck);
			kc.Format("%.2f",kcindex[i].kc);
			m_list.InsertItem(i,stri);
			m_list.SetItemText(i,1,product.name);
			m_list.SetItemText(i,2,rk);
			m_list.SetItemText(i,3,ck);
			m_list.SetItemText(i,4,kc);
			m_list.SetItemText(i,5,kcindex[i].time);
			m_list.SetItemText(i,6,kcindex[i].remark);
		}
	}
	m_list.SetRedraw(1);
	m_list.Invalidate();

	*pResult = 0;
}


void M_I_detail::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(!m_changePics.IsWindowVisible())
	{
		CRect text(552,10,793,28);
		CString str;
		m_edit.GetWindowText(str);

		CRect mzrect0(70,620,178,650);
		CRect mzrect1(180,620,288,650);
		CRect mzrect3(400,620,508,650);
		CRect mzrect4(510,620,618,650);
		CRect retur(630,540,688,560);
		int startpage;
		startpage=page;
		CString strs;
		CRect prect(20,380,605,615);
		if(picMonth)
		{
			if(retur.PtInRect(point))
			{
				picMonth=false;
				InvalidateRect(CRect(0,380,745,620),0);
			}
		}
		for(int i=0;i<12;i++)
		{
			if(prect.PtInRect(point))
			{
				if(chooseMonth==i)
				{
					picMonth=true;
					tallyMonth(chooseMonth+1);
					InvalidateRect(CRect(20,380,745,620),0);
				}
			}else{
				//picMonth=false;
			}
		}
		/*CString s;
		s.Format("%d",picMonth);
		MessageBox(s);*/
		if(mzrect0.PtInRect(point))
		{
			if(isChoose0&&page>1)
			{
				if(pc->GetCheck())
				{
					pc->SetCheck(0);
				}
				if(pr->GetCheck())
				{
					pr->SetCheck(0);
				}
				page=page-2;
				if(picMonth)
					tallyMonth(chooseMonth+1);
				else
					tally();
				InvalidateRect(CRect(0,375,745,620),0);
				InvalidateRect(CRect(60,620,590,660),0);
				if(page==0)
					m_lastpage.EnableWindow(0);
				else
					m_lastpage.EnableWindow(1);
				m_nextpage.EnableWindow(1);
				//picMonth=false;
			}
		}
		if(mzrect1.PtInRect(point))
		{
			if(isChoose1&&page>0)
			{
				if(pc->GetCheck())
				{
					pc->SetCheck(0);
				}
				if(pr->GetCheck())
				{
					pr->SetCheck(0);
				}

				page=page-1;
				if(picMonth)
					tallyMonth(chooseMonth+1);
				else
					tally();
				InvalidateRect(CRect(0,375,745,620),0);
				InvalidateRect(CRect(60,620,590,660),0);
				if(page==0)
					m_lastpage.EnableWindow(0);
				else
					m_lastpage.EnableWindow(1);
				m_nextpage.EnableWindow(1);
				//picMonth=false;
			}
		}
		if(mzrect3.PtInRect(point))
		{
			if(isChoose3&&page<=pageMax-2)
			{
				if(pc->GetCheck())
				{
					pc->SetCheck(0);
				}
				if(pr->GetCheck())
				{
					pr->SetCheck(0);
				}

				page=page+1;
				if(picMonth)
					tallyMonth(chooseMonth+1);
				else
					tally();
				InvalidateRect(CRect(0,375,745,620),0);
				InvalidateRect(CRect(60,620,590,660),0);
				if(page==pageMax-1)
					m_nextpage.EnableWindow(0);
				else
					m_nextpage.EnableWindow(1);
				m_lastpage.EnableWindow(1);
				//picMonth=false;
			}
		}
		if(mzrect4.PtInRect(point))
		{
			if(isChoose4&&page<=pageMax-3)
			{
				if(pc->GetCheck())
				{
					pc->SetCheck(0);
				}
				if(pr->GetCheck())
				{
					pr->SetCheck(0);
				}

				page=page+2;
				if(picMonth)
					tallyMonth(chooseMonth+1);
				else
					tally();
				InvalidateRect(CRect(0,375,745,620),0);
				InvalidateRect(CRect(60,620,590,660),0);
				if(page==pageMax-1)
					m_nextpage.EnableWindow(0);
				else
					m_nextpage.EnableWindow(1);
				m_lastpage.EnableWindow(1);
				//picMonth=false;
			}
		}
		if (text.PtInRect(point))       
		{
			//m_edit.SetParent(this);//转换坐标为窗口中的坐标
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
	}else{
		if(Fcdetail)
		{
			CRect rectFcdt(105,368,205,368+18);
			if(rectFcdt.PtInRect(point))//返回
			{
				InvalidateRect(CRect(105,368,850,714),0);
				Fcdetail=false;
				fanchart=true;
				PanPie=-1;
				isPanrk=false;			
				m_lastpage.ShowWindow(0);
				m_nextpage.ShowWindow(0);
				m_lastpage.MoveWindow(20,620,32,32);
				m_nextpage.MoveWindow(590,620,32,32);
				Fcpage=1;
				FcpageMax=1;
			}
			CRect lapg(550,620,550+40,620+15);
			CRect nxpg(770,620,770+40,620+15);
			if(lapg.PtInRect(point))
			{
				if(Fcpage>1)
				{
					Fcpage--;
					InvalidateRect(CRect(105,388,850,588),0);
					InvalidateRect(CRect(140,588,270,600),0);
					InvalidateRect(CRect(305,588,850,714),0);
				}
			}
			if(nxpg.PtInRect(point))
			{
				if(Fcpage<FcpageMax)
				{
					Fcpage++;
					InvalidateRect(CRect(105,388,850,588),0);
					InvalidateRect(CRect(140,588,270,600),0);
					InvalidateRect(CRect(305,588,850,714),0);
				}
			}
		}else{
			for(int i=0;i<6;i++)
			{
				//入库圆形  
				CRect rectr1(105+i*120,368+20,105+i*120+70,368+20+70);
				CRect rectr7(105+i*120,368+100,105+i*120+70,368+100+70);
				//出库圆形                      
				CRect rectc1(105+i*120,368+190,105+i*120+70,368+190+70);
				CRect rectc7(105+i*120,368+270,105+i*120+70,368+270+70);
				if(rectr1.PtInRect(point))
				{
					InvalidateRect(CRect(105,368,850,714),0);
					//FcMonth
					Fcdetail=true;
					fanchart=false;
					if(FcMonth==0 || FcMonth==12)
						m_lastpage.EnableWindow(0);
					else
						m_lastpage.EnableWindow(1);
					m_nextpage.EnableWindow(1);	
					m_lastpage.EnableWindow(1);
					m_nextpage.EnableWindow(1);	
					m_lastpage.ShowWindow(1);
					m_nextpage.ShowWindow(1);
					m_lastpage.MoveWindow(105,588,32,32);
					m_nextpage.MoveWindow(270,588,32,32);
				}
				if(rectr7.PtInRect(point))
				{
					InvalidateRect(CRect(105,368,850,714),0);
					Fcdetail=true;
					fanchart=false;
					m_lastpage.EnableWindow(1);
					if(FcMonth==11 || FcMonth-12==11)
					{
						m_nextpage.EnableWindow(0);	
					}else{
						m_nextpage.EnableWindow(1);	
					}
					m_lastpage.ShowWindow(1);
					m_nextpage.ShowWindow(1);
					m_lastpage.MoveWindow(105,588,32,32);
					m_nextpage.MoveWindow(270,588,32,32);
				}
				if(rectc1.PtInRect(point))
				{
					InvalidateRect(CRect(105,368,850,714),0);
					Fcdetail=true;
					fanchart=false;
					m_nextpage.EnableWindow(1);
					if(FcMonth==0 || FcMonth==12)
						m_lastpage.EnableWindow(0);
					else
						m_lastpage.EnableWindow(1);
					m_lastpage.ShowWindow(1);
					m_nextpage.ShowWindow(1);
					m_lastpage.MoveWindow(105,588,32,32);
					m_nextpage.MoveWindow(270,588,32,32);
				}
				if(rectc7.PtInRect(point))
				{
					InvalidateRect(CRect(105,368,850,714),0);
					Fcdetail=true;
					fanchart=false;
					m_lastpage.EnableWindow(1);
					if(FcMonth==11 || FcMonth-12==11)
					{
						m_nextpage.EnableWindow(0);	
					}else{
						m_nextpage.EnableWindow(1);	
					}
					m_lastpage.ShowWindow(1);
					m_nextpage.ShowWindow(1);
					m_lastpage.MoveWindow(105,588,32,32);
					m_nextpage.MoveWindow(270,588,32,32);
				}
			}
		}
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}


void M_I_detail::OnHdnItemclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	CString strItem0;
	LVCOLUMN lvcol;
	lvcol.mask = LVCF_TEXT;
	char str[256];
	lvcol.pszText = str;
	lvcol.cchTextMax = 256;
	if(phdr->iItem==0)
	{
		m_list.GetColumn(0,&lvcol);
		strItem0=lvcol.pszText;
		if(strItem0=="◢筛选")
		{
			strcpy( str,"◤筛选");
			lvcol.pszText=str;
			m_list.SetColumn(0,&lvcol);
			m_d1.ShowWindow(1);
			m_d2.ShowWindow(1);
		}else{
			strcpy( str,"◢筛选");
			lvcol.pszText=str;
			m_list.SetColumn(0,&lvcol);
			m_d1.ShowWindow(0);
			m_d2.ShowWindow(0);
			show();
		}
	}else if(phdr->iItem==1&&!m_d1.IsWindowVisible()&&!m_d2.IsWindowVisible()){
		m_list.GetColumn(1,&lvcol);
		strItem0=lvcol.pszText;
		m_list.SetRedraw(0);
		if(strItem0=="品名")
		{
			m_list.DeleteAllItems();
			strcpy( str,"品名○");
			lvcol.pszText=str;
			m_list.SetColumn(1,&lvcol);

			inventory.selectSql("SELECT * FROM tally.inventory order by I_goodsId asc;");
			CString stri,rk,ck,kc;
			for(int i=0;i<kcdtNum;i++)
			{
				product.id=kcindex[i].goodsId;
				product=product.selectId(product);

				stri.Format("%d",i+1);
				rk.Format("%.2f",kcindex[i].rk);
				ck.Format("%.2f",kcindex[i].ck);
				kc.Format("%.2f",kcindex[i].kc);
				m_list.InsertItem(i,stri);
				m_list.SetItemText(i,1,product.name);
				m_list.SetItemText(i,2,rk);
				m_list.SetItemText(i,3,ck);
				m_list.SetItemText(i,4,kc);
				m_list.SetItemText(i,5,kcindex[i].time);
				m_list.SetItemText(i,6,kcindex[i].remark);
			}
			if(barchart)
			{
				tally();
			}else{
				tallyMonth(chooseMonth+1);
			}
			if(barchart)
			{
				InvalidateRect(CRect(0,368,620,600),0);
				InvalidateRect(CRect(60,620,590,660),0);
			}
		}else if(strItem0=="品名○")
		{
			m_list.DeleteAllItems();
			strcpy( str,"品名●");
			lvcol.pszText=str;
			m_list.SetColumn(1,&lvcol);
			inventory.selectSql("SELECT * FROM tally.inventory order by I_goodsId desc;");
			CString stri,rk,ck,kc;
			for(int i=0;i<kcdtNum;i++)
			{
				/*product.id=kcindex[i].goodsId;
				product=product.selectId(product);*/
				product.id=kcindex[i].goodsId;
				product=product.selectId(product);

				stri.Format("%d",i+1);
				rk.Format("%.2f",kcindex[i].rk);
				ck.Format("%.2f",kcindex[i].ck);
				kc.Format("%.2f",kcindex[i].kc);
				m_list.InsertItem(i,stri);
				m_list.SetItemText(i,1,product.name);
				m_list.SetItemText(i,2,rk);
				m_list.SetItemText(i,3,ck);
				m_list.SetItemText(i,4,kc);
				m_list.SetItemText(i,5,kcindex[i].time);
				m_list.SetItemText(i,6,kcindex[i].remark);
			}
			if(barchart)
			{
				tally();
				InvalidateRect(CRect(0,368,620,600),0);
				InvalidateRect(CRect(60,620,590,660),0);
			}else{
				tallyMonth(chooseMonth+1);
			}
			
		}else if(strItem0=="品名●"){
			m_list.DeleteAllItems();
			strcpy( str,"品名");
			lvcol.pszText=str;
			m_list.SetColumn(1,&lvcol);
			show();
		}
		m_list.SetRedraw(1);
		m_list.Invalidate();
		if(barchart)
		{
			tally();
			InvalidateRect(CRect(0,368,620,600),0);
			InvalidateRect(CRect(60,620,590,660),0);
		}else{
			tallyMonth(chooseMonth+1);
		}
		
	}else if(phdr->iItem==5){
		if(!m_d1.IsWindowVisible()&&!m_d2.IsWindowVisible())
		{
			m_list.GetColumn(5,&lvcol);
			strItem0=lvcol.pszText;
			if(strItem0=="时间")
			{
				m_list.DeleteAllItems();
				strcpy( str,"时间▽");
				lvcol.pszText=str;
				m_list.SetColumn(5,&lvcol);

				inventory.selectSql("SELECT * FROM tally.inventory order by I_time desc;");
				CString stri,rk,ck,kc;
				for(int i=0;i<kcdtNum;i++)
				{
					/*product.id=kcindex[i].goodsId;
					product=product.selectId(product);*/
					product.id=kcindex[i].goodsId;
					product=product.selectId(product);

					stri.Format("%d",i+1);
					rk.Format("%.2f",kcindex[i].rk);
					ck.Format("%.2f",kcindex[i].ck);
					kc.Format("%.2f",kcindex[i].kc);
					m_list.InsertItem(i,stri);
					m_list.SetItemText(i,1,product.name);
					m_list.SetItemText(i,2,rk);
					m_list.SetItemText(i,3,ck);
					m_list.SetItemText(i,4,kc);
					m_list.SetItemText(i,5,kcindex[i].time);
					m_list.SetItemText(i,6,kcindex[i].remark);
				}
				if(barchart)
				{
					tally();
					InvalidateRect(CRect(0,368,620,600),0);
					InvalidateRect(CRect(60,620,590,660),0);
				}else{
					tallyMonth(chooseMonth+1);
				}
			
			}else{
				m_list.DeleteAllItems();
				strcpy( str,"时间");
				lvcol.pszText=str;
				m_list.SetColumn(5,&lvcol);
				show();
				if(barchart)
				{
					tally();
					InvalidateRect(CRect(0,368,620,600),0);
					InvalidateRect(CRect(60,620,590,660),0);
				}else{
					tallyMonth(chooseMonth+1);
				}
			
			}
		}
	}
	*pResult = 0;
}


void M_I_detail::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_LISTVIEW* pNMListView=(NM_LISTVIEW*)pNMHDR;
	CRect rc;
	m_Row = pNMListView->iItem;//获得选中的行
	m_Col = pNMListView->iSubItem;//获得选中列

	if   (pNMListView->iSubItem != 0 && pNMListView->iItem !=-1 )
	{
		m_list.GetSubItemRect(m_Row,m_Col,LVIR_LABEL,rc);//获得子项的RECT；
		rc.bottom=rc.bottom-1;
		m_edit1.SetParent(&m_list);//转换坐标为列表框中的坐标
		m_edit1.MoveWindow(rc);//移动Edit到RECT坐在的位置;
		m_edit1.SetWindowText(m_list.GetItemText(m_Row,m_Col));//将该子项中的值放在Edit控件中；
		m_edit1.ShowWindow(SW_SHOW);//显示Edit控件；
		m_edit1.SetFocus();//设置Edit焦点
		m_edit1.ShowCaret();//显示光标
		m_edit1.SetSel(-1);//将光标移动到最后
		start_date=m_list.GetItemText(m_Row,m_Col);//还原初始数据
	}
	*pResult = 0;
}

void M_I_detail::OnEnKillfocusEdit2()
{
	CString tem;
	m_edit1.GetWindowText(tem);    //得到用户输入的新的内容
	m_list.SetItemText(m_Row,m_Col,tem);   //设置编辑框的新内容
	m_edit1.ShowWindow(SW_HIDE); //应藏编辑框
	CString sql;
	CString Id;
	Id.Format("%d",kcindex[m_Row].id);
	if(m_Col==1&&tem!=start_date)
	{	
		product.id=0;
		product.name=tem;
		product=product.select(product);

		CString goodsId;
		goodsId.Format("%d",product.id);

		if(product.id>0)
		{
			sql.Format("update tally.inventory set I_goodsId=%s where I_id=%s",goodsId,Id);
			if(inventory.update(sql))
			{
				//1.获取当前时间,插入历史记录
				GetLocalTime(&CurTime);////获取本地时间 
				h.time.Format("%d:%d:%d",CurTime.wHour,CurTime.wMinute,CurTime.wSecond);
				h.content="编辑库存明细\n变更产品"+product.name+"的品名\n"+start_date+"→"+m_list.GetItemText(m_Row,1);
				h.table="inventory";
				h.tableId=kcindex[m_Row].id;
				h.add();
				//2.插入listcontrol
				m_ListCtrl.InsertItem(0,h.time);
				m_ListCtrl.SetItemText(0,1,h.content);
				//3.更新图
				show();
	            if(barchart)
				{
					tally();
					InvalidateRect(CRect(20,380,620,600),0);
					InvalidateRect(CRect(60,620,590,660),0);
				}
				else
					tallyFanchart();
				
			}else{
				MessageBox("修改失败","提示",MB_ICONEXCLAMATION);
			}
		}else{
			MessageBox("修改失败,无此产品","提示",MB_ICONEXCLAMATION);
			m_list.SetItemText(m_Row,m_Col,start_date);   
		}
	}
	if(m_Col==2&&tem!=start_date)
	{
		sql.Format("update tally.inventory set I_rk=%s where I_id=%s",tem,Id);
		if(inventory.update(sql))
		{
			//1.获取当前时间,插入历史记录
			GetLocalTime(&CurTime);////获取本地时间 
			h.time.Format("%d:%d:%d",CurTime.wHour,CurTime.wMinute,CurTime.wSecond);
			h.content="编辑库存明细\n变更产品"+product.name+"的入库\n"+start_date+"→"+m_list.GetItemText(m_Row,2);
			h.table="inventory";
			h.tableId=kcindex[m_Row].id;
			h.add();
			//2.插入listcontrol
			m_ListCtrl.InsertItem(0,h.time);
			m_ListCtrl.SetItemText(0,1,h.content);
			//3.更新图
			show();
			if(barchart)
			{
				tally();
				InvalidateRect(CRect(20,380,620,600),0);
				InvalidateRect(CRect(60,620,590,660),0);
			}
			else
				tallyFanchart();
			
		}else{
			MessageBox("修改失败,输入数据不是纯数字","提示",MB_ICONEXCLAMATION);
			m_list.SetItemText(m_Row,m_Col,start_date);   
		}
	}
	if(m_Col==3&&tem!=start_date)
	{
		sql.Format("update tally.inventory set I_ck=%s where I_id=%s",tem,Id);
		if(inventory.update(sql))
		{
			//1.获取当前时间,插入历史记录
			GetLocalTime(&CurTime);////获取本地时间 
			h.time.Format("%d:%d:%d",CurTime.wHour,CurTime.wMinute,CurTime.wSecond);
			h.content="编辑库存明细\n变更产品"+product.name+"的出库\n"+start_date+"→"+m_list.GetItemText(m_Row,3);
			h.table="inventory";
			h.tableId=kcindex[m_Row].id;
			h.add();
			//2.插入listcontrol
			m_ListCtrl.InsertItem(0,h.time);
			m_ListCtrl.SetItemText(0,1,h.content);
			//3.更新图
			show();
			if(barchart)
			{
				tally();
				InvalidateRect(CRect(20,380,620,600),0);
				InvalidateRect(CRect(60,620,590,660),0);
			}
			else
				tallyFanchart();
			
		}else{
			MessageBox("修改失败,输入数据不是纯数字","提示",MB_ICONEXCLAMATION);
			m_list.SetItemText(m_Row,m_Col,start_date);   
		}
	}
	if(m_Col==4&&tem!=start_date)
	{
		sql.Format("update tally.inventory set I_kc=%s where I_id=%s",tem,Id);
		if(inventory.update(sql))
		{
			//1.获取当前时间,插入历史记录
			GetLocalTime(&CurTime);////获取本地时间 
			h.time.Format("%d:%d:%d",CurTime.wHour,CurTime.wMinute,CurTime.wSecond);
			h.content="编辑库存明细\n变更产品"+product.name+"的库存\n"+start_date+"→"+m_list.GetItemText(m_Row,4);
			h.table="inventory";
			h.tableId=kcindex[m_Row].id;
			h.add();
			//2.插入listcontrol
			m_ListCtrl.InsertItem(0,h.time);
			m_ListCtrl.SetItemText(0,1,h.content);

		}else{
			MessageBox("修改失败,输入数据不是纯数字","提示",MB_ICONEXCLAMATION);
			m_list.SetItemText(m_Row,m_Col,start_date);   
		}
	}
	if(m_Col==5&&tem!=start_date)
	{
		sql.Format("update tally.inventory set I_time='%s' where I_id=%s",tem,Id);
		if(inventory.update(sql))
		{
			//1.获取当前时间,插入历史记录
			GetLocalTime(&CurTime);////获取本地时间 
			h.time.Format("%d:%d:%d",CurTime.wHour,CurTime.wMinute,CurTime.wSecond);
			h.content="编辑库存明细\n变更产品"+product.name+"的时间\n"+start_date+"→"+m_list.GetItemText(m_Row,5);
			h.table="inventory";
			h.tableId=kcindex[m_Row].id;
			h.add();
			//2.插入listcontrol
			m_ListCtrl.InsertItem(0,h.time);
			m_ListCtrl.SetItemText(0,1,h.content);
		}else{
			MessageBox("修改失败，输入数据含有字母、特殊字符、长度不符","提示",MB_ICONEXCLAMATION);
			m_list.SetItemText(m_Row,m_Col,start_date);   
		}
	}
	if(m_Col==6&&tem!=start_date)
	{
		sql.Format("update tally.inventory set I_remark='%s' where I_id=%s",tem,Id);
		if(inventory.update(sql))
		{
			//1.获取当前时间,插入历史记录
			GetLocalTime(&CurTime);////获取本地时间 
			h.time.Format("%d:%d:%d",CurTime.wHour,CurTime.wMinute,CurTime.wSecond);
			h.content="编辑库存明细\n变更产品"+product.name+"的备注\n"+start_date+"→"+m_list.GetItemText(m_Row,6);
			h.table="inventory";
			h.tableId=kcindex[m_Row].id;
			h.add();
			//2.插入listcontrol
			m_ListCtrl.InsertItem(0,h.time);
			m_ListCtrl.SetItemText(0,1,h.content);
		}else{
			MessageBox("修改失败","提示",MB_ICONEXCLAMATION);
			m_list.SetItemText(m_Row,m_Col,start_date);   
		}
	}
}


void M_I_detail::OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult)
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


void M_I_detail::On32772()
{
	CString str;
	for(int i=0; i<m_list.GetItemCount();i++)
	{
		if( m_list.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED )
		{
			str.Format("%d",kcindex[i].id);
			CString sql;
			CString t;
			t=kcindex[i].time;
			sql.Format("DELETE FROM tally.inventory where I_id=%s",str);
			if(inventory.delet(sql))
			{
				//1.获取当前时间,插入历史记录
				GetLocalTime(&CurTime);////获取本地时间 
				h.time.Format("%d:%d:%d",CurTime.wHour,CurTime.wMinute,CurTime.wSecond);
				h.content="删除库存明细\n产品"+product.name+"的一条\n"+t+"记录";
				h.table="inventory";
				h.tableId=kcindex[i].id;
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


void M_I_detail::OnCancel()
{
	/*if(barchart)
	{
		tally();
	}else{
		tallyMonth(chooseMonth+1);
	}*/
	/*if(penPic)
	{
		penPic=false;
		m_lastpage.ShowWindow(0);
		m_nextpage.ShowWindow(0);
		m_changePic.ShowWindow(0);
		pc->ShowWindow(0);
		pr->ShowWindow(0);
		m_changePics.ShowWindow(0);
	}
	else
	{
		penPic=true;
		if(barchart)
		{
			m_lastpage.ShowWindow(1);
			m_nextpage.ShowWindow(1);
			m_changePic.ShowWindow(1);
			pc->ShowWindow(1);
			pr->ShowWindow(1);
			if(pc->GetCheck())
			{
				pc->SetCheck(0);
			}
			if(pr->GetCheck())
			{
				pr->SetCheck(0);
			}
		}else{
			m_changePics.ShowWindow(1);
		}
	}*/
	//InvalidateRect(CRect(0,368,850,714),0);
}


void M_I_detail::OnMouseMove(UINT nFlags, CPoint point)
{
	if(!m_changePics.IsWindowVisible())
	{
		CRect ckrect(630,385,680,400);
		CRect rkrect(630,415,680,430);
		CRect mzrect0(70,620,178,650);
		CRect mzrect1(180,620,288,650);
		CRect mzrect3(400,620,508,650);
		CRect mzrect4(510,620,618,650);
		CRect rect;
		
		if(!picMonth)
		{
			for(int i=0;i<12;i++)
			{
				if(i==0)
					rect.left=20+i*50;
				else
					rect.left=i*50;
				rect.top=390;
				rect.right=55+i*50;
				rect.bottom=615;
				////30.0f+i*50.0f, 600.0f
				//Point(55+50*i,390),Point(55+50*i,590)
				if(rect.PtInRect(point))
				{
					chooseMonth=i;
					InvalidateRect(CRect(20,600,670,620),0);
				}
			}
		}else{
			CRect retur(630,540,688,560);
			if(retur.PtInRect(point))
			{
				changeColor=true;
				InvalidateRect(retur,0);
			}else{
				changeColor=false;
				InvalidateRect(retur,0);
			}
			for(int d=0;d<dmax;d++)
			{
				if(d==0)
					rect.left=17+d*(590/dmax);
				else
					rect.left=22+d*(590/dmax);
				rect.top=390;
				rect.right=22+(d+1)*(590/dmax);
				rect.bottom=615;
				if(rect.PtInRect(point))
				{
					chooseDay=d;
					InvalidateRect(CRect(20,600,670,620),0);
				}
			}
		}
		if(mzrect0.PtInRect(point))
		{
			if(page>=2)
				isChoose0=true;
			else
				isChoose0=false;
		}else{
			isChoose0=false;
		}
		if(mzrect1.PtInRect(point))
		{
			if(page>=1)
				isChoose1=true;
			else
				isChoose1=false;
		}else{
			isChoose1=false;
		}
		if(mzrect3.PtInRect(point))
		{
			if(page<=pageMax-2)
				isChoose3=true;
			else
				isChoose3=false;
		}else{
			isChoose3=false;
		}
		if(mzrect4.PtInRect(point))
		{
			if(page<=pageMax-3)
				isChoose4=true;
			else
				isChoose4=false;
		}else{
			isChoose4=false;
		}
		if(ckrect.PtInRect(point))
		{
			isShowck=true;
			InvalidateRect(CRect(20,380,640,620),0);
		}else{
			if(!pc->GetCheck())
			{
				isShowck=false;
				InvalidateRect(CRect(20,380,640,620),0);
				InvalidateRect(CRect(60,620,590,660),0);
			}
		}
		if(rkrect.PtInRect(point))
		{
			isShowrk=true;
			InvalidateRect(CRect(20,380,640,620),0);
		}else{
			if(!pr->GetCheck())
			{
				isShowrk=false;
				InvalidateRect(CRect(20,380,640,620),0);
				InvalidateRect(CRect(60,620,590,660),0);
			}
		}
    }else{
		if(!Fcdetail)
		{
			for(int i=0;i<6;i++)
			{
				//入库圆形  
				CRect rectr1(105+i*120,368+20,105+i*120+70,368+20+70);
				CRect rectr7(105+i*120,368+100,105+i*120+70,368+100+70);
				//出库圆形                      
				CRect rectc1(105+i*120,368+190,105+i*120+70,368+190+70);
				CRect rectc7(105+i*120,368+270,105+i*120+70,368+270+70);
				if(rectr1.PtInRect(point))
				{
					InvalidateRect(CRect(105,368,850,714),0);
					FcMonth=i;
				}
				if(rectr7.PtInRect(point))
				{
					InvalidateRect(CRect(105,368,850,714),0);
					FcMonth=i+6;
				}
				if(rectc1.PtInRect(point))
				{
					InvalidateRect(CRect(105,368,850,714),0);
					FcMonth=i+12;
				}
				if(rectc7.PtInRect(point))
				{
					InvalidateRect(CRect(105,368,850,714),0);
					FcMonth=i+18;
				}	
			}
		}else{
			CRect rext;
			rext.left=305;
			rext.right=305+500;	
			CString stri;
			for(int i=0;i<15;i++)
			{
				rext.top=388+15*i;
				rext.bottom=388+15*i+15;
				if(rext.PtInRect(point))
				{
					if(i<(jrkPie[FcMonth]-(Fcpage-1)*15)&&FcMonth<12)
					{
						PanPie=i;
						isPanrk=true;
						InvalidateRect(CRect(105,388,850,588),0);
						InvalidateRect(CRect(140,588,270,600),0);
						InvalidateRect(CRect(305,588,850,714),0);
					}
					if(i<(jckPie[FcMonth-12]-(Fcpage-1)*15)&&FcMonth>=12)
					{
						PanPie=i;
						isPanrk=false;
						InvalidateRect(CRect(105,388,850,588),0);
						InvalidateRect(CRect(140,588,270,600),0);
						InvalidateRect(CRect(305,588,850,714),0);
						/*CString stri;
						stri.Format("%d",PanPie);
						MessageBox(stri);*/
					}
				}
			}
		}
	}
	CDialogEx::OnMouseMove(nFlags, point);
}


void M_I_detail::Onlastpage()
{
	if(Fcdetail)
	{
		if(FcMonth>0&&FcMonth!=12)
		{
			FcMonth--;
			Fcpage=1;
			InvalidateRect(CRect(105,388,850,714),0);
			m_nextpage.EnableWindow(1);
		}else{
			m_lastpage.EnableWindow(0);
		}
	}else{
		if(pc->GetCheck())
		{
			pc->SetCheck(0);
		}
		if(pr->GetCheck())
		{
			pr->SetCheck(0);
		}
		/*CString stc;
		stc.Format("%d %d",isShowck,isShowrk);
		MessageBox(stc);*/
		if(page>0)
		{
			m_nextpage.EnableWindow(1);
			page--;
			if(!picMonth)
				tally();
			else
				tallyMonth(chooseMonth+1);
			InvalidateRect(CRect(0,375,745,620),0);
			InvalidateRect(CRect(60,620,590,660),0);
		}
		if(page==0)
			m_lastpage.EnableWindow(0);
	}
}


void M_I_detail::Onnextpage()
{
	if(Fcdetail)
	{
		if( (FcMonth<11) || (FcMonth<23&&FcMonth>=12) )
		{
			FcMonth++;
			Fcpage=1;
			InvalidateRect(CRect(105,388,850,714),0);
			m_lastpage.EnableWindow(1);
			m_nextpage.EnableWindow(1);
		}else{
			m_nextpage.EnableWindow(0);
		}
	}else{
		if(pc->GetCheck())
		{
			pc->SetCheck(0);
		}
		if(pr->GetCheck())
		{
			pr->SetCheck(0);
		}
		if(page<pageMax-1)
		{
			m_lastpage.EnableWindow(1);
			page++;
			if(!picMonth)
				tally();
			else
				tallyMonth(chooseMonth+1);
			InvalidateRect(CRect(0,375,745,620),0);
			InvalidateRect(CRect(60,620,590,660),0);
		
		}
		if(page==pageMax-1)
				m_nextpage.EnableWindow(0);
	}
}


void M_I_detail::OnTimer(UINT_PTR nIDEvent)
{	
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


void M_I_detail::OnBnClickedCk()
{
	if(pc->GetCheck())
	{
		isShowck=true;
		InvalidateRect(CRect(20,380,620,600),0);
	}else{
		isShowck=false;
		InvalidateRect(CRect(20,380,620,600),0);
	}
}


void M_I_detail::OnBnClickedRk()
{
	if(pr->GetCheck())
	{
		isShowrk=true;
		InvalidateRect(CRect(20,380,620,600),0);
	}else{
		isShowrk=false;
		InvalidateRect(CRect(20,380,620,600),0);
	}
}

//扇形图 Fanchart
void M_I_detail::OnFanchart()
{
	tallyFanchart();
	fanchart=true;
	barchart=false;
	InvalidateRect(CRect(0,368,745,714),0);//(745,368,105,346);
	m_lastpage.ShowWindow(0);
	m_nextpage.ShowWindow(0);
	if(pc->GetCheck())
	{
		pc->SetCheck(0);
	}
	if(pr->GetCheck())
	{
		pr->SetCheck(0);
	}
	pc->ShowWindow(0);
	pr->ShowWindow(0);

	m_changePics.ShowWindow(1);
	m_changePic.ShowWindow(0);
}

//条形图 bar chart
void M_I_detail::OnBarchart()
{
	tally();
	/*penPic=true;*/
	fanchart=false;
	barchart=true;
	Fcdetail=false;
	FcMonth=-1;
	InvalidateRect(CRect(0,368,745,714),0);//(745,368,105,346);
	m_lastpage.ShowWindow(1);
	m_nextpage.ShowWindow(1);
	if(pc->GetCheck())
	{
		pc->SetCheck(0);
	}
	if(pr->GetCheck())
	{
		pr->SetCheck(0);
	}
	pc->ShowWindow(1);
	pr->ShowWindow(1);

	m_changePics.ShowWindow(0);
	m_changePic.ShowWindow(1);
	m_lastpage.ShowWindow(1);
	m_nextpage.ShowWindow(1);
	m_lastpage.MoveWindow(20,620,32,32);
	m_nextpage.MoveWindow(590,620,32,32);
}


void M_I_detail::OnOk()
{
	CString text,GID;
	m_edit.GetWindowTextA(text);
	product.id=0;
	product.name=text;
	product=product.select(product);
	GID.Format("%d",product.id);
	CString SQL;
	SQL.Format("SELECT * FROM tally.inventory where I_goodsId='%s' or I_remark like '%s%s%s' order by I_time asc;",GID,"%",text,"%");
	inventory.selectSql(SQL);

	m_list.SetRedraw(0);
	m_list.DeleteAllItems();

	if(kcdtNum>0)
	{
		m_d1.SetWindowTextA(kcindex[0].time.Left(10));
		m_d2.SetWindowTextA(kcindex[kcdtNum-1].time.Left(10));
		CString stri,rk,ck,kc;
		for(int i=0;i<kcdtNum;i++)
		{
			product.id=kcindex[i].goodsId;
			product=product.selectId(product);

			stri.Format("%d",i+1);
			rk.Format("%.2f",kcindex[i].rk);
			ck.Format("%.2f",kcindex[i].ck);
			kc.Format("%.2f",kcindex[i].kc);
			m_list.InsertItem(i,stri);
			m_list.SetItemText(i,1,product.name);
			m_list.SetItemText(i,2,rk);
			m_list.SetItemText(i,3,ck);
			m_list.SetItemText(i,4,kc);
			m_list.SetItemText(i,5,kcindex[i].time);
			m_list.SetItemText(i,6,kcindex[i].remark);
		}
	}
	m_list.SetRedraw(1);
	m_list.Invalidate();
}

