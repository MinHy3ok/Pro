// CInputDlg.cpp: ���� ����
//

#include "pch.h"
#include "ImageProcess_20200778.h"
#include "afxdialogex.h"
#include "CInputDlg.h"


// CInputDlg ��ȭ ����

IMPLEMENT_DYNAMIC(CInputDlg, CDialogEx)

CInputDlg::CInputDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_zoom_in_ratio(0)
{

}

CInputDlg::~CInputDlg()
{
}

void CInputDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_zoom_in_ratio);
	DDV_MinMaxFloat(pDX, m_zoom_in_ratio, 0, 360);
}


BEGIN_MESSAGE_MAP(CInputDlg, CDialogEx)
END_MESSAGE_MAP()


// CInputDlg �޽��� ó����
