// AddDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SaleSystem.h"
#include "AddDlg.h"
#include "InfoFile.h"



// CAddDlg

IMPLEMENT_DYNCREATE(CAddDlg, CFormView)

CAddDlg::CAddDlg()
	: CFormView(CAddDlg::IDD)
	, m_price1(0)
	, m_num1(0)
	, m_name2(_T(""))
	, m_price2(0)
	, m_num2(0)
	, m_left1(0)
{

}

CAddDlg::~CAddDlg()
{
}

void CAddDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Text(pDX, IDC_EDIT1, m_price1);
	DDX_Text(pDX, IDC_EDIT3, m_num1);
	DDX_Text(pDX, IDC_EDIT4, m_name2);
	DDX_Text(pDX, IDC_EDIT5, m_price2);
	DDX_Text(pDX, IDC_EDIT6, m_num2);
	DDX_Text(pDX, IDC_EDIT7, m_left1);
}

BEGIN_MESSAGE_MAP(CAddDlg, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CAddDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CAddDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CAddDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CAddDlg::OnBnClickedButton4)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CAddDlg::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// CAddDlg 诊断

#ifdef _DEBUG
void CAddDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CAddDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CAddDlg 消息处理程序


void CAddDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	//初始化商品名称列表下拉框
	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it!=file.ls.end(); it++)
	{
		////m_combo = it->name;
		//////char * ---> CString
		m_combo.AddString((CString)it->name.c_str());
		m_price1 = it->price;
	}
	UpdateData(FALSE);
	m_combo.SetCurSel(0);	///默认选中第一个商品
	OnCbnSelchangeCombo1(); //初始化默认选中的第一个商品的单价
}


void CAddDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);	//取出控件中的值到变量里面去
	// 购买功能的实现
	if(m_num1<=0)
	{
		MessageBox(TEXT("添加个数不能小于等于0"));
		return;
	}

	//购买
	//获取到具体的要购买的商品名称
	CString name;
	int index = m_combo.GetCurSel();
	m_combo.GetLBText(index, name);

	CInfoFile file;
	file.ReadDocline();
	for(list<msg>::iterator it=file.ls.begin(); it != file.ls.end(); it++)
	{
		if((CString)it->name.c_str() == name)
		{
			//
			it->num = it->num + m_num1;
			m_left1 = it->num;
			MessageBox(_T("添加成功！"));
			file.WriteDocline();
		}	
	}

	//清空数据
	m_num1 = 0;
	UpdateData(FALSE);

}


void CAddDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	//清空数据
	UpdateData(TRUE);
	m_num1 = 0;
	m_combo.SetCurSel(0);	///默认选中第一个商品
	OnCbnSelchangeCombo1();
	
	UpdateData(FALSE);
}


void CAddDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);	//取出控件中的值到变量里面去
	// 购买功能的实现
	if(m_num2<=0)
	{
		MessageBox(TEXT("添加个数不能小于等于0"));
		return;
	}
	if(m_price2<=0)
	{
		MessageBox(TEXT("添加商品单价不能小于等于0"));
		return;
	}
	if(m_name2.IsEmpty() || m_name2.GetLength()>8)
	{
		MessageBox(TEXT("添加商品名为空或者长度大于8个字符"));
		return;
	}

	CInfoFile file;
	file.ReadDocline();
	file.Addline(m_name2, m_num2, m_price2);
	file.WriteDocline();
	MessageBox(TEXT("添加成功！"));

	//同步到左侧的商品名称下拉列表中
	m_combo.InsertString(0,m_name2);
	m_combo.SetCurSel(0);
	OnCbnSelchangeCombo1();

	//清空输入的内容
	m_name2.Empty();
	m_price2 = 0;
	m_num2 = 0;
	UpdateData(FALSE);
}


void CAddDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	//清空数据
	UpdateData(TRUE);	//此句是为了保留住在 左边的m_num1 添加的库存值不会变动
	m_name2.Empty();
	m_num2 = 0;
	m_price2 = 0;
	UpdateData(FALSE);
}


void CAddDlg::OnCbnSelchangeCombo1()	//控件中的内容被改变时调用的方法
{
	// TODO: 在此添加控件通知处理程序代码;
	//切换商品时，控件内容发生改变的时候被调用
	//先获取商品的名称
	int index = m_combo.GetCurSel();
	//根据索引获取到具体的内容
	CString name;
	m_combo.GetLBText(index, name);

	//根据商品的名称，获取到商品的单价和库存，并且显示到控件中去
	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if(CString(it->name.c_str()) == name)
		{
			m_price1 = it->price;
			m_left1 = it->num;
			UpdateData(FALSE);	//变量的值马上同步到控件上
		}

	}
}
