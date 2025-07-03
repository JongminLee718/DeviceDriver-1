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

	EXPECT_THROW(dd.read(0xA), std::exception);
}

TEST(DeviceDriver, Write) {
	// TODO : replace hardware with a Test Double
	NiceMock<MockFlashMemory>  mockHw;
	DeviceDriver dd{ &mockHw };

	EXPECT_CALL(mockHw, read(0xA))
		.WillRepeatedly(Return(0xFF));
	dd.write(0xA, 0xABC);
}

TEST(DeviceDriver, WriteException) {
	// TODO : replace hardware with a Test Double
	MockFlashMemory  mockHw;
	DeviceDriver dd{ &mockHw };

	EXPECT_CALL(mockHw, read(0xA))
		.Times(5)
		.WillRepeatedly(Return(0x12));

	EXPECT_THROW(dd.write(0xA, 0xABC), std::exception);
}

TEST(DeviceDriver, ReadAndPrint) {
	// TODO : replace hardware with a Test Double
	MockFlashMemory  mockHw;
	DeviceDriver dd{ &mockHw };

	EXPECT_CALL(mockHw, read(_)).Times(5 * 11);
	dd.readAndPrint(10,20);
}

TEST(DeviceDriver, WriteAll) {
	// TODO : replace hardware with a Test Double
	NiceMock<MockFlashMemory>  mockHw;
	DeviceDriver dd{ &mockHw };
	EXPECT_CALL(mockHw, read(_))
		.Times(25)
		.WillRepeatedly(Return(0xFF));
	EXPECT_CALL(mockHw, write(_,_)).Times(5);

	dd.writeAll(100);
}

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}