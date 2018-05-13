// SkinHeaderCtrl.cpp : ʵ���ļ�
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



// CSkinHeaderCtrl ��Ϣ�������




void CSkinHeaderCtrl::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	 CRect rect;
	 GetClientRect(rect);
	 dc.FillSolidRect(rect,/*m_clrHead*/RGB(160,160,160));   //�ػ��������ɫ
	 int nItems = GetItemCount();
	 CRect rectItem;
	 CPen m_pen(PS_SOLID,1,/*m_clrHeadItem*/RGB(160,160,160));      //�ָ�����ɫ
	 CPen * pOldPen=dc.SelectObject(&m_pen);
	 CFont m_font;
	 //m_font.Attach(m_fontHead);
	 //m_font.CreateFont(m_fontHeight,m_fontWith,0,0,0,FALSE,FALSE,0,0,0,0,0,0,_T("΢���ź�"));//�������� 
	 m_font.CreatePointFont(nPointSize,"����");        //����
	 CFont * pOldFont=dc.SelectObject(&m_font);
	 dc.SetTextColor(/*m_clrHeadText*/RGB(15,255,255));     //������ɫ
	 for(int i = 0; i <nItems; i++)                    //�Ա����ÿ���н����ػ�
	 {  
		  GetItemRect(i, &rectItem);
		  /*rectItem.top+=6;
		  rectItem.bottom+=6; */
		  dc.MoveTo(rectItem.right,rect.top);                //�ػ�ָ���
		  dc.LineTo(rectItem.right,rectItem.bottom);
		  TCHAR buf[256];
		  HD_ITEM hditem;
		  hditem.mask = HDI_TEXT | HDI_FORMAT | HDI_ORDER;
		  hditem.pszText = buf;
		  hditem.cchTextMax = 255;
		  GetItem( i, &hditem );                                       //��ȡ��Ȼ�е�����
		  UINT uFormat = DT_SINGLELINE | DT_NOPREFIX | DT_TOP |DT_CENTER | DT_END_ELLIPSIS ;
	      dc.DrawText(buf, &rectItem, uFormat);           //�ػ������������

	 }
	 dc.SelectObject(pOldPen);
	 dc.SelectObject(pOldFont);

	// ��Ϊ��ͼ��Ϣ���� CHeaderCtrl::OnPaint()
}
LRESULT CSkinHeaderCtrl::OnLayout( WPARAM wParam, LPARAM lParam )
{
	 LRESULT lResult = CSkinHeaderCtrl::DefWindowProc(HDM_LAYOUT, 0, lParam); 
	 HD_LAYOUT &hdl = *( HD_LAYOUT * ) lParam; 
	 RECT *prc = hdl.prc; 
	 WINDOWPOS *pwpos = hdl.pwpos;
	 //��ͷ�߶�Ϊԭ��1.5�������Ҫ��̬�޸ı�ͷ�߶ȵĻ�����1.5���һ��ȫ�ֱ��� 
	// int nHeight = (int)(pwpos->cy * m_Height);
	 int nHeight = (int)(pwpos->cy * m_Height);
	 pwpos->cy = nHeight; 
	 prc->top = nHeight; 
	 return lResult; 
}