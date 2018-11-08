// InfoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include <tchar.h>
#include "SaleSystem.h"
#include "InfoDlg.h"
#include "InfoFile.h"

// CInfoDlg

IMPLEMENT_DYNCREATE(CInfoDlg, CFormView)
int m_nSortedCol; // 记录点击的列
bool m_bAsc;		// 升降序

CInfoDlg::CInfoDlg()
	: CFormView(CInfoDlg::IDD)
{

}

CInfoDlg::~CInfoDlg()
{
}

void CInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listTest);
}

BEGIN_MESSAGE_MAP(CInfoDlg, CFormView)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST1, &CInfoDlg::OnLvnColumnclickList1)
END_MESSAGE_MAP()


// CInfoDlg 诊断

#ifdef _DEBUG
void CInfoDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CInfoDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

// CInfoDlg 消息处理程序

struct DEMO_DATA
{
	CString szName;
	int iAge;
}strAllData[7]={{TEXT("艾叶"),30},{TEXT("哦快"),50},{TEXT("粗低"),40},{TEXT("鄙视"),32},{TEXT("喝水"),20},{TEXT("张"),36},{TEXT("心"),26}};

void CInfoDlg::OnInitialUpdate()	///初始化对话框
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类

	//初始化ListCtrl中数据列表
	m_listTest.InsertColumn(0,TEXT("姓名"));
	m_listTest.InsertColumn(1,TEXT("年龄"));
	m_listTest.SetColumnWidth(0,80);
	m_listTest.SetColumnWidth(1,80);
	for(int i=0;i<7;i++)
	{
		m_listTest.InsertItem(i, LPCTSTR(strAllData[i].szName));
		CString szAge;
		szAge.Format(_T("%d"),strAllData[i].iAge);
		
		m_listTest.SetItemText(i,1,  szAge);
		//设置每项的ItemData为数组中数据的索引
		//在排序函数中通过该ItemData来确定数据
		//////m_listTest.SetItemData(i,i);
		m_listTest.SetItemData(i,i);     
	}
	
	/*
		
	//设置扩展风格
	/////|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES,整行选中，网格
	m_list.SetExtendedStyle(m_list.GetExtendedStyle()|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	//初始化表头
	CString field[] = {TEXT("商品ID"),TEXT("商品名称"),TEXT("商品单价"),TEXT("商品库存")};

	for(int i=0; i<sizeof(field)/sizeof(field[0]);++i)
	{
		m_list.InsertColumn(i, field[i], LVCFMT_CENTER, 90);
	}

	CInfoFile file;
	file.ReadDocline();	//读取商品信息
	// 添加数据
	int i=0;
	CString str;
	for(list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		str.Format(TEXT("%d"),it->id);
		m_list.InsertItem(i,str);
		int column = 1;
		m_list.SetItemText(i, column++, (CString)it->name.c_str());
		str.Format(TEXT("%d"),it->price);
		m_list.SetItemText(i, column++, str);
		str.Format(TEXT("%d"),it->num);
		m_list.SetItemText(i, column++, str);
		m_list.SetItemData(i,i);//用于存储排序关键字
	}
	*/

}

//第三步：添加列头点击事件
void CInfoDlg::OnLvnColumnclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	//设置排序方式
	if( pNMListView->iSubItem == m_listTest.m_nSortedCol )
		m_listTest.m_fAsc = !m_listTest.m_fAsc;
	else
	{
		m_listTest.m_fAsc = TRUE;
		m_listTest.m_nSortedCol = pNMListView->iSubItem;
	}
	//调用排序函数
	m_listTest.SortItems( FileListCompareFunction, (DWORD)&m_listTest );        
	*pResult = 0;
}


int CALLBACK CInfoDlg::FileListCompareFunction( LPARAM lParam1,LPARAM lParam2,LPARAM lParamSort )
{
	//通过传递的参数来得到CSortList对象指针，从而得到排序方式
	CSortList* pV=(CSortList*)lParamSort;
	//通过ItemData来确定数据
	DEMO_DATA* pInfo1=strAllData+(lParam1);
	DEMO_DATA* pInfo2=strAllData+(lParam2);
	CString szComp1,szComp2;
	int iCompRes;
	switch(pV->m_nSortedCol)
	{
	case(0):
		{
		//以第一列为根据排序
		szComp1=pInfo1->szName;
		szComp2=pInfo2->szName;

		//字符串CString需要转成char *, 然后从char *转成string,才能正确的比较出中文字符的顺序
		CStringA szAtemp1, szAtemp2;
		szAtemp1 = szComp1;
		szAtemp2 = szComp2;
		char * szx1 = szAtemp1.GetBuffer();
		char * szx2 = szAtemp2.GetBuffer();
		string str1 = szx1;					//char*转换为string
		string str2 = szx2;		

		iCompRes= str1.compare(str2);
		}
		break;
	case(1):
		//以第二列为根据排序
		if(pInfo1->iAge == pInfo2->iAge)
			iCompRes = 0;
		else
			iCompRes=(pInfo1->iAge < pInfo2->iAge)?-1:1;
		break;
	default:
		ASSERT(0);
		break;
	}
	//根据当前的排序方式进行调整
	if(pV->m_fAsc)
		return iCompRes;
	else
		return iCompRes*-1;
}
