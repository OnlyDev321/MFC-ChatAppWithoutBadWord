// ExamServerDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "ExamServer.h"
#include "ExamServerDlg.h"
#include "afxdialogex.h"
#include "afx.h"
#include "vector"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void MyServer::AddWorkForAccept(TW_UserData* ap_user)
{
	CString str;
	str.Format(L"%s에서 새로운 사용자가 접속했습니다!", ap_user->GetIP());
	mp_parent->AddEventString(str);
}

void MyServer::AddWorkForCloseUser(TW_UserData* ap_user, int a_error_code)
{
	CString str;
	str.Format(L"%s에서 사용자가 접속을 해제했습니다!", ap_user->GetIP());
	mp_parent->AddEventString(str);
}

int MyServer::ProcessRecvData(SOCKET ah_socket, unsigned char a_msg_id, char* ap_recv_data, BS a_body_size)
{
	TW_UserData* p_user = (TW_UserData*)FindUserData(ah_socket);

	if (a_msg_id == NM_CHAT_DATA) {
		CString str;
		str.Format(L"%s : %s", p_user->GetIP(), (wchar_t*)ap_recv_data);
		mp_parent->AddEventString(str);

		for (int i = 0; i < m_max_user_count; i++) {
			// 현재 사용자가 접속 상태인지 확인한다.
			if (mp_user_list[i]->GetHandle() != -1) { // 0xFFFFFFFF
				SendFrameData(mp_user_list[i]->GetHandle(), NM_CHAT_DATA, (const char*)(const wchar_t*)str, (str.GetLength() + 1) * 2);
			}
		}
	}

	return 1;
}

// CExamServerDlg 대화 상자

CExamServerDlg::CExamServerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EXAMSERVER_DIALOG, pParent), m_server(this)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExamServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EVENT_LIST, m_event_list);
}

BEGIN_MESSAGE_MAP(CExamServerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(25001, &CExamServerDlg::OnAcceptUser)
	ON_MESSAGE(25002, &CExamServerDlg::OnReadAndClose)
END_MESSAGE_MAP()

// CExamServerDlg 메시지 처리기

BOOL CExamServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	// 프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	m_server.StartServer(L"10.21.35.179", 27100, m_hWnd);
	AddEventString(L"서버 서비스를 시작합니다!");

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
// 아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
// 프레임워크에서 이 작업을 자동으로 수행합니다.

void CExamServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
// 이 함수를 호출합니다.
HCURSOR CExamServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CExamServerDlg::AddEventString(const wchar_t* ap_string)
{
	CString str = ap_string;

	int index = m_event_list.InsertString(-1, str);
	m_event_list.SetCurSel(index);
}

afx_msg LRESULT CExamServerDlg::OnAcceptUser(WPARAM wParam, LPARAM lParam)
{
	// 새로운 클라이언트가 접속했을 때 발생하는 메시지를 처리한다.
	m_server.ProcessToAccept(wParam, lParam);  // FD_ACCEPT

	return 0;
}

afx_msg LRESULT CExamServerDlg::OnReadAndClose(WPARAM wParam, LPARAM lParam)
{
	// 접속한 클라이언트가 데이터를 전송하거나 접속을 해제할 때 발생하는 메시지를 처리한다.
	m_server.ProcessClientEvent(wParam, lParam); // FD_READ, FD_CLOSE

	return 0;
}
