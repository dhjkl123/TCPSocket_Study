#pragma once

// CListenSocket 명령 대상
#include "Socket_StudyDlg.h"

class CSocketStudyDlg;
class CListenSocket : public CSocket
{
public:
	CListenSocket(CSocketStudyDlg* pDlg);
	virtual ~CListenSocket();

	CSocketStudyDlg* m_pDlg;
	virtual void OnAccept(int nErrorCode);
};


