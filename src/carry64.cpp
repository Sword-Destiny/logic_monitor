//
// Created by sworddestiny on 17-12-7.
//

#include "carry64.h"

logic_monitor::carry64::~carry64() {
	for (int i = 0; i < N4; i++) {
		delete c4[i];
		delete p4[i];
		delete g4[i];
		delete lp4[i];
		delete lg4[i];
	}
	for (int i = 0; i < N16; i++) {
		delete c16[i];
		delete p16[i];
		delete g16[i];
        delete lp16[i];
        delete lg16[i];
	}
	for (int i = 0; i < N_LC16; i++) {
		delete lc16[i];
	}
	for (int i = 0; i < N_LC64; i++) {
		delete lc64[i];
	}
	delete[] lc16;
	delete[] lc64;
	delete[] c4;delete[] p4;delete[] g4;delete[] lp4;delete[] lg4;
	delete[] p16;delete[] g16;delete[] c16;delete[] lp16;delete[] lg16;
	delete c64;
	delete dp4_15c0;
	delete p4_15c0;
	delete lp4_15c0;
	delete dc;
	delete dng4_15;
	delete ng4_15;
	delete lng4_15;
}

logic_monitor::signal logic_monitor::carry64::get_signal(logic_monitor::output *out_iface) {
	if (out_iface == P64) {
		return P64->get_signal();
	}
	if (out_iface == G64) {
		return G64->get_signal();
	}
	if (out_iface == Cout) {
		return Cout->get_signal();
	}
	for (int i = 0; i < N; i++) {
		if (out_iface == c[i]) {
			return c[i]->get_signal();
		}
	}
	return false;
}

void logic_monitor::carry64::update_signal() {
	for (int i = 0; i < N4; i++) {
		c4[i]->update_signal();
	}
	for (int i = 0; i < N16; i++) {
		c16[i]->update_signal();
	}
	c64->update_signal();
	dp4_15c0->update_signal();
	dng4_15->update_signal();
	dc->update_signal();
	for (int i = 0; i < N4; i++) {
		lp4[i]->update_signal();
		lg4[i]->update_signal();
	}
	for (int i = 0; i < N16; i++) {
		lp16[i]->update_signal();
		lg16[i]->update_signal();
	}
	for (int i = 0; i < N_LC16; i++) {
		lc16[i]->update_signal();
	}
	for (int i = 0; i < N_LC64; i++) {
		lc64[i]->update_signal();
	}
	lp4_15c0->update_signal();
	lng4_15->update_signal();
	c[0]->update_signal(c0->get_signal());
}

logic_monitor::input *logic_monitor::carry64::getC0() const {
	return c0;
}

logic_monitor::output **logic_monitor::carry64::getC() const {
	return c;
}

void logic_monitor::carry64::setC(logic_monitor::output **c) {
	carry64::c = c;
	for (int i = 0; i < N4; i++) {
		c4[i]->setC1(c[i * 4 + 1]);
		c4[i]->setC2(c[i * 4 + 2]);
		c4[i]->setC3(c[i * 4 + 3]);
	}
	for (int i = 0; i < N16; i++) {
		c16[i]->setC1(c[i * 16 + 4]);
		c16[i]->setC2(c[i * 16 + 8]);
		c16[i]->setC3(c[i * 16 + 12]);
	}
	c64->setC1(c[16]);
	c64->setC2(c[16 * 2]);
	c64->setC3(c[16 * 3]);
	for (int i = 0; i < N_LC64; i++) {
		lc64[i]->setOut_iface(c[(i + 1) * 16]);
	}
	for (int i = 0; i < N_LC16; i++) {
		lc16[i]->setOut_iface(c[((i / 3) * 4 + i % 3 + 1) * 4]);
	}
}

logic_monitor::output *logic_monitor::carry64::getP64() const {
	return P64;
}

void logic_monitor::carry64::setP64(logic_monitor::output *P64) {
	carry64::P64 = P64;
	c64->setP(P64);
}

logic_monitor::output *logic_monitor::carry64::getG64() const {
	return G64;
}

void logic_monitor::carry64::setG64(logic_monitor::output *G64) {
	carry64::G64 = G64;
	c64->setG(G64);
}

logic_monitor::input **logic_monitor::carry64::getP() const {
	return p;
}

logic_monitor::input **logic_monitor::carry64::getG() const {
	return g;
}

logic_monitor::output *logic_monitor::carry64::getCout() const {
	return Cout;
}

void logic_monitor::carry64::setCout(logic_monitor::output *Cout) {
	carry64::Cout = Cout;
	dc->setO(Cout);
}

logic_monitor::carry64::carry64(const string &name, logic_monitor::input *c0, logic_monitor::input **p,
								logic_monitor::input **g) : logic_device(name), c0(c0), p(p), g(g) {
	int n4n = N / N4;
	c4 = new carry4 *[N4];
	p4 = new output *[N4];
	g4 = new output *[N4];
	lp4 = new link *[N4];
	lg4 = new link *[N4];
	c16 = new carry4 *[N16];
	p16 = new output *[N16];
	g16 = new output *[N16];
	lc16 = new linkp[N_LC16];
	lc64 = new linkp[N_LC64];
	lp16 = new link *[N16];
	lg16 = new link *[N16];
	int lc16_index = 0;
	for (int i = 0; i < N4; i++) {
		input *c0_tmp = nullptr;
		if (i == 0) {
			c0_tmp = c0;
		} else if (i % 4 == 0) {
			lc64[i / 4 - 1] = new link("lc64", nullptr);
			c0_tmp = lc64[0];
		} else {
			lc16[lc16_index] = new link("lc16", nullptr);
			c0_tmp = lc16[lc16_index];
			lc16_index++;
		}
		c4[i] = new carry4("c4", c0_tmp, g[i * n4n], g[i * n4n + 1], g[i * n4n + 2], g[i * n4n + 3], p[i * n4n],
						   p[i * n4n + 1], p[i * n4n + 2], p[i * n4n + 3]);
		p4[i] = new output("p4", c4[i]);
		g4[i] = new output("g4", c4[i]);
		c4[i]->setP(p4[i]);
		c4[i]->setG(g4[i]);
		lp4[i] = new link("lp4", p4[i]);
		lg4[i] = new link("lg4", g4[i]);
	}
	for (int i = 0; i < N16; i++) {
		input *c0_tmp = nullptr;
		if (i == 0) {
			c0_tmp = c0;
		} else {
			c0_tmp = lc64[i - 1];
		}
		c16[i] = new carry4("c16", c0_tmp, lg4[i * N4 / N16], lg4[i * N4 / N16 + 1], lg4[i * N4 / N16 + 2],
							lg4[i * N4 / N16 + 3], lp4[i * N4 / N16], lp4[i * N4 / N16 + 1], lp4[i * N4 / N16 + 2],
							lp4[i * N4 / N16 + 3]);
		p16[i] = new output("p16", c16[i]);
		g16[i] = new output("g16", c16[i]);
		c16[i]->setG(g16[i]);
		c16[i]->setP(p16[i]);
		lg16[i] = new link("lg16", g16[i]);
		lp16[i] = new link("lp16", p16[i]);
	}
	c64 = new carry4("c64", c0, lg16[0], lg16[1], lg16[2], lg16[3], lp16[0], lp16[1], lp16[2], lp16[3]);
	dp4_15c0 = new nand("dp4_15c0", lp4[N4 - 1], c0);
	p4_15c0 = new output("p4_15c0", dp4_15c0);
	dp4_15c0->setO(p4_15c0);
	lp4_15c0 = new link("lp4_15c0", p4_15c0);
	dng4_15 = new nd("dng4_15", lg4[N4 - 1]);
	ng4_15 = new output("ng4_15", dng4_15);
	dng4_15->setOutput(ng4_15);
	lng4_15 = new link("lng4_15", ng4_15);
	dc = new nand("dc", lp4_15c0, lng4_15);
}

void logic_monitor::carry64::print() {
	for (int i = 63; i >= 0; i--) {
		cout << p[i]->get_signal();
	}
	cout << " ";
	for (int i = 63; i >= 0; i--) {
		cout << g[i]->get_signal();
	}
	cout << " ";
	cout << c4[0]->getG()->get_signal() << "    ";
	cout << c4[0]->getP()->get_signal() << "    ";
	cout << c4[0]->getC1()->get_signal() << "     ";
	cout << c4[0]->getC2()->get_signal() << "     ";
	cout << c4[0]->getC3()->get_signal() << "     ";
	cout << c0->get_signal() << "  ";
	cout << P64->get_signal() << "   ";
	cout << G64->get_signal() << "   ";
	cout << Cout->get_signal() << "    ";
	for (int i = 63; i >= 0; i--) {
		cout << c[i]->get_signal();
	}
}

