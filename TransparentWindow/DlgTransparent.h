#pragma once

#pragma comment(lib, "Gdiplus.lib")
#include <GdiPlus.h>
using namespace Gdiplus;

class CDlgTransparent : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgTransparent)

public:
	CDlgTransparent(CWnd* pParent = nullptr);
	virtual ~CDlgTransparent();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TRANSPARENT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX); 

	DECLARE_MESSAGE_MAP()

	BLENDFUNCTION	_blend;

	virtual BOOL OnInitDialog();
	void UpdateLayeredWindow();
	void DrawScreen();

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnPaint();
};
