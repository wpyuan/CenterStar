// SkinHeaderCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "CenterStar.h"
#include "SkinHeaderCtrl.h"


// CSkinHeaderCtrl

IMPLEMENT_DYNAMIC(CSkinHeaderCtrl, CHeaderCtrl)

CSkinHeaderCtrl::CSkinHeaderCtrl()
{
	nPointSize=160;
	m_Height = 1.9;
}

CSkinHeaderCtrl::~CSkinHeaderCtrl()
{
}


BEGIN_MESSAGE_MAP(CSkinHeaderCtrl, CHeaderCtrl)
	ON_WM_PAINT()
	ON_MESSAGE(HDM_LAYOUT, OnLayout)
END_MESSAGE_MAP()



// CSkinHeaderCtrl 消息处理程序




void CSkinHeaderCtrl::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	 CRect rect;
	 GetClientRect(rect);
	 dc.FillSolidRect(rect,/*m_clrHead*/RGB(160,160,160));   //重绘标题栏颜色
	 int nItems = GetItemCount();
	 CRect rectItem;
	 CPen m_pen(PS_SOLID,1,/*m_clrHeadItem*/RGB(160,160,160));      //分隔线颜色
	 CPen * pOldPen=dc.SelectObject(&m_pen);
	 CFont m_font;
	 //m_font.Attach(m_fontHead);
	 //m_font.CreateFont(m_fontHeight,m_fontWith,0,0,0,FALSE,FALSE,0,0,0,0,0,0,_T("微软雅黑"));//创建字体 
	 m_font.CreatePointFont(nPointSize,"宋体");        //字体
	 CFont * pOldFont=dc.SelectObject(&m_font);
	 dc.SetTextColor(/*m_clrHeadText*/RGB(15,255,255));     //字体颜色
	 for(int i = 0; i <nItems; i++)                    //对标题的每个列进行重绘
	 {  
		  GetItemRect(i, &rectItem);
		  /*rectItem.top+=6;
		  rectItem.bottom+=6; */
		  dc.MoveTo(rectItem.right,rect.top);                //重绘分隔栏
		  dc.LineTo(rectItem.right,rectItem.bottom);
		  TCHAR buf[256];
		  HD_ITEM hditem;
		  hditem.mask = HDI_TEXT | HDI_FORMAT | HDI_ORDER;
		  hditem.pszText = buf;
		  hditem.cchTextMax = 255;
		  GetItem( i, &hditem );                                       //获取当然列的文字
		  UINT uFormat = DT_SINGLELINE | DT_NOPREFIX | DT_TOP |DT_CENTER | DT_END_ELLIPSIS ;
	      dc.DrawText(buf, &rectItem, uFormat);           //重绘标题栏的文字

	 }
	 dc.SelectObject(pOldPen);
	 dc.SelectObject(pOldFont);

	// 不为绘图消息调用 CHeaderCtrl::OnPaint()
}
LRESULT CSkinHeaderCtrl::OnLayout( WPARAM wParam, LPARAM lParam )
{
	 LRESULT lResult = CSkinHeaderCtrl::DefWindowProc(HDM_LAYOUT, 0, lParam); 
	 HD_LAYOUT &hdl = *( HD_LAYOUT * ) lParam; 
	 RECT *prc = hdl.prc; 
	 WINDOWPOS *pwpos = hdl.pwpos;
	 //表头高度为原来1.5倍，如果要动态修改表头高度的话，将1.5设成一个全局变量 
	// int nHeight = (int)(pwpos->cy * m_Height);
	 int nHeight = (int)(pwpos->cy * m_Height);
	 pwpos->cy = nHeight; 
	 prc->top = nHeight; 
	 return lResult; 
}