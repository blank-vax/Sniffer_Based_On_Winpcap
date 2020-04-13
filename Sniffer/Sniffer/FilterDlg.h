#pragma once


// CFilterDlg �Ի���

class CFilterDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFilterDlg)

public:
	CFilterDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFilterDlg();

// �Ի�������
	enum { IDD = IDD_FILTER_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CButton m_tcp;
	CButton m_udp;
	CButton m_arp;
	CButton m_rarp;
	CButton m_icmp;
	virtual BOOL OnInitDialog();
	CString filtername;
	CButton m_igmp;
	CString GetFilterName(void);
};
