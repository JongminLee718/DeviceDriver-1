#include "gmock/gmock.h"
#include "device_driver.h"
#include <vector>
#include <stdexcept>

using namespace std;
using namespace testing;

class MockFlashMemory : public FlashMemoryDevice {
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

TEST(DeviceDriver, Read5times) {
	// TODO : replace hardware with a Test Double
	MockFlashMemory  mockHw;
	DeviceDriver dd{ &mockHw };
	EXPECT_CALL(mockHw, read(0xA))
		.Times(5)
		.WillRepeatedly(Return(0x77));

	int result = dd.read(0xA);
}

TEST(DeviceDriver, ReadException) {
	// TODO : replace hardware with a Test Double
	MockFlashMemory  mockHw;
	DeviceDriver dd{ &mockHw };

	EXPECT_CALL(mockHw, read(0xA))
		.WillOnce(Return(0x5))
		.WillRepeatedly(Return(0x77));

	EXPECT_THROW({
		dd.read(0xA);
		}, std::exception);
}

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}