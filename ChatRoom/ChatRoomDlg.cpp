
// ChatRoomDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ChatRoom.h"
#include "ChatRoomDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define DEFAULT_PORT 6000
#define WM_RCVDATA WM_USER+1
// CChatRoomDlg �Ի���

struct ThreadParam
{
	SOCKET sock;
	HWND hwd;
};


CChatRoomDlg::CChatRoomDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CHATROOM_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChatRoomDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CChatRoomDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CChatRoomDlg::OnBnClickedButton1)
	ON_MESSAGE(WM_RCVDATA,OnRcvData)
END_MESSAGE_MAP()


// CChatRoomDlg ��Ϣ�������

BOOL CChatRoomDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	InitSocket();

	ThreadParam *pRcvParam = new ThreadParam;
	pRcvParam->sock = m_socket;
	pRcvParam->hwd = m_hWnd;

	HANDLE h_Thread = CreateThread(NULL, 0, RcvProc, (LPVOID)pRcvParam,0, NULL);
	CloseHandle(h_Thread);
	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CChatRoomDlg::OnPaint()
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
HCURSOR CChatRoomDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CChatRoomDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	DWORD dwIp;
	((CIPAddressCtrl*)GetDlgItem(IDC_IP_Addr))->GetAddress(dwIp);
	SOCKADDR_IN add_send;
	add_send.sin_addr.S_un.S_addr = htonl(dwIp);
	add_send.sin_family = AF_INET;
	add_send.sin_port = htons(DEFAULT_PORT);

	CString strSend;
	GetDlgItemText(IDC_EDIT_Send, strSend);
	/*USES_CONVERSION;*/
	if (SOCKET_ERROR == sendto(m_socket ,strSend, strSend.GetLength() + 1, 0, (SOCKADDR*)&add_send, sizeof(SOCKADDR))) {
		MessageBox("����ʧ�ܣ�");
		return;
	}
	SetDlgItemText(IDC_EDIT_Send, "");
}


BOOL CChatRoomDlg::InitSocket() {
	m_socket = socket(AF_INET, SOCK_DGRAM, 0);
	if (INVALID_SOCKET == m_socket) 
	{
		MessageBox("�׽��ִ���ʧ�ܣ�");
		return FALSE; 
	}

	SOCKADDR_IN sock_addr;
	sock_addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	sock_addr.sin_family = AF_INET;
	sock_addr.sin_port = htons(DEFAULT_PORT);

	if (SOCKET_ERROR == bind(m_socket, (SOCKADDR*)&sock_addr, sizeof(SOCKADDR))) { 
		closesocket(m_socket);
		MessageBox("��ʧ�ܣ�");
		return FALSE; 
	}
}


char* CChatRoomDlg::GetTimeNow() {
	static char time_buff[20];
	time_t _time;
	time(&_time);
	strftime(time_buff, 20, "%Y-%m-%d %H:%M:%S", localtime(&_time));
	return time_buff;
}

DWORD CChatRoomDlg::RcvProc(LPVOID lpParameter)
{
	SOCKET sock = ((ThreadParam*)lpParameter)->sock;
	HWND wnd = ((ThreadParam*)lpParameter)->hwd;

	SOCKADDR_IN add_from;
	int len = sizeof(add_from);

	
	char rcv_buff[1024];
	char temp_buff[1024];
	
	while (TRUE)
	{
		if (SOCKET_ERROR == recvfrom(sock,rcv_buff, 1024, 0, (SOCKADDR*)&add_from, &len)) break;
		/*CString send_temp;
		send_temp.Format("%s_%s:%s",GetTimeNow(), inet_ntoa(add_from.sin_addr), rcv_buff);*/
		sprintf(temp_buff, "%s %s: %s", GetTimeNow(), inet_ntoa(add_from.sin_addr), rcv_buff);
		::PostMessage(wnd, WM_RCVDATA, 0, (LPARAM)temp_buff);
	}
	return 0;
}

LRESULT CChatRoomDlg::OnRcvData(WPARAM wParam, LPARAM lParam)
{
	/*CString* str_temp = (CString*)lParam;*/
	CString str((char*)lParam);
	CString strTemp;
	GetDlgItemText(IDC_EDIT_Rcv, strTemp);
	str += "\r\n";
	str += strTemp;
	SetDlgItemText(IDC_EDIT_Rcv, str);
	return 0;
}

