#include "stdafx.h"
#include "wiimote.h"
#include<iostream>

// 表示しなきゃいけないらしいライセンス文
#define WII_YOURSELF_LICENSE_WSTRING L"contains WiiYourself! wiimote code by gl.tter\nhttp://gl.tter.org\n"


int main(void){

	SetConsoleTitle(_T("Wiiリモコンプラスコントロールテスト"));

	wiimote remote;

	std::cout << "Connect..." << std::endl;

	//wiiリモコン接続完了まで待機
	while (!remote.Connect(wiimote::FIRST_AVAILABLE)) Sleep(1);
		remote.SetReportType(wiimote::IN_BUTTONS_ACCEL_IR);

	//接続済み
	if (remote.IsConnected()){
		printf("OK!\n");
	}

	while (true){

		if (remote.ConnectionLost() == true){
			std::cout << "Wiiリモコンが切断されました。" << std::endl;
			while (!remote.Connect(wiimote::FIRST_AVAILABLE)) Sleep(1);
			remote.SetReportType(wiimote::IN_BUTTONS_ACCEL_IR);
			if (remote.IsConnected()){
				printf("OK!\n");
			}
		}

		//wiiリモコンのデータを更新
		remote.RefreshState();

		if (remote.Button.A() == true){
			remote.SetLEDs(0x1);
		}
		else{
			remote.SetLEDs(0x8);
		}
	}


	return 0;
}