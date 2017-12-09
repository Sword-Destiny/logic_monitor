//
// Created by sworddestiny on 17-12-8.
//

#ifndef LOGICMONITOR_ADDER64_H
#define LOGICMONITOR_ADDER64_H

#include "iface.h"
#include "carry64.h"
#include "full_adder.h"
#include "or_device.h"
#include "and_device.h"

namespace lm {

	/**
	 * 64位加法器
	 */
	class adder64 : public lgc_dev {
	public:
		adder64(const string &name, input *c0, input **a, input **b);

		~adder64();

		signal get_signal(output *out_iface) override;

		void update_signal() override;

		void print();

	private:
		static const int BITS = 64;
		input *c0;    //低位进位
		input *a[BITS];    //操作数a
		input *b[BITS];    //操作数b
		output *s[BITS];    // s=a+b
		output *Cout;//向高位进位
	private:
		carry64 *c64; //64位进位逻辑
		and2 *dg[BITS]; //64个与门,g[i] = a[i]&b[i]
		or2 *dp[BITS]; //64个或门,p[i] = a[i]|b[i]
		output *og[BITS];
		output *op[BITS];
		link *lg[BITS];
		link *lp[BITS];
		output *oc[BITS];//c[i]代表第i位是否进位，这是64位进位逻辑的输出
		link *lc[BITS];
		full_adder *adder[BITS];//最后得到s要使用64个全加器
		output *P;
		output *G;
		output *adder_cout[BITS];

	public:
		input *getC0() const;

		input *const *getA() const;

		input *const *getB() const;

		output *const *getS() const;

		output *getCout() const;

		void setS(output **s);

		void setCout(output *Cout);
	};

}


#endif //LOGICMONITOR_ADDER64_H
