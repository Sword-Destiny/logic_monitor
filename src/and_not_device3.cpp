//
// Created by sworddestiny on 17-12-7.
//

#include "and_not_device3.h"
using namespace lm;

input *and_not_device3::getA() const {
	return a;
}

void and_not_device3::setA(input *a) {
	and_not_device3::a = a;
}

input *and_not_device3::getB() const {
	return b;
}

void and_not_device3::setB(input *b) {
	and_not_device3::b = b;
}

input *and_not_device3::getC() const {
	return c;
}

void and_not_device3::setC(input *c) {
	and_not_device3::c = c;
}

output *and_not_device3::getO() const {
	return o;
}

void and_not_device3::setO(output *o) {
	and_not_device3::o = o;
}

void and_not_device3::update_signal() {
	o->update_signal(!(a->get_signal() && b->get_signal() && c->get_signal()));
}

and_not_device3::and_not_device3(const string &name, input *a, input *b, input *c) : logic_device(name), a(a), b(b),
																					 c(c), o(nullptr) {}

signal and_not_device3::get_signal(output *out_iface) {
	if (out_iface == o) {
		return o->get_signal();
	}
	return false;
}

and_not_device3::~and_not_device3() = default;
