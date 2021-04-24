#pragma once

#include "Socket_StudyDlg.h"
// CDataSocket 명령 대상
class CSocketStudyDlg;
class CDataSocket : public CSocket
{
public:
	CDataSocket(CSocketStudyDlg* pDlg);
	virtual ~CDataSocket();

	CSocketStudyDlg* m_pDlg;
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
};


