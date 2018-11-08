// InfoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include <tchar.h>
#include "SaleSystem.h"
#include "InfoDlg.h"
#include "InfoFile.h"

// CInfoDlg

IMPLEMENT_DYNCREATE(CInfoDlg, CFormView)
int m_nSortedCol; // ��¼�������
bool m_bAsc;		// ������

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


// CInfoDlg ���

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

// CInfoDlg ��Ϣ�������

struct DEMO_DATA
{
	CString szName;
	int iAge;
}strAllData[7]={{TEXT("��Ҷ"),30},{TEXT("Ŷ��"),50},{TEXT("�ֵ�"),40},{TEXT("����"),32},{TEXT("��ˮ"),20},{TEXT("��"),36},{TEXT("��"),26}};

void CInfoDlg::OnInitialUpdate()	///��ʼ���Ի���
{
	CFormView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���

	//��ʼ��ListCtrl�������б�
	m_listTest.InsertColumn(0,TEXT("����"));
	m_listTest.InsertColumn(1,TEXT("����"));
	m_listTest.SetColumnWidth(0,80);
	m_listTest.SetColumnWidth(1,80);
	for(int i=0;i<7;i++)
	{
		m_listTest.InsertItem(i, LPCTSTR(strAllData[i].szName));
		CString szAge;
		szAge.Format(_T("%d"),strAllData[i].iAge);
		
		m_listTest.SetItemText(i,1,  szAge);
		//����ÿ���ItemDataΪ���������ݵ�����
		//����������ͨ����ItemData��ȷ������
		//////m_listTest.SetItemData(i,i);
		m_listTest.SetItemData(i,i);     
	}
	
	/*
		
	//������չ���
	/////|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES,����ѡ�У�����
	m_list.SetExtendedStyle(m_list.GetExtendedStyle()|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	//��ʼ����ͷ
	CString field[] = {TEXT("��ƷID"),TEXT("��Ʒ����"),TEXT("��Ʒ����"),TEXT("��Ʒ���")};

	for(int i=0; i<sizeof(field)/sizeof(field[0]);++i)
	{
		m_list.InsertColumn(i, field[i], LVCFMT_CENTER, 90);
	}

	CInfoFile file;
	file.ReadDocline();	//��ȡ��Ʒ��Ϣ
	// �������
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
		m_list.SetItemData(i,i);//���ڴ洢����ؼ���
	}
	*/

}

//�������������ͷ����¼�
void CInfoDlg::OnLvnColumnclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	//��������ʽ
	if( pNMListView->iSubItem == m_listTest.m_nSortedCol )
		m_listTest.m_fAsc = !m_listTest.m_fAsc;
	else
	{
		m_listTest.m_fAsc = TRUE;
		m_listTest.m_nSortedCol = pNMListView->iSubItem;
	}
	//����������
	m_listTest.SortItems( FileListCompareFunction, (DWORD)&m_listTest );        
	*pResult = 0;
}


int CALLBACK CInfoDlg::FileListCompareFunction( LPARAM lParam1,LPARAM lParam2,LPARAM lParamSort )
{
	//ͨ�����ݵĲ������õ�CSortList����ָ�룬�Ӷ��õ�����ʽ
	CSortList* pV=(CSortList*)lParamSort;
	//ͨ��ItemData��ȷ������
	DEMO_DATA* pInfo1=strAllData+(lParam1);
	DEMO_DATA* pInfo2=strAllData+(lParam2);
	CString szComp1,szComp2;
	int iCompRes;
	switch(pV->m_nSortedCol)
	{
	case(0):
		{
		//�Ե�һ��Ϊ��������
		szComp1=pInfo1->szName;
		szComp2=pInfo2->szName;

		//�ַ���CString��Ҫת��char *, Ȼ���char *ת��string,������ȷ�ıȽϳ������ַ���˳��
		CStringA szAtemp1, szAtemp2;
		szAtemp1 = szComp1;
		szAtemp2 = szComp2;
		char * szx1 = szAtemp1.GetBuffer();
		char * szx2 = szAtemp2.GetBuffer();
		string str1 = szx1;					//char*ת��Ϊstring
		string str2 = szx2;		

		iCompRes= str1.compare(str2);
		}
		break;
	case(1):
		//�Եڶ���Ϊ��������
		if(pInfo1->iAge == pInfo2->iAge)
			iCompRes = 0;
		else
			iCompRes=(pInfo1->iAge < pInfo2->iAge)?-1:1;
		break;
	default:
		ASSERT(0);
		break;
	}
	//���ݵ�ǰ������ʽ���е���
	if(pV->m_fAsc)
		return iCompRes;
	else
		return iCompRes*-1;
}
