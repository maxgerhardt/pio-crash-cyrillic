//	Библиотека для работы с GSM/GPRS Shield A6: http://iarduino.ru/shop/Expansion-payments/gsm-gprs-shield.html
//  Версия: 1.0.1
//  Последнюю версию библиотеки Вы можете скачать по ссылке: http://iarduino.ru/file/345.html
//  Подробное описание функции бибилиотеки доступно по ссылке: https://wiki.iarduino.ru/page/gsm-gprs-shield/
//  Библиотека является собственностью интернет магазина iarduino.ru и может свободно использоваться и распространяться!
//  При публикации устройств или скетчей с использованием данной библиотеки, как целиком, так и её частей,
//  в том числе и в некоммерческих целях, просим Вас опубликовать ссылку: http://iarduino.ru
//  Автор библиотеки: Панькин Павел
//  Если у Вас возникли технические вопросы, напишите нам: shop@iarduino.ru

#ifndef iarduino_GSM_h
#define iarduino_GSM_h

#include "SoftwareSerial.h"

#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#define GSM_UART_SPEED		9600																					//	Скорость шины UART на которой требуется работать			(9600 бит/сек)
#define	GSM_TXT_CP866		0																						//	Название кодировки в которой написан текст.					(паремр функций TXTsendCoding() и TXTreadCoding() указывающий кодировку CP866)
#define	GSM_TXT_UTF8		1																						//	Название кодировки в которой написан текст.					(паремр функций TXTsendCoding() и TXTreadCoding() указывающий кодировку UTF8)
#define	GSM_TXT_WIN1251		2																						//	Название кодировки в которой написан текст.					(паремр функций TXTsendCoding() и TXTreadCoding() указывающий кодировку WIN1251)
#define	GSM_SMS_CLASS_0		0																						//	Класс отправляемых SMS сообщений.							(паремр функции SMSsendClass() указывающий что отправляются SMS класса 0)
#define	GSM_SMS_CLASS_1		1																						//	Класс отправляемых SMS сообщений.							(паремр функции SMSsendClass() указывающий что отправляются SMS класса 1)
#define	GSM_SMS_CLASS_2		2																						//	Класс отправляемых SMS сообщений.							(паремр функции SMSsendClass() указывающий что отправляются SMS класса 2)
#define	GSM_SMS_CLASS_3		3																						//	Класс отправляемых SMS сообщений.							(паремр функции SMSsendClass() указывающий что отправляются SMS класса 3)
#define	GSM_SMS_CLASS_NO	4																						//	Класс отправляемых SMS сообщений.							(паремр функции SMSsendClass() указывающий что отправляются SMS без класса)
#define GSM_OK				0																						//	Статус GSM - без ошибок.									(возвращается функцией CALLstatus / status если ошибки не обнаружены и модуль готов к работе)
#define GSM_SPEED_ERR		1																						//	Не удалось согласовать скорость UART.						(возвращается функцией     status если в функции _begin был сброшен флаг flgSpeed)
#define GSM_UNAVAILABLE		2																						//	Статус GSM - модуль недоступен (AT-команды не выполняются).	(возвращается функцией     status если на команду "AT+CPAS"  пришел ответ "+CPAS:1"       )
#define GSM_UNKNOWN			3																						//	Статус GSM - неизвестен (AT-команды могут не выполнятся).	(возвращается функцией     status если на команду "AT+CPAS"  пришел ответ "+CPAS:2"       )
#define GSM_SLEEP			4																						//	Статус GSM - модуль режиме ограниченной функциональности.	(возвращается функцией     status если на команду "AT+CPAS"  пришел ответ "+CPAS:5"       )
#define GSM_SIM_PIN			5																						//	Требуется ввод PIN1 (CHV1).									(возвращается функцией     status если на команду "AT+CPIN?" пришел ответ "+CPIN:SIM PIN" )
#define GSM_SIM_PUK			6																						//	Требуется ввод PUK1 и новый PIN1.							(возвращается функцией     status если на команду "AT+CPIN?" пришел ответ "+CPIN:SIM PUK" )
#define GSM_SIM_PIN2		7																						//	Требуется ввод PIN2 (CHV2).									(возвращается функцией     status если на команду "AT+CPIN?" пришел ответ "+CPIN:SIM PIN2")
#define GSM_SIM_PUK2		8																						//	Требуется ввод PUK2 и новый PIN2.							(возвращается функцией     status если на команду "AT+CPIN?" пришел ответ "+CPIN:SIM PUK2")
#define GSM_SIM_NO			9																						//	Нет SIM-карты.												(возвращается функцией     status если на команду "AT+CPIN?" пришел ответ "+CME ERROR:10" )
#define GSM_SIM_FAULT		10																						//	SIM-карта неисправна.										(возвращается функцией     status если на команду "AT+CPIN?" пришел ответ "+CME ERROR:13" )
#define GSM_SIM_ERR			11																						//	Неопределённое состояние SIM-карты.							(возвращается функцией     status если на команду "AT+CPIN?" пришел ответ не "+CPIN:READY")
#define GSM_REG_NO			12																						//	Модем не зарегистрирован в сети оператора.					(возвращается функцией     status если на команду "AT+CREG?" пришел ответ где второй параметр равен 0, 2 или равен значению отсутствующему в документации.
#define GSM_REG_FAULT		13																						//	Регистрация модема в сети оператора отклонена.				(возвращается функцией     status если на команду "AT+CREG?" пришел ответ где второй параметр равен 3
#define GSM_REG_ERR			14																						//	Статус регистрации модема в сети оператора не читается.		(возвращается функцией     status если на команду "AT+CREG?" пришел ответ без символов "+CREG".
#define GSM_CALL_ACTIVE		1																						//	Состояние вызова - активное голосовое соединение.			(возвращается функцией CALLstatus если на команду "AT+CLCC"  пришел список текущих вызовов среди которых есть актывный)
#define GSM_CALL_HELD		2																						//	Состояние вызова - удерживаемый.							(возвращается функцией CALLstatus если на команду "AT+CLCC"  пришел список текущих вызовов среди которых есть удерживаемый)
#define GSM_CALL_END		3																						//	Состояние вызова - разъединение.							(возвращается функцией CALLstatus если на команду "AT+CLCC"  пришел список текущих вызовов среди которых есть разъединяенмый)
#define GSM_CALL_OUT_DIAL	4																						//	Состояние вызова - исходящий в режиме набора адреса.		(возвращается функцией CALLstatus если на команду "AT+CLCC"  пришел список текущих вызовов среди которых есть исходящий набираемый)
#define GSM_CALL_OUT_BEEP	5																						//	Состояние вызова - исходящий в режиме дозвона.				(возвращается функцией CALLstatus если на команду "AT+CLCC"  пришел список текущих вызовов среди которых есть исходящий дозванивающийся)
#define GSM_CALL_IN_BEEP	6																						//	Состояние вызова - входящий  в режиме дозвона.				(возвращается функцией CALLstatus если на команду "AT+CLCC"  пришел список текущих вызовов среди которых есть входящий дозванивающийся)
#define GSM_CALL_IN_WAIT	7																						//	Состояние вызова - входящий  в режиме ожидания.				(возвращается функцией CALLstatus если на команду "AT+CLCC"  пришел список текущих вызовов среди которых есть входящий ожидающий)
#define GSM_CALL_ERR		8																						//	Состояние вызова - неопределено.							(возвращается функцией CALLstatus если на команду "AT+CLCC"  пришел список текущих вызовов среди которых есть не описанный в докуметации)
#define GSM_HEADSET			0																						//	Звук принимается/передаётся с гарнитуры						(паремр функций SOUNDdevice() указывающий использовать наушники и микрофон гарнитуры)
#define GSM_SPEAKER			1																						//	Звук принимается/передаётся по громкой связи				(паремр функций SOUNDdevice() указывающий использовать динамик и микрофон подключённые к штыревым выводам на плате)
#define GSM_MICROPHONE		2																						//	Звук передаётся с микрофона громкой связи					(паремр функций SOUNDdevice() указывающий использовать только микрофон подключённый к штыревым выводам на плате)

																													//	
class iarduino_GSM{																									//	
																													//	
	public:			iarduino_GSM			(uint8_t=9);															//	Объявляем  конструктор класса								(аргумент функции: № вывода к которому подключён вход PWR модуля)
		bool		begin					(HardwareSerial &i){flgType=0; objSerial=&i; return _begin();}			//	Определяем функцию инициализации модуля						(аргумент функции: объект для работы с аппаратным UART)
		bool		begin					(SoftwareSerial &i){flgType=1; objSerial=&i; return _begin();}			//	Определяем функцию инициализации модуля						(аргумент функции: объект для работы с программным UART)
		String		runAT					(const char*, uint32_t=200, bool=true);									//	Объявляем  функцию выполнения AT-команд						(аргумент функции: строка с АТ-командой,  таймаут в миллисекундах, флаг разрешающий досрочный выход при ответе "\r\nOK\r\n" или "ERROR")
		String		runAT					(String,      uint32_t=200, bool=true);									//	Объявляем  функцию выполнения AT-команд						(аргумент функции: строка с АТ-командой,  таймаут в миллисекундах, флаг разрешающий досрочный выход при ответе "\r\nOK\r\n" или "ERROR")
		String		runUSSD					(const char*, uint32_t=10000);											//	Объявляем  функцию выполнения USSD-запроса					(аргумент функции: строка с USSD-запросом, таймаут в миллисекундах)
		String		runUSSD					(String,      uint32_t=10000);											//	Объявляем  функцию выполнения USSD-запроса					(аргумент функции: строка с USSD-запросом, таймаут в миллисекундах)
		void		pwr						(bool);																	//	Объявляем  функцию вкл/выкл модуля							(аргумент функции: флаг true/false)
		void		reset					(void){pwr(false); delay(2000); pwr(true);}								//	Определяем функцию перезагрузки модуля						(без аргументов)
		uint8_t		status					(void);																	//	Объявляем  функцию получения состояния GSM					(без аргументов)
		bool		pin						(const char*);															//	Объявляем  функцию для ввода pin-кода						(аргумент функции: строка с pin-кодом)
		bool		pin						(String);																//	Объявляем  функцию для ввода pin-кода						(аргумент функции: строка с pin-кодом)
		bool		puk						(const char*, const char*);												//	Объявляем  функцию для ввода puk-кода и нового pin-кода		(аргумент функции: строка с puk-кодом, строка с новым pin-кодом)
		bool		puk						(String,      const char*);												//	Объявляем  функцию для ввода puk-кода и нового pin-кода		(аргумент функции: строка с puk-кодом, строка с новым pin-кодом)
		bool		puk						(const char*, String     );												//	Объявляем  функцию для ввода puk-кода и нового pin-кода		(аргумент функции: строка с puk-кодом, строка с новым pin-кодом)
		bool		puk						(String,      String     );												//	Объявляем  функцию для ввода puk-кода и нового pin-кода		(аргумент функции: строка с puk-кодом, строка с новым pin-кодом)
		uint8_t		signal					(void);																	//	Объявляем  функцию получения уровня сигнала					(без аргументов)
		uint8_t		SMSavailable			(void);																	//	Объявляем  функцию проверки наличия принятых SMS			(без аргументов)
		uint8_t		SMSmax					(void);																	//	Объявляем  функцию получения объема памяти SMS				(без аргументов)
		bool		SMSread					(char*);																//	Объявляем  функцию для чтения самой ранней одной SMS		(аргумент функции: указатель на строку для получения текста)
		bool		SMSread					(char*, char*);															//	Объявляем  функцию для чтения самой ранней одной SMS		(аргумент функции: указатель на строку для получения текста, указатель на строку для получения номера)
		bool		SMSread					(char*, char*, char*);													//	Объявляем  функцию для чтения самой ранней одной SMS		(аргумент функции: указатель на строку для получения текста, указатель на строку для получения номера, указатель на строку для получения даты)
		bool		SMSread					(char*, char*, char*, uint16_t&, uint8_t&, uint8_t&);					//	Объявляем  функцию для чтения самой ранней одной SMS		(аргумент функции: указатель на строку для получения текста, указатель на строку для получения номера, указатель на строку для получения даты, ссылка для получения идентификатора SMS, ссылка для получения количества SMS,  ссылка для получения номера SMS)
		bool		SMSsend					(const char*, const char*, uint16_t=0, uint8_t=1, uint8_t=1);			//	Объявляем  функцию для чтения самой ранней одной SMS		(аргумент функции: текст,                                    номер,                                                                            идентификатор составного SMS сообщения,  количество SMS в составном сообщении, номер SMS в составном сообщении)
		bool		SMSsend					(String,      const char*, uint16_t=0, uint8_t=1, uint8_t=1);			//	Объявляем  функцию для отправки SMS							(аргумент функции: текст,                                    номер,                                                                            идентификатор составного SMS сообщения,  количество SMS в составном сообщении, номер SMS в составном сообщении)
		bool		SMSsend					(const char*, String,      uint16_t=0, uint8_t=1, uint8_t=1);			//	Объявляем  функцию для отправки SMS							(аргумент функции: текст,                                    номер,                                                                            идентификатор составного SMS сообщения,  количество SMS в составном сообщении, номер SMS в составном сообщении)
		bool		SMSsend					(String,      String,      uint16_t=0, uint8_t=1, uint8_t=1);			//	Объявляем  функцию для отправки SMS							(аргумент функции: текст,                                    номер,                                                                            идентификатор составного SMS сообщения,  количество SMS в составном сообщении, номер SMS в составном сообщении)
		void		SMSsendClass			(uint8_t cls){clsSMSsend=cls;}											//	Определяем функцию указания класса    отправляемых SMS		(аргумент функции: класс SMS сообщения GSM_SMS_CLASS_0 / GSM_SMS_CLASS_1 / GSM_SMS_CLASS_2 / GSM_SMS_CLASS_3 / GSM_SMS_CLASS_NO )
		void		TXTsendCoding			(uint8_t cod){codTXTsend=cod;}											//	Определяем функцию указания кодировки отправляемых SMS		(аргумент функции: кодировка GSM_TXT_CP866 / GSM_TXT_UTF8 / GSM_TXT_WIN1251 )
		void		TXTreadCoding			(uint8_t cod){codTXTread=cod;}											//	Определяем функцию указания кодировки получаемых   SMS		(аргумент функции: кодировка GSM_TXT_CP866 / GSM_TXT_UTF8 / GSM_TXT_WIN1251 )
		void		TXTsendCodingDetect		(const char*);															//	Объявляем  функцию для автоопределения кодировки скетча		(аргумент функции: строка состоящая из символа 'п' и символа конца строки.)
		uint8_t		CALLstatus				(void);																	//	Объявляем  функцию получения состояния голосовых вызовов	(без аргументов)
		bool		CALLavailable			(void);																	//	Объявляем  функцию проверки наличия входящих вызов			(без аргументов)
		bool		CALLavailable			(char*);																//	Объявляем  функцию проверки наличия входящих вызов			(аргумент функции: указатель на строку для получения адреса (номера) вызывающего абонента)
		void		CALLup					(void);																	//	Объявляем  функцию поднятия трубки (ответ на вх. вызов)		(без аргументов)
		void		CALLend					(void);																	//	Объявляем  функцию опускания трубки (завершение вызова)		(без аргументов)
		bool		CALLdial				(const char*);															//	Объявляем  функцию инициализации исходящего голос. вызова	(аргумент функции: строка с номером абонента)
		bool		CALLdial				(String);																//	Объявляем  функцию инициализации исходящего голос. вызова	(аргумент функции: строка с номером абонента)
		uint8_t		SOUNDdevice				(uint8_t=255);															//	Объявляем  функцию выбора устройства ввода/вывода звука		(аргумент функции: устройство GSM_HEADSET / GSM_SPEAKER / GSM_MICROPHONE / без аргумента - получить выбранное устройство)
		uint8_t		SOUNDvolume				(uint8_t=255);															//	Объявляем  функцию установки громкости звука				(аргумент функции: громкость от 0-нет до 7-макс / без аргументов - получить значение громкости)
		bool		SOUNDmute				(bool);																	//	Объявляем  функцию отключения микрофона						(аргумент функции: флаг true-отключить / false-не отключать)
		bool		SOUNDmute				(void);																	//	Объявляем  функцию проверки отключения микрофона			(без аргументов)
																													//	
	private:																										//	
		bool		_begin					(void);																	//	Объявляем  функцию инициализации модуля						(без аргументов)
		uint8_t		_num					(char);																	//	Объявляем  функцию преобразования символа в число			(аргумент функции: символ 0-9,a-f,A-F)
		char		_char					(uint8_t);																//	Объявляем  функцию преобразования числа в символ			(аргумент функции: число 0-15)
		uint8_t		_SMSsum					(void);																	//	Объявляем  функцию для получения кол SMS в памяти			(без аргументов)
		uint16_t	_SMStxtLen				(const char*);															//	Объявляем  функцию получения количества символов в строке	(строка с текстом)
		uint16_t	_SMScoderGSM			(const char*, uint16_t, uint16_t=255);									//	Объявляем  функцию кодирования текста в GSM в strBuffer		(строка с текстом,  позиция взятия из строки,     количество кодируемых символов)		Функция возвращает позицию после последнего закодированного символа из строки txt.
		void		_SMSdecodGSM			(      char*, uint16_t, uint16_t, uint16_t=0);							//	Объявляем  функцию разкодирования текста GSM из strBuffer	(строка для текста, количество символов в тексте, позиция начала текста в строке strBuffer, количество байт занимаемое заголовком)
	//	uint16_t	_SMScoder8BIT			(const char*, uint16_t, uint16_t=255);									//	Объявляем  функцию кодирования текста в 8BIT в strBuffer	(строка с текстом,  позиция взятия из строки,     количество кодируемых символов)		Функция возвращает позицию после последнего закодированного символа из строки txt.
		void		_SMSdecod8BIT			(      char*, uint16_t, uint16_t);										//	Объявляем  функцию разкодирования текста 8BIT из strBuffer	(строка для текста, количество байт в тексте,     позиция начала текста в строке strBuffer)
		uint16_t	_SMScoderUCS2			(const char*, uint16_t, uint16_t=255);									//	Объявляем  функцию кодирования текста в UCS2 в strBuffer	(строка с текстом,  позиция взятия из строки,     количество кодируемых символов)		Функция возвращает позицию после последнего закодированного символа из строки txt.
		void		_SMSdecodUCS2			(      char*, uint16_t, uint16_t);										//	Объявляем  функцию разкодирования текста UCS2 из strBuffer	(строка для текста, количество байт в тексте,     позиция начала текста в строке strBuffer)
		void		_SMScoderAddr			(const char*);															//	Объявляем  функцию кодирования адреса SMS в strBuffer		(строка с адресом)
		void		_SMSdecodAddr			(      char*, uint16_t, uint16_t);										//	Объявляем  функцию разкодирования адреса SMS из strBuffer	(строка для адреса, количество полубайт в адресе, позиция адреса  в строке strBuffer)
		void		_SMSdecodDate			(      char*,           uint16_t);										//	Объявляем  функцию разкодирования даты SMS из strBuffer		(строка для даты,                                 позиция даты    в строке strBuffer)
		uint8_t		pinPWR;																							//	Объявляем  переменную для хранения номера вывода PRR		(число)
		bool		flgType;																						//	Объявляем  флаг указывающий на тип соединения				(0-HardwareSerial, 1-SoftwareSerial)
		bool		flgSpeed;																						//	Объявляем  флаг указывающий на согласование скорости		(true/false)
		void*		objSerial;																						//	Объявляем  указатель на объект работы с UART				(Serial, Serial1, ..., SoftwareSerial)
		String		strBuffer;																						//	Объявляем  строку для работы с текстовыми данными			(массив)
		uint8_t		numSMS;																							//	Объявляем  переменную для хранения № прочитанной SMS		(число)
		uint8_t		maxSMS;																							//	Объявляем  переменную для хранения объема памяти SMS		(число)
		uint8_t		codTXTread =			GSM_TXT_UTF8;															//	Тип кодировки строки StrIn.
		uint8_t		codTXTsend =			GSM_TXT_UTF8;															//	Тип кодировки строки StrIn.
		uint8_t		clsSMSsend =			GSM_SMS_CLASS_NO;														//	Класс отправляемых SMS сообщений.
																													//	
};

#endif