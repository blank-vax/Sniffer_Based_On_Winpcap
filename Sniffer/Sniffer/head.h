#ifndef _HEAD_H
#define _HEAD_H

/* �����Э������ */
#define IP       0x0800          
#define ARP      0x0806          
#define RARP     0x8035 

/* ��������� */
#define ICMP       0x01
#define IGMP       0x02 
#define TCP        0x06
#define EGP        0x08   
#define UDP        0x11 
#define IPv6       0x29
#define OSPF       0x59

/* Ӧ�ò����� */
#define HTTP       0x50
#define DNS        0x35 

/* 6�ֽڵ�MAC��ַ */
typedef struct ethernet_address
{
	u_char byte1;
	u_char byte2;
	u_char byte3;
	u_char byte4;
	u_char byte5;
	u_char byte6;
}ethernet_address;

/* ��̫��֡�ײ� */
typedef struct ethernet_header
{
	ethernet_address daddr;		// Ŀ��MAC��ַ
	ethernet_address saddr;		// ԴMAC��ַ
	u_short type;				// Э������
}ethernet_header;



/* 4�ֽڵ�IP��ַ */
typedef struct ip_address
{
	u_char byte1;
	u_char byte2;
	u_char byte3;
	u_char byte4;
}ip_address;

/* IPv4 �ײ� */
typedef struct ip_header
{
	u_char  ver_ihl;        // �汾 (4 bits) + �ײ����� (4 bits)
	u_char  tos;            // ��������(Type of service) 
	u_short tlen;           // �ܳ�(Total length) 
	u_short identification; // ��ʶ(Identification)
	u_short flags_fo;       // ��־λ(Flags) (3 bits) + ��ƫ����(Fragment offset) (13 bits)
	u_char  ttl;            // ����ʱ��(Time to live)
	u_char  type;           // Э��(Protocol)
	u_short crc;            // �ײ�У���(Header checksum)
	ip_address  saddr;      // Դ��ַ(Source address)
	ip_address  daddr;      // Ŀ�ĵ�ַ(Destination address)
	u_int   op_pad;         // ѡ�������(Option + Padding)
}ip_header;

/* ARP �ײ� */
typedef struct arp_header
{

	u_short arp_hdr;				//Ӳ�����ͣ�ָ���˷��ͷ���֪����Ӳ���ӿ����ͣ���̫����ֵΪ1
	u_short arp_pro;				//Э�����ͣ�ָ���˷��ͷ��ṩ�ĸ߲�Э�����ͣ�IPΪ0800��16���ƣ�
	u_char arp_hln;					//Ӳ�����ȣ�8λ�ֶΣ������Ӧ�����ַ���ȣ���̫�������ֵΪ6
	u_char apr_pln;					//Э�鳤�ȣ�8λ�ֶΣ��������ֽ�Ϊ��λ���߼���ַ���ȣ���IPV4Э�����ֵΪ4
	u_short arp_opt;				//�������ͣ�������ʾ������ĵ����ͣ�ARP����Ϊ1��ARP��ӦΪ2��RARP����Ϊ3��RARP��ӦΪ4
	ethernet_address arp_smac;		//���Ͷ�Ӳ����ַ���ɱ䳤���ֶΣ�����̫������ֶ���6�ֽڳ�
	ip_address arp_sip;				//���Ͷ�Э���ַ���ɱ䳤���ֶΣ���IPЭ�飬����ֶ���4�ֽڳ�
	ethernet_address arp_dmac;		//���ܶ�Ӳ����ַ
	ip_address arp_dip;				//���ն�Э���ַ
}arp_header;

/* TCP �ײ�*/
typedef struct tcp_header
{
	u_short sport;          // Դ�˿�(Source port)
	u_short dport;          // Ŀ�Ķ˿�(Destination port)
	u_int seq;              // ˳���
	u_int ack;              // ȷ�Ϻ�
	u_char len;				// TCPͷ�����ȣ�����ƫ�Ƶ�λ��4�ֽڣ�����ֻ��ǰ4λ
	u_char flags;			// ��6λ�ֱ�Ϊ��URG��ACK��PSH��RST��SYN��FIN
	u_short win;			// ���ڴ�С
	u_short crc;			// У���
	u_short urp;			// ����ָ��
}tcp_header;

/* UDP �ײ�*/
typedef struct udp_header
{
	u_short sport;          // Դ�˿�(Source port)
	u_short dport;          // Ŀ�Ķ˿�(Destination port)
	u_short len;            // UDP��ͷ��UDP���ݵĳ���
	u_short crc;            // У���(Checksum)
}udp_header;

/* ICMP �ײ�*/
typedef struct icmp_header
{
	u_char type;			//����
	u_char code;			//����
	u_short checksum;		//У���
}icmp_header;

/* DNS �ײ�*/
typedef struct dns_header
{
	u_short identification;     // ��ʶ
	u_short flags;				// ��־
	u_short questions_num;      // ������
	u_short answers_num;        // ��Դ��¼��
	u_short authority_num;      //��Ȩ��Դ��¼��
	u_short addition_num;		//������Դ��¼��
}dns_header;

#endif