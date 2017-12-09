//
// Created by sworddestiny on 17-12-7.
//

#include "include/carry4.h"
using namespace lm;

input *carry4::getC0() const {
	return c0;
}

input *carry4::getG0() const {
	return g0;
}

input *carry4::getG1() const {
	return g1;
}

input *carry4::getG2() const {
	return g2;
}

input *carry4::getG3() const {
	return g3;
}

input *carry4::getP0() const {
	return p0;
}

input *carry4::getP1() const {
	return p1;
}

input *carry4::getP2() const {
	return p2;
}

input *carry4::getP3() const {
	return p3;
}

output *carry4::getP() const {
	return P;
}

void carry4::setP(output *P) {
	carry4::P = P;
	dp.setOutput(P);
}

output *carry4::getG() const {
	return G;
}

void carry4::setG(output *G) {
	carry4::G = G;
	dg.setO(G);
}

output *carry4::getC1() const {
	return c1;
}

void carry4::setC1(output *c1) {
	carry4::c1 = c1;
	dc1.setO(c1);
}

output *carry4::getC2() const {
	return c2;
}

void carry4::setC2(output *c2) {
	carry4::c2 = c2;
	dc2.setO(c2);
}

output *carry4::getC3() const {
	return c3;
}

void carry4::setC3(output *c3) {
	carry4::c3 = c3;
	dc3.setO(c3);
}

carry4::carry4(const string &name, input *c0, input *g0, input *g1, input *g2, input *g3, input *p0, input *p1,
			   input *p2, input *p3) : logic_device(name), c0(c0), g0(g0), g1(g1), g2(g2), g3(g3), p0(p0), p1(p1),
									   p2(p2), p3(p3), P(nullptr), G(nullptr), c1(nullptr), c2(nullptr), c3(nullptr),
									   dng0("dng0", g0), dng1("dng1", g1), dng2("dng2", g2), dng3("dng3", g3),
									   ng0(new output("ng0", &dng0)), ng1(new output("ng1", &dng1)),
									   ng2(new output("ng2", &dng2)), ng3(new output("ng3", &dng3)),
									   lng0(new link("lng0", ng0)), lng1(new link("lng1", ng1)),
									   lng2(new link("lng2", ng2)), lng3(new link("lng3", ng3)),
									   dp0c0("dp0c0", p0, c0), dp1g0("dp1g0", p1, g0),
									   dp2g1("dp2g1", p2, g1), dp3g2("dp3g2", p3, g2),
									   p0c0(new output("p0c0", &dp0c0)), p1g0(new output("p1g0", &dp1g0)),
									   p2g1(new output("p2g1", &dp2g1)), p3g2(new output("p3g2", &dp3g2)),
									   lp0c0(new link("lp0c0", p0c0)), lp1g0(new link("lp1g0", p1g0)),
									   lp2g1(new link("lp2g1", p2g1)), lp3g2(new link("lp3g2", p3g2)),
									   dp1p0c0("dp1p0c0", p1, p0, c0),
									   dp2p1g0("dp2p1g0", p2, p1, g0),
									   dp3p2g1("dp3p2g1", p3, p2, g1),
									   p1p0c0(new output("p1p0c0", &dp1p0c0)),
									   p2p1g0(new output("p2p1pg0", &dp2p1g0)),
									   p3p2g1(new output("p3p2g1", &dp3p2g1)),
									   lp1p0c0(new link("lp1p0c0", p1p0c0)),
									   lp2p1g0(new link("lp2p1g0", p2p1g0)),
									   lp3p2g1(new link("lp3p2g1", p3p2g1)),
									   dp2p1p0c0("dp2p1p0c0", p2, p1, p0, c0),
									   dp3p2p1g0("dp3p2p1g0", p3, p2, p1, g0),
									   dp3p2p1p0("dp3p2p1p0", p3, p2, p1, p0),
									   p2p1p0c0(new output("p2p1p0c0", &dp2p1p0c0)),
									   p3p2p1g0(new output("p3p2p1g0", &dp3p2p1g0)),
									   p3p2p1p0(new output("p3p2p1p0", &dp3p2p1p0)),
									   lp2p1p0c0(new link("lp2p1p0c0", p2p1p0c0)),
									   lp3p2p1g0(new link("lp3p2p1g0", p3p2p1g0)),
									   lp3p2p1p0(new link("lp3p2p1p0", p3p2p1p0)),
									   dp("dp", lp3p2p1p0),
									   dc1("dc1", lng0, lp0c0),
									   dc2("dc2", lng1, lp1g0, lp1p0c0),
									   dc3("dc3", lng2, lp2g1, lp2p1g0, lp2p1p0c0),
									   dg("dg", lng3, lp3g2, lp3p2g1, lp3p2p1g0) {
	dng0.setOutput(ng0);
	dng1.setOutput(ng1);
	dng2.setOutput(ng2);
	dng3.setOutput(ng3);

	dp0c0.setO(p0c0);
	dp1g0.setO(p1g0);
	dp2g1.setO(p2g1);
	dp3g2.setO(p3g2);

	dp1p0c0.setO(p1p0c0);
	dp2p1g0.setO(p2p1g0);
	dp3p2g1.setO(p3p2g1);

	dp2p1p0c0.setO(p2p1p0c0);
	dp3p2p1g0.setO(p3p2p1g0);
	dp3p2p1p0.setO(p3p2p1p0);


}

signal carry4::get_signal(output *out_iface) {
	if (out_iface == P) {
		return P->get_signal();
	}
	if (out_iface == G) {
		return G->get_signal();
	}
	if (out_iface == c1) {
		return c1->get_signal();
	}
	if (out_iface == c2) {
		return c2->get_signal();
	}
	if (out_iface == c3) {
		return c3->get_signal();
	}
	return false;
}

void carry4::update_signal() {
	dp.update_signal();
	dc1.update_signal();
	dc2.update_signal();
	dc3.update_signal();
	dg.update_signal();
	dng0.update_signal();
	dng1.update_signal();
	dng2.update_signal();
	dng3.update_signal();
	dp0c0.update_signal();
	dp1g0.update_signal();
	dp2g1.update_signal();
	dp3g2.update_signal();
	dp1p0c0.update_signal();
	dp2p1g0.update_signal();
	dp3p2g1.update_signal();
	dp2p1p0c0.update_signal();
	dp3p2p1g0.update_signal();
	dp3p2p1p0.update_signal();

	lng0->update_signal();
	lng1->update_signal();
	lng2->update_signal();
	lng3->update_signal();

	lp0c0->update_signal();
	lp1g0->update_signal();
	lp2g1->update_signal();
	lp3g2->update_signal();

	lp1p0c0->update_signal();
	lp2p1g0->update_signal();
	lp3p2g1->update_signal();

	lp2p1p0c0->update_signal();
	lp3p2p1g0->update_signal();
	lp3p2p1p0->update_signal();
}

carry4::~carry4() {
	delete ng0;delete ng1;delete ng2;delete ng3;
	delete lng0;delete lng1;delete lng2;delete lng3;
	delete p0c0;delete p1g0;delete p2g1;delete p3g2;
	delete lp0c0;delete lp1g0;delete lp2g1;delete lp3g2;
	delete p1p0c0;delete p2p1g0;delete p3p2g1;
	delete lp1p0c0;delete lp2p1g0;delete lp3p2g1;
	delete p2p1p0c0;delete p3p2p1g0;
	delete lp2p1p0c0;delete lp3p2p1g0;
	delete p3p2p1p0;
	delete lp3p2p1p0;
};
