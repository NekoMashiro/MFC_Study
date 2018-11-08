// SellDlg.cpp : ʵ���ļ�
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


// CSellDlg ���

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


// CSellDlg ��Ϣ�������


void CSellDlg::OnBnClickedButton1()
{
	UpdateData(TRUE);
	// �����ܵ�ʵ��
	if(m_num<=0)
	{
		MessageBox(TEXT("�����������С�ڵ���0"));
		return;
	}
	if(m_num>m_left)
	{
		MessageBox(TEXT("����������ܴ��ڿ��"));
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
			//ͬ�������ؼ���
			it->num = m_left - m_num;
			m_left  = it->num;	//�ؼ��ϵĿ����
			//�����û�����Ĺ�����Ϣ
			CString str;
			str.Format(_T("��Ʒ����%s \r\n����������%d \r\n���ۣ�%d \r\n�ܼۣ�%d"),name, m_num, m_price, m_price*m_num);
			m_sellInfo = str;
			UpdateData(FALSE);
			MessageBox(_T("����ɹ���"));
		}	
	}

	file.WriteDocline();
	//�������
	m_num = 0;
	m_sellInfo.Empty();
	UpdateData(FALSE);

}


void CSellDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//�������
	m_num = 0;
	m_sellInfo.Empty();
	UpdateData(FALSE);
}


void CSellDlg::OnInitialUpdate()
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
	}
	m_combo.SetCurSel(0);	///Ĭ��ѡ�е�һ����Ʒ
	OnCbnSelchangeCombo1();	//���µ�һ����Ʒ��������ݣ����ۣ���棩
}


void CSellDlg::OnCbnSelchangeCombo1()
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
