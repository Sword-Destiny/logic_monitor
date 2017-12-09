#include <iostream>
#include "include/document.h"
#include "include/carry4.h"
#include "include/full_adder.h"
#include "include/carry64.h"
#include "include/adder64.h"

using namespace lm;

void test_not();

void test_nand2();

void test_carry4();

void test_full_adder();

void test_carry_64(int seed);

void test_adder_64(int seed);

int main() {
	test_adder_64(7);
}

void test_adder_64(int seed) {
	logic_document doc("doc");
	auto **p = new input *[64];
	auto **g = new input *[64];
	auto **s = new output *[64];

	int i1 = (seed >> 3) % 2;
	int i2 = (seed >> 2) % 2;
	int i3 = (seed >> 1) % 2;
	int i4 = seed % 2;

	for (int i = 0; i < 64; i++) {
		if (i % 2 == 0) {
			p[i] = new clock_iface("p", i1 == 1 ? constant_clock::one() : constant_clock::zero());
			g[i] = new clock_iface("g", i2 == 1 ? constant_clock::one() : constant_clock::zero());
		} else {
			p[i] = new clock_iface("p", i3 == 1 ? constant_clock::one() : constant_clock::zero());
			g[i] = new clock_iface("g", i4 == 1 ? constant_clock::one() : constant_clock::zero());
		}
		doc.ifaces.push_back(p[i]);
		doc.ifaces.push_back(g[i]);
	}
	doc.clocks.push_back(constant_clock::one());
	doc.clocks.push_back(constant_clock::zero());

	clock_iface c0("c0", constant_clock::one());
	doc.ifaces.push_back(&c0);

	adder64 *a64 = new adder64("a64", &c0, p, g);
	doc.devices.push_back(a64);
	output Cout("Cout", a64);
	a64->setCout(&Cout);
	doc.ifaces.push_back(&Cout);
	for (int i = 0; i < 64; i++) {
		s[i] = new output("s", a64);
		doc.ifaces.push_back(s[i]);
	}
	a64->setS(s);
	printf("%4s %64s %64s c0 Cout %64s\n", "time", "a", "b", "s");
	for (int i = 0; i < 100; i++) {
		doc.update_document();
		printf("%4d ", i);
		a64->print();
		cout<<endl;
	}


	for (int i = 0; i < 64; i++) {
		delete p[i], g[i], s[i];
	}
	delete[] p, g, s;
	delete a64;
}

void test_carry_64(int seed) {
	logic_document doc("doc");
	auto **p = new input *[64];
	auto **g = new input *[64];
	auto **c = new output *[64];

	int i1 = (seed >> 3) % 2;
	int i2 = (seed >> 2) % 2;
	int i3 = (seed >> 1) % 2;
	int i4 = seed % 2;

	for (int i = 0; i < 64; i++) {
		if (i % 2 == 0) {
			p[i] = new clock_iface("p", i1 == 1 ? constant_clock::one() : constant_clock::zero());
			g[i] = new clock_iface("g", i2 == 1 ? constant_clock::one() : constant_clock::zero());
		} else {
			p[i] = new clock_iface("p", i3 == 1 ? constant_clock::one() : constant_clock::zero());
			g[i] = new clock_iface("g", i4 == 1 ? constant_clock::one() : constant_clock::zero());
		}
		doc.ifaces.push_back(p[i]);
		doc.ifaces.push_back(g[i]);
	}
	doc.clocks.push_back(constant_clock::one());
	doc.clocks.push_back(constant_clock::zero());

	clock_iface c0("c0", constant_clock::one());
	doc.ifaces.push_back(&c0);

	carry64 *c64 = new carry64("c64", &c0, p, g);
	doc.devices.push_back(c64);
	output P("P", c64);
	output G("G", c64);
	output Cout("Cout", c64);
	c64->setCout(&Cout);
	c64->setG64(&G);
	c64->setP64(&P);
	doc.ifaces.push_back(&P);
	doc.ifaces.push_back(&G);
	doc.ifaces.push_back(&Cout);
	for (int i = 0; i < 64; i++) {
		c[i] = new output("c", c64);
		doc.ifaces.push_back(c[i]);
	}
	c64->setC(c);
	printf("%64s %64s c40G c40P c40c1 c40c2 c40c3 c0 P64 G64 cout %64s\n", "p", "g", "c");
	for (int i = 0; i < 100; i++) {

		doc.update_document();
		c64->println();
	}


	for (int i = 0; i < 64; i++) {
		delete p[i], g[i], c[i];
	}
	delete[] p, g, c;
	delete c64;
}

void test_full_adder() {
	logic_document doc("doc");
	auto *cycle_a = new bool[8]{true, true, true, true, false, false, false, false};
	auto *cycle_b = new bool[8]{true, true, false, false, true, true, false, false};
	auto *cycle_c = new bool[8]{true, false, true, false, true, false, true, false};

	periodic_clock ca(3, false, true, cycle_a, 8, 2, 5, false, "ca");
	periodic_clock cb(3, false, true, cycle_b, 8, 2, 5, false, "cb");
	periodic_clock cc(3, false, true, cycle_c, 8, 2, 5, false, "cc");
	clock_iface a("a", &ca);
	clock_iface b("b", &cb);
	clock_iface c("a", &cc);

	fadd f("f", &a, &b, &c);

	output co("co", &f);
	output s("s", &f);

	f.setCo(&co);
	f.setS(&s);

	doc.clocks.push_back(&ca);
	doc.clocks.push_back(&cb);
	doc.clocks.push_back(&cc);
	doc.ifaces.push_back(&a);
	doc.ifaces.push_back(&b);
	doc.ifaces.push_back(&c);
	doc.ifaces.push_back(&co);
	doc.ifaces.push_back(&s);
	doc.devices.push_back(&f);
	cout << "a b ci s co" << endl;
	for (int i = 0; i < 100; i++) {
		doc.update_document();
		cout << a.get_signal() << " " << b.get_signal() << " " << c.get_signal() << "  " << s.get_signal() << " "
			 << co.get_signal() << endl;
	}

	delete[] cycle_a, cycle_b, cycle_c;
}

void test_carry4() {
	logic_document doc("doc");
	auto *cycle = new bool[2]{true, false};

	periodic_clock c1(3, false, true, cycle, 2, 2, 64, false, "c1");
	periodic_clock c2(3, false, true, cycle, 2, 4, 32, false, "c2");
	periodic_clock c3(3, false, true, cycle, 2, 8, 16, false, "c3");
	periodic_clock c4(3, false, true, cycle, 2, 16, 8, false, "c4");

	clock_iface a1("a1", &c1);
	clock_iface a2("a1", &c2);
	clock_iface a3("a1", &c3);
	clock_iface a4("a1", &c4);

	clock_iface b1("b1", &c4);
	clock_iface b2("b1", &c3);
	clock_iface b3("b1", &c2);
	clock_iface b4("b1", &c1);

	clock_iface c0("c0", constant_clock::zero());

	carry4 cy4("cy4", &c0, &a1, &a2, &a3, &a4, &b1, &b2, &b3, &b4);
	output P("P", &cy4);
	output G("G", &cy4);
	output oc1("oc1", &cy4);
	output oc2("oc2", &cy4);
	output oc3("oc3", &cy4);
	cy4.setP(&P);
	cy4.setG(&G);
	cy4.setC1(&oc1);
	cy4.setC2(&oc2);
	cy4.setC3(&oc3);

	doc.clocks.push_back(&c1);
	doc.clocks.push_back(&c2);
	doc.clocks.push_back(&c3);
	doc.clocks.push_back(&c4);
	doc.ifaces.push_back(&a1);
	doc.ifaces.push_back(&a2);
	doc.ifaces.push_back(&a3);
	doc.ifaces.push_back(&a4);
	doc.ifaces.push_back(&b1);
	doc.ifaces.push_back(&b2);
	doc.ifaces.push_back(&b3);
	doc.ifaces.push_back(&b4);
	doc.ifaces.push_back(&P);
	doc.ifaces.push_back(&G);
	doc.ifaces.push_back(&oc1);
	doc.ifaces.push_back(&oc2);
	doc.ifaces.push_back(&oc3);
	doc.devices.push_back(&cy4);

	cout << "a1 a2 a3 a4 b1 b2 b3 b4 c0 P G c1 c2 c3" << endl;
	for (int i = 0; i < 200; i++) {
		doc.update_document();
		cout << a1.get_signal() << "  " << a2.get_signal() << "  " << a3.get_signal() << "  " << a4.get_signal() << "  "
			 << b1.get_signal() << "  " << b2.get_signal() << "  " << b3.get_signal() << "  " << b4.get_signal() << "  "
			 << c0.get_signal() << "  " << P.get_signal() << " " << G.get_signal() << " " << c1.get_signal() << "  "
			 << c2.get_signal() << "  " << c3.get_signal() << "  " << endl;
	}

	delete[] cycle;
}

void test_nand2() {
	logic_document doc("doc");
	auto *cycle_a = new bool[4]{true, false, true, false};
	auto *cycle_b = new bool[4]{true, true, false, false};

	periodic_clock ca(3, false, true, cycle_a, 4, 2, 2, false, "ca");
	periodic_clock cb(3, false, true, cycle_b, 4, 2, 2, false, "cb");
	clock_iface a("a", &ca);
	clock_iface b("b", &cb);
	and_not_device nand("nand", &a, &b);
	output o("o", &nand);
	nand.setO(&o);

	doc.clocks.push_back(&ca);
	doc.clocks.push_back(&cb);
	doc.ifaces.push_back(&a);
	doc.ifaces.push_back(&b);
	doc.ifaces.push_back(&o);
	doc.devices.push_back(&nand);
	cout << "ca cb a b o" << endl;
	for (int i = 0; i < 100; i++) {
		doc.update_document();
		cout << ca << "  " << cb << "  " << a.get_signal() << " " << b.get_signal() << " "
			 << o.get_signal() << endl;
	}

	delete[] cycle_a, cycle_b;
}

void test_not() {
	logic_document doc("doc");
	auto *cycle = new bool[4]{true, false, true, false};

	periodic_clock c(3, false, true, cycle, 4, 2, 2, false, "c");
	clock_iface a("a", &c);
	nd n1("n1", &a);
	output_iface on1("on1", &n1);
	n1.setOutput(&on1);
	link_iface l1("l1", &on1);
	nd n2("n2", &l1);
	output_iface on2("on2", &n2);
	n2.setOutput(&on2);

	doc.clocks.push_back(&c);
	doc.ifaces.push_back(&a);
	doc.ifaces.push_back(&on1);
	doc.ifaces.push_back(&l1);
	doc.ifaces.push_back(&on2);
	doc.devices.push_back(&n1);
	doc.devices.push_back(&n2);
	cout << "c a on1 l1 on2" << endl;
	for (int i = 0; i < 100; i++) {
		doc.update_document();
		cout << c.get_signal() << " " << a.get_signal() << " " << on1.get_signal() << "   " << l1.get_signal() << "  "
			 << on2.get_signal() << endl;
	}

	delete[] cycle;
}