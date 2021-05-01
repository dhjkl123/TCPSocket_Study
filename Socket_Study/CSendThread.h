#pragma once

#include "CDataSocket.h"
#include "Socket_Study.h"
// CSendThread
class CSocketStudyDlg;
class CDataSocket;
class CSendThread : public CWinThread
{
	DECLARE_DYNCREATE(CSendThread)

protected:
	CSendThread();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CSendThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
public:
	int m_nFileLen;
	CString m_sPath;
	CDataSocket* m_pDataSocket;
	CSocketStudyDlg* m_pDlg;
public:
	virtual int Run();

	void SetFilePath(CString sPath)
	{
		m_sPath = sPath;
	}

	void SetPtr(CSocketStudyDlg* pDlg, CDataSocket* pDataSocket)
	{
		m_pDlg = pDlg;
		m_pDataSocket = pDataSocket;
	}

};


