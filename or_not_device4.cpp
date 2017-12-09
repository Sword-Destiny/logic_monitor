//
// Created by sworddestiny on 17-12-7.
//

#include "include/or_not_device4.h"
using namespace lm;

input *or_not_device4::getA() const {
	return a;
}

void or_not_device4::setA(input *a) {
	or_not_device4::a = a;
}

input *or_not_device4::getB() const {
	return b;
}

void or_not_device4::setB(input *b) {
	or_not_device4::b = b;
}

input *or_not_device4::getC() const {
	return c;
}

void or_not_device4::setC(input *c) {
	or_not_device4::c = c;
}

input *or_not_device4::getD() const {
	return d;
}

void or_not_device4::setD(input *d) {
	or_not_device4::d = d;
}

void or_not_device4::update_signal() {
	o->update_signal(!(a->get_signal() || b->get_signal() || c->get_signal() || d->get_signal()));
}

signal or_not_device4::get_signal(output *out_iface) {
	if (out_iface == o) {
		return o->get_signal();
	}
	return false;
}

or_not_device4::or_not_device4(const string &name, input *a, input *b, input *c, input *d) : logic_device(name), a(a),
																							 b(b), c(c), d(d),
																							 o(nullptr) {}

or_not_device4::~or_not_device4() = default;
