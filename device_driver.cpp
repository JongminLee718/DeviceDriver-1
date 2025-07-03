#include "device_driver.h"
#include <iostream>
#include <stdexcept>

class ReadFail : public std::exception {};
class WriteFail : public std::exception {};

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    int result = 0;
    result = (int)(m_hardware->read(address));
    readValidationCheck(address, result);
    return result;
}

void DeviceDriver::readValidationCheck(long address, int result)
{
    int readResult;
    for (int cnt = 0; cnt < DEFAULT_READ_RETRY_NUM;cnt++) {
        readResult = (int)(m_hardware->read(address));
        if (readResult != result) {
            throw ReadFail();
        }
    }
}

void DeviceDriver::write(long address, int data)
{
    int result = 0;
    writeValidationCheck(address);
    m_hardware->write(address, (unsigned char)data);
}

void DeviceDriver::writeValidationCheck(long address)
{
    int result = read(address);
    if (result != 0xFF) {
        throw WriteFail();
    }
}

void DeviceDriver::readAndPrint(long startAddr, long endAddr)
{
    for (int addr = startAddr; addr < endAddr + 1;addr++) {
        std::cout << read(addr) << "\n";
    }
}

void DeviceDriver::writeAll(unsigned char data)
{
    for (int addr = 0; addr < 5;addr++) {
        write(addr, data);
    }
}
