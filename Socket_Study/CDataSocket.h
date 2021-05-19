#pragma once

#include "Socket_StudyDlg.h"
// CDataSocket 명령 대상
class CSocketStudyDlg;
class CDataSocket : public CSocket
{
public:
	CDataSocket(CSocketStudyDlg* pDlg);
	CDataSocket();
	virtual ~CDataSocket();

	CSocketStudyDlg* m_pDlg;

	CWinThread* m_pThread;

	HWND m_hWnd;
	void SetWnd(HWND hWnd, LPVOID pDlg);

	virtual void OnAccept(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
};


