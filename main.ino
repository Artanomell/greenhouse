#include <LiquidCrystal_I2C.h> // подключаем библиотеку дисплея
LiquidCrystal_I2C lcd(0x27, 16, 2); // адрес, столбцов, строк
#include <GyverBME280.h>
GyverBME280 bme;
boolean butt_flag = 0;
boolean butt;
boolean rele_flag = 1;
byte a = 1;
void setup() {

pinMode(5, INPUT_PULLUP); // указываем пин, подтяжка сопротивления
pinMode(6, OUTPUT); // объявление пина на выход для реле
Serial.begin(9600); // открываем порт для связи
Serial.println("Start");

// запуск датчика и проверка на работоспособность
if (!bme.begin(0x76)) Serial.println("Error!");
lcd.init(); // инициализация
lcd.backlight(); // включить подсветку

}
void loop() {
butt = !digitalRead(5);
if (butt == 1 && butt_flag == 0) {
butt_flag = 1;
}
if (butt == 0 && butt_flag == 1) {
butt_flag = 0;
}
if (butt_flag == 1) a++;
if (a > 3) a = 1;
else a = a;
if (bme.readTemperature() > 28 && rele_flag == 0) {
rele_flag = !rele_flag;
digitalWrite (6, !rele_flag);
}
if (bme.readTemperature() < 25 && rele_flag == 1) {
rele_flag = !rele_flag;
digitalWrite (6, !rele_flag);
}
Serial.println(butt);
Serial.println(butt_flag);
Serial.println(a);
// температура
//Serial.print("Temperature: ");
//Serial.println(bme.readTemperature());
// влажность
//Serial.print("Humidity: ");
//Serial.println(bme.readHumidity());
// давление
//Serial.print("Pressure: ");
//Serial.println(bme.readPressure());
Serial.println();
delay(500); // ждём ответа
switch (a) {
case 1:
lcd.home(); // курсор в 0,0
lcd.print("T ");
lcd.print(bme.readTemperature()); // выводим температуру
lcd.write(223); // символ градуса
lcd.print("C "); // С и пара пробелов для очистки
break;
case 2:
lcd.home(); // курсор в 0,0
lcd.print("P ");
lcd.print(bme.readHumidity()); // выводим влажность
lcd.print("% "); // % и пара пробелов для очистки
break;
default:
lcd.home(); // курсор в 0,0
lcd.print("P ");
lcd.print((bme.readPressure()/133.3223684)); // выводим давление
lcd.print("mm Hg "); // mm Hg и пара пробелов для очистки
break;
}

}
