// CDataSocket.cpp: 구현 파일
//

#include "pch.h"
#include "Socket_Study.h"
#include "CDataSocket.h"
#include "CSocketThread.h"

// CDataSocket

CDataSocket::CDataSocket(CSocketStudyDlg* pDlg)
{
	m_pDlg = pDlg;
}

CDataSocket::CDataSocket()
{
}

CDataSocket::~CDataSocket()
{
}

void CDataSocket::SetWnd(HWND hWnd, LPVOID pDlg)
{
	m_hWnd = hWnd;
	m_pDlg = (CSocketStudyDlg*)pDlg;
}

// CDataSocket 멤버 함수
void CDataSocket::OnAccept(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	CSocket sock;
	if (Accept(sock))
	{
		CSocketThread* pThread = (CSocketThread*)AfxBeginThread(RUNTIME_CLASS(CSocketThread), THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);
		pThread->SetWnd(m_hWnd, m_pDlg);

		if (!pThread)
		{
			sock.Close();
			m_pDlg->m_list->AddString(_T("ERROR : Thread could not be created !!"));
			return;
		}

		sock.Send(_T("Connect with Server"), 43);

		pThread->m_hSocket = sock.Detach();
		pThread->ResumeThread();
	}

	CSocket::OnAccept(nErrorCode);
	//m_pDlg->ProcessAccept(nErrorCode);
}

void CDataSocket::OnReceive(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	char buf[100] = { 0, };
	int nBytes = this->Receive(buf, 100);
	int nFileLen = 0;
	CString str, sTmp, sPath;
	BOOL Bool = FALSE;
	str.Format(_T("%s"), &buf);

	if (str.Left(8) == "FileSend")
	{
		int nStrPos = 0;
		Bool = TRUE;
		sTmp = str.Right(4);
		sPath = _T("Recive") + sTmp;
		str.Replace(_T("FileSend"), _T(""));

		nStrPos = str.Find(_T("."));
		nFileLen = _ttoi(str.Left(nStrPos));
	}

	if (Bool)
	{
		nBytes = 0;
		int nPos = 0;
		char* szSend = NULL;
		szSend = new char[nFileLen + 1];
		memset(szSend, 0x00, nFileLen + 1);
		int nCnt = 0;

		while (nFileLen > nPos)
		{

			nBytes += this->Receive(szSend + nPos, 2048);
			nPos += 2048;
			//str.Format(_T("nCnt : %d"), nCnt);
			//m_pDlg->m_list->AddString(str);
			if (nFileLen < nPos + 2048)
			{
				int nLsatSize = nFileLen - nPos;
				int nTmp = 0;
				nTmp = this->Receive(szSend + nPos, nLsatSize);
				nBytes += nTmp;
				//str.Format(_T("Last!"));
				//m_pDlg->m_list->AddString(str);
				break;
			}
			Sleep(1);
			nCnt++;
		}

		try
		{
			CFile file;
			file.Open(sPath, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);
			file.Write(szSend, nFileLen);
			file.Close();
			m_pDlg->m_list->AddString(sPath +_T(" is Recived!"));
			this->Receive(szSend, 2048);
		}
		catch (CFileException* e)
		{
			e->m_cause;
		}
		delete[] szSend;
		Bool = FALSE;
	}
	else
	{
		if (!str.IsEmpty())
			m_pDlg->m_list->AddString(str);
	}

	CSocket::OnReceive(nErrorCode);
	//m_pDlg->ProcessReceive(this,nErrorCode);
}


void CDataSocket::OnClose(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	//m_pThread->PostThreadMessage(WM_QUIT, 0, 0);

	//SendMessage(m_hWnd, WM_CLIENT_CLOSE, 0, (LPARAM)this);

	CSocket::OnClose(nErrorCode);
	m_pDlg->ProcessClose(this, nErrorCode);
}
