//
// Created by sworddestiny on 17-12-8.
//

#include "include/no_devices.h"

logic_monitor::no_device::no_device(const string &name, logic_monitor::input *input) : lgc_dev(name), i(input),
																					   o(nullptr) {

}

logic_monitor::no_device::~no_device() = default;

logic_monitor::signal logic_monitor::no_device::get_signal(logic_monitor::output *out_iface) {
	if (out_iface == o) {
		return o->get_signal();
	}
	return false;
}

void logic_monitor::no_device::update_signal() {
	o->update_signal(i->get_signal());
}

logic_monitor::input *logic_monitor::no_device::getInput() const {
	return i;
}

void logic_monitor::no_device::setInput(logic_monitor::input *input) {
	this->i = i;
}

logic_monitor::output *logic_monitor::no_device::getOutput() const {
	return o;
}

void logic_monitor::no_device::setOutput(logic_monitor::output *o) {
	this->o = o;
}
