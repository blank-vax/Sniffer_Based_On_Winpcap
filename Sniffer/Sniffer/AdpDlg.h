#pragma once


// CAdpDlg �Ի���

class CAdpDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAdpDlg)

public:
	CAdpDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAdpDlg();

// �Ի�������
	enum { IDD = IDD_ADP_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list1;
	virtual BOOL OnInitDialog();
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	pcap_if_t* GetDevice(void);

private:
	pcap_if_t *alldevs; //�����豸ָ��
	CString adpname;    // ��ѡ�����������ַ���
	pcap_if_t *d;
public:
	afx_msg void OnBnClickedOk();
	pcap_if_t* returnd();
};
