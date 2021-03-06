
// Socket_StudyDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Socket_Study.h"
#include "Socket_StudyDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.




// CSocketStudyDlg 대화 상자



CSocketStudyDlg::CSocketStudyDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SOCKET_STUDY_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pListenSocket = NULL;
	m_pDataSocket = NULL;
	m_bool = FALSE;
	m_nFileLen = 0;
}
CSocketStudyDlg::~CSocketStudyDlg()
{
	if (m_pListenSocket == NULL)
		delete m_pListenSocket;
	if (m_pDataSocket == NULL)
		delete m_pDataSocket;
}
void CSocketStudyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS1, m_ipaddr);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
	DDX_Control(pDX, IDC_EDIT2, m_edit_path);
	DDX_Control(pDX, IDC_PROGRESS1, m_progress);
}

BEGIN_MESSAGE_MAP(CSocketStudyDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CSocketStudyDlg::OnBnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_DISCON, &CSocketStudyDlg::OnBnClickedButtonDiscon)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CSocketStudyDlg::OnBnClickedButtonSend)
	ON_BN_CLICKED(IDC_BUTTON_SELECT, &CSocketStudyDlg::OnBnClickedButtonSelect)
	ON_BN_CLICKED(IDC_BUTTON_FILESEND, &CSocketStudyDlg::OnBnClickedButtonFilesend)
	ON_BN_CLICKED(IDC_BUTTON1, &CSocketStudyDlg::OnBnClickedButton1)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CSocketStudyDlg 메시지 처리기

BOOL CSocketStudyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
#ifdef DEBUG
	m_ipaddr.SetWindowTextW(_T("172.30.1.7"));
	m_ipaddr.SetWindowTextW(_T("127.0.0.1")); // outdoor
#else // RELEASE
	m_ipaddr.SetWindowTextW(_T("172.30.1.41"));
#endif
	m_list = (CListBox *)GetDlgItem(IDC_LIST1);
	m_progress.SetRange(0,100);

	//
	//ASSERT(m_pListenSocket == NULL);


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CSocketStudyDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		//CAboutDlg dlgAbout;
		//dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CSocketStudyDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CSocketStudyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL CSocketStudyDlg::DestroyWindow()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (m_pListenSocket != NULL)
	{
		delete m_pListenSocket;
		m_pListenSocket = NULL;
	}

	if (m_pDataSocket != NULL)
	{
		delete m_pDataSocket;
		m_pDataSocket = NULL;
	}

	return CDialogEx::DestroyWindow();
}

void CSocketStudyDlg::ProcessAccept(int nErrorCode)
{
	// TODO: 여기에 구현 코드 추가.
	CString sPeerAddr;
	UINT PeerPort;
	CString str;

	ASSERT(nErrorCode == 0);

	if (m_pDataSocket == NULL)
	{
		m_pDataSocket = new CDataSocket(this);
		if (m_pListenSocket->Accept(*m_pDataSocket))
		{
			m_pDataSocket->GetPeerName(sPeerAddr, PeerPort);
			str.Format(_T("## IP: %s, Port : %d ##"),sPeerAddr,PeerPort);
			m_list->AddString(str);
		}
		else
		{
			delete m_pDataSocket;
			m_pDataSocket = NULL;
		}
	}

}

void CSocketStudyDlg::ProcessReceive(CDataSocket *pSocket, int nErrorCode)
{

}

void CSocketStudyDlg::ProcessClose(CDataSocket* pSocket, int nErrorCode)
{
	pSocket->Close();
	delete m_pDataSocket;
	m_pDataSocket = NULL;
	m_list->AddString(_T("##접속 종료"));
}


void CSocketStudyDlg::OnBnClickedButtonConnect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_pDataSocket == NULL)
	{
		m_pDataSocket = new CDataSocket(this);
		m_pDataSocket->Create();
		CString addr;
		m_ipaddr.GetWindowText(addr);
		//SetTimer(0, 1, NULL);
		if (m_pDataSocket->Connect(addr, 8000))
		{
			
			MessageBox(_T("접속 성공"));
			m_edit.SetFocus();
		}
		else
		{
			MessageBox(_T("접속 실패"));
			delete m_pDataSocket;
			m_pDataSocket = NULL;
		}
	}
	else
	{
		MessageBox(_T("이미 접속된 서버"));
		m_edit.SetFocus();
	}
}


void CSocketStudyDlg::OnBnClickedButtonDiscon()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_pDataSocket == NULL)
	{
		MessageBox(_T("서버 접속 안함"));
	}
	else
	{
		m_pDataSocket->Close();
		delete m_pDataSocket;
		m_pDataSocket = NULL;
		MessageBox(_T("접속 해제"));
	}
}


void CSocketStudyDlg::OnBnClickedButtonSend()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_pDataSocket == NULL)
	{
		MessageBox(_T("서버 접속 안함"));
	}
	else
	{
		CString message;
		m_edit.GetWindowText(message);
		int n;
		n = m_pDataSocket->Send((LPCTSTR)message, (message.GetLength() + 1) * sizeof(TCHAR));
		if (n < 0)
		{
			MessageBox(_T("음수 결과!"));
		}
		m_edit.SetWindowText(_T(""));
		m_edit.SetFocus();
	}
}


void CSocketStudyDlg::OnBnClickedButtonSelect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFileDialog dlg(TRUE);
	if (dlg.DoModal() == IDOK)
	{
		m_edit_path.SetWindowText(dlg.GetPathName());
	}
}


void CSocketStudyDlg::OnBnClickedButtonFilesend()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sForm;
	CFile file;
	CString sPath;	
	char* pbuf = NULL;
	char pszBuf[2048] = { 0, };
	int nPos = 0;
	int n = 0;
	m_progress.SetPos(0);
	m_edit_path.GetWindowText(sPath);

	m_pSendTread = (CSendThread*)AfxBeginThread(RUNTIME_CLASS(CSendThread),
		THREAD_PRIORITY_HIGHEST,
		0,
		CREATE_SUSPENDED);

	m_pSendTread->SetFilePath(sPath);

	m_pSendTread->SetPtr(this, m_pDataSocket);

	m_pSendTread->ResumeThread();

	return;
}


void CSocketStudyDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ASSERT(m_pDataSocket == NULL);
	DWORD dwTimeOut = 3000;
	m_pDataSocket = new CDataSocket(this);
	//if (m_pListenSocket->Create(8000))
	if (m_pDataSocket->Create(8000))
	{
		
		//if (m_pListenSocket->Listen())
		if (m_pDataSocket->Listen())
		{		
			AfxMessageBox(_T("서버를 시작합니다."));
			return;
		}

	}

	AfxMessageBox(_T("이미 실행중인 서버가 있습니다."));
	return;

}


void CSocketStudyDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	switch (nIDEvent)
	{
	case 0:
		if (!m_bool)
		{
			m_bool = TRUE;
		}
		else
		{
			
			m_pDataSocket->Close();
			m_bool = FALSE;
			KillTimer(0);
			AfxMessageBox(_T("소켓 Close"));
		}
		Sleep(1400);
		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}
