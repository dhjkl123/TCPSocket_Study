#pragma once

// CListenSocket ��� ���
#include "Socket_Client_StudyDlg.h"

class CSocketClientStudyDlg;
class CListenSocket : public CSocket
{
public:
	CListenSocket(CSocketClientStudyDlg* pDlg);
	virtual ~CListenSocket();

	CSocketClientStudyDlg* m_pDlg;
	virtual void OnAccept(int nErrorCode);
};


