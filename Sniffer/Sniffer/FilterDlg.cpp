// FilterDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Sniffer.h"
#include "FilterDlg.h"
#include "afxdialogex.h"


// CFilterDlg �Ի���

IMPLEMENT_DYNAMIC(CFilterDlg, CDialogEx)

CFilterDlg::CFilterDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFilterDlg::IDD, pParent)
	, filtername(_T(""))
{

}

CFilterDlg::~CFilterDlg()
{
}

void CFilterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK1, m_tcp);
	DDX_Control(pDX, IDC_CHECK2, m_udp);
	DDX_Control(pDX, IDC_CHECK3, m_arp);
	DDX_Control(pDX, IDC_CHECK4, m_rarp);
	DDX_Control(pDX, IDC_CHECK5, m_icmp);
	DDX_Control(pDX, IDC_CHECK6, m_igmp);
}


BEGIN_MESSAGE_MAP(CFilterDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CFilterDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CFilterDlg ��Ϣ�������


BOOL CFilterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	m_tcp.SetCheck(1);   
	m_udp.SetCheck(1);   
	m_arp.SetCheck(1);   
	m_rarp.SetCheck(1);   
	m_icmp.SetCheck(1);
	m_igmp.SetCheck(1);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CFilterDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (1 == m_tcp.GetCheck())   
	{   
		filtername += _T("(tcp and ip) or ");   
	}   
	if (1 == m_udp.GetCheck())   
	{   
		filtername += _T("(udp and ip) or ");   
	}   
	if (1 == m_arp.GetCheck())   
	{   
		filtername += _T("arp or ");   
	}    
	if (1 == m_rarp.GetCheck())   
	{   
		filtername += _T("rarp or ");   
	}   
	if (1 == m_icmp.GetCheck())   
	{   
		filtername += _T("(icmp and ip) or ");   
	} 
	if (1 == m_igmp.GetCheck())   
	{   
		filtername += _T("(igmp and ip) or ");   
	}  
	filtername = filtername.Left(filtername.GetLength()-4);  //ȥ�������" or ",ʹ�ù��˹������

	CDialogEx::OnOK();

}

CString CFilterDlg::GetFilterName(void)
{
	return filtername;
}
