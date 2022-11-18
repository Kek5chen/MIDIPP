#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "winmidipp.h"

void print_midi_device_info(unsigned int deviceId, mpp::device_info_t& deviceInfo)
{
	printf("MIDI Device %i specifiers:\n", deviceId);
	printf("- Manufacturer ID: %i\n", deviceInfo.manufacturerId);
	printf("- Product ID: %i\n", deviceInfo.productId);
	printf("- DriverVersion Major: %x\n", deviceInfo.driverVersionMajor);
	printf("- DriverVersion Minor: %x\n", deviceInfo.driverVersionMinor);
	printf("- Product Name: %s\n", deviceInfo.name);
}

int main()
{
	unsigned int deviceAmount;
	unsigned int i;
	mpp::device_info_t info;
	unsigned int result;

	deviceAmount = mpp::base::get_device_amount();
	printf("Found %i MIDI compatible devices.\n", deviceAmount);
	if (deviceAmount == 0) {
		printf("No devices found.. Exiting.\n");
		exit(0);
	}
	for(i = 0; i < deviceAmount; i++) {
		result = mpp::base::get_device_info(&info, i);
		if (result) {
			printf("Error when querying device info from id %i (%x)\n", i, result);
			exit(1);
		}
		print_midi_device_info(i, info);
		printf("\n");
	}
}