#ifndef TIMER_H
#define TIMER_H
#include <functional>
#include <chrono>
#include <thread>
#include <atomic>
#include <memory>
#include <mutex>
#include <condition_variable>
class Timer{
public:
	Timer() :expired_(true), try_to_expire_(false){

	}
	Timer(const Timer& t){
		expired_ = t.expired_.load();
		try_to_expire_ = t.try_to_expire_.load();
	}
	~Timer(){
		Expire();
	}
	void StartTimer(int interval, std::function<void()> task);

	void Expire();

	template<typename callable, class... arguments>
	void SyncWait(int after, callable&& f, arguments&&... args){

		std::function<typename std::result_of<callable(arguments...)>::type()> task
			(std::bind(std::forward<callable>(f), std::forward<arguments>(args)...));
		std::this_thread::sleep_for(std::chrono::milliseconds(after));
		task();
	}

	template<typename callable, class... arguments>
	void AsyncWait(int after, callable&& f, arguments&&... args){
		std::function<typename std::result_of<callable(arguments...)>::type()> task
			(std::bind(std::forward<callable>(f), std::forward<arguments>(args)...));

		std::thread([after, task](){
			std::this_thread::sleep_for(std::chrono::milliseconds(after));
			task();
		}).detach();

	}
private:
	std::atomic<bool> expired_;
	std::atomic<bool> try_to_expire_;
	std::mutex mutex_;
	std::condition_variable expired_cond_;
};
#endif