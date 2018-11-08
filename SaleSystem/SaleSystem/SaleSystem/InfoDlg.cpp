// InfoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include <tchar.h>
#include "SaleSystem.h"
#include "InfoDlg.h"
#include "InfoFile.h"
#include "SortList.h"
// CInfoDlg

IMPLEMENT_DYNCREATE(CInfoDlg, CFormView)

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
	DDX_Control(pDX, IDC_LIST1, m_list);
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

void CInfoDlg::OnInitialUpdate()	///初始化对话框
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类

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
		i++;
	}
	
}

//第三步：添加列头点击事件
void CInfoDlg::OnLvnColumnclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	//设置排序方式
	if( pNMListView->iSubItem == m_list.m_nSortedCol )
		m_list.m_fAsc = !m_list.m_fAsc;
	else
	{
		m_list.m_fAsc = TRUE;
		m_list.m_nSortedCol = pNMListView->iSubItem;
	}
	//调用排序函数
	m_list.SortItems( FileListCompareFunction, (DWORD)&m_list );        
	*pResult = 0;
}


int CALLBACK CInfoDlg::FileListCompareFunction( LPARAM lParam1,LPARAM lParam2,LPARAM lParamSort )
{
	CSortList* pV=(CSortList*)lParamSort;
	CListCtrl *pListCtrl = (CListCtrl*)lParamSort;
	int rValue=0;

	int nItem1,nItem2;
	LVFINDINFO FindInfo;
	FindInfo.flags=LVFI_PARAM;
	FindInfo.lParam=lParam1;
	nItem1=pListCtrl->FindItem(&FindInfo,-1);
	FindInfo.lParam=lParam2;
	nItem2=pListCtrl->FindItem(&FindInfo,-1);
	if((nItem1 == -1)||(nItem2 == -1))
	{
		return 0;
	}

	CString szComp1,szComp2;
	szComp1=pListCtrl->GetItemText(nItem1,pV->m_nSortedCol);
	szComp2=pListCtrl->GetItemText(nItem2,pV->m_nSortedCol);

	int num1,num2;
	num1 = _ttoi(szComp1.GetBuffer());
	num2 = _ttoi(szComp2.GetBuffer());
	szComp1.ReleaseBuffer();
	szComp2.ReleaseBuffer();
		
	int iCompRes;
	switch(pV->m_nSortedCol)
	{
	case(0):
		{
			//以第1列为根据排序,（数字排序法）
			if(num1 == num2)
				iCompRes = 0;
			else
				iCompRes=(num1 < num2)?-1:1;
		}
		break;
	case(1):
		{
			//以第2列为根据排序
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
	case(2):
		{
			if(num1 == num2)
				iCompRes = 0;
			else
				iCompRes=(num1 < num2)?-1:1;
		}
		break;
	case(3):
		{
			if(num1 == num2)
				iCompRes = 0;
			else
				iCompRes=(num1 < num2)?-1:1;
		}
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
