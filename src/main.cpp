#include "mbed.h"
#include "BME280.h"

// Serial pc(USBTX, USBRX);
DigitalOut led(LED1);


BME280 sensor(I2C_SDA, I2C_SCL);


int main() {
    while(1) {
        // pc.printf("%2.2f degC, %04.2f hPa, %2.2f %%\n", sensor.getTemperature(), sensor.getPressure(), sensor.getHumidity());
        if(sensor.getHumidity() && sensor.getPressure() && sensor.getTemperature()){
             led = !led;
             }
        wait(0.5);
    }
}
