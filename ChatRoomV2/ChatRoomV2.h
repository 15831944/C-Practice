
// ChatRoomV2.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CChatRoomV2App: 
// �йش����ʵ�֣������ ChatRoomV2.cpp
//

class CChatRoomV2App : public CWinApp
{
public:
	CChatRoomV2App();
	~CChatRoomV2App();
// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CChatRoomV2App theApp;