
// Socket_Client_StudyDlg.h: 헤더 파일
//

#pragma once
#include "CDataSocket.h"

// CSocketClientStudyDlg 대화 상자
class CDataSocket;
class CSocketClientStudyDlg : public CDialog
{
// 생성입니다.
public:
	CSocketClientStudyDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

	CDataSocket* m_pDataSocket;
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SOCKET_CLIENT_STUDY_DIALOG };
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
	CIPAddressCtrl m_ipdaar;
	CEdit m_edit;
	afx_msg void OnBnClickedButtonConnect();
	afx_msg void OnBnClickedButtonDiscon();
	afx_msg void OnBnClickedButtonSend();
};
