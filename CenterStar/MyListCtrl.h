#pragma once
#include "SkinHeaderCtrl.h"
// MyListCtrl

class MyListCtrl : public CListCtrl
{
	DECLARE_DYNAMIC(MyListCtrl)

public:
	int m_nRowHeight;
	CSkinHeaderCtrl m_Header;

	MyListCtrl();
	virtual ~MyListCtrl();

protected:
	DECLARE_MESSAGE_MAP()
public:
	void SetRowHeight(int nHeight);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	virtual void PreSubclassWindow();
};


