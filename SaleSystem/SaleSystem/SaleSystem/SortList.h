#pragma once
#include "afxcmn.h"
class CSortList: public CListCtrl
{
public:
	CSortList(void);

	BOOL m_fAsc;		//是否顺序排序
	int m_nSortedCol;	//当前排序的列


	~CSortList(void);
};

