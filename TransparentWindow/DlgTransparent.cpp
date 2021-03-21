#include "pch.h"
#include "TransparentWindow.h"
#include "DlgTransparent.h"
#include "afxdialogex.h"

#define TIMER_UPDATE_LAYER 1
#define TIMER_DRAW_SRCEEN 2


IMPLEMENT_DYNAMIC(CDlgTransparent, CDialogEx)

CDlgTransparent::CDlgTransparent(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_TRANSPARENT, pParent)
{

}

CDlgTransparent::~CDlgTransparent()
{
}

void CDlgTransparent::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgTransparent, CDialogEx)
	ON_WM_TIMER()
	ON_WM_PAINT()
END_MESSAGE_MAP()

BOOL CDlgTransparent::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// GDI+
	ULONG_PTR gdiplusToken;
	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	_blend.AlphaFormat = AC_SRC_ALPHA;
	_blend.BlendFlags = 0;
	_blend.BlendOp = AC_SRC_OVER;
	_blend.SourceConstantAlpha = 255;

	//SetTimer(TIMER_UPDATE_LAYER, 10, nullptr);
	//SetTimer(TIMER_DRAW_SRCEEN, 10, nullptr);

	LONG extendedStyle = GetWindowLong(GetSafeHwnd(), GWL_EXSTYLE);
	SetWindowLong(GetSafeHwnd(), GWL_EXSTYLE, extendedStyle | WS_EX_TRANSPARENT | WS_EX_LAYERED);
	SetLayeredWindowAttributes(0, 128, LWA_ALPHA);

	MoveWindow(0, 0, 400, 400);
	CenterWindow();

	return TRUE;
}

void CDlgTransparent::UpdateLayeredWindow()
{
	CRect rect;
	::GetWindowRect(GetSafeHwnd(), rect);

	CClientDC dc(this);
	CDC memDC;
	CBitmap memBmp;
	memDC.CreateCompatibleDC(&dc);
	memBmp.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	CBitmap* oldBmp = memDC.SelectObject(&memBmp);

	POINT ptWinPos = { rect.left, rect.top };
	POINT ptSrc = { 0,0 };

	SIZE sizeWindow = { rect.Width(), rect.Height() };

	Graphics g(memDC);
	g.FillRectangle(&SolidBrush(Color(128, 100, 255, 100)), 0, 0, rect.Width(), rect.Height());

	::UpdateLayeredWindow(GetSafeHwnd(), dc.GetSafeHdc(), &ptWinPos, &sizeWindow, memDC.GetSafeHdc(), &ptSrc, 0, &_blend, ULW_ALPHA);

	memDC.SelectObject(oldBmp);
}

void CDlgTransparent::DrawScreen()
{
	CRect rect;
	::GetWindowRect(GetSafeHwnd(), rect);

	CDC* desktopDC = GetDesktopWindow()->GetDC();
	Graphics g(*desktopDC);
	g.FillRectangle(&SolidBrush(Color(128, 100, 255, 100)), 200, 200, rect.Width(), rect.Height());
}

void CDlgTransparent::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == TIMER_UPDATE_LAYER)
	{
		UpdateLayeredWindow();
	}
	else if (nIDEvent == TIMER_DRAW_SRCEEN)
	{
		DrawScreen();
	}

	CDialogEx::OnTimer(nIDEvent);
}

void CDlgTransparent::OnPaint()
{
	CRect rect;
	::GetWindowRect(GetSafeHwnd(), rect);

	CPaintDC dc(this);
	CDC memDC;
	CBitmap memBmp;
	memDC.CreateCompatibleDC(&dc);
	memBmp.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	CBitmap* oldBmp = memDC.SelectObject(&memBmp);

	Graphics g(memDC);
	g.FillRectangle(&SolidBrush(Color(255, 100, 100)), 0, 0, rect.Width(), rect.Height());

	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);
	memDC.SelectObject(oldBmp);
	memBmp.DeleteObject();
	memDC.DeleteDC();
}
