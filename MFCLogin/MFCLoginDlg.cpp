
// MFCLoginDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCLogin.h"
#include "AVLTree.h"
#include "MFCLoginDlg.h"
#include "afxdialogex.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCLoginDlg dialog



CMFCLoginDlg::CMFCLoginDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCLOGIN_DIALOG, pParent)
	, m_name(_T(""))
	, m_pass(_T(""))
	, m_passtwo(_T(""))
	, m_passagain(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_name);
	DDX_Text(pDX, IDC_EDIT2, m_pass);
	DDX_Text(pDX, IDC_EDIT4, m_passagain);
}

BEGIN_MESSAGE_MAP(CMFCLoginDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCLoginDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCLoginDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCLoginDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCLoginDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CMFCLoginDlg message handlers

BOOL CMFCLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCLoginDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCLoginDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCLoginDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//登录按钮功能实现
void CMFCLoginDlg::OnBnClickedButton1()
{
	UpdateData(true);
	GetDlgItem(IDC_STATIC1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT4)->ShowWindow(SW_HIDE);
	if (m_name.IsEmpty()) {
		MessageBox(_T("登录失败，用户名不能为空"));
		return;
	}
	string name = CW2A(m_name.GetString());
	string pass = CW2A(m_pass.GetString());
	AVLTree user;
	user.readTree();
	if (user.search(name)) {
		if (user.logIn(name,pass)) {
			MessageBox(_T("登录成功"));
		}
		else {
			MessageBox(_T("登录失败，密码错误"));
		}
	}
	else {
		MessageBox(_T("登录失败，用户名不存在"));
	}
}

//注册按钮功能实现
void CMFCLoginDlg::OnBnClickedButton2()
{
	UpdateData(true);
	GetDlgItem(IDC_STATIC1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT4)->ShowWindow(SW_HIDE);
	UpdateData(true);
	string name = CW2A(m_name.GetString());
	string pass = CW2A(m_pass.GetString());
	AVLTree user;
	user.readTree();
	if (user.registerUser(name,pass)&&name!="") {
		MessageBox(_T("用户名已存在"));
	}
	else {
		if (name != "") {
			MessageBox(_T("注册成功"));
		}
	}
}


//修改密码功能实现
void CMFCLoginDlg::OnBnClickedButton3()
{
	UpdateData(true);
	GetDlgItem(IDC_STATIC1)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT4)->ShowWindow(SW_SHOW);
	string name = CW2A(m_name.GetString());
	string pass = CW2A(m_pass.GetString());
	string passEnd = CW2A(m_passagain.GetString());
	AVLTree user;
	user.readTree();
	if (user.search(name)) {
		
		if (user.passChange(name, pass, passEnd)) {
			MessageBox(_T("密码修改成功"));
		}
		else {
			MessageBox(_T("原密码错误，修改失败"));
		}
	}
	else {
		if (name != "") {
			MessageBox(_T("用户名不存在"));
		}
	}
}

//注销功能的实现
void CMFCLoginDlg::OnBnClickedButton4()
{
	UpdateData(true);
	GetDlgItem(IDC_STATIC1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT4)->ShowWindow(SW_HIDE);
	string name = CW2A(m_name.GetString());
	string pass = CW2A(m_pass.GetString());
	AVLTree user;
	user.readTree();
	if (user.search(name)) {
		if (user.logIn(name,pass)) {
			user.remove(user.getRoot(), name);
			MessageBox(_T("注销成功"));
		}
		else {
			MessageBox(_T("密码错误，注销失败"));
		}
	}
	else {
		MessageBox(_T("用户名不存在,注销失败"));
	}
}
