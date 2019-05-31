
// ChatRoomV2Dlg.h : ͷ�ļ�
//

#pragma once


// CChatRoomV2Dlg �Ի���
class CChatRoomV2Dlg : public CDialogEx
{
// ����
public:
	CChatRoomV2Dlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CChatRoomV2Dlg();
// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHATROOMV2_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg LRESULT OnSockMessage(WPARAM wParam,LPARAM lParam);
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	SOCKET m_socket;

	BOOL InitSocket();
	afx_msg void OnBnClickedButtonSend();
};
