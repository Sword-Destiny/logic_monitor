//
// Created by sworddestiny on 17-12-8.
//

#include "and_device.h"

logic_monitor::and_device::~and_device() = default;

logic_monitor::signal logic_monitor::and_device::get_signal(logic_monitor::output *out_iface) {
	if (out_iface == o) {
		return o->get_signal();
	}
	return false;
}

void logic_monitor::and_device::update_signal() {
	dnand.update_signal();
	dn.update_signal();
	lnand.update_signal();
}

logic_monitor::input *logic_monitor::and_device::getA() const {
	return a;
}

void logic_monitor::and_device::setA(logic_monitor::input *a) {
	and_device::a = a;
	dnand.setA(a);
}

logic_monitor::input *logic_monitor::and_device::getB() const {
	return b;
}

void logic_monitor::and_device::setB(logic_monitor::input *b) {
	and_device::b = b;
	dnand.setB(b);
}

logic_monitor::output *logic_monitor::and_device::getO() const {
	return o;
}

void logic_monitor::and_device::setO(logic_monitor::output *o) {
	and_device::o = o;
	dn.setOutput(o);
}

logic_monitor::and_device::and_device(const string &name, logic_monitor::input *a, logic_monitor::input *b)
		: logic_device(name), a(a), b(b), dnand("dnand", a, b), onand("onand", &dnand), lnand("lnand", &onand),
		  dn("dn", &lnand)
{
	dnand.setO(&onand);
}
