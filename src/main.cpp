#include "mbed.h"
#include "BME280.h"
#include "PinNames.h"
#include "MPU6050.h"

#define     DEVICE_STDIO_MESSAGES 0

// int main() {
//     while(1) {
//         pc.printf("%2.2f degC, %04.2f hPa, %2.2f %%\r\n \r\n", sensor.getTemperature(), sensor.getPressure(), sensor.getHumidity());
//         // if(sensor.getHumidity() && sensor.getPressure() && sensor.getTemperature()){
//             led = !led;
//             wait(0.5);
//              }
//     }

Serial      pc(SERIAL_TX, SERIAL_RX); // TX PA_2  , RX PA_3
DigitalOut  myled(LED1);   // on-board LED
I2C i2c(I2C_SDA,I2C_SCL);

#define bmeAddress 0x76
#define mpuAddress 0x68

BME280 bme(i2c, bmeAddress << 1);
MPU6050 mpu(I2C_SDA, I2C_SCL);

int address;


void bmeinit() 
{       
   if( i2c.write(bmeAddress << 1) == 1) {
        pc.printf("bme found");
        bme.initialize();
        }
}

void mpuInit(){
        if( i2c.write(mpuAddress << 1) == 1) {
        pc.printf("mpu found");
        }
}
//                 pc.printf("%f degC, %f hPa, %f %% \r\n \r\n", sensor.getTemperature() , sensor.getPressure(), sensor.getHumidity() );
//         }
// }

 //
int main()
{   
        pc.baud(115200);
    pc.printf("RUN\r\n");
    for(int i = 0; i < 128 ; i++) {
        i2c.start();
        i2c.frequency(100000);
        if( i2c.write(i << 1) == 1) /*return 0 if NAK was received, 1 if ACK was received, 2 for timeout*/ 
                {
                pc.printf("0x%x ACK \r\n",i); // Send command string
                } 
        i2c.stop();
    }
        mpu.setAcceleroRange(MPU6050_ACCELERO_RANGE_2G);
        while(1){
        pc.printf("%-10i X\t", mpu.getAcceleroRawX());
        pc.printf("%-10i Y\t", mpu.getAcceleroRawY());
        pc.printf("%-10i Z\r\n", mpu.getAcceleroRawZ());
        }


        // while(i2c.write(address << 1)){
        //         pc.printf("%f degC, %f hPa, %f %% \r\n \r\n", bme.getTemperature() , bme.getPressure(), bme.getHumidity() );
        // }
        
}

// 0x3c - display
//0x68 - mpu6050