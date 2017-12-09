//
// Created by sworddestiny on 17-12-7.
//

#include "include/full_adder.h"
using namespace lm;

full_adder::~full_adder() {
	delete na, nb, nc;
	delete nanbc, nabnc, anbnc, abc;
	delete ab, ac, bc;
	delete lna, lnb, lnc;
	delete lnanbc, lnabnc, lanbnc, labc;
	delete lab, lac, lbc;
}

input *full_adder::getA() const {
	return a;
}

input *full_adder::getB() const {
	return b;
}

input *full_adder::getCi() const {
	return ci;
}

output *full_adder::getCo() const {
	return co;
}

void full_adder::setCo(output *co) {
	full_adder::co = co;
	dco.setO(co);
}

output *full_adder::getS() const {
	return s;
}

void full_adder::setS(output *s) {
	full_adder::s = s;
	ds.setO(s);
}

signal full_adder::get_signal(output *out_iface) {
	if (out_iface == co) {
		return co->get_signal();
	}
	if (out_iface == s) {
		return s->get_signal();
	}
	return false;
}

void full_adder::update_signal() {
	dna.update_signal();
	dnb.update_signal();
	dnc.update_signal();
	dab.update_signal();
	dac.update_signal();
	dbc.update_signal();
	dnanbc.update_signal();
	dnabnc.update_signal();
	danbnc.update_signal();
	dabc.update_signal();
	ds.update_signal();
	dco.update_signal();

	lna->update_signal();
	lnb->update_signal();
	lnc->update_signal();
	lnanbc->update_signal();
	lnabnc->update_signal();
	lanbnc->update_signal();
	labc->update_signal();
	lab->update_signal();
	lac->update_signal();
	lbc->update_signal();
}

full_adder::full_adder(const string &name, input *a, input *b, input *ci) : logic_device(name), a(a), b(b), ci(ci),
																			dna("dna", a), dnb("dnb", b),
																			dnc("dnc", ci),
																			na(new output("na", &dna)),
																			nb(new output("nb", &dnb)),
																			nc(new output("nc", &dnc)),
																			lna(new link("lna", na)),
																			lnb(new link("lnb", nb)),
																			lnc(new link("lnc", nc)),
																			dab("dab", a, b), dac("dac", a, ci),
																			dbc("dbc", b, ci),
																			ab(new output("ab", &dab)),
																			ac(new output("ac", &dac)),
																			bc(new output("bc", &dbc)),
																			lab(new link("lab", ab)),
																			lac(new link("lac", ac)),
																			lbc(new link("lbc", bc)),
																			dnanbc("dnanbc", lna, lnb, ci),
																			dnabnc("dnabnc", lna, b, lnc),
																			danbnc("danbnc", a, lnb, lnc),
																			dabc("dabc", a, b, ci),
																			nanbc(new output("nanbc", &dnanbc)),
																			nabnc(new output("nabnc", &dnabnc)),
																			anbnc(new output("anbnc", &danbnc)),
																			abc(new output("abc", &dabc)),
																			lnanbc(new link("lnanbc", nanbc)),
																			lnabnc(new link("lnabnc", nabnc)),
																			lanbnc(new link("lanbnc", anbnc)),
																			labc(new link("labc", abc)),
																			dco("dco", lab, lac, lbc),
																			ds("ds", lnanbc, lnabnc, lanbnc, labc) {
	dna.setOutput(na);
	dnb.setOutput(nb);
	dnc.setOutput(nc);
	dab.setO(ab);
	dac.setO(ac);
	dbc.setO(bc);
	dnanbc.setO(nanbc);
	dnabnc.setO(nabnc);
	danbnc.setO(anbnc);
	dabc.setO(abc);
}
