// ModifyRect.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CModifyRectApp:
// �йش����ʵ�֣������ ModifyRect.cpp
//

class CModifyRectApp : public CWinApp
{
public:
	CModifyRectApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CModifyRectApp theApp;