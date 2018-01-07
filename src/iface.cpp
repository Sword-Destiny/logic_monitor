//
// Created by sworddestiny on 17-12-6.
//

#include "iface.h"
using namespace lm;


iface::iface(const string &name, iface_type type) : sgl(false), name(name), type(type), uid(get_uuid()) {

}

const string &iface::getName() const {
	return name;
}

void iface::setName(const string &name) {
	iface::name = name;
}

iface_type iface::getType() const {
	return type;
}

uuid iface::getUid() const {
	return uid;
}

iface::~iface() = default;

input_iface::input_iface(const string &name, iface_type type) : iface(name, type) {}

clock_iface::clock_iface(const string &name, clock *clk) : input_iface(name, CLOCK_IFACE),
														   clk(clk) {}

clock_iface::~clock_iface() = default;

signal clock_iface::get_signal() {
	return sgl;
}

void clock_iface::update_signal() {
	sgl = clk->get_signal();
}

signal output_iface::get_signal() {
	return sgl;
}

void output_iface::update_signal(signal sgl) {
	this->sgl = sgl;
}

output_iface::output_iface(const string &name, logic_device *device) : iface(name, OUTPUT_IFACE),
																	   device(device) {}

output_iface::~output_iface() = default;


signal link_iface::get_signal() {
	return sgl;
}

link_iface::link_iface(const string &name, output_iface *out_iface) : input_iface(name, LINK_IFACE),
																	  out_iface(out_iface) {}

void link_iface::update_signal() {
	sgl = out_iface->get_signal();
}

output_iface *link_iface::getOut_iface() const {
	return out_iface;
}

void link_iface::setOut_iface(output_iface *out_iface) {
	link_iface::out_iface = out_iface;
}

link_iface::~link_iface() = default;
