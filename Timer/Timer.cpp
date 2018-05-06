#include "Timer.h"
#include <iostream>
void Timer::StartTimer(int interval, std::function<void()> task)
{
	if (expired_ == false)
	{
		return;
	}
	expired_ = false;
	std::thread([this, interval, task](){
		while (!try_to_expire_){
			std::this_thread::sleep_for(std::chrono::milliseconds(interval));
			task();
		}
		std::cout << "stop task..." << std::endl;
		{
			std::lock_guard<std::mutex> locker(mutex_);
			expired_ = true;
			expired_cond_.notify_one();
		}
	}).detach();
}

void Timer::Expire(){
	if (expired_)
		return;
	if (try_to_expire_){
		return;
	}
	try_to_expire_ = true;
	{
		std::unique_lock<std::mutex> locker(mutex_);
		expired_cond_.wait(locker, [this]{return expired_ == true; });
		if (expired_ == true){

			try_to_expire_ = false;
		}
	}
}

//template<typename callable, class... arguments>
//void Timer::SyncWait(int after, callable&& f, arguments&&... args){
//	
//	std::function<typename std::result_of<callable(arguments...)>::type()> task
//		(std::bind(std::forward<callable>(f), std::forward<arguments>(args)...));
//	std::this_thread::sleep_for(std::chrono::milliseconds(after));
//	task();
//}
//
//template<typename callable, class... arguments>
//void Timer::AsyncWait(int after, callable&& f, arguments&&... args){
//	std::function<typename std::result_of<callable(arguments...)>::type()> task
//		(std::bind(std::forward<callable>(f), std::forward<arguments>(args)...));
//
//	std::thread([after, task](){
//		std::this_thread::sleep_for(std::chrono::milliseconds(after));
//		task();
//	}).detach();
//
//}