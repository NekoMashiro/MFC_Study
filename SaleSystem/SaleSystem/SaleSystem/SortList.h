#pragma once
#include "afxcmn.h"
class CSortList: public CListCtrl
{
public:
	CSortList(void);

	BOOL m_fAsc;		//�Ƿ�˳������
	int m_nSortedCol;	//��ǰ�������


	~CSortList(void);
};

