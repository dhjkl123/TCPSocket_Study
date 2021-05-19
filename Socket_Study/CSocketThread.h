#pragma once


#include "CListenSocket.h"
#include "Socket_StudyDlg.h"
// CSocketThread
class CDataSocket;
class CSocketThread : public CWinThread
{
	DECLARE_DYNCREATE(CSocketThread)

protected:
	CSocketThread();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CSocketThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	CSocketStudyDlg* m_pDlg;
	CDataSocket m_DataSocket;
	SOCKET m_hSocket;

	HWND m_hWnd;
	void SetWnd(HWND hWnd, LPVOID pDlg);

protected:
	DECLARE_MESSAGE_MAP()
};


