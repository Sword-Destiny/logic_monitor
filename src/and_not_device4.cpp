//
// Created by sworddestiny on 17-12-7.
//

#include "and_not_device4.h"
using namespace lm;

and_not_device4::and_not_device4(const string &name, input *a, input *b, input *c, input *d) : logic_device(name), a(a),
																							   b(b), c(c), d(d) {}

input *and_not_device4::getA() const {
	return a;
}

void and_not_device4::setA(input *a) {
	and_not_device4::a = a;
}

input *and_not_device4::getB() const {
	return b;
}

void and_not_device4::setB(input *b) {
	and_not_device4::b = b;
}

input *and_not_device4::getC() const {
	return c;
}

void and_not_device4::setC(input *c) {
	and_not_device4::c = c;
}

input *and_not_device4::getD() const {
	return d;
}

void and_not_device4::setD(input *d) {
	and_not_device4::d = d;
}

output *and_not_device4::getO() const {
	return o;
}

void and_not_device4::setO(output *o) {
	and_not_device4::o = o;
}

signal and_not_device4::get_signal(output *out_iface) {
	if (out_iface == o) {
		return o->get_signal();
	}
	return false;
}

void and_not_device4::update_signal() {
	o->update_signal(!(a->get_signal() && b->get_signal() && c->get_signal() && d->get_signal()));
}

and_not_device4::~and_not_device4() = default;
