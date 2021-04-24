#pragma once

// CDataSocket 명령 대상
#include "Socket_Client_StudyDlg.h"
class CSocketClientStudyDlg;
class CDataSocket : public CSocket
{
public:
	CDataSocket(CSocketClientStudyDlg* pDlg);
	virtual ~CDataSocket();

	CSocketClientStudyDlg* m_pDlg;
};


