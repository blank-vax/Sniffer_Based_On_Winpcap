
// SnifferDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Sniffer.h"
#include "SnifferDlg.h"
#include "afxdialogex.h"


#include "AdpDlg.h"
#include "FilterDlg.h"
#include "head.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

DWORD WINAPI CapturePacket(LPVOID lpParam);

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
public:

};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_COMMAND(ID_HELP, &CAboutDlg::OnHelp)
END_MESSAGE_MAP()


// CSnifferDlg �Ի���




CSnifferDlg::CSnifferDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSnifferDlg::IDD, pParent)
	, m_pDevice(NULL)
	, m_bFlag(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_tcpnum = _T("");
	m_udpnum = _T("");
	m_arpnum = _T("");
	m_icmpnum = _T("");
	m_igmpnum = _T("");
	m_totalnum = _T("");
	m_httpnum = _T("");
	m_dnsnum = _T("");
}

void CSnifferDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list1);
	DDX_Control(pDX, IDC_TREE1, m_tree1);
	DDX_Control(pDX, IDC_EDIT1, m_edit1);
	DDX_Text(pDX, IDC_EDIT2, m_tcpnum);
	DDX_Text(pDX, IDC_EDIT3, m_udpnum);
	DDX_Text(pDX, IDC_EDIT4, m_arpnum);
	DDX_Text(pDX, IDC_EDIT5, m_icmpnum);
	DDX_Text(pDX, IDC_EDIT6, m_igmpnum);
	DDX_Text(pDX, IDC_EDIT7, m_totalnum);
	DDX_Text(pDX, IDC_EDIT8, m_httpnum);
	DDX_Text(pDX, IDC_EDIT9, m_dnsnum);
	//  DDX_Text(pDX, IDC_EDIT11, m_qqnum);
	//	DDX_Text(pDX, IDC_EDIT11, m_wangnum);
	//  DDX_Text(pDX, IDC_EDIT10, m_qqnum);
	//  DDX_Text(pDX, IDC_EDIT12, m_msnnum);
}

BEGIN_MESSAGE_MAP(CSnifferDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_ADP, &CSnifferDlg::OnAdp)
	ON_COMMAND(ID_HELP, &CSnifferDlg::OnHelp)
	ON_COMMAND(ID_FILTER, &CSnifferDlg::OnFilter)
	ON_COMMAND(ID_START, &CSnifferDlg::OnStart)
	ON_COMMAND(ID_STOP, &CSnifferDlg::OnStop)
//	ON_NOTIFY(HDN_ITEMCHANGED, 0, &CSnifferDlg::OnHdnItemchangedList1)
ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CSnifferDlg::OnLvnItemchangedList1)
ON_COMMAND(ID_EXIT, &CSnifferDlg::OnExit)
ON_EN_CHANGE(IDC_EDIT8, &CSnifferDlg::OnEnChangeEdit8)
END_MESSAGE_MAP()


// CSnifferDlg ��Ϣ�������

BOOL CSnifferDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	m_pDevice = NULL;
	m_bFlag = false;

	//�б���ͼ��ʼ��
	m_list1.SetExtendedStyle(m_list1.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);// Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����
	m_list1.InsertColumn(0,_T("���"),LVCFMT_CENTER,50);
	m_list1.InsertColumn(1,_T("ʱ��"),LVCFMT_CENTER,120);
	m_list1.InsertColumn(2,_T("ԴMAC��ַ"),LVCFMT_CENTER,120);
	m_list1.InsertColumn(3,_T("Ŀ��MAC��ַ"),LVCFMT_CENTER,120);
	m_list1.InsertColumn(4,_T("����"),LVCFMT_CENTER,50);
	m_list1.InsertColumn(5,_T("Э��"),LVCFMT_CENTER,70);
	m_list1.InsertColumn(6,_T("ԴIP��ַ"),LVCFMT_CENTER,120);
	m_list1.InsertColumn(7,_T("Ŀ��IP��ַ"),LVCFMT_CENTER,120);

	m_tcpCount = 0;
	m_udpCount = 0;
	m_arpCount = 0;
	m_icmpCount = 0;
	m_igmpCount = 0;
	m_totalCount = 0;
	m_httpCount = 0;
	m_dnsCount = 0;
	m_wangCount = 0;
	m_qqCount = 0;
	m_msnCount = 0;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CSnifferDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSnifferDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CSnifferDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//��ʾѡ���������Ի���
void CSnifferDlg::OnAdp()
{
	// TODO: �ڴ���������������
	CAdpDlg adpdlg;
	if(adpdlg.DoModal() == IDOK)
	{
		m_pDevice = adpdlg.returnd();
	}
}

//��ʾ���ڶԻ���
void CSnifferDlg::OnHelp()
{
	// TODO: �ڴ���������������
	CAboutDlg aboutdlg;
	aboutdlg.DoModal();
}


void CSnifferDlg::OnFilter()
{
	// TODO: �ڴ���������������
	CFilterDlg filterdlg;
	if(filterdlg.DoModal() == IDOK)
	{
		int len =WideCharToMultiByte(CP_ACP,0,filterdlg.GetFilterName(),-1,NULL,0,NULL,NULL); 
		WideCharToMultiByte(CP_ACP,0,filterdlg.GetFilterName(),-1,m_filtername,len,NULL,NULL );
		
	}
}

void CSnifferDlg::OnStart()
{
	// TODO: �ڴ���������������
	if(m_pDevice == NULL)
	{
		AfxMessageBox(_T("��ѡ��Ҫ�󶨵�����"));
		return ;
	}
	m_bFlag = true;
	CreateThread(NULL,NULL,CapturePacket,(LPVOID)this,true,NULL);
}

void CSnifferDlg::OnStop()
{
	// TODO: �ڴ���������������
	m_bFlag = false;
}

DWORD WINAPI CapturePacket(LPVOID lpParam)
{
	CSnifferDlg *pDlg = (CSnifferDlg *)lpParam;
	pcap_t *pCap;
	char	strErrorBuf[PCAP_ERRBUF_SIZE];
	int res;
	struct pcap_pkthdr *pkt_header;
	const u_char *pkt_data;
	u_int netmask;
	struct bpf_program fcode;

	if((pCap=pcap_open_live(pDlg->m_pDevice->name,65536,PCAP_OPENFLAG_PROMISCUOUS,1000,strErrorBuf))==NULL)
	{		
		return -1;
	}

	if(pDlg->m_pDevice->addresses != NULL)
		/* ��ýӿڵ�һ����ַ������ */
		netmask=((struct sockaddr_in *)(pDlg->m_pDevice->addresses->netmask))->sin_addr.S_un.S_addr;
	else
		/* ����ӿ�û�е�ַ����ô���Ǽ���һ��C������� */
		netmask=0xffffff; 
		//���������
		if (pcap_compile(pCap, &fcode,pDlg->m_filtername, 1, netmask) <0 )
		{
			AfxMessageBox(_T("�����ù��˹���"));
			return -1;
		}
		//���ù�����
		if (pcap_setfilter(pCap, &fcode)<0)
			return -1;
	Sleep(5000);
	if (res = pcap_next_ex(pCap, &pkt_header, &pkt_data) == 0) {
		AfxMessageBox(_T("δ������������������������������"));
	}
	while((res = pcap_next_ex( pCap, &pkt_header, &pkt_data)) >= 0)
	{

		if(res == 0)
			continue;
		if(!pDlg->m_bFlag)
			break;
		CSnifferDlg *pDlg = (CSnifferDlg *)AfxGetApp()->GetMainWnd(); 
		pDlg->ShowPacketList(pkt_header,pkt_data);
		pDlg = NULL;
	}
	pcap_close(pCap);
	pDlg = NULL;
	return 1;	 
}

void CSnifferDlg::ShowPacketList(const pcap_pkthdr *pkt_header, const u_char *pkt_data)
{
	//���ڴ��������е����ݣ������浽CArray��,�Ա�����ʹ��
	struct pcap_pkthdr *pHeader = new pcap_pkthdr;
	u_char *pData;
	unsigned char *pPosition = (unsigned char *)pkt_data;	

	long nIndex = 0;//��ʶ��ǰ�����ݰ�λ��
	long nCount = 0;//��ʶ����

	pHeader->caplen=pkt_header->caplen;
	pHeader->len=pkt_header->len;

	pData=new unsigned char[pHeader->len];
	memcpy((void *)pData,pkt_data,pHeader->len);

	m_pktHeaders.Add(pHeader);
	m_pktDatas.Add(pData);

	nIndex=m_pktHeaders.GetSize()-1;
	CString str;
	str.Format(_T("%d"),nIndex);
	nCount=m_list1.InsertItem(nIndex,str,0);
	m_totalCount++;//�����ݰ���1

	/*��ʾʱ��*/
	struct tm *ltime;   
	time_t local_tv_sec;
	local_tv_sec = pkt_header->ts.tv_sec;
	ltime=localtime(&local_tv_sec); 
	str.Format(_T("%d:%d:%d.%.6d"),ltime->tm_hour,ltime->tm_min,ltime->tm_sec,pkt_header->ts.tv_usec);
	m_list1.SetItemText(nCount,1,str);
	/*������·��*/
	ethernet_header *eh;
	eh = (ethernet_header *)pkt_data;
	str.Format(_T("%x:%x:%x:%x:%x:%x"),eh->saddr.byte1,eh->saddr.byte2,eh->saddr.byte3,eh->saddr.byte4,eh->saddr.byte5,eh->saddr.byte6);
	m_list1.SetItemText(nCount,2,str);
	str.Format(_T("%x:%x:%x:%x:%x:%x"),eh->daddr.byte1,eh->daddr.byte2,eh->daddr.byte3,eh->daddr.byte4,eh->daddr.byte5,eh->daddr.byte6);
	m_list1.SetItemText(nCount,3,str);
	str.Format(_T("%ld"),pHeader->len);
	m_list1.SetItemText(nCount,4,str);
	/*���������*/
	switch(ntohs(eh->type))
	{
	case IP:
		{
			ip_header *ih;
			const u_char *ip_data;
			ip_data=pkt_data+14;
			ih = (ip_header *)ip_data;
			u_int ip_len;//IP�ײ�����
			ip_len = (ih->ver_ihl & 0xf) * 4;
			str.Format(_T("%d.%d.%d.%d"),ih->saddr.byte1,ih->saddr.byte2,ih->saddr.byte3,ih->saddr.byte4);
			m_list1.SetItemText(nCount,6,str);
			str.Format(_T("%d.%d.%d.%d"),ih->saddr.byte1,ih->saddr.byte2,ih->saddr.byte3,ih->saddr.byte4);
			m_list1.SetItemText(nCount,7,str);
			/*�������*/
			switch(ih->type)
			{
			case TCP:
				{
					m_tcpCount++;
					tcp_header *th;
					const u_char *tcp_data;
					tcp_data = ip_data+ip_len;
					th = (tcp_header *)tcp_data;
					if(ntohs( th->sport ) == HTTP)
					{
						m_list1.SetItemText(nCount,5,_T("ԴHTTP"));
						m_httpCount++;
					}
					else if(ntohs( th->dport ) == HTTP)
					{
						m_list1.SetItemText(nCount,5,_T("Ŀ��HTTP"));
						m_httpCount++;
					}
					else if(ntohs( th->dport ) == DNS || ntohs( th->sport ) == DNS)
					{
						m_list1.SetItemText(nCount,5,_T("DNS"));
						m_dnsCount++;
					}
					else
						m_list1.SetItemText(nCount,5,_T("TCP"));
					break;	
				}
			case UDP:
				{
					m_udpCount++;
					udp_header *uh;
					const u_char *udp_data;
					udp_data = ip_data+ip_len;
					uh = (udp_header *)udp_data;
					if(ntohs( uh->dport ) == DNS || ntohs( uh->sport ) == DNS)
					{
						m_list1.SetItemText(nCount,5,_T("DNS"));
						m_dnsCount++;
					}
					else
						m_list1.SetItemText(nCount,5,_T("UDP"));
					break;
				}
			case ICMP:m_icmpCount++;m_list1.SetItemText(nCount,5,_T("ICMP"));break;
			case IGMP:m_igmpCount++;m_list1.SetItemText(nCount,5,_T("IGMP"));break;
			case EGP:m_list1.SetItemText(nCount,5,_T("EGP"));break;
			case IPv6:m_list1.SetItemText(nCount,5,_T("IPv6"));break;
			case OSPF:m_list1.SetItemText(nCount,5,_T("OSPF"));break;
			default:m_list1.SetItemText(nCount,5,_T("δ֪"));
			}
			break;
		}
	case ARP:
		{
			m_arpCount++;
			arp_header *ah;
			const u_char *arp_data;
			arp_data=pkt_data+14;
			ah = (arp_header *)arp_data;
			str.Format(_T("%d.%d.%d.%d"),ah->arp_sip.byte1,ah->arp_sip.byte2,ah->arp_sip.byte3,ah->arp_sip.byte4);
			m_list1.SetItemText(nCount,6,str);
			str.Format(_T("%d.%d.%d.%d"),ah->arp_dip.byte1,ah->arp_dip.byte2,ah->arp_dip.byte3,ah->arp_dip.byte4);
			m_list1.SetItemText(nCount,7,str);
			m_list1.SetItemText(nCount,5,_T("ARP"));
			break;
		}
	case RARP:
		m_list1.SetItemText(nCount,5,_T("RARP"));
		break;
	default:
		m_list1.SetItemText(nCount,5,_T("δ֪Э��"));
	}
	ShowPckNum();
}

// ���ݰ�ϸ�������νṹ����չʾ
void CSnifferDlg::ShowPacketTree(const pcap_pkthdr *pkt_header, const u_char *pkt_data,long index)
{
	m_tree1.DeleteAllItems();
	CString str;
	str.Format(_T("���ݰ�:%ld"),index);
	HTREEITEM hRoot;
	HTREEITEM hSubItem;
	HTREEITEM hItem;
	HTREEITEM hItem2;

	hRoot = m_tree1.InsertItem(str);
	hSubItem = m_tree1.InsertItem(_T("������·��"),hRoot);
	ethernet_header *eh;
	eh = (ethernet_header *)pkt_data;
	str.Format(_T("ԴMAC:%x:%x:%x:%x:%x:%x"),eh->saddr.byte1,eh->saddr.byte2,eh->saddr.byte3,eh->saddr.byte4,eh->saddr.byte5,eh->saddr.byte6);
	hItem = m_tree1.InsertItem(str,hSubItem);
	str.Format(_T("Ŀ��MAC:%x:%x:%x:%x:%x:%x"),eh->daddr.byte1,eh->daddr.byte2,eh->daddr.byte3,eh->daddr.byte4,eh->daddr.byte5,eh->daddr.byte6);
	hItem = m_tree1.InsertItem(str,hSubItem);
	switch(ntohs(eh->type))
	{
	case IP:
		{
			hItem = m_tree1.InsertItem(_T("�ϲ�Э��:IP"),hSubItem);
			hSubItem = m_tree1.InsertItem(_T("�����"),hRoot);
			ip_header *ih;
			const u_char *ip_data;
			ip_data=pkt_data+14;
			ih = (ip_header *)ip_data;
			str.Format(_T("�汾��%d"),(ih->ver_ihl & 0xf0) / 0x10);
			hItem = m_tree1.InsertItem(str,hSubItem);
			u_int ip_len;//IP�ײ�����
			ip_len = (ih->ver_ihl & 0xf) * 4;
			str.Format(_T("�ײ����ȣ�%d"),ip_len);
			hItem = m_tree1.InsertItem(str,hSubItem);
			str.Format(_T("�������ͣ�0x%x"),ih->tos);
			hItem = m_tree1.InsertItem(str,hSubItem);
			str.Format(_T("�ܳ��ȣ�%d"),ntohs( ih->tlen ));
			hItem = m_tree1.InsertItem(str,hSubItem);
			str.Format(_T("��ʶ��0x%x"),ntohs( ih->identification ));
			hItem = m_tree1.InsertItem(str,hSubItem);
			str.Format(_T("��־��0x%x"),ntohs( ih->flags_fo ) & 0xe000 / 0x2000);
			hItem = m_tree1.InsertItem(str,hSubItem);
			str.Format(_T("Ƭƫ�ƣ�%d"),ntohs( ih->flags_fo ) & 0x1fff);
			hItem = m_tree1.InsertItem(str,hSubItem);
			str.Format(_T("����ʱ�䣺%d"),ih->ttl);
			hItem = m_tree1.InsertItem(str,hSubItem);
			str.Format(_T("�ײ�У��ͣ�0x%x"),ntohs( ih->crc ));
			hItem = m_tree1.InsertItem(str,hSubItem);
			str.Format(_T("ԴIP��ַ��%d.%d.%d.%d"),ih->saddr.byte1,ih->saddr.byte2,ih->saddr.byte3,ih->saddr.byte4);
			hItem = m_tree1.InsertItem(str,hSubItem);
			str.Format(_T("Ŀ��IP��ַ��%d.%d.%d.%d"),ih->saddr.byte1,ih->saddr.byte2,ih->saddr.byte3,ih->saddr.byte4);
			hItem = m_tree1.InsertItem(str,hSubItem);
			switch(ih->type)
			{
			case TCP:
				{
					hItem = m_tree1.InsertItem(_T("�ϲ�Э��:TCP"),hSubItem);
					hSubItem = m_tree1.InsertItem(_T("�����"),hRoot);
					tcp_header *th;
					const u_char *tcp_data;
					tcp_data = ip_data+ip_len;
					th = (tcp_header *)tcp_data;
					str.Format(_T("Դ�˿ںţ�%d"),ntohs( th->sport ));
					hItem = m_tree1.InsertItem(str,hSubItem);
					str.Format(_T("Ŀ�Ŀںţ�%d"),ntohs( th->dport ));
					hItem = m_tree1.InsertItem(str,hSubItem);
					str.Format(_T("˳��ţ�%d"),ntohs( th->seq ));
					hItem = m_tree1.InsertItem(str,hSubItem);
					str.Format(_T("ȷ�Ϻţ�%d"),ntohs( th->ack ));
					hItem = m_tree1.InsertItem(str,hSubItem);
					str.Format(_T("TCPͷ����%d"),(th->len & 0xf0) / 0x10 * 4);
					hItem = m_tree1.InsertItem(str,hSubItem);
					hItem = m_tree1.InsertItem(_T("����λ"),hSubItem);
					str.Format(_T("����URG:%d"),(th->flags & 0x20) / 0x20 );
					hItem2 = m_tree1.InsertItem(str,hItem);
					str.Format(_T("ȷ��ACK:%d"),(th->flags & 0x10) / 0x10);
					hItem2 = m_tree1.InsertItem(str,hItem);
					str.Format(_T("����PSH:%d"),(th->flags & 0x08) / 0x08);
					hItem2 = m_tree1.InsertItem(str,hItem);
					str.Format(_T("��λRSTG:%d"),(th->flags & 0x04) / 0x04);
					hItem2 = m_tree1.InsertItem(str,hItem);
					str.Format(_T("ͬ��SYN:%d"),(th->flags & 0x02) / 0x02);
					hItem2 = m_tree1.InsertItem(str,hItem);
					str.Format(_T("����FIN:%d"),(th->flags & 0x01) / 0x01);
					hItem2 = m_tree1.InsertItem(str,hItem);
					str.Format(_T("���ڣ�%d"),ntohs( th->win ));
					hItem = m_tree1.InsertItem(str,hSubItem);
					str.Format(_T("У��ͣ�0x%x"),ntohs( th->crc ));
					hItem = m_tree1.InsertItem(str,hSubItem);
					str.Format(_T("����ָ�룺0x%x"),ntohs( th->urp ));
					hItem = m_tree1.InsertItem(str,hSubItem);
					break;
				}
			case UDP:
				{
					hItem = m_tree1.InsertItem(_T("�ϲ�Э��:UDP"),hSubItem);
					hSubItem = m_tree1.InsertItem(_T("�����"),hRoot);
					udp_header *uh;
					const u_char *udp_data;
					udp_data = ip_data+ip_len;
					uh = (udp_header *)udp_data;
					str.Format(_T("Դ�˿ںţ�%d"),ntohs( uh->sport ));
					hItem = m_tree1.InsertItem(str,hSubItem);
					str.Format(_T("Ŀ�Ŀںţ�%d"),ntohs( uh->dport ));
					hItem = m_tree1.InsertItem(str,hSubItem);
					str.Format(_T("���ȣ�%d"),ntohs( uh->len ));
					hItem = m_tree1.InsertItem(str,hSubItem);
					str.Format(_T("У��ͣ�0x%x"),ntohs( uh->crc ));
					hItem = m_tree1.InsertItem(str,hSubItem);
					if(ntohs( uh->dport ) == DNS || ntohs( uh->sport ) == DNS)
					{
						hSubItem = m_tree1.InsertItem(_T("Ӧ�ò�"),hRoot);
						dns_header *dh;
						const u_char *dns_data;
						dns_data = udp_data+8;
						dh = (dns_header *)dns_data;
						str.Format(_T("��ʶ��0x%x"),ntohs( dh->identification ));
						hItem = m_tree1.InsertItem(str,hSubItem);
						str.Format(_T("��־��0x%x"),ntohs( dh->flags ));
						hItem = m_tree1.InsertItem(str,hSubItem);
						str.Format(_T("��������%d"),ntohs( dh->questions_num ));
						hItem = m_tree1.InsertItem(str,hSubItem);
						str.Format(_T("��Դ��¼����%d"),ntohs( dh->answers_num ));
						hItem = m_tree1.InsertItem(str,hSubItem);
						str.Format(_T("��Ȩ��Դ��¼����%d"),ntohs( dh->authority_num ));
						hItem = m_tree1.InsertItem(str,hSubItem);
						str.Format(_T("������Դ��¼����%d"),ntohs( dh->addition_num ));
						hItem = m_tree1.InsertItem(str,hSubItem);
					}
					break;
				}
			case ICMP:
				{
					hItem = m_tree1.InsertItem(_T("�ϲ�Э��:ICMP"),hSubItem);
					hSubItem = m_tree1.InsertItem(_T("�����"),hRoot);
					icmp_header *icmph;
					const u_char *icmp_data;
					icmp_data = ip_data+ip_len;
					icmph = (icmp_header *)icmp_data;
					str.Format(_T("���ͣ�%d"),icmph->type);
					hItem = m_tree1.InsertItem(str,hSubItem);
					str.Format(_T("���룺%d"),icmph->code);
					hItem = m_tree1.InsertItem(str,hSubItem);
					str.Format(_T("У��ͣ�0x%x"),ntohs( icmph->checksum ));
					hItem = m_tree1.InsertItem(str,hSubItem);
					break;
				}
			case IGMP:hItem = m_tree1.InsertItem(_T("�ϲ�Э��:IGMP"),hSubItem);break;
			case EGP:hItem = m_tree1.InsertItem(_T("�ϲ�Э��:EGP"),hSubItem);break;
			case IPv6:hItem = m_tree1.InsertItem(_T("�ϲ�Э��:IPv6"),hSubItem);break;
			case OSPF:hItem = m_tree1.InsertItem(_T("�ϲ�Э��:OSPF"),hSubItem);break;
			default:hItem = m_tree1.InsertItem(_T("�ϲ�Э��:δ֪"),hSubItem);
			}
			break;
		}
	case ARP:
		{
			hItem = m_tree1.InsertItem(_T("�ϲ�Э��:ARP"),hSubItem);
			hSubItem = m_tree1.InsertItem(_T("�����"),hRoot);
			arp_header *ah;
			const u_char *arp_data;
			arp_data=pkt_data+14;
			ah = (arp_header *)arp_data;
			str.Format(_T("Ӳ�����ͣ�%d"),ntohs( ah->arp_hdr ));
			hItem = m_tree1.InsertItem(str,hSubItem);
			str.Format(_T("Э�����ͣ�0x%x"),ntohs( ah->arp_pro ));
			hItem = m_tree1.InsertItem(str,hSubItem);
			str.Format(_T("Ӳ�����ȣ�%d"),ah->arp_hln);
			hItem = m_tree1.InsertItem(str,hSubItem);
			str.Format(_T("Э�鳤�ȣ�%d"),ah->apr_pln );
			hItem = m_tree1.InsertItem(str,hSubItem);
			str.Format(_T("�������ͣ�%d"),ntohs( ah->arp_opt ));
			hItem = m_tree1.InsertItem(str,hSubItem);
			str.Format(_T("���Ͷ�MAC��ַ��%x:%x:%x:%x:%x:%x"),ah->arp_smac.byte1,ah->arp_smac.byte2,ah->arp_smac.byte3,ah->arp_smac.byte4,ah->arp_smac.byte5,ah->arp_smac.byte6);
			hItem = m_tree1.InsertItem(str,hSubItem);
			str.Format(_T("���Ͷ�Э���ַ��%d.%d.%d.%d"),ah->arp_sip.byte1,ah->arp_sip.byte2,ah->arp_sip.byte3,ah->arp_sip.byte4);
			hItem = m_tree1.InsertItem(str,hSubItem);
			str.Format(_T("���ն�MAC��ַ��%x:%x:%x:%x:%x:%x"),ah->arp_dmac.byte1,ah->arp_dmac.byte2,ah->arp_dmac.byte3,ah->arp_dmac.byte4,ah->arp_dmac.byte5,ah->arp_dmac.byte6);
			hItem = m_tree1.InsertItem(str,hSubItem);
			str.Format(_T("���ն�Э���ַ��%d.%d.%d.%d"),ah->arp_dip.byte1,ah->arp_dip.byte2,ah->arp_dip.byte3,ah->arp_dip.byte4);
			hItem = m_tree1.InsertItem(str,hSubItem);
			break;
		}
	case RARP:
		{
			hItem = m_tree1.InsertItem(_T("�ϲ�Э��:RARP"),hSubItem);
			break;
		}
	default:
		hItem = m_tree1.InsertItem(_T("�ϲ�Э��:δ֪"),hSubItem);
	}

	m_tree1.Expand(hRoot,TVE_EXPAND);		//Ĭ��չ��Ŀ¼
	m_tree1.Expand(hSubItem,TVE_EXPAND);

	CString strHex;
	int nCount = 0;
	CString strText;
	for (unsigned short i = 0; i < pkt_header->caplen ; i++)
	{
		CString hex;
		if ( (i % 16) == 0) 
		{
			hex.Format(_T("\x0d\x0a 0X%04x   "),nCount);
			nCount++;
			if( i != 0)
			{
				strHex +=_T("  ")+strText ;
				strText = _T("");
			}
			strHex += hex;
		}
		hex.Format(_T("%2.2x "),pkt_data[i-1]);
		strHex += hex; 
		if(pkt_data[i-1] <= 127 && pkt_data[i-1] >= 0)
			hex.Format(_T("%c"),pkt_data[i-1]);
		else
			hex = _T(".");
		strText += hex;		           
	}
	if( strText !=_T(""))
		strHex += strText;
	m_edit1.SetWindowText(strHex);	
}

void CSnifferDlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	POSITION pos=m_list1.GetFirstSelectedItemPosition();
	if(pos==NULL) 
		return;

	long index=m_list1.GetNextSelectedItem(pos);
	if(index < 0)
		return ;

	ShowPacketTree(m_pktHeaders.GetAt(index),m_pktDatas.GetAt(index),index);
}

void CSnifferDlg::ShowPckNum()
{
	m_tcpnum.Format(_T("%ld"),m_tcpCount);
	this->SetDlgItemText(IDC_EDIT2,m_tcpnum);
	m_udpnum.Format(_T("%ld"),m_udpCount);
	this->SetDlgItemText(IDC_EDIT3,m_udpnum);
	m_arpnum.Format(_T("%ld"),m_arpCount);
	this->SetDlgItemText(IDC_EDIT4,m_arpnum);
	m_icmpnum.Format(_T("%ld"),m_icmpCount);
	this->SetDlgItemText(IDC_EDIT5,m_icmpnum);
	m_igmpnum.Format(_T("%ld"),m_igmpCount);
	this->SetDlgItemText(IDC_EDIT6,m_igmpnum);
	m_totalnum.Format(_T("%ld"),m_totalCount);
	this->SetDlgItemText(IDC_EDIT7,m_totalnum);
	m_httpnum.Format(_T("%ld"),m_httpCount);
	this->SetDlgItemText(IDC_EDIT8,m_httpnum);
	m_dnsnum.Format(_T("%ld"),m_dnsCount);
	this->SetDlgItemText(IDC_EDIT9,m_dnsnum);
}

void CSnifferDlg::OnExit()
{
	// TODO: �ڴ���������������
	CDialogEx::OnCancel();
}



void CSnifferDlg::OnEnChangeEdit8()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
