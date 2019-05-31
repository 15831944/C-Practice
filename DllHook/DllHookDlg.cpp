
// DllHookDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DllHook.h"
#include "DllHookDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//#pragma comment (lib,"HandDLL.lib")
//extern "C" _declspec(dllimport) void  SetHook(HWND hwnd);
// CDllHookDlg �Ի���



CDllHookDlg::CDllHookDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLLHOOK_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDllHookDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDllHookDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CDllHookDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CDllHookDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDllHookDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CDllHookDlg ��Ϣ�������
HHOOK g_keyHook;
HWND g_hwnd;
BOOL CDllHookDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	g_keyHook = NULL;
	g_hwnd = m_hWnd;
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CDllHookDlg::OnPaint()
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
HCURSOR CDllHookDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDllHookDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}
LRESULT CALLBACK MouseProc(
	_In_ int    nCode,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
) {
	return 1;
}


LRESULT CALLBACK KeyboardProc(
	_In_ int    code,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
) {
	//if (VK_SPACE == wParam ) {
	//	return CallNextHookEx(g_keyHook, code, wParam, lParam); 
	//}
	//return 1;
	if (VK_F1 == wParam && (lParam >> 29 & 1)) {
		::SendMessage(g_hwnd, WM_CLOSE, 0, 0);
		UnhookWindowsHookEx(g_keyHook);
	}
	else
	{
		return 1;
	}
}

void CDllHookDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	/*SetWindowsHookEx(WH_MOUSE, MouseProc, NULL, GetCurrentThreadId());*/

	typedef void(*hook)(HWND m_hwnd);
	HINSTANCE hDll;
	hDll = LoadLibrary(L"HandDLL.dll");
	if (hDll == NULL) {
		DWORD dwErrorCode = ::GetLastError();
		TCHAR* buffer = NULL;
		::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwErrorCode, 0, (LPTSTR)&buffer, 0, NULL);
		MessageBox(buffer);
		return;
	}
	hook h;
	h = (hook)GetProcAddress(hDll, "SetHook");
	h(m_hWnd);
}


void CDllHookDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	g_keyHook =	SetWindowsHookEx(WH_KEYBOARD, KeyboardProc, NULL, GetCurrentThreadId());
}
