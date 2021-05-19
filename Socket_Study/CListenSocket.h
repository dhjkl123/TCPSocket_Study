#pragma once

#define WM_CLIENT_CLOSE WM_USER+3
// CListenSocket 명령 대상
#include "Socket_StudyDlg.h"

class CSocketStudyDlg;
class CListenSocket : public CSocket //Server
{
public:
	CListenSocket(CSocketStudyDlg* pDlg);
	//CListenSocket();
	virtual ~CListenSocket();

	CSocketStudyDlg* m_pDlg;
	//CWinThread* m_pThread;

	//HWND m_hWnd;
	//void SetWnd(HWND hWnd);

	//virtual void OnAccept(int nErrorCode);
	virtual void OnClose(int nErrorCode);
};


