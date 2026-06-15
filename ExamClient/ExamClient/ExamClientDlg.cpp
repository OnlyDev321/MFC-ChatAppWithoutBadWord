// ExamClientDlg.cpp: 구현 파일
#include "stdafx.h"
#include "ExamClient.h"
#include "ExamClientDlg.h"
#include "afxdialogex.h"
#include "afx.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int MyClient::ProcessRecvData(SOCKET ah_socket, unsigned char a_msg_id, char* ap_recv_data, BS a_body_size)
{
    if (a_msg_id == NM_CHAT_DATA) {
        mp_parent->AddEventString((wchar_t*)ap_recv_data);
    }

    return 1;
}

// CExamClientDlg 대화 상자
CExamClientDlg::CExamClientDlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_EXAMCLIENT_DIALOG, pParent), m_client(this)
    , m_strEdit(_T(""))
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExamClientDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EVENT_LIST, m_event_list);
    DDX_Control(pDX, IDC_LIST_OUT, m_listBox);
    DDX_Text(pDX, IDC_EDIT_STRING, m_strEdit);
    DDX_Control(pDX, IDC_COMBO_AUTO, m_cbListItem);
}

BEGIN_MESSAGE_MAP(CExamClientDlg, CDialogEx)
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_SEND_BTN, &CExamClientDlg::OnBnClickedSendBtn)
    ON_MESSAGE(26001, &CExamClientDlg::OnConnected)
    ON_MESSAGE(26002, &CExamClientDlg::OnReadAndClose)
    ON_BN_CLICKED(IDC_BUTTON_ADD, &CExamClientDlg::OnClickedButtonAdd)
    ON_BN_CLICKED(IDC_BUTTON_DELETE, &CExamClientDlg::OnClickedButtonDelete)
    ON_EN_CHANGE(IDC_EDIT_STRING, &CExamClientDlg::OnEnChangeEditString)
END_MESSAGE_MAP()

// CExamClientDlg 메시지 처리기

BOOL CExamClientDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    SetIcon(m_hIcon, TRUE);         // 큰 아이콘 설정
    SetIcon(m_hIcon, FALSE);        // 작은 아이콘 설정

    m_client.ConnectToServer(L"10.21.35.179", 27100, m_hWnd);

    return TRUE;
}

void CExamClientDlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this);

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialogEx::OnPaint();
    }
}

HCURSOR CExamClientDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}

void CExamClientDlg::OnBnClickedSendBtn()
{
    CString str;
    GetDlgItemText(IDC_CHAT_EDIT, str);
    SetDlgItemText(IDC_CHAT_EDIT, L"");

    if (m_client.IsConnected()) {
        m_client.SendFrameData(NM_CHAT_DATA, (char*)(const wchar_t*)str, (str.GetLength() + 1) * 2);
    }
}

void CExamClientDlg::AddEventString(const wchar_t* ap_string)
{
    CString str = ap_string;

    int nCount = m_listBox.GetCount();
    for (int i = 0; i < nCount; ++i)
    {
        CString badWord;
        m_listBox.GetText(i, badWord);

        CString replacement;
        replacement.Format(L"%s", CString('*', badWord.GetLength()));
        str.Replace(badWord, replacement);
    }

    int index = m_event_list.InsertString(-1, str);
    m_event_list.SetCurSel(index);
}

afx_msg LRESULT CExamClientDlg::OnConnected(WPARAM wParam, LPARAM lParam)
{
    if (m_client.ResultOfConnection(lParam) == 1) {
        AddEventString(L"서버에 접속했습니다!");
    }
    else {
        AddEventString(L"서버에 접속할 수 없습니다!");
    }

    return 0;
}

afx_msg LRESULT CExamClientDlg::OnReadAndClose(WPARAM wParam, LPARAM lParam)
{
    m_client.ProcessServerEvent(wParam, lParam); // FD_READ, FD_CLOSE    

    return 0;
}

void CExamClientDlg::OnClickedButtonAdd()
{
    UpdateData(TRUE);
    if (!m_strEdit.IsEmpty())
    {
        m_listBox.AddString(m_strEdit);
        m_strEdit.Empty();
    }
    else
    {
        AfxMessageBox(_T("문자열이 없습니다."));
    }
    UpdateData(FALSE);
    UpdateComboBox();
}

void CExamClientDlg::UpdateComboBox()
{
    int nCount = m_listBox.GetCount();
    m_cbListItem.ResetContent();

    for (int i = 0; i < nCount; i++)
    {
        CString strItem;
        m_listBox.GetText(i, strItem);
        CString formattedItem;
        formattedItem.Format(_T("리스트 항목 : %s"), strItem);
        m_cbListItem.AddString(formattedItem);
    }
}


void CExamClientDlg::OnClickedButtonDelete()
{
    int index = m_cbListItem.GetCurSel();
    if (index != CB_ERR)
    {
        m_listBox.DeleteString(index);
        UpdateComboBox();
    }
    else
    {
        AfxMessageBox(_T("삭제할 항목을 선택하세요."));
    }
}


void CExamClientDlg::OnEnChangeEditString()
{
    // TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
    // CDialogEx::OnInitDialog() 함수를 재지정 
    //하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
    // 이 알림 메시지를 보내지 않습니다.

    // TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
