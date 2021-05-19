// CSendThread.cpp: 구현 파일
//

#include "pch.h"
#include "Socket_Study.h"
#include "CSendThread.h"


// CSendThread

IMPLEMENT_DYNCREATE(CSendThread, CWinThread)

CSendThread::CSendThread()
{
	m_sPath = _T("");
	m_pDataSocket = NULL;
	m_pDlg = NULL;
}

CSendThread::~CSendThread()
{
}

BOOL CSendThread::InitInstance()
{
	// TODO:  여기에서 각 스레드에 대한 초기화를 수행합니다.
	return TRUE;
}

int CSendThread::ExitInstance()
{
	// TODO:  여기에서 각 스레드에 대한 정리를 수행합니다.
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CSendThread, CWinThread)
END_MESSAGE_MAP()


// CSendThread 메시지 처리기


int CSendThread::Run()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CString sForm;
	CFile file;
	char* pbuf = NULL;
	char pszBuf[2048] = { 0, };
	int nPos = 0;
	int n = 0;

	if (!file.Open(m_sPath, CFile::modeRead | CFile::typeBinary))
	{
		m_pDlg->m_list->AddString(_T("파일 열기 실패!"));
		return -1;
	}

	ULONGLONG nFileLen = file.GetLength();

	sForm.Format(_T("FileSend%d%s"), nFileLen, m_sPath.Right(4));

	n = m_pDataSocket->Send((LPCTSTR)sForm, (sForm.GetLength() + 1) * sizeof(TCHAR));
	if (n < 0)
	{
		m_pDlg->m_list->AddString(_T("요청 실패!"));
		return -2;
	}
	else
	{
		m_pDlg->m_list->AddString(_T("요청 성공!"));
		Sleep(250);
	}




	pbuf = new char[nFileLen];
	UINT nRead = file.Read(pbuf, (UINT)nFileLen);
	if (nRead < 0)
	{
		m_pDlg->m_list->AddString(_T("파일 읽기 실패!"));
		//file.Close();
		return -3;
	}
	else
	{
		double nPercent = 2048 / (double)nFileLen * 100;

		int nCnt = 1;
		while (nPos < nFileLen)
		{
			// nPos + sizeof(pszBuf) > nFileLen
			if((nPos + sizeof(pszBuf)) > nFileLen)
				memcpy(pszBuf, pbuf + nPos, nFileLen - nPos);
			else
				memcpy(pszBuf, pbuf + nPos, sizeof(pszBuf));

			n = m_pDataSocket->Send(pszBuf, 2048);

			if (n < 0)
			{
				m_pDlg->m_list->AddString(_T("음수 결과!"));
				break;
			}
			nPos += 2048;
			memset(pszBuf, 0x00, sizeof(pszBuf));

			if (nPercent > 100)
				m_pDlg->m_progress.SetPos(100);
			else
			{
				m_pDlg->m_progress.SetPos((int)(nPercent * nCnt));
				nCnt++;
			}

			Sleep(2);
		}
		file.Close();
	}
	delete[] pbuf;

	PostThreadMessage(WM_QUIT, 0, 0);

	return CWinThread::Run();
}
