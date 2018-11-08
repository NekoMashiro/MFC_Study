// AddDlg.cpp : ʵ���ļ�
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


// CAddDlg ���

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


// CAddDlg ��Ϣ�������


void CAddDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	//��ʼ����Ʒ�����б�������
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
	m_combo.SetCurSel(0);	///Ĭ��ѡ�е�һ����Ʒ
	OnCbnSelchangeCombo1(); //��ʼ��Ĭ��ѡ�еĵ�һ����Ʒ�ĵ���
}


void CAddDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);	//ȡ���ؼ��е�ֵ����������ȥ
	// �����ܵ�ʵ��
	if(m_num1<=0)
	{
		MessageBox(TEXT("��Ӹ�������С�ڵ���0"));
		return;
	}

	//����
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
			//
			it->num = it->num + m_num1;
			m_left1 = it->num;
			MessageBox(_T("��ӳɹ���"));
			file.WriteDocline();
		}	
	}

	//�������
	m_num1 = 0;
	UpdateData(FALSE);

}


void CAddDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//�������
	UpdateData(TRUE);
	m_num1 = 0;
	m_combo.SetCurSel(0);	///Ĭ��ѡ�е�һ����Ʒ
	OnCbnSelchangeCombo1();
	
	UpdateData(FALSE);
}


void CAddDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);	//ȡ���ؼ��е�ֵ����������ȥ
	// �����ܵ�ʵ��
	if(m_num2<=0)
	{
		MessageBox(TEXT("��Ӹ�������С�ڵ���0"));
		return;
	}
	if(m_price2<=0)
	{
		MessageBox(TEXT("�����Ʒ���۲���С�ڵ���0"));
		return;
	}
	if(m_name2.IsEmpty() || m_name2.GetLength()>8)
	{
		MessageBox(TEXT("�����Ʒ��Ϊ�ջ��߳��ȴ���8���ַ�"));
		return;
	}

	CInfoFile file;
	file.ReadDocline();
	file.Addline(m_name2, m_num2, m_price2);
	file.WriteDocline();
	MessageBox(TEXT("��ӳɹ���"));

	//ͬ����������Ʒ���������б���
	m_combo.InsertString(0,m_name2);
	m_combo.SetCurSel(0);
	OnCbnSelchangeCombo1();

	//������������
	m_name2.Empty();
	m_price2 = 0;
	m_num2 = 0;
	UpdateData(FALSE);
}


void CAddDlg::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//�������
	UpdateData(TRUE);	//�˾���Ϊ�˱���ס�� ��ߵ�m_num1 ��ӵĿ��ֵ����䶯
	m_name2.Empty();
	m_num2 = 0;
	m_price2 = 0;
	UpdateData(FALSE);
}


void CAddDlg::OnCbnSelchangeCombo1()	//�ؼ��е����ݱ��ı�ʱ���õķ���
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
			m_price1 = it->price;
			m_left1 = it->num;
			UpdateData(FALSE);	//������ֵ����ͬ�����ؼ���
		}

	}
}
