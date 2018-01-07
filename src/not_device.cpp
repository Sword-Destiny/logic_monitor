//
// Created by sworddestiny on 17-12-6.
//

#include "not_device.h"
using namespace lm;

signal not_device::get_signal(output *out_iface) {
	if (out_iface == this->o) {
		return o->get_signal();
	}
	return false;
}

void not_device::update_signal() {
	o->update_signal(!i->get_signal());
}

not_device::not_device(const string &name, input *input) : logic_device(name), i(input),
																					   o(nullptr) {}

input *not_device::getInput() const {
	return i;
}

void not_device::setInput(input_iface *input) {
	not_device::i = input;
}

output *not_device::getOutput() const {
	return o;
}

void not_device::setOutput(output *o) {
	not_device::o = o;
}

not_device::~not_device() = default;
