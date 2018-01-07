//
// Created by sworddestiny on 17-12-7.
//

#include "or_not_device.h"
using namespace lm;

input *or_not_device::getA() const {
	return a;
}

void or_not_device::setA(input *a) {
	or_not_device::a = a;
}

input *or_not_device::getB() const {
	return b;
}

void or_not_device::setB(input *b) {
	or_not_device::b = b;
}

output *or_not_device::getO() const {
	return o;
}

void or_not_device::setO(output *o) {
	or_not_device::o = o;
}

void or_not_device::update_signal() {
	o->update_signal(!(a->get_signal() || b->get_signal()));
}

signal or_not_device::get_signal(output *out_iface) {
	if (out_iface == o) {
		return o->get_signal();
	}
	return false;
}

or_not_device::or_not_device(const string &name, input *a, input *b) : logic_device(name), a(a), b(b), o(nullptr) {}

or_not_device::~or_not_device() = default;