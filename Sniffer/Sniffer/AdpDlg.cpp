// AdpDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Sniffer.h"
#include "AdpDlg.h"
#include "afxdialogex.h"

#include "SnifferDlg.h"


// CAdpDlg �Ի���

IMPLEMENT_DYNAMIC(CAdpDlg, CDialogEx)

CAdpDlg::CAdpDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAdpDlg::IDD, pParent)
{

}

CAdpDlg::~CAdpDlg()
{
}

void CAdpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list1);
}


BEGIN_MESSAGE_MAP(CAdpDlg, CDialogEx)

	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CAdpDlg::OnNMClickList1)
	ON_BN_CLICKED(IDOK, &CAdpDlg::OnBnClickedOk)
END_MESSAGE_MAP()

// CAdapDlg ��Ϣ�������


BOOL CAdpDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_list1.SetExtendedStyle(m_list1.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_list1.InsertColumn(0,_T("�豸��"),LVCFMT_LEFT,350);
	m_list1.InsertColumn(1,_T("�豸����"),LVCFMT_LEFT,250);

	char errbuf[PCAP_ERRBUF_SIZE];

	if (pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL, &alldevs, errbuf) == -1)
		return FALSE;

	for(d=alldevs; d; d=d->next)
	{
		m_list1.InsertItem(0,(CString)d->name);		//d->name��������char *,��Ҫǿ��ת��ΪCString������InsertItem����ʾ
		m_list1.SetItemText(0,1,(CString)d->description);
	}
	d = NULL; //����Ա���������ʹ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


//��ȡ��ѡ�е���������
void CAdpDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	   
	NMLISTVIEW *pNMListView = (NMLISTVIEW*)pNMHDR;   

	if (-1 != pNMListView->iItem)        // ���iItem����-1����˵�����б��ѡ��   
	{   
		// ��ȡ��ѡ���б����һ��������ı�   
		adpname = m_list1.GetItemText(pNMListView->iItem, 0);   
		// ��ѡ���������ʾ��༭����   
		SetDlgItemText(IDC_EDIT1, adpname);   
	}   
}

//������ѡ���豸
pcap_if_t* CAdpDlg::GetDevice()
{
	if(adpname)
	{
		for(d=alldevs; d; d=d->next)
			if(d->name == adpname)
				return d;
	}
	return NULL;
}


void CAdpDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	d = GetDevice();
	if(d)
	{
		MessageBox(_T("�����󶨳ɹ�!"));
		CDialogEx::OnOK();
	}
	else
		MessageBox(_T("��ѡ��Ҫ�󶨵�����"));
}

pcap_if_t* CAdpDlg::returnd()
{
	return d;
}