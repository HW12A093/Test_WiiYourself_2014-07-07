#include "stdafx.h"
#include "wiimote.h"
#include<iostream>

// �\�����Ȃ��Ⴂ���Ȃ��炵�����C�Z���X��
#define WII_YOURSELF_LICENSE_WSTRING L"contains WiiYourself! wiimote code by gl.tter\nhttp://gl.tter.org\n"


int main(void){

	SetConsoleTitle(_T("Wii�����R���v���X�R���g���[���e�X�g"));

	wiimote remote;

	std::cout << "Connect..." << std::endl;

	//wii�����R���ڑ������܂őҋ@
	while (!remote.Connect(wiimote::FIRST_AVAILABLE)) Sleep(1);
		remote.SetReportType(wiimote::IN_BUTTONS_ACCEL_IR);

	//�ڑ��ς�
	if (remote.IsConnected()){
		printf("OK!\n");
	}

	while (true){

		if (remote.ConnectionLost() == true){
			std::cout << "Wii�����R�����ؒf����܂����B" << std::endl;
			while (!remote.Connect(wiimote::FIRST_AVAILABLE)) Sleep(1);
			remote.SetReportType(wiimote::IN_BUTTONS_ACCEL_IR);
			if (remote.IsConnected()){
				printf("OK!\n");
			}
		}

		//wii�����R���̃f�[�^���X�V
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