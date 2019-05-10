// ADOConn.cpp: implementation of the ADOConn class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ADOConn.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ADOConn::ADOConn()
{

}

ADOConn::~ADOConn()
{

}

void ADOConn::OnInitADOConn()
{
//��ʼ��OLE/COM�⻷��
    ::CoInitialize(NULL);
	try
	{
		//����connection����
		m_pConnection.CreateInstance("ADODB.Connection");	   
		//���������ַ���
		_bstr_t strConnect="Provider=SQLOLEDB.1;Integrated Security=SSPI;Persist Security Info=False;Initial Catalog=vcjsdq;Data Source=.";
		//SERVER��UID,PWD�����ø���ʵ�����������
		m_pConnection->Open(strConnect,"","",adModeUnknown);
	}
	//��׽�쳣
	catch(_com_error e)
	{
		//��ʾ������Ϣ
		//AfxMessageBox(e.Description());
		MessageBox(NULL,"ERROR!","��׽�쳣��",MB_OK);
	}

}
_RecordsetPtr& ADOConn::GetRecordSet(_bstr_t bstrSQL)
{
	try
	{
		//�������ݿ⣬���connection����Ϊ�գ��������������ݿ�
		if(m_pConnection==NULL)
              OnInitADOConn();
		//������¼������
		m_pRecordset.CreateInstance(__uuidof(Recordset));
		//ȡ�ñ��еļ�¼
        m_pRecordset->Open(bstrSQL,m_pConnection.GetInterfacePtr(),
			adOpenDynamic,adLockOptimistic,adCmdText);
	}
    catch(_com_error e)
	{
		e.Description();
	}
	//���ؼ�¼��
	return m_pRecordset;
}

BOOL ADOConn::ExecuteSQL(_bstr_t bstrSQL)
{
_variant_t RecordsAffected;
	try
	{
		//�Ƿ����������ݿ�
        if(m_pConnection==NULL)
	     	OnInitADOConn();
		//connection�����Execute����(_bstr_t CommandText,
        //VARIANT * RecordsAffected,long Options)
		//����CommandText�������ַ���,ͨ����SQL����
		//����RecordsAffected�ǲ�����ɺ���Ӱ�������
		//����Options��ʾCommandText������,adCmdText-�ı�����,adCmdTable-����
		//adCmdStoredProc-�洢����,adCmdUnknown-δ֪
        m_pConnection->Execute(bstrSQL,NULL,adCmdText);
		return true;
	}
	catch(_com_error e)
	{
		e.Description();
		return false;
	}
}
void ADOConn::ExitConnect()
{
//�رռ�¼��������
    if(m_pRecordset!=NULL)
		m_pRecordset->Close();
	m_pConnection->Close();
	//�ͷŻ���
	::CoUninitialize();
}
//DEL _RecordsetPtr& ADOConn::GetRecordSet(_bstr_t bstrSQL)
//DEL {
//DEL     try
//DEL 	{
//DEL 		//�������ݿ⣬���connection����Ϊ�գ��������������ݿ�
//DEL 		if(m_pConnection==NULL)
//DEL               OnInitADOConn();
//DEL 		//������¼������
//DEL 		m_pRecordset.CreateInstance(__uuidof(Recordset));
//DEL 		//ȡ�ñ��еļ�¼
//DEL         m_pRecordset->Open(bstrSQL,m_pConnection.GetInterfacePtr(),
//DEL 			adOpenDynamic,adLockOptimistic,adCmdText);
//DEL 	}
//DEL     catch(_com_error e)
//DEL 	{
//DEL 		e.Description();
//DEL 	}
//DEL 	//���ؼ�¼��
//DEL 	return m_pRecordset;
//DEL }

//DEL void ADOConn::GetRecordSet()
//DEL {
//DEL 
//DEL }

//DEL void ADOConn::GetRecordSet(_bstr_t bstrSQL)
//DEL {
//DEL 
//DEL }


