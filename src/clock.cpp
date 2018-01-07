//
// Created by sworddestiny on 17-12-6.
//

#include "clock.h"

using namespace lm;

lm::periodic_clock::periodic_clock(logic_time start_time, signal init_signal, signal final_signal,
								   signal *cycle_signal, int cycle_signal_len, int cycle_num,
								   logic_time interval, bool always_cycle, const string &name)
		: start_time(start_time), init_signal(init_signal), final_signal(final_signal), cycle_signal(cycle_signal),
		  cycle_signal_len(cycle_signal_len), cycle_num(cycle_num), interval(interval), always_cycle(always_cycle),
		  name(name), sgl(SIGNAL_ZERO), current_time(-1) {

}

lm::periodic_clock::~periodic_clock() = default;

lm::signal lm::periodic_clock::get_signal(lm::logic_time time) {
	if (time < start_time) {
		return init_signal;
	}
	if (always_cycle) {
		return cycle_signal[((time - start_time) % (cycle_signal_len * interval)) / interval];
	} else {
		if (time < start_time + cycle_signal_len * interval * cycle_num) {
			return cycle_signal[((time - start_time) % (cycle_signal_len * interval)) / interval];
		} else {
			return final_signal;
		}
	}
}

logic_time periodic_clock::getStart_time() const {
	return start_time;
}

void periodic_clock::setStart_time(logic_time start_time) {
	periodic_clock::start_time = start_time;
}

signal periodic_clock::getInit_signal() const {
	return init_signal;
}

void periodic_clock::setInit_signal(signal init_signal) {
	periodic_clock::init_signal = init_signal;
}

signal periodic_clock::getFinal_signal() const {
	return final_signal;
}

void periodic_clock::setFinal_signal(signal final_signal) {
	periodic_clock::final_signal = final_signal;
}

signal *periodic_clock::getCycle_signal() const {
	return cycle_signal;
}

void periodic_clock::setCycle_signal(signal *cycle_signal) {
	periodic_clock::cycle_signal = cycle_signal;
}

int periodic_clock::getCycle_signal_len() const {
	return cycle_signal_len;
}

void periodic_clock::setCycle_signal_len(int cycle_signal_len) {
	periodic_clock::cycle_signal_len = cycle_signal_len;
}

int periodic_clock::getCycle_num() const {
	return cycle_num;
}

void periodic_clock::setCycle_num(int cycle_num) {
	periodic_clock::cycle_num = cycle_num;
}

logic_time periodic_clock::getInterval() const {
	return interval;
}

void periodic_clock::setInterval(logic_time interval) {
	periodic_clock::interval = interval;
}

bool periodic_clock::isAlways_cycle() const {
	return always_cycle;
}

void periodic_clock::setAlways_cycle(bool always_cycle) {
	periodic_clock::always_cycle = always_cycle;
}

const string &periodic_clock::getName() const {
	return name;
}

void periodic_clock::setName(const string &name) {
	periodic_clock::name = name;
}

signal periodic_clock::get_signal() {
	return sgl;
}

void periodic_clock::update_signal() {
	current_time++;
	if (current_time < start_time) {
		sgl = init_signal;
	} else {
		if (always_cycle) {
			sgl = cycle_signal[((current_time - start_time) % (cycle_signal_len * interval)) / interval];
		} else {
			if (current_time < start_time + cycle_signal_len * interval * cycle_num) {
				sgl = cycle_signal[((current_time - start_time) % (cycle_signal_len * interval)) / interval];
			} else {
				sgl = final_signal;
			}
		}
	}
}

signal constant_clock::get_signal(logic_time time) {
	return sgl;
}

constant_clock::~constant_clock() = default;

constant_clock::constant_clock(signal sgl) : sgl(sgl) {

}

constant_clock *z, *o;

constant_clock *constant_clock::zero() {
	if (!z) {
		z = new constant_clock(SIGNAL_ZERO);
	}
	return z;
}

constant_clock *constant_clock::one() {
	if (!o) {
		o = new constant_clock(SIGNAL_ONE);
	}
	return o;
}

signal constant_clock::get_signal() {
	return sgl;
}

void constant_clock::update_signal() {

}

lm::clock::~clock() = default;

uuid lm::clock::getUid() const {
	return uid;
}

lm::clock::clock() : uid(get_uuid()) {

}
