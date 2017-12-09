//
// Created by sworddestiny on 17-12-7.
//

#ifndef LOGICMONITOR_CARRY4_H
#define LOGICMONITOR_CARRY4_H

#include "iface.h"
#include "logic_device.h"
#include "and_not_device.h"
#include "not_device.h"
#include "and_not_device3.h"
#include "and_not_device4.h"

namespace lm {
	/**
	 * 4位进位逻辑
	 */
	class carry4 : public lgc_dev {
	public:
		carry4(const string &name, input *c0, input *g0, input *g1, input *g2, input *g3, input *p0, input *p1,
			   input *p2, input *p3);

		signal get_signal(output *out_iface) override;

		void update_signal() override;

		~carry4() override;

	private:
		input *c0; //输入c0
		input *g0, *g1, *g2, *g3; //输入g0-3 ,g[i]=a[i]&b[i]
		input *p0, *p1, *p2, *p3; //输入p0-3 ,p[i]=a[i]|b[i]
		output *P, *G; //输出 P G
		output *c1, *c2, *c3; //输出 c1 c2 c3
	private:
		nd dng0, dng1, dng2, dng3; // ～g0 , ~g1 , ~g2 , ~g3
		output *ng0, *ng1, *ng2, *ng3;
		link *lng0, *lng1, *lng2, *lng3;
		nand2 dp0c0, dp1g0, dp2g1, dp3g2; // ~(p0&c0),~(p1&g0),~(p2&g1),~(p3&g2)
		output *p0c0, *p1g0, *p2g1, *p3g2;
		link *lp0c0, *lp1g0, *lp2g1, *lp3g2;
		nand3 dp1p0c0, dp2p1g0, dp3p2g1; //~(p1&p0&c0),~(p2&p1&g0),~(p3&p2&p1)
		output *p1p0c0, *p2p1g0, *p3p2g1;
		link *lp1p0c0, *lp2p1g0, *lp3p2g1;
		nand4 dp2p1p0c0, dp3p2p1g0, dp3p2p1p0; //~(p2&p1&p0&c0),~(p3&p2&p1&g0),~(p3&p2&p1&p0)
		output *p2p1p0c0, *p3p2p1g0, *p3p2p1p0;
		link *lp2p1p0c0, *lp3p2p1g0, *lp3p2p1p0;
	private:
		nd dp; // P=p3&p2&p1&p0
		nand dc1; // c1=g0|p0&c0=~(~(g0)&~(p0&c0))
		nand3 dc2;// c[i+1]=g[i]|c[i]&p[i],以此类推
		nand4 dc3;// 同上
		nand4 dg; // G = g3|(p3&g2)|(p3&p2&g1)|(p3&p2&p1&g0)
	public:
		input *getC0() const;

		input *getG0() const;

		input *getG1() const;

		input *getG2() const;

		input *getG3() const;

		input *getP0() const;

		input *getP1() const;

		input *getP2() const;

		input *getP3() const;

		output *getP() const;

		void setP(output *P);

		output *getG() const;

		void setG(output *G);

		output *getC1() const;

		void setC1(output *c1);

		output *getC2() const;

		void setC2(output *c2);

		output *getC3() const;

		void setC3(output *c3);
	};

}


#endif //LOGICMONITOR_CARRY4_H
