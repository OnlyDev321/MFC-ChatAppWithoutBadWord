
// ExamClient.cpp: 응용 프로그램에 대한 클래스 동작을 정의합니다.
//

#include "stdafx.h"
#include "ExamClient.h"
#include "ExamClientDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CExamClientApp

BEGIN_MESSAGE_MAP(CExamClientApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CExamClientApp 생성

CExamClientApp::CExamClientApp()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CExamClientApp 개체입니다.

CExamClientApp theApp;

// CExamClientApp 초기화

BOOL CExamClientApp::InitInstance()
{
	CWinApp::InitInstance();
	
	CExamClientDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	return FALSE;

}

