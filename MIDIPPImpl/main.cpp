#include <cstdio>
#include <cstdlib>
#include <chrono>
#include <thread>

#include "winmidipp.h"

mpp::midi_handle hMidiIn;
mpp::midi_handle hMidiOut;

void print_midi_device_info(unsigned int deviceId, mpp::device_info_t& deviceInfo)
{
	printf("MIDI Device %i specifiers:\n", deviceId);
	printf("- Manufacturer ID: %i\n", deviceInfo.manufacturerId);
	printf("- Product ID: %i\n", deviceInfo.productId);
	printf("- DriverVersion Major: %x\n", deviceInfo.driverVersionMajor);
	printf("- DriverVersion Minor: %x\n", deviceInfo.driverVersionMinor);
	printf("- Product Name: %s\n", deviceInfo.name);
}

/* controller for a Novation Launchpad (Tested on Launchpad Mini) */
void callback_in(unsigned char firstData, unsigned char secondData, unsigned char status)
{
	char posX;
	char posY;
	bool pressed;

	if (status != 0x90 && status != 0xB0) {
		printf("Received: firstData: 0x%02X, secondData: 0x%02X, status: 0x%02X\n",
			firstData,
			secondData,
			status);
		return;
	}
	posX = secondData & 0xF;
	posY = secondData >> 4 & 0xF;
	pressed = firstData == 0x7F;
	if (status == 0x90) {
		printf("User %s launchkey X: %d, Y: %d\n",
			pressed ? "pressed" : "released", posX, posY);
	} else {
		printf("User %s extra-key X: %d, Y: %d\n",
			pressed ? "pressed" : "released", posX, posY);
	}
	if(mpp::novation::set_led(hMidiOut, posX, posY, pressed ? NOVCOLOR(3, 0) : NOVCOLOR(0, 0))) {
		printf("error switching led color\n");
	}
}

void callback_out(unsigned char firstData, unsigned char secondData, unsigned char status)
{
	printf("User defined out-callback got called\n");
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
	mpp::base::add_in_callback(callback_in);
	mpp::base::add_out_callback(callback_out);
	result = mpp::base::open_midi_in(0, &hMidiIn);
	if (result) {
		printf("Error when opening midi in device with id %i (%x)\n", 0, result);
		exit(1);
	}
	result = mpp::start_recording(hMidiIn);
	if (result) {
		printf("Error when starting a recording with id %i (%x)\n", 0, result);
		exit(1);
	}
	result = mpp::base::open_midi_out(1, &hMidiOut);
	if (result) {
		printf("Error when opening midi out device with id %i (%x)\n", 0, result);
		exit(1);
	}
	std::this_thread::sleep_for(std::chrono::seconds(1));
	printf("Press Enter to Exit...\n");
	getchar();
	result = mpp::stop_recording(hMidiIn);
	if (result) {
		printf("Error when stopping a recording with id %i (%x)\n", 0, result);
		exit(1);
	}
	mpp::base::close_midi_in(hMidiIn);
	mpp::base::close_midi_out(hMidiOut);
}