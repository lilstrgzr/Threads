#include <iostream>
#include <thread> //Подключение библиотеки для создания потоков и управления ими
#include <chrono> //Подключение библиотеки, содержащей в себе команды для управления временем в стиле языка с++
#include <conio.h>//Библиотека языка С для удобного взаимодействия с консолью
#include<string>
#include <Windows.h>

void doSomething() {
	for (size_t i = 0; i < 10; ++i) {
		std::cout << "Thread №" << std::this_thread::get_id() << "\tdoSomething\t" << i << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
}

void calculate(double num1, double num2) {
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	
	std::cout << "Thread №" << std::this_thread::get_id() << "\tSTART CALCULATE======================\n";
	
	std::this_thread::sleep_for(std::chrono::milliseconds(3000));
	
	std::cout << "Thread №" << std::this_thread::get_id() << "\t" << num1 << " + " << num2 << " = " << num1 + num2 << std::endl;
	
	std::this_thread::sleep_for(std::chrono::milliseconds(1500));
	
	std::cout << "Thread №" << std::this_thread::get_id() << "\tEND CALCULATE========================\n";
}

void calculateTo(double& result,double num1, double num2) {
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	
	std::cout << "Thread №" << std::this_thread::get_id() << "\tSTART CALCULATE TO REF==============\n";
	
	std::this_thread::sleep_for(std::chrono::milliseconds(3000));
	
	result = num1 + num2;

	std::cout << "Thread №" << std::this_thread::get_id() << "\tEND CALCULATE TO REF================\n";
}

void pressBtn(char& key, bool& pressed) {
	while (true) {
		if (_kbhit()) {
			key = _getch();
			pressed = true;
		}
	}
}

void fieldEvents() {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coords{ 0,0 };
	while (true) {
		coords.X = rand() % 11;
		coords.Y = rand() % 11;
		SetConsoleCursorPosition(handle, coords);
		std::cout << '.';
		std::this_thread::sleep_for(std::chrono::seconds(1));
		
	}
}

int main() {
	setlocale(LC_ALL, "russian");
	double n;

	//Потоки
	/*
	std::cout << "START\n";

	//doSomething(); //Плохо, так как нагружается основной поток
	//calculate(5, 8); //Плохо, так как нагружается основной поток
	//calculateTo(n, 57, 25); //Плохо, так как нагружается основной поток
	
	//std::thread th1(doSomething);
	//th1.detach(); //Остановка потока при заверщении основной программы
	
	//std::thread th2(doSomething);

	//std::thread th3(calculate, 55, 440);

	std::thread th4(calculateTo, std::ref( n), 2134, 4213);

	for (size_t i = 0; i < 10; ++i) {
		std::cout << "Thread №" << std::this_thread::get_id() << "\tmain()\t\t" << i << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}


//th1.join();//"Yсыпление" текущего потока до тех пор пока не будет завершен поток th1
//th2.join();
	//th3.join();
	th4.join();
	
	std::cout << "Calculation result is " << n << std::endl;
	
std::cout << "END\n";
*/
	COORD coords{ 0,0 };
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout << 'H';

	char pressedKey = 0;
	bool isPressed = false;

	std::thread btnth(pressBtn, std::ref(pressedKey), std::ref(isPressed));
	std::thread spawnTh(fieldEvents);
	btnth.detach();
	spawnTh.detach();

	bool loop = true;

	while (true) {
		if (isPressed) {
			SetConsoleCursorPosition(handle, coords);
			std::cout << ' ';
			switch (std::tolower(pressedKey)) {
			case 'w':
				if (coords.Y > 0)
					coords.Y -= 1;
				break;
			case'a':
				if (coords.X > 0)
					coords.X -= 1;
				break;
			case's':
				coords.Y += 1;
				break;
			case 'd':
				if (coords.X < 30)
					coords.X += 1;
				break;
			case 'q':
				loop = false;
				break;
			}
			SetConsoleCursorPosition(handle, coords);
			std::cout << "H";
			if (!loop) break;
			isPressed = false;
		}
	}














	return 0;
}