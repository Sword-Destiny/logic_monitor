//
// Created by sworddestiny on 17-12-6.
//

#ifndef LOGICMONITOR_CLOCK_H
#define LOGICMONITOR_CLOCK_H

#include "common.h"

namespace lm {
	/**
	 * 时钟信号
	 */
	class clock {

	public:
		virtual signal get_signal() = 0;

		virtual signal get_signal(logic_time time) = 0; //获取信号

		virtual void update_signal() = 0;

		virtual ~clock();
		clock();
		uuid getUid() const;

		friend ostream& operator<<(ostream &out,clock &c){
			return out << c.get_signal();
		}
	private:
		uuid uid;
	};

	/**
	 * 周期时钟信号
	 */
	class periodic_clock : public clock {
	private:
		signal sgl;//信号
		logic_time start_time;//初始信号持续时间
		signal init_signal;//初始信号
		signal final_signal;//最终信号
		signal *cycle_signal;//循环信号
		int cycle_signal_len;//循环信号数组长度
		int cycle_num;//信号循环次数
		logic_time interval;//信号变更间隔
		bool always_cycle;//是否永远循环
		string name;
		long current_time;//当前时间

	public:
		periodic_clock(logic_time start_time, signal init_signal, signal final_signal, signal *cycle_signal,
					   int cycle_signal_len, int cycle_num, logic_time interval, bool always_cycle, const string &name);

		~periodic_clock() override;

		signal get_signal() override;

		signal get_signal(logic_time time) override;

		void update_signal() override;

	public:

		logic_time getStart_time() const;

		void setStart_time(logic_time start_time);

		signal getInit_signal() const;

		void setInit_signal(signal init_signal);

		signal getFinal_signal() const;

		void setFinal_signal(signal final_signal);

		signal *getCycle_signal() const;

		void setCycle_signal(signal *cycle_signal);

		int getCycle_signal_len() const;

		void setCycle_signal_len(int cycle_signal_len);

		int getCycle_num() const;

		void setCycle_num(int cycle_num);

		logic_time getInterval() const;

		void setInterval(logic_time interval);

		bool isAlways_cycle() const;

		void setAlways_cycle(bool always_cycle);

		const string &getName() const;

		void setName(const string &name);
	};

	/**
	 * 恒定时钟信号
	 */
	class constant_clock : public clock {
	public:
		signal get_signal(logic_time time) override;

		~constant_clock() override;

		signal get_signal() override;

		void update_signal() override;

		static constant_clock *zero();//信号0
		static constant_clock *one();//信号1
	private:

		const signal sgl;
		explicit constant_clock(signal sgl);
	};

}


#endif //LOGICMONITOR_CLOCK_H
