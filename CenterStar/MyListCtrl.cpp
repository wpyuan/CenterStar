// MyListCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "CenterStar.h"
#include "MyListCtrl.h"


// MyListCtrl

IMPLEMENT_DYNAMIC(MyListCtrl, CListCtrl)

MyListCtrl::MyListCtrl()
{

}

MyListCtrl::~MyListCtrl()
{
}


BEGIN_MESSAGE_MAP(MyListCtrl, CListCtrl)
	ON_WM_MEASUREITEM_REFLECT()
END_MESSAGE_MAP()



// MyListCtrl 消息处理程序
void MyListCtrl::SetRowHeight(int nHeight)  
{  
    m_nRowHeight = nHeight;  
    //如果没有下面的代码，设置并不能奏效  
    CRect rcWin;  
    GetWindowRect(&rcWin);  
    WINDOWPOS wp;  
    wp.hwnd = m_hWnd;  
    wp.cx = rcWin.Width();  
    wp.cy = rcWin.Height();  
    wp.flags = SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER;  
    SendMessage(WM_WINDOWPOSCHANGED, 0, (LPARAM)&wp);  
}  

void MyListCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	 TCHAR lpBuffer[256];
	 LV_COLUMN lvc/*, lvcprev*/ ;
	 ::ZeroMemory(&lvc, sizeof(lvc));
	 lvc.mask = LVCF_WIDTH | LVCF_FMT;
	 long hight = 0;
	 for ( int nCol=0; GetColumn(nCol, &lvc); nCol++)
	 {
		lpDrawItemStruct->rcItem.left += hight ;
		lpDrawItemStruct->rcItem.right += hight ;
		hight = lvc.cx ;
		LV_ITEM lvi;
		::ZeroMemory(&lvi, sizeof(lvi));
		lvi.iItem = lpDrawItemStruct->itemID;
		lvi.mask = LVIF_TEXT | LVIF_PARAM;
		lvi.iSubItem = nCol;
		lvi.pszText = lpBuffer;
		lvi.cchTextMax = sizeof(lpBuffer);
		VERIFY(GetItem(&lvi));
		CDC* pDC;
		pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
		if ( lpDrawItemStruct->itemState & ODS_SELECTED )
		{
			pDC->FillSolidRect(&lpDrawItemStruct->rcItem,RGB(231, 243, 229)) ;	
			pDC->SetTextColor(RGB(0, 0, 0)) ;
		}
		else
		{
			pDC->FillSolidRect(&lpDrawItemStruct->rcItem, GetSysColor(COLOR_WINDOW)) ;
			pDC->SetTextColor(GetSysColor(COLOR_WINDOWTEXT)) ;
		}
		CFont lfont;
		lfont.CreateFont(20, 0, 0, 0, 0 ,0, 0, 0, GB2312_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH ,"宋体");
		CFont* pold = pDC->SelectObject(&lfont);
		lpDrawItemStruct->rcItem.left+=1;
		::DrawText(lpDrawItemStruct->hDC, lpBuffer, strlen(lpBuffer), &lpDrawItemStruct->rcItem, DT_LEFT) ;
		pDC->SelectStockObject(SYSTEM_FONT) ;
	 }
}


void MyListCtrl::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	lpMeasureItemStruct->itemHeight = m_nRowHeight;  
	//CListCtrl::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}


void MyListCtrl::PreSubclassWindow()
{
	if(GetHeaderCtrl()) 
	{   
		m_Header.SubclassWindow(GetHeaderCtrl()->m_hWnd);
	}

	CListCtrl::PreSubclassWindow();
}
