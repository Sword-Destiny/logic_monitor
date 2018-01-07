//
// Created by sworddestiny on 17-12-7.
//

#include "or_not_device3.h"
using namespace lm;

input *or_not_device3::getA() const {
	return a;
}

void or_not_device3::setA(input *a) {
	or_not_device3::a = a;
}

input *or_not_device3::getB() const {
	return b;
}

void or_not_device3::setB(input *b) {
	or_not_device3::b = b;
}

output *or_not_device3::getO() const {
	return o;
}

void or_not_device3::setO(output *o) {
	or_not_device3::o = o;
}

void or_not_device3::update_signal() {
	o->update_signal(!(a->get_signal() || b->get_signal() || c->get_signal()));
}

input *or_not_device3::getC() const {
	return c;
}

void or_not_device3::setC(input *c) {
	or_not_device3::c = c;
}

or_not_device3::or_not_device3(const string &name, input *a, input *b, input *c) : logic_device(name), a(a), b(b),
																				   c(c), o(nullptr) {}

signal or_not_device3::get_signal(output *out_iface) {
	if (out_iface == o) {
		return o->get_signal();
	}
	return false;
}

or_not_device3::~or_not_device3() = default;
