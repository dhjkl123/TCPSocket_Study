// CListenSocket.cpp: 구현 파일
//

#include "pch.h"
#include "Socket_Study.h"
#include "CListenSocket.h"



// CListenSocket

CListenSocket::CListenSocket(CSocketStudyDlg* pDlg)
{
	m_pDlg = pDlg;
}

CListenSocket::~CListenSocket()
{
}


// CListenSocket 멤버 함수


//void CListenSocket::OnAccept(int nErrorCode)
//{
//	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
//	
//	CSocket sock;
//	if (Accept(sock))
//	{
//		CSocketThread* pThread = (CSocketThread*)AfxBeginThread(RUNTIME_CLASS(CSocketThread), THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);
//		pThread->SetWnd(m_hWnd);
//
//		if (!pThread)
//		{
//			sock.Close();
//			m_pDlg->m_list->AddString(_T("ERROR : Thread could not be created !!"));
//			return;
//		}
//
//		sock.Send(_T("Connect with Server"), 43);
//
//		pThread->m_hSocket = sock.Detach();
//		pThread->ResumeThread();
//	}
//
//	CSocket::OnAccept(nErrorCode);
//	//m_pDlg->ProcessAccept(nErrorCode);
//}


void CListenSocket::OnClose(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.


	CSocket::OnClose(nErrorCode);
}

//void CListenSocket::SetWnd(HWND hWnd)
//{
//	m_hWnd = hWnd;
//}