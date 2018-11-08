// DelDlg.cpp : ʵ���ļ�
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


// CDelDlg ���

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


// CDelDlg ��Ϣ�������


void CDelDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	//��ȡ�ļ�����ȡ��Ʒ��Ϣ������Ͽ��������Ʒ�����ַ�����
	CInfoFile file;
	file.ReadDocline();
	for(list<msg>::iterator it = file.ls.begin(); it!=file.ls.end(); it++)
	{
		m_combo.AddString((CString)it->name.c_str());
	}
	m_combo.SetCurSel(0);
	OnCbnSelchangeCombo1();	//���µ�һ����Ʒ��������ݣ����ۣ�
}


void CDelDlg::OnCbnSelchangeCombo1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������;
	//�л���Ʒʱ���ؼ����ݷ����ı��ʱ�򱻵���
	//�Ȼ�ȡ��Ʒ������
	int index = m_combo.GetCurSel();
	//����������ȡ�����������
	CString name;
	m_combo.GetLBText(index, name);

	//������Ʒ�����ƣ���ȡ����Ʒ�ĵ��ۺͿ�棬������ʾ���ؼ���ȥ
	CInfoFile file;
	file.ReadDocline();

	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if(CString(it->name.c_str()) == name)
		{
			m_left = it->num;
			m_price = it->price;
			UpdateData(FALSE);	//������ֵ����ͬ�����ؼ���
		}
	}

}


void CDelDlg::OnBnClickedButton1()
{
	UpdateData();
	// ɾ�����ܵ�ʵ��
	if(m_num<=0)
	{
		MessageBox(TEXT("ɾ����������С�ڵ���0"));
		return;
	}
	if(m_num>=m_left)
	{
		MessageBox(TEXT("ɾ���������ܴ��ڵ��ڿ������"));
		return;
	}

	//ɾ��
	//��ȡ�������Ҫ�������Ʒ����
	CString name;
	int index = m_combo.GetCurSel();
	m_combo.GetLBText(index, name);

	CInfoFile file;
	file.ReadDocline();
	for(list<msg>::iterator it=file.ls.begin(); it != file.ls.end(); it++)
	{
		if((CString)it->name.c_str() == name)
		{
			//ͬ�������ؼ���
			m_left = it->num - m_num;	//ԭ���Ŀ����-��Ҫɾ���Ŀ����
			it->num = m_left;
			//�����û������ɾ����Ϣ
			CString str;
			str.Format(_T("��Ʒ����%s \r\nɾ��������%d \r\n���ۣ�%d \r\n \r\nɾ���ɹ��� "),name, m_num, m_price);
			file.WriteDocline();
			MessageBox(str);
		}	
	}

	//�������
	m_num = 0;
	UpdateData(FALSE);
}


void CDelDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//�������
	m_num = 0;
	m_combo.SetCurSel(0);
	OnCbnSelchangeCombo1();	//���µ�һ����Ʒ��������ݣ����ۣ�
	UpdateData(FALSE);
}
