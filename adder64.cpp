//
// Created by sworddestiny on 17-12-8.
//

#include "include/adder64.h"

logic_monitor::input *logic_monitor::adder64::getC0() const {
	return c0;
}

logic_monitor::input *const *logic_monitor::adder64::getA() const {
	return a;
}

logic_monitor::input *const *logic_monitor::adder64::getB() const {
	return b;
}

logic_monitor::output *const *logic_monitor::adder64::getS() const {
	return s;
}

logic_monitor::output *logic_monitor::adder64::getCout() const {
	return Cout;
}

void logic_monitor::adder64::setCout(logic_monitor::output *Cout) {
	adder64::Cout = Cout;
	c64->setCout(Cout);
}

void logic_monitor::adder64::setS(logic_monitor::output **s) {
	for (int i = 0; i < BITS; i++) {
		this->s[i] = s[i];
		this->adder[i]->setS(s[i]);
	}
}

logic_monitor::adder64::~adder64() {
	for (int i = 0; i < BITS; i++) {
		delete dg[i];
		delete dp[i];
		delete og[i];
		delete op[i];
		delete lg[i];
		delete lp[i];
		delete oc[i];
		delete lc[i];
		delete adder[i];
		delete adder_cout[i];
	}
	delete c64;
	delete P;
	delete G;
}

logic_monitor::signal logic_monitor::adder64::get_signal(logic_monitor::output *out_iface) {
	if (out_iface == Cout) {
		return Cout->get_signal();
	}
	for (auto &i : s) {
		if (out_iface == i) {
			return i->get_signal();
		}
	}
	return false;
}

void logic_monitor::adder64::update_signal() {
	for (int i = 0; i < BITS; i++) {
		dg[i]->update_signal();
		dp[i]->update_signal();
	}
	c64->update_signal();
	for (auto &a : adder) {
		a->update_signal();
	}
	for (int i = 0; i < BITS; i++) {
		lg[i]->update_signal();
		lp[i]->update_signal();
		lc[i]->update_signal();
	}
}

void logic_monitor::adder64::print() {
	for (int i = 63; i >= 0; i--) {
		cout << a[i]->get_signal();
	}
	cout << " ";
	for (int i = 63; i >= 0; i--) {
		cout << b[i]->get_signal();
	}
	cout << " ";
	printf("%2d ", c0->get_signal());
	printf("%4d ", Cout->get_signal());
	for (int i = 63; i >= 0; i--) {
		cout << s[i]->get_signal();
	}
}

logic_monitor::adder64::adder64(const string &name, logic_monitor::input *c0, logic_monitor::input **a,
								logic_monitor::input **b) : logic_device(name), c0(c0) {
	for (int i = 0; i < BITS; i++) {
		this->a[i] = a[i];
		this->b[i] = b[i];
	}
	for (int i = 0; i < BITS; i++) {
		dg[i] = new and2("dg", a[i], b[i]);
		og[i] = new output("og", dg[i]);
		dg[i]->setO(og[i]);
		lg[i] = new link("lg", og[i]);
		dp[i] = new or2("dp", a[i], b[i]);
		op[i] = new output("op", dp[i]);
		dp[i]->setO(op[i]);
		lp[i] = new link("lp", op[i]);
	}
	c64 = new carry64("c64", c0, (input **) (lp), (input **) (lg));
	for (int i = 0; i < BITS; i++) {
		oc[i] = new output("oc", c64);
		lc[i] = new link("lc", oc[i]);
	}
	P = new output("P", c64);
	G = new output("G", c64);
	c64->setC(oc);
	c64->setP64(P);
	c64->setG64(G);
	for (int i = 0; i < BITS; i++) {
		adder[i] = new full_adder("adder", a[i], b[i], lc[i]);
		adder_cout[i] = new output("adder_cout", adder[i]);
		adder[i]->setCo(adder_cout[i]);
	}
}
