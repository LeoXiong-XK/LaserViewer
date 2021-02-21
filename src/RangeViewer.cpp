#include <iostream>
#include <fstream>
#include <thread>
#include <stack>
#include <time.h>
#include <vector>
#include "base\lidar.h"
#include "base\opencv_writer.h"
using namespace std;

#define PI 3.141592653589793
#define DEGREETORAD (PI/180.)
#define PAUSE {system("pause");}
Dev device;
rangedata dataPack[8];
std::vector<rangedata> dataset;
const int databuff = 600;
int fps = 0;
bool dataEnable = false, is_data_available=false, is_serial_available=false;
char buff[256];
void CheckSerial()
{
	int count = 0;
	while (true)
	{
		char byte_cur = NULL;
		int rtn = device.readByte(&byte_cur, 60);
		if (rtn > 0)
		{
			is_serial_available = true;
			return;
		}
		else
		{
			//SwitchToThisWindow(hWnd_main, 1);
			is_data_available = false;
			is_serial_available = false;
			printf("Warning: Invalid serial data!\n");
			Sleep(500);
			count++;
			if (count > 10)
			{
				printf("\n\n");
				return;
			}
		}
	}
}
void SerialDataThread() {
	int rtn;
	while (dataEnable) {
		rtn = device.ReadData_serial(60);
		if (rtn < 0) {
			is_data_available = false;
			CheckSerial();
			if(is_serial_available) {
				printf("Read serial data successfully!\n");
				Sleep(100);
			}
			else {
				printf("Unable to read serial data!\n");
				printf("Try to open serial port...\n");
				device.closeSerial();
				int port = 3;
				int baud = 115200;
				char com[8];
				sprintf_s(com, "com%d", port);
				printf("rangeView port=%s, baudRate=%d\n", com, baud);
				rtn = device.openSerial(com, baud);
				if (rtn < 0)
				{
					sprintf_s(buff, "Error: Open serial port (%s)£¡", com);
					printf("%s\n", buff);
				}
				else
				{
					printf("Open serial port successfully!\n");
					is_serial_available = true;
				}
			}
			continue;
		}
		else {
			is_data_available = true;
		}
		device.ParseData_serial(dataPack, fps);
		for (int i = 0; i < 8; i++)
		{
			dataset.push_back(dataPack[i]);
			if (dataset.size() > databuff)
			{
				dataset.erase(dataset.begin());
			}
		}
	}
}
void drawRangeData() {
	if (dataset.size() == databuff) {
		float lidar_dist[databuff];
		for (int i = 0; i < databuff; ++i) {
			lidar_dist[i] = dataset[i].dist;
		}
		//frame_debug(lidar_dist,"debug");
	}
}
void drawScene() {
	if (is_data_available)
	{
		drawRangeData();
	}
}
int main(int argc, char ** argv) {
	std::thread sThread(SerialDataThread);
	//std::thread gThread(drawRangeData);
	sThread.join();
	return 0;
}
