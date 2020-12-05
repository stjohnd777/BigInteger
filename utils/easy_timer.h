#pragma once

#include <thread>
#include <memory>

namespace dsj
{
	class BaseTimer
	{
	public:

		BaseTimer() : isDetached(false) {}

		BaseTimer(bool isDetached ) : isDetached(isDetached) {}

		void stop() {
			this->clear = true;
		}
		
		std::shared_ptr <std::thread> the_thread;

	protected:

		bool clear = false;

		bool isDetached = false;

		
	};

	class Alarm : public BaseTimer {

	public:

		Alarm() : BaseTimer() {}

		Alarm(bool isDetached = true) : BaseTimer(isDetached)
		{
		}

		template<typename Function>
		void setTimeout(Function function, int delay) {
			this->clear = false;
			auto t = new std::thread([=]() {
				if (this->clear) return;
				std::this_thread::sleep_for(std::chrono::milliseconds(delay));
				if (this->clear) return;
				function();
			});
		    t->detach();
			this->the_thread.reset(t);
			
		}

	};


	class IntervalTimer : public BaseTimer
	{

	public:

		IntervalTimer() : BaseTimer() {}

		IntervalTimer(bool isDetached = true) : BaseTimer(isDetached) {}

		template<typename Function>
		void setInterval(Function function, int interval) {
			this->clear = false;
			auto t = new  std::thread([=]() {
				while (true) {
					if (this->clear) return;
					std::this_thread::sleep_for(std::chrono::milliseconds(interval));
					if (this->clear) return;
					function();
				}
			});
			this->the_thread.reset(t);
			this->the_thread->detach();
		}

	};
	
	template <class Function>
	struct TimerHandle
	{
		enum Status { INIT, RUNNING, SLEEPING, REQUEST_CANCEL, IS_CANCELED, COMPLETED, ERROR_STATE} ;
		Function f;
		int delay;
		Status state = INIT;
        std::thread* theThread;

		
	};

	template<typename Function>
    void SetTimeout(TimerHandle<Function>& handle) {
		handle.state = TimerHandle<Function>::INIT;
		auto  spThread = new std::thread( [&]() {
			if (handle.state == TimerHandle<Function>::IS_CANCELED) return;
			std::this_thread::sleep_for(std::chrono::milliseconds(handle.delay));
			if (handle.state == TimerHandle< Function>::IS_CANCELED) return;
			handle.f();
			handle.state = TimerHandle< Function>::COMPLETED;
		});
        handle.theThread = spThread;
	}

	template<typename Function>
	void SetInterval(TimerHandle<Function>& handle) {

		handle.state = TimerHandle<Function>::INIT;

		auto wrapper = [&]() {
			
			while (true) 
			{
				if (handle.state == TimerHandle< Function>::REQUEST_CANCEL) {
					handle.state = TimerHandle< Function>::IS_CANCELED;
					return;
				}
				handle.state = TimerHandle< Function>::SLEEPING;
				std::this_thread::sleep_for(std::chrono::milliseconds(interval));
				if (handle.state == TimerHandle< Function>::REQUEST_CANCEL) {
					handle.state = TimerHandle< Function>::IS_CANCELED;
					return;
				}
				handle.state = TimerHandle< Function>::RUNNING;
				handle.f();
			}
		};

		auto spThread= new std::thread(wrapper);
	}

}