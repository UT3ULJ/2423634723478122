
//------------------------------------------------<                   axlib v1.1                      >----------------------------------------------------
//------------------------------------------------<   ����� �������� ��� ������ � ����������� MH_BUS  >----------------------------------------------------
//------------------------------------------------<    �������� ������� 2015 http://www.avrki.ru      >----------------------------------------------------

#ifndef MHBUS_CONST_H_
#define MHBUS_CONST_H_

//-------------------------------------------------------------------------
//						�������
//-------------------------------------------------------------------------

#define MH_BUS_RE_ADD			0x21	// �������� ����� �������� ���������� � �������� �� �����.
										// ����� ���������� � ����� ��������. ��� �����������������
										// ��������, ����� �������� ������� ���������� �� ���������
										// ID, ������������ � ������ ���� ������.
#define MH_BUS_RETURN_T_1		0x22	// ������� �������� �����������. (������ ��� ������� ������ �������)
#define MH_BUS_RETURN_P_1		0x23	// ������� �������� ��������. (������ ��� ������� ������ �������)
#define MH_BUS_RESERV_0			0x24	// ������
#define MH_BUS_RESERV_1			0x25	// ������
#define MH_BUS_RESERV_2			0x26	// ������
#define MH_BUS_RESERV_3			0x27	// ������
#define MH_BUS_RESERV_4			0x28	// ������
#define MH_BUS_RESERV_5			0x29	// ������
#define MH_BUS_RETURN_ADD_PARAM	0x2A	// ������� �������� ������������� �� ������ ��������
#define MH_BUS_RETURN_ADD_DIS	0x2B	// ������� ������� ������������� �� ������ ��������
#define MH_BUS_RETURN_1_BYTE	0x2C	// ������� 1 ���� ������
#define MH_BUS_RETURN_2_BYTE	0x2D	// ������� 2 ����� ������
#define MH_BUS_RETURN_3_BYTE	0x2E	// ������� 3 ����� ������
#define MH_BUS_RETURN_4_BYTE	0x2F	// ������� 4 ����� ������
#define MH_BUS_RETURN_8_DIS		0x30	// ������� 8 ��������� (������ ����)
#define MH_BUS_RETURN_16_DIS	0x31	// ������� 16 ��������� (������ 2 �����)
#define MH_BUS_RETURN_24_DIS	0x32	// ������� 24 �������� (������ 3 �����)
#define MH_BUS_RETURN_32_DIS	0x33	// ������� 32 �������� (��� 4 �����)
#define MH_BUS_WRITE_ADD_PARAM	0x34	// �������� �������� ��������� � ������� �� ������
#define MH_BUS_WRITE_ADD_DIS	0x35	// �������� ������� � ������� �� ������
#define MH_BUS_WRITE_1_BYTE		0x36	// �������� 1 ���� ������
#define MH_BUS_WRITE_2_BYTE		0x37	// �������� 2 ����� ������
#define MH_BUS_WRITE_3_BYTE		0x38	// �������� 3 ����� ������
#define MH_BUS_WRITE_4_BYTE		0x39	// �������� 4 ����� ������
#define MH_BUS_WRITE_8_DIS		0x3A	// �������� 8 ��������� (������ ����)
#define MH_BUS_WRITE_16_DIS		0x3B	// �������� 16 ��������� (������ 2 �����)
#define MH_BUS_WRITE_24_DIS		0x3C	// �������� 24 �������� (������ 3 �����)
#define MH_BUS_WRITE_32_DIS		0x3D	// �������� 32 �������� (��� 4 �����)

//-------------------------------------------------------------------------
//						���� ������ �� ����
//-------------------------------------------------------------------------

#define MH_BUS_STOP_FAIL	0x01	// ����� ���� ����
#define MH_BUS_CON_SUM_FAIL	0x02	// ������������ ����������� �����
#define MH_BUS_COM_FAIL		0x03	// ������������ �������
#define MH_BUS_NO_REG		0x04	// ���������� � ������ �������������� ��������
#define MH_BUS_DAT_FAIL		0x05	// ������������� ������� � �������
#define MH_BUS_NO_WR		0x06	// ���������� �������� ������
#define MH_BUS_ERR_ALL		0x07	// �������� ������ � ������������ ������
#define MH_BUS_START_FAIL	0x08	// ����� ����� ����
#define MH_BUS_MOD_FAIL		0x09	// ������ �� �������� (�� ��������)
#define MH_BUS_MOD_ADD		0x0A	// ������������ ������
#define MH_BUS_ADD_OVF		0x0B	// ����� ��� ���������
#define MH_BUS_ADD_FAIL		0x0C	// ����� �� ���������
#define MH_BUS_ERR_ID		0x0D	// ������������ ID ���������� � ������������ �� �������
#define MH_BUS_FAIL_DATA	0x0E	// ����� �����

//-------------------------------------------------------------------------
//						����������� ����
//-------------------------------------------------------------------------

#define MH_BUS_ALL_ADD		0x00	// ����� �������������
#define MH_BUS_START_BYTE	0xAA	// ����� ����
#define MH_BUS_STOP_BYTE	0x55	// ���� ����

#define MH_BUS_OK			0x20	// ��

#endif /* MHBUS_CONST_H_ */