#include <iostream>
#include <string>
#include <memory>
#include "Timer.h"
using namespace std;
void EchoFunc(std::string&& s){
	std::cout << "test : " << s << std::endl;
}

int main(){
	Timer t;
	//������ִ�ж�ʱ����
	t.StartTimer(1000, std::bind(EchoFunc, "hello world"));
	std::this_thread::sleep_for(std::chrono::seconds(4));
	std::cout << "try to expire timer!" << std::endl;
	t.Expire();
	//������ִ�ж�ʱ����
	t.StartTimer(1000, std::bind(EchoFunc, "hello C++11"));
	std::this_thread::sleep_for(std::chrono::seconds(4));
	std::cout << "try to expire timer!" << std::endl;
	t.Expire();

	std::this_thread::sleep_for(std::chrono::seconds(2));

	//ִֻ��һ�ζ�ʱ����
	//ͬ��
	t.SyncWait(1000, EchoFunc, "hello world");
	//�첽
	t.AsyncWait(1000, EchoFunc, "hello C++11");

	std::this_thread::sleep_for(std::chrono::seconds(2));

	return 0;
}