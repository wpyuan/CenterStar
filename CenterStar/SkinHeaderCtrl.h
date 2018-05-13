#pragma once


// CSkinHeaderCtrl

class CSkinHeaderCtrl : public CHeaderCtrl
{
	DECLARE_DYNAMIC(CSkinHeaderCtrl)

public:
	int nPointSize;
	int m_Height;
	CSkinHeaderCtrl();
	virtual ~CSkinHeaderCtrl();

protected:
	DECLARE_MESSAGE_MAP()
	LRESULT OnLayout( WPARAM wParam, LPARAM lParam );
public:
	afx_msg void OnPaint();
};


