// CSocketThread.cpp: 구현 파일
//

#include "pch.h"
#include "CSocketThread.h"


// CSocketThread

IMPLEMENT_DYNCREATE(CSocketThread, CWinThread)

CSocketThread::CSocketThread()
{
	
}

CSocketThread::~CSocketThread()
{
}

BOOL CSocketThread::InitInstance()
{
	// TODO:  여기에서 각 스레드에 대한 초기화를 수행합니다.
	m_DataSocket.Attach(m_hSocket);
	m_DataSocket.m_pThread = this;
	m_DataSocket.SetWnd(m_hWnd,m_pDlg);
	return TRUE;
}

int CSocketThread::ExitInstance()
{
	// TODO:  여기에서 각 스레드에 대한 정리를 수행합니다.
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CSocketThread, CWinThread)
END_MESSAGE_MAP()


// CSocketThread 메시지 처리기
void CSocketThread::SetWnd(HWND hWnd, LPVOID pDlg)
{
	m_hWnd = hWnd;
	m_pDlg = (CSocketStudyDlg*)pDlg;
}
