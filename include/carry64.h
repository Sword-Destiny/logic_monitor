//
// Created by sworddestiny on 17-12-7.
//

#ifndef LOGICMONITOR_CARRY64_H
#define LOGICMONITOR_CARRY64_H

#include "carry4.h"
#include "iface.h"

namespace lm {
	/**
	 * 64位进位逻辑
	 */
	class carry64 : public lgc_dev {
	private:
		static const int N4 = 16;
		static const int N16 = 4;
		static const int N = 64;
		static const int N_LC64 = 3;
		static const int N_LC16 = 12;
	public:
		~carry64();

		carry64(const string &name, input *c0, input **p, input **g);

		signal get_signal(output *out_iface) override;

		void update_signal() override;

		input *c0; //低位进位
		output **c; //输出进位
		output *P64, *G64;
		input **p; //输入p[0-63]
		input **g; //输入g[0-63]
		output *Cout;//输出Cout，向高位进位

		void print();

	private:
		carry4 **c4; //第一层16个4位并行进位逻辑
		output **p4, **g4; //第一层每个c4产生的p和g
		link **lp4, **lg4;
		carry4 **c16;//第二层4个4位并行进位逻辑
		output **p16, **g16;//第二层每个c4产生的p和g
		link **lp16, **lg16;
		carry4 *c64;//第三层一个4位进位逻辑

		nand2 *dp4_15c0; // ~(p4[15] & c0[15])
		output *p4_15c0;
		link *lp4_15c0;
		nd *dng4_15; // ~g4[15]
		output *ng4_15;
		link *lng4_15;
		nand2 *dc;
		// 最高的一个carry4器件用于生成Cout
		// cout = g4[15] | p4[15] & c0[15]
		//      = ~( ~g4[15] & ~(p4[15] & c0[15]))

		linkp *lc16; // 第一层的c0来自于第二层的输出c1-3，第一个例外来自于c0
		linkp *lc64; // 第二层的c0来自于第三层的输出c1-3，第一个例外来自于c0

	public:

		input *getC0() const;

		output **getC() const;

		void setC(output **c);

		output *getP64() const;

		void setP64(output *P64);

		output *getG64() const;

		void setG64(output *G64);

		input **getP() const;

		input **getG() const;

		output *getCout() const;

		void setCout(output *cout);

	};
}


#endif //LOGICMONITOR_CARRY64_H
