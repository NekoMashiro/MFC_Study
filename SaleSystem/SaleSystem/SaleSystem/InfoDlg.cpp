// InfoDlg.cpp : ʵ���ļ�
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

void CInfoDlg::OnInitialUpdate()	///��ʼ���Ի���
{
	CFormView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���

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
		i++;
	}
	
}

//�������������ͷ����¼�
void CInfoDlg::OnLvnColumnclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	//��������ʽ
	if( pNMListView->iSubItem == m_list.m_nSortedCol )
		m_list.m_fAsc = !m_list.m_fAsc;
	else
	{
		m_list.m_fAsc = TRUE;
		m_list.m_nSortedCol = pNMListView->iSubItem;
	}
	//����������
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
			//�Ե�1��Ϊ��������,���������򷨣�
			if(num1 == num2)
				iCompRes = 0;
			else
				iCompRes=(num1 < num2)?-1:1;
		}
		break;
	case(1):
		{
			//�Ե�2��Ϊ��������
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
	//���ݵ�ǰ������ʽ���е���
	if(pV->m_fAsc)
		return iCompRes;
	else
		return iCompRes*-1;
}
