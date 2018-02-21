#include "Sensor.h"

#include <iostream>
#include <cstdio>

Sensor::Sensor(const char* i2c_dev):i2c_dev(i2c_dev){
    Sensor::init();
    Sensor::setConfig();
}

Sensor::~Sensor() {}

void Sensor::init()
{
    // OPEN BUS
    if ((file = open(i2c_dev, O_RDWR)) < 0) {
        /* ERROR HANDLING: you can check errno to see what went wrong */
        perror("Failed to open the i2c bus");    
    }
    // Connect to device   
    if (ioctl(file, I2C_SLAVE, ISL_I2C_ADDR) < 0) {
        perror("Failed to acquire bus access and/or talk to slave.\n");
        /* ERROR HANDLING; you can check errno to see what went wrong */        
    }    
    // Check if device ID is correct    
    unsigned char device_id = read8(ISL_DEVICE_ID);
    if (!(device_id==ISL_DEVICE_ID_VAL)){
        perror("Device not found");
    }
}

void Sensor::setConfig() {
    // Config 1
    write8(ISL_CONFIG_1, ISL_CFG1_MODE_RGB | ISL_CFG1_375LUX);
    // Config 2
    write8(ISL_CONFIG_2, ISL_CFG2_IR_ADJUST_HIGH);
    // Config 3
    write8(ISL_CONFIG_3, ISL_CFG_DEFAULT);
}

void Sensor::write8(unsigned char reg, unsigned char data) {
    unsigned char buffer[2] = {};
    buffer[0] = reg;
    buffer[1] = data;
    if (write(file, buffer, 2) != 2) {
        /* ERROR HANDLING: i2c transaction failed */
        perror("Failed to write byte to the i2c bus");
    }    
}

unsigned char Sensor::read8(unsigned char reg) {    
    if (write(file, &reg, 1) != 1) {
        /* ERROR HANDLING: i2c transaction failed */
        perror("Failed to write byte to the i2c bus");
    }    
    unsigned char byteBuffer;
    if (read(file, &byteBuffer, 1) != 1) {
        /* ERROR HANDLING: i2c transaction failed */
        perror("Failed to read byte from i2c bus");
    } else {
        return byteBuffer;
    } 
}

unsigned int Sensor::readRed() {
    unsigned int red_low = read8(ISL_RED_L);
    unsigned int red_high = read8(ISL_RED_H);
    unsigned int red = (red_high << 8) | red_low;    
    return red;
}

unsigned int Sensor::readGreen() {
    unsigned int green_low = read8(ISL_GREEN_L);
    unsigned int green_high = read8(ISL_GREEN_H);
    unsigned int green = (green_high << 8) | green_low;    
    return green;
}

unsigned int Sensor::readBlue() {
    unsigned int blue_low = read8(ISL_BLUE_L);
    unsigned int blue_high = read8(ISL_BLUE_H);
    unsigned int blue = (blue_high << 8) | blue_low;    
    return blue;
}

unsigned int Sensor::dominantColor(){
    unsigned int red, green, blue, mainColor;    
    red = readRed();
    green = readGreen();
    blue = readBlue();
    
    mainColor = 0;
    if (red>blue && red>green){
        mainColor = 1;
    } 
    if (green>red && green>blue){
        mainColor = 2;
    }
    if (blue>red && blue>green){
        mainColor = 3;
    }
    return mainColor;
}