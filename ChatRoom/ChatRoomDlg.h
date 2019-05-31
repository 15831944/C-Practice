
// ChatRoomDlg.h : ͷ�ļ�
//

#pragma once


// CChatRoomDlg �Ի���
class CChatRoomDlg : public CDialogEx
{
// ����
public:
	CChatRoomDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHATROOM_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	BOOL InitSocket();
	static char* GetTimeNow();
	static	DWORD WINAPI RcvProc(
		_In_ LPVOID lpParameter
	);

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnRcvData(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	SOCKET m_socket;
};
