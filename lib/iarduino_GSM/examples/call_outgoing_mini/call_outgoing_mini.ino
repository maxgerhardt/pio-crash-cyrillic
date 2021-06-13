//  Данный пример демонстрирует совершение исходящего голосового вызова:
//  ==========================================================================================
    #include <iarduino_GSM.h>                                                                 // Подключаем библиотеку iarduino_GSM для работы с GSM/GPRS Shield.
    iarduino_GSM gsm;                                                                         // Создаём объект gsm для работы с функциями и методами библиотеки iarduino_GSM.
                                                                                              //
//  Следующие 2 строки нужны для работы по программной шине UATR (выводы 7 и 8):              //
    #include <SoftwareSerial.h>                                                               // Подключаем библиотеку SoftwareSerial для программной реализации шины UART.
    SoftwareSerial softSerial(7,8);                                                           // Создаём объект softSerial указывая выводы RX и TX платы Arduino.
//  Если Вы работаете c GSM/GPRS Shield по аппаратной шине UATR, удалите 2 предыдущие строки, //
//  а в функции gsm.begin(), вместо softSerial укажите Serial или Serial1, Serial2 ...        // Зависит от номера аппаратной шины UART использующей выводы 0 и 1 Вашей платы Arduino.
                                                                                              //
void setup(){                                                                                 //
//  Выводим текст в монитор последовательного порта:                                          //
    Serial.begin(9600);                                                                       // Инициируем передачу данных по аппаратной шине UART для вывода результата в монитор последовательного порта.
    Serial.print( F("Initialization, please wait ... ") );                                    // Выводим текст.
                                                                                              //
//  Инициируем GSM/GPRS Shield и проверяем его готовность к работе:                           //
    gsm.begin(softSerial);                                                                    // Инициируем работу GSM/GPRS Shield, указывая объект шины UART.
    while(gsm.status()!=GSM_OK){Serial.print("."); delay(1000);} Serial.println(" OK!");      // Ждём завершения регистрации модема в сети оператора связи.
    Serial.println( F("--------------------") );                                              //
                                                                                              //
//  Инициируем исходящий вызов на указанный ниже номер:                                       // Номер можно указывать со знаком плюс ("+70123456789") или указывать короткие номера (например, "0525" - голосовая почта beeline).
    if(gsm.CALLdial( "70123456789" )){                                                        // Если исходящий вызов на номер +7(012)345-67-89 инициирован, то...
        Serial.println( "Dialing ..." );                                                      //
    }else{                                                                                    //
        Serial.println( "Error!" );                                                           //
    }                                                                                         //
}                                                                                             //
                                                                                              //
void loop (){                                                                                 // В данном скетче вызов не осуществляется в цикле loop, для экономии Ваших средств на счёте.
}                                                                                             //
                                                                                              //
/*  Примечание:
 *  ==========================================================================================
 *  Перед загрузкой данного скетча измените номер телефона вызываемого абонента !!!
 *  ==========================================================================================
 *  Номер телефона можно указывать как с символом +, так и без него, а так же можно указывать короткие номера.
 *  Вызов осуществляется функцией CALLdial(), после чего выполняются: набор номера, дозвон и соединение, которые не отслеживаются в данном скетче, см. пример call_outgoing.
 *  Если соединение будет разорвано во время набора или отклонено отвечающей стороной во время дозвона, то возможна установка голосового соединения с оператором для отправки голосового сообщения.
 *  Во время разговора используется громкая связь, для переключения на гарнитуру и обратно воспользуйтесь функцией SOUNDdevice(), см. пример all.
 */