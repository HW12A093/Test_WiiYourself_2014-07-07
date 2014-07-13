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
		remote.SetLEDs(0x1);
	}

	if (!remote.IsConnected()){
		std::cout << "すでに通信が切れている。";
		remote.SetLEDs(0x8);
		return -1;
	}
	for (int i = 0; i < 10; i++){
		remote.SetLEDs(0x1);
		remote.SetLEDs(0x8);
	}
	remote.SetLEDs(0x7);
	Sleep(1000);
	
	for (int i = 0; i < 30;i++){
		std::wcout << "i =" << i << std::endl;
		/*
		if (remote.ConnectionLost() == true){
			std::cout << "Wiiリモコンが切断されました。" << std::endl;
			while (!remote.Connect(wiimote::FIRST_AVAILABLE)) Sleep(1);
			remote.SetReportType(wiimote::IN_BUTTONS_ACCEL_IR);
			if (remote.IsConnected()){
				printf("OK!\n");
			}
		}*/
		
		//wiiリモコンのデータを更新
		//remote.RefreshState();
		
		if (remote.Button.B() == true){
			remote.SetLEDs(0x1);
			std::cout << "	A = true"<< std::endl;
		}
		else if (remote.Button.B() == false){
			remote.SetLEDs(0x8);
			std::cout << "	A = false" << std::endl;
		}

		if (i%5 == 0){
			remote.SetRumble(true); // 振動させる(振動させ続けるには連続して呼ぶ必要がある)http://keanwortd.o-oi.net/Page/3/
		} else {
			remote.SetRumble(false);
		}

		std::cout << "	角度 ピッチ ＝ " << remote.Acceleration.Orientation.Pitch << std::endl;
		std::cout << "	角度 ロール ＝ " << remote.Acceleration.Orientation.Roll << std::endl;
		std::cout << std::endl;

		Sleep(1000);
	}
	

	return 0;
}