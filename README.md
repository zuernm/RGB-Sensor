**RGB Sensor (ISL29125)**


**Setup**

    (for Raspberry Pi 3)
    
    SDA --> Pin 3
    SCL --> Pin 5
    
    enable I2C interface under raspi-config
    
    run: 
    make clean all

**Info**

    the i2c connection can be checked by installing:
    	apt-get install i2c-tools
    and running:
	i2cdetect -y 1
    the device address must be returned (0x44)

**Running**

    rgb_sensor --> return dominant color (1 for Red, 2 for Green, 3 for Blue, 0 undefined)
    rgb_sensor print --> prints out the values of each color reading
    rgb_sensor loop --> returns the dominant color every 1 second


