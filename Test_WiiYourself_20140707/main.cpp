#include "stdafx.h"
#include "wiimote.h"
#include<iostream>

// �\�����Ȃ��Ⴂ���Ȃ��炵�����C�Z���X��
#define WII_YOURSELF_LICENSE_WSTRING L"contains WiiYourself! wiimote code by gl.tter\nhttp://gl.tter.org\n"

//WiiYourself!�֐��ꗗ 2014�N8��7��16��54��
//http://file.keanwortd.o-oi.net/wiiyourself_functions_reference.html


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
		remote.SetLEDs(0x1);
	}

	if (!remote.IsConnected()){
		std::cout << "���łɒʐM���؂�Ă���B";
		remote.SetLEDs(0x8);
		return -1;
	}
	for (int i = 0; i < 10; i++){
		remote.SetLEDs(0x1);
		remote.SetLEDs(0x8);
	}
	remote.SetLEDs(0x7);
	std::cout << "Wii�����R���ڑ��� : " << remote.TotalConnected() << std::endl; //2014�N8��7��16��58��
	std::cout << "�o�b�e���c�� : "<< remote.BatteryPercent <<"% " <<std::endl; //�o�b�e���c�ʕ\��(%�\��)

	/*�ԊO�����g���Ă݂�*/ //2014�N8��7��18��10��
	wiimote_state::ir::dot dot = remote.IR.Dot[0];
	/*�ԊO�����g���Ă݂�*/

	Sleep(1000);

	//���[�V�����v���X��L���ɂ��Ă݂� 2014�N8��4��23��09��
	remote.EnableMotionPlus();
	
	int i = 0;
	while(true){//for (int i = 0; i<30; i++){
		i++;
		std::cout << "i =" << i << std::endl;
		/*
		if (remote.ConnectionLost() == true){
			std::cout << "Wii�����R�����ؒf����܂����B" << std::endl;
			while (!remote.Connect(wiimote::FIRST_AVAILABLE)) Sleep(1);
			remote.SetReportType(wiimote::IN_BUTTONS_ACCEL_IR);
			if (remote.IsConnected()){
				printf("OK!\n");
			}
		}*/
		
		//wii�����R���̃f�[�^���X�V
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
			//remote.SetRumble(true); // �U��������(�U������������ɂ͘A�����ČĂԕK�v������)http://keanwortd.o-oi.net/Page/3/
		} else {
			remote.SetRumble(false);
		}

		std::cout << "	�p�x �s�b�` �� " << remote.Acceleration.Orientation.Pitch << std::endl;
		std::cout << "	�p�x ���[�� �� " << remote.Acceleration.Orientation.Roll << std::endl;
		std::cout << std::endl;
		

		//�R�}���h���̓`�F�b�N
		if (remote.Button.A() == true){
			std::cout << "A= true" << std::endl;
		}
		if (remote.Button.B() == true){
			std::cout << "B = true" << std::endl;
		}
		if (remote.Button.Home() == false){
			std::cout << "HOME = false" << std::endl;
		}
		//�R�}���h���̓`�F�b�N

		//HOME�{�^���Ńv���O�����I��
		if (remote.Button.Home() == true){
			return 0;
		}


		//�ԊO���֌W�������Ă݂�
		std::cout << "/*�ԊO���֌W*/" << std::endl;
		std::cout << "bVisible = " << dot.bVisible << std::endl;
		std::cout << "dot.size = " << dot.Size << std::endl;
		std::cout << "dot.X = " << dot.X << std::endl;
		std::cout << "dot.Y = " << dot.Y << std::endl;
		std::cout << std::endl;
		//�ԊO���֌W


		Sleep(1000);
	}
	

	return 0;
}