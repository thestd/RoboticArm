#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

// Налаштування
#define SERIAL_SPEED     115200  // Швидкість послідовного порту
#define SENDING_INTERVAL 10      // Інтервал між надсиланнями даних в послідовний порт


// Об'єкти класів та змінні
Adafruit_MPU6050 mpu;
sensors_event_t a, g, temp;
uint32_t lastSendTime = 0;


void setup()
{
	// Ініціалізація послідовного порту
	Serial.begin(SERIAL_SPEED);

    // Ініціалізація гіроакселерометра
	if (!mpu.begin())
	{   
        // У випадку помилки програма залишиться у вічному циклі і не пройде далі
		Serial.println("Failed to find MPU6050 chip");
		while (1)
		{
			delay(10);
		}
	}

  	mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
	mpu.setGyroRange(MPU6050_RANGE_2000_DEG);
	mpu.setFilterBandwidth(MPU6050_BAND_260_HZ);
	delay(100);
}


void loop()
{
    // Перевіряємо, чи пройшла потрібна кількість часу перед надсиланням
	if((millis() - lastSendTime) >= SENDING_INTERVAL) {

        // Отримуємо останні дані від гіроакселерометра
		mpu.getEvent(&a, &g, &temp);

        // Надсилаємо дані в послідовний порт
		Serial.print(a.acceleration.x); 
		Serial.print(",");
		Serial.print(a.acceleration.y);
		Serial.print(",");
		Serial.print(a.acceleration.z);
		Serial.print(",");
		Serial.print(g.gyro.x);
		Serial.print(",");
		Serial.print(g.gyro.y);
		Serial.print(",");
		Serial.print(g.gyro.z);
		Serial.println();

		// Фіксуємо час, коли відбулось надсилання
		lastSendTime = millis();
	}
}