
// Socket_StudyDlg.h: 헤더 파일
//

#pragma once
#include "CDataSocket.h"
#include "CListenSocket.h"

// CSocketStudyDlg 대화 상자
class CDataSocket;
class CListenSocket;
class CSocketStudyDlg : public CDialogEx
{
// 생성입니다.
public:
	CSocketStudyDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	~CSocketStudyDlg();
	CListenSocket* m_pListenSocket;
	CDataSocket* m_pDataSocket;
	void ProcessAccept(int nErrorCode);
	void ProcessReceive(CDataSocket* pSocket, int nErrorCode);
	void ProcessClose(CDataSocket* pSocket, int nErrorCode);
	CListBox* m_list;
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SOCKET_STUDY_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL DestroyWindow();
	CIPAddressCtrl m_ipaddr;
	CEdit m_edit;
	afx_msg void OnBnClickedButtonConnect();
	afx_msg void OnBnClickedButtonDiscon();
	afx_msg void OnBnClickedButtonSend();
};
