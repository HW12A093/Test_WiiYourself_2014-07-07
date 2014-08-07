#include "stdafx.h"
#include "wiimote.h"
#include<iostream>

// 表示しなきゃいけないらしいライセンス文
#define WII_YOURSELF_LICENSE_WSTRING L"contains WiiYourself! wiimote code by gl.tter\nhttp://gl.tter.org\n"

//WiiYourself!関数一覧 2014年8月7日16時54分
//http://file.keanwortd.o-oi.net/wiiyourself_functions_reference.html


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
	std::cout << "Wiiリモコン接続数 : " << remote.TotalConnected() << std::endl; //2014年8月7日16時58分
	std::cout << "バッテリ残量 : "<< remote.BatteryPercent <<"% " <<std::endl; //バッテリ残量表示(%表示)

	/*赤外線を使ってみる*/ //2014年8月7日18時10分
	wiimote_state::ir::dot dot = remote.IR.Dot[0];
	/*赤外線を使ってみる*/

	Sleep(1000);

	//モーションプラスを有効にしてみる 2014年8月4日23時09分
	remote.EnableMotionPlus();
	
	int i = 0;
	while(true){//for (int i = 0; i<30; i++){
		i++;
		std::cout << "i =" << i << std::endl;
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
		remote.RefreshState();
		
		if (remote.Button.A() == true){
			remote.SetLEDs(0x1);
			std::cout << "	A = true"<< std::endl;
		}
		else if (remote.Button.A() == false){
			remote.SetLEDs(0x8);
			std::cout << "	A = false" << std::endl;
		}

		if (i%5 == 0){
			//remote.SetRumble(true); // 振動させる(振動させ続けるには連続して呼ぶ必要がある)http://keanwortd.o-oi.net/Page/3/
		} else {
			remote.SetRumble(false);
		}

		std::cout << "	角度 ピッチ ＝ " << remote.Acceleration.Orientation.Pitch << std::endl;
		std::cout << "	角度 ロール ＝ " << remote.Acceleration.Orientation.Roll << std::endl;
		std::cout << std::endl;
		

		//コマンド入力チェック
		if (remote.Button.A() == true){
			std::cout << "A= true" << std::endl;
		}
		if (remote.Button.B() == true){
			std::cout << "B = true" << std::endl;
		}
		if (remote.Button.Home() == false){
			std::cout << "HOME = false" << std::endl;
		}
		//コマンド入力チェック

		//HOMEボタンでプログラム終了
		if (remote.Button.Home() == true){
			return 0;
		}


		//赤外線関係を試してみる
		std::cout << "/*赤外線関係*/" << std::endl;
		std::cout << "bVisible = " << dot.bVisible << std::endl;
		std::cout << "dot.size = " << dot.Size << std::endl;
		std::cout << "dot.X = " << dot.X << std::endl;
		std::cout << "dot.Y = " << dot.Y << std::endl;
		std::cout << std::endl;
		//赤外線関係


		Sleep(1000);
	}
	

	return 0;
}