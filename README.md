**RGB Sensor (ISL29125)**


**Setup**

    (for Raspberry Pi 3)
    
    SDA --> Pin 3
    SCL --> Pin 5
    
    enable I2C interface under raspi-config
    
**Running**

    rgb_sensor --> return dominant color (1 for Red, 2 for Green, 3 for Blue, 0 undefined)
    rgb_sensor print --> prints out the values of each color reading
    rgb_sensor loop --> returns the dominant color every 10 seconds