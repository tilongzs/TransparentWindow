#include "pch.h"
#include "framework.h"
#include "TransparentWindow.h"
#include "TransparentWindowDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CTransparentWindowDlg::CTransparentWindowDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TRANSPARENTWINDOW_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTransparentWindowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTransparentWindowDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SHOW, &CTransparentWindowDlg::OnBnClickedButtonShow)
END_MESSAGE_MAP()


BOOL CTransparentWindowDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	_dlgTransparent.Create(IDD_DIALOG_TRANSPARENT);


	return TRUE;
}

void CTransparentWindowDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this);

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

HCURSOR CTransparentWindowDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTransparentWindowDlg::OnBnClickedButtonShow()
{
	if (_dlgTransparent.IsWindowVisible())
	{
		_dlgTransparent.ShowWindow(SW_HIDE);
	}
	else
	{
		_dlgTransparent.ShowWindow(SW_SHOW);
	}
}
