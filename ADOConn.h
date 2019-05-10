// ADOConn.h: interface for the ADOConn class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ADOCONN_H__1DE0C08D_4F11_4F79_83A2_179662D1A4D3__INCLUDED_)
#define AFX_ADOCONN_H__1DE0C08D_4F11_4F79_83A2_179662D1A4D3__INCLUDED_
#import "C:\Program Files\Common Files\System\ado\msado15.dll"no_namespace no_namespace \
rename("EOF","adoEOF")rename("BOF","adoBOF")

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ADOConn  
{
public:
	//���һ��ָ��Connection�����ָ��
    _ConnectionPtr m_pConnection;
	//���һ��ָ��Recordset�����ָ��
	_RecordsetPtr m_pRecordset;

public:
	ADOConn();
	virtual ~ADOConn();

	//��ʼ��--�������ݿ�
    void OnInitADOConn();
	//ִ�в�ѯ
    _RecordsetPtr& GetRecordSet(_bstr_t bstrSQL);
	//ִ��SQL���
    BOOL ExecuteSQL(_bstr_t bstrSQL);
	//�Ͽ����ݿ�����
	void ExitConnect();
};

#endif // !defined(AFX_ADOCONN_H__1DE0C08D_4F11_4F79_83A2_179662D1A4D3__INCLUDED_)
