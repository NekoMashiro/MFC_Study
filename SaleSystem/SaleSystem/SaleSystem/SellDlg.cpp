// SellDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SaleSystem.h"
#include "SellDlg.h"
#include "InfoFile.h"

// CSellDlg

IMPLEMENT_DYNCREATE(CSellDlg, CFormView)

CSellDlg::CSellDlg()
	: CFormView(CSellDlg::IDD)
	, m_price(0)
	, m_left(0)
	, m_num(0)
	, m_sellInfo(_T(""))
{

}

CSellDlg::~CSellDlg()
{
}

void CSellDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Text(pDX, IDC_EDIT1, m_price);
	DDX_Text(pDX, IDC_EDIT3, m_left);
	DDX_Text(pDX, IDC_EDIT4, m_num);
	DDX_Text(pDX, IDC_EDIT5, m_sellInfo);
}

BEGIN_MESSAGE_MAP(CSellDlg, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CSellDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CSellDlg::OnBnClickedButton2)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CSellDlg::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// CSellDlg 诊断

#ifdef _DEBUG
void CSellDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CSellDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSellDlg 消息处理程序


void CSellDlg::OnBnClickedButton1()
{
	UpdateData(TRUE);
	// 购买功能的实现
	if(m_num<=0)
	{
		MessageBox(TEXT("购买个数不能小于等于0"));
		return;
	}
	if(m_num>m_left)
	{
		MessageBox(TEXT("购买个数不能大于库存"));
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
			//同步到库存控件上
			it->num = m_left - m_num;
			m_left  = it->num;	//控件上的库存量
			//告诉用户具体的购买信息
			CString str;
			str.Format(_T("商品名：%s \r\n购买数量：%d \r\n单价：%d \r\n总价：%d"),name, m_num, m_price, m_price*m_num);
			m_sellInfo = str;
			UpdateData(FALSE);
			MessageBox(_T("购买成功！"));
		}	
	}

	file.WriteDocline();
	//清空数据
	m_num = 0;
	m_sellInfo.Empty();
	UpdateData(FALSE);

}


void CSellDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	//清空数据
	m_num = 0;
	m_sellInfo.Empty();
	UpdateData(FALSE);
}


void CSellDlg::OnInitialUpdate()
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
	}
	m_combo.SetCurSel(0);	///默认选中第一个商品
	OnCbnSelchangeCombo1();	//更新第一个商品里面的数据（单价，库存）
}


void CSellDlg::OnCbnSelchangeCombo1()
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
			m_left = it->num;
			m_price = it->price;
			UpdateData(FALSE);	//变量的值马上同步到控件上
		}

	}


}
