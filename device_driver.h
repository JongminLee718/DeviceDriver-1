#pragma once
#include "flash_memory_device.h"

class DeviceDriver
{
public:
    DeviceDriver(FlashMemoryDevice* hardware);
    int read(long address);
    void write(long address, int data);
    void readAndPrint(long startAddr, long endAddr);
    void writeAll(unsigned char data);

protected:
    FlashMemoryDevice* m_hardware;

private:
    const int DEFAULT_READ_RETRY_NUM = 4;
    void readValidationCheck(long address, int result);
    void writeValidationCheck(long address);
};