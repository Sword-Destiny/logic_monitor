//
// Created by sworddestiny on 17-12-7.
//

#include "include/and_not_device.h"
using namespace lm;

and_not_device::~and_not_device() = default;

signal and_not_device::get_signal(output_iface *out_iface) {
	if(out_iface == o) {
		return o->get_signal();
	}
	return false;
}

void and_not_device::update_signal() {
	o->update_signal(!(a->get_signal() && b->get_signal()));
}

input *and_not_device::getA() const {
	return a;
}

void and_not_device::setA(input *a) {
	and_not_device::a = a;
}

input *and_not_device::getB() const {
	return b;
}

void and_not_device::setB(input *b) {
	and_not_device::b = b;
}

output *and_not_device::getO() const {
	return o;
}

void and_not_device::setO(output *o) {
	and_not_device::o = o;
}

and_not_device::and_not_device(const string &name, input *a, input *b) : logic_device(name), a(a), b(b), o(nullptr) {}


