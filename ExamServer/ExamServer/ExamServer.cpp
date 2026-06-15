
// ExamServer.cpp: 응용 프로그램에 대한 클래스 동작을 정의합니다.
//

#include "stdafx.h"
#include "ExamServer.h"
#include "ExamServerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CExamServerApp

BEGIN_MESSAGE_MAP(CExamServerApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CExamServerApp 생성

CExamServerApp::CExamServerApp()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CExamServerApp 개체입니다.

CExamServerApp theApp;


// CExamServerApp 초기화

BOOL CExamServerApp::InitInstance()
{
	CWinApp::InitInstance();
	
	CExamServerDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	return FALSE;
}

