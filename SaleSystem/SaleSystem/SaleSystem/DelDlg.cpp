// DelDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SaleSystem.h"
#include "DelDlg.h"
#include "InfoFile.h"

// CDelDlg

IMPLEMENT_DYNCREATE(CDelDlg, CFormView)

CDelDlg::CDelDlg()
	: CFormView(CDelDlg::IDD)
	, m_price(0)
	, m_num(0)
	, m_left(0)
{

}

CDelDlg::~CDelDlg()
{
}

void CDelDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Text(pDX, IDC_EDIT1, m_price);
	DDX_Text(pDX, IDC_EDIT3, m_num);
	DDV_MinMaxInt(pDX, m_num, 1, 9999);
	DDX_Text(pDX, IDC_EDIT4, m_left);
}

BEGIN_MESSAGE_MAP(CDelDlg, CFormView)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CDelDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON1, &CDelDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDelDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CDelDlg 诊断

#ifdef _DEBUG
void CDelDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CDelDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDelDlg 消息处理程序


void CDelDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	//读取文件，获取商品信息，给组合框添加上商品名称字符串串
	CInfoFile file;
	file.ReadDocline();
	for(list<msg>::iterator it = file.ls.begin(); it!=file.ls.end(); it++)
	{
		m_combo.AddString((CString)it->name.c_str());
	}
	m_combo.SetCurSel(0);
	OnCbnSelchangeCombo1();	//更新第一个商品里面的数据（单价）
}


void CDelDlg::OnCbnSelchangeCombo1()
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


void CDelDlg::OnBnClickedButton1()
{
	UpdateData();
	// 删除功能的实现
	if(m_num<=0)
	{
		MessageBox(TEXT("删除个数不能小于等于0"));
		return;
	}
	if(m_num>=m_left)
	{
		MessageBox(TEXT("删除个数不能大于等于库存数量"));
		return;
	}

	//删除
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
			m_left = it->num - m_num;	//原来的库存量-需要删除的库存量
			it->num = m_left;
			//告诉用户具体的删除信息
			CString str;
			str.Format(_T("商品名：%s \r\n删除数量：%d \r\n单价：%d \r\n \r\n删除成功！ "),name, m_num, m_price);
			file.WriteDocline();
			MessageBox(str);
		}	
	}

	//清空数据
	m_num = 0;
	UpdateData(FALSE);
}


void CDelDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	//清空数据
	m_num = 0;
	m_combo.SetCurSel(0);
	OnCbnSelchangeCombo1();	//更新第一个商品里面的数据（单价）
	UpdateData(FALSE);
}
