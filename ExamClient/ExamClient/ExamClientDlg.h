
// ExamClientDlg.h: 헤더 파일
//

#pragma once

#define NM_CHAT_DATA     1

class CExamClientDlg;

class MyClient : public TW_ClientSocket
{
private:
	CExamClientDlg *mp_parent;

public:
	MyClient(CExamClientDlg *ap_parent) : TW_ClientSocket(0x27)
	{
		mp_parent = ap_parent;
	}

	virtual int ProcessRecvData(SOCKET ah_socket, unsigned char a_msg_id, char *ap_recv_data, BS a_body_size);
};

// CExamClientDlg 대화 상자
class CExamClientDlg : public CDialogEx
{
private: 
	MyClient m_client;

// 생성입니다.
public:
	CExamClientDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

	void AddEventString(const wchar_t *ap_string);

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EXAMCLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListBox m_event_list;
	afx_msg void OnBnClickedSendBtn();
protected:
	afx_msg LRESULT OnConnected(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnReadAndClose(WPARAM wParam, LPARAM lParam);
public:
	CListBox m_listBox;
	afx_msg void OnClickedButtonAdd();
	CString m_strEdit;
	void UpdateComboBox();
	CComboBox m_cbListItem;
	afx_msg void OnClickedButtonInsert();
	afx_msg void OnClickedButtonDelete();
	afx_msg void OnEnChangeEditString();
};
