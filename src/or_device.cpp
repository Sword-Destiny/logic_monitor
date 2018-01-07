//
// Created by sworddestiny on 17-12-8.
//

#include "or_device.h"

logic_monitor::input *logic_monitor::or_device::getA() const {
	return a;
}

void logic_monitor::or_device::setA(logic_monitor::input *a) {
	or_device::a = a;
	dnor.setA(a);
}

logic_monitor::input *logic_monitor::or_device::getB() const {
	return b;
}

void logic_monitor::or_device::setB(logic_monitor::input *b) {
	or_device::b = b;
	dnor.setB(b);
}

logic_monitor::output *logic_monitor::or_device::getO() const {
	return o;
}

void logic_monitor::or_device::setO(logic_monitor::output *o) {
	or_device::o = o;
	dn.setOutput(o);
}

logic_monitor::signal logic_monitor::or_device::get_signal(logic_monitor::output *out_iface) {
	if (out_iface == o) {
		return o->get_signal();
	}
	return false;
}

void logic_monitor::or_device::update_signal() {
	dnor.update_signal();
	dn.update_signal();
	lnor.update_signal();
}

logic_monitor::or_device::or_device(const string &name, logic_monitor::input *a, logic_monitor::input *b)
		: logic_device(name), a(a), b(b), dnor("dnor", a, b), onor("onor", &dnor), lnor("lnor", &onor),
		  dn("dn", &lnor)
{
	dnor.setO(&onor);
}

logic_monitor::or_device::~or_device() = default;
