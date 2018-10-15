
//--------------------------------------<                         axlib v1.1                             >-------------------------------------------
//--------------------------------------< Библиотека для работы с датчиком температуры и влажности SHT21 >-------------------------------------------
//--------------------------------------<           Кузнецов Алексей 2015 http://www.avrki.ru            >-------------------------------------------


#ifndef SHT21_H_
#define SHT21_H_

#if !defined(MAIN_INIT_H_)
#error "You must included (#include \"main_init.h\") befor use (#include <axlib/sht21.h>)."
#endif

//-------------------------------------------------------------------------
//							Макроопределения
//-------------------------------------------------------------------------

#define SHT21_WRITE	0x80
#define SHT21_READ	0x81

// Команды
#define TRIGER_T_MSU_HM		0xE3	// Выбор измерения температуры с прижатием SCL к нулю
#define TRIGER_RH_MSU_HM	0xE5	// Выбор измерения влажности с прижатием SCL к нулю
#define TRIGER_T_MSU_NHM	0xF3	// Выбор измерения температуры без прижатия SCL к нулю
#define TRIGER_RH_MSU_NHM	0xF5	// Выбор измерения влажности без прижатия SCL к нулю
#define WU_REGISTER			0xE6	// Запись в пользовательский регистр
#define RU_REGISTER			0xE7	// Чтение из пользовательского регистра
#define SOFT_RESET			0xFE	// Программный сброс датчика

// Паузы
#define PAUSE_TEMP			85		// Максимальный мериод отцифровки температуры
#define PAUSE_RH			29		// Максимальный период отцифровки влажности

#define SHT21_ERR			0xFF	// Код ошибки


// Формула вычисления температуры
#define TEMP_CALL(t)		(((175.72 * t)/65536) - 46.85)

// Формула расчета влажности
#define RH_CALL(rh)		(((125 * rh)/65536) - 6)


//-------------------------------------------------------------------------
//							Подключение файлов
//-------------------------------------------------------------------------
#include <axlib/type_var.h>
#include <axlib/i2c.h>

//-------------------------------------------------------------------------
//							Инициализация датчика
//-------------------------------------------------------------------------
BYTE sht21_init(void)
{
	_delay_ms(15);
	i2c_init();
	
	BYTE answer = NACK;
	
	i2c_start();
	// Передача  адреса микросхемы
	answer = i2c_send_byte(SHT21_READ);
	if(answer == NACK) return answer;
	i2c_stop();
	
	return answer;
}

//-------------------------------------------------------------------------
//							Получение температуры
//-------------------------------------------------------------------------

ADATA sht21_read_temp(void)
{
	BYTE answer = NACK;
	BYTE tempL = 0;
	BYTE tempH = 0;
	UWORD out = 0;
	
	i2c_start();
	// Передача адреса и бита на запись
	answer = i2c_send_byte(SHT21_WRITE);
	if(answer == NACK) return 201; //SHT21_ERR;
	
	// Передача команды на преобразование температуры
	answer = i2c_send_byte(TRIGER_T_MSU_NHM);
	if(answer == NACK) return 202; //SHT21_ERR;
	
	i2c_restart();
	
	// Передача адреса и бита на чтение
	answer = i2c_send_byte(SHT21_READ);
	if(answer == NACK) return 203; //SHT21_ERR;
	
	_delay_ms(PAUSE_TEMP);
	
	tempH = i2c_read_byte(ACK);
	tempL = i2c_read_byte(NACK);
	
	i2c_stop();
	
	out = (tempH << 8);
	out |= (tempL & 0xFC);
	
	return (ADATA)TEMP_CALL(out);
}

//-------------------------------------------------------------------------
//							Получение влажности
//-------------------------------------------------------------------------

BYTE sht21_read_rh(void)
{
	BYTE answer = NACK;
	BYTE rhL = 0;
	BYTE rhH = 0;
	UWORD out = 0;
	
	i2c_start();
	// Передача адреса и бита на запись
	answer = i2c_send_byte(SHT21_WRITE);
	if(answer == NACK) return 211; //SHT21_ERR;
	
	// Передача команды на преобразование влажности
	answer = i2c_send_byte(TRIGER_RH_MSU_NHM);
	if(answer == NACK) return 212; //SHT21_ERR;
	
	i2c_restart();
	
	// Передача адреса и бита на чтение
	answer = i2c_send_byte(SHT21_READ);
	if(answer == NACK) return 213; //SHT21_ERR;
	
	_delay_ms(PAUSE_RH);
	
	rhH = i2c_read_byte(ACK);
	rhL = i2c_read_byte(NACK);
	
	i2c_stop();
	
	out = (rhH << 8);
	out |= (rhL & 0xF0);
	
	return (BYTE)RH_CALL(out);
}

#endif /* SHT21_H_ */ 