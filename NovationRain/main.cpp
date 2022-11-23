#include <cstdio>
#include <Windows.h>
#include <cstdlib>
#include <ctime>
#include <thread>

#include "winmidipp.h"

#define TOPOS(x,y) ((short) (((y) & 0xFF) << 8 | (x) & 0xFF))
#define GETX(pos) ((char) ((pos) & 0xFF))
#define GETY(pos) ((char) (((pos) >> 8) & 0xFF))

void update_droplet(short pos, mpp::midi_handle handle)
{
	char x = GETX(pos);
	char y = GETY(pos);

	mpp::novation::set_led(handle, x, y - 2, NOVCOLOR(0, 0));
	mpp::novation::set_led(handle, x, y - 1, NOVCOLOR(1, 0));
	mpp::novation::set_led(handle, x, y, NOVCOLOR(1, 0));
	mpp::novation::set_led(handle, x, y + 1, NOVCOLOR(1, 0));
}

int main()
{
	mpp::device_info_t deviceInfo;
	mpp::midi_handle hMidiOut;
	short positions[5] { 0 };
	char x, y;

	std::srand((unsigned int) std::time(nullptr) + 5695);
	if (mpp::base::get_device_amount() == 0) {
		printf("No devices connected.. Exiting\n");
		return 0;
	}
	mpp::base::get_device_info(&deviceInfo, 0);
	printf("Connected to device %s\n", deviceInfo.name);
	mpp::base::open_midi_out(1, &hMidiOut); // output port is mapped one after the input port
	mpp::novation::reset(hMidiOut);
	for (short& position : positions) {
		position = TOPOS(std::rand() % 9, -2 - std::rand() % 2);
	}
	while (!GetKeyState(VK_END)) {
		for (short& position : positions) {
			update_droplet(position, hMidiOut);
			x = GETX(position);
			y = GETY(position) + 1;
			if (y - 1 > 6) {
				x = std::rand() % 9;
				y = (char) (-2 - std::rand() % 5);
			}
			position = TOPOS(x,y);
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	mpp::novation::reset(hMidiOut);
	mpp::base::close_midi_out(hMidiOut);
	return 0;
}