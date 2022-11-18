#include <cstdio>
#include <cstdlib>
#include <chrono>
#include <thread>

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

void callback_in()
{
	printf("User defined in-callback got called\n");
}

void callback_out()
{
	printf("User defined out-callback got called\n");
}

int main()
{
	unsigned int deviceAmount;
	unsigned int i;
	mpp::device_info_t info;
	unsigned int result;
	mpp::handle hMidiIn;
	mpp::handle hMidiOut;

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
	mpp::base::add_in_callback(callback_in);
	mpp::base::add_out_callback(callback_out);
	for(i = 0; i < deviceAmount; i++) {
		result = mpp::base::open_midi_in(i, &hMidiIn);
		if (result) {
			printf("Error when opening midi in device with id %i (%x)\n", i, result);
			exit(1);
		}
		result = mpp::base::open_midi_out(i, &hMidiOut);
		if (result) {
			printf("Error when opening midi out device with id %i (%x)\n", i, result);
			exit(1);
		}
		printf("Closing In/Out Handles in 2 seconds\n");
		std::this_thread::sleep_for(std::chrono::seconds(2));
		mpp::base::close_midi_in(hMidiIn);
		mpp::base::close_midi_out(hMidiOut);
	}
}