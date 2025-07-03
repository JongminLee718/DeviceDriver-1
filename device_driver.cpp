#include "device_driver.h"
#include <stdexcept>

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    int result = 0, temp = 0;
    result = (int)(m_hardware->read(address));
    for (int cnt = 0; cnt < 4;cnt++) {
        temp = (int)(m_hardware->read(address));
        if (temp != result) {
            throw std::exception("Read Result is not same");
        }
    }
    return result;
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}