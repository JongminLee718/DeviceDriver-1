#include "device_driver.h"
#include <stdexcept>

class ReadFiveTimeFail : public std::exception {};

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    int result = 0;
    result = (int)(m_hardware->read(address));
    ReadValidationCheck(address, result);
    return result;
}

void DeviceDriver::ReadValidationCheck(long address, int result)
{
    int readResult;
    for (int cnt = 0; cnt < DEFAULT_READ_RETRY_NUM;cnt++) {
        readResult = (int)(m_hardware->read(address));
        if (readResult != result) {
            throw ReadFiveTimeFail();
        }
    }
}

void DeviceDriver::write(long address, int data)
{
    int result = 0;
    WriteValidationCheck(address);
    m_hardware->write(address, (unsigned char)data);
}

void DeviceDriver::WriteValidationCheck(long address)
{
    int result = read(address);
    if (result != 0xFF) {
        throw std::exception();
    }
}
