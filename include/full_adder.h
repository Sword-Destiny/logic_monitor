//
// Created by sworddestiny on 17-12-7.
//

#ifndef LOGICMONITOR_FULL_ADDER_H
#define LOGICMONITOR_FULL_ADDER_H

#include "logic_device.h"
#include "iface.h"
#include "not_device.h"
#include "and_not_device3.h"
#include "and_not_device4.h"
#include "and_not_device.h"

namespace lm {

	/**
	 * 全加器
	 */
	typedef class full_adder :public lgc_dev{

	public:
		full_adder(const string &name, input *a, input *b, input *ci);

		signal get_signal(output *out_iface) override;

		void update_signal() override;

		~full_adder() override ;
	private:
		input *a,*b,*ci; // 输入a,b,c(低位进位)
		output *co,*s; // co:向高位进位,s:和
	private:
		nd dna,dnb,dnc;// ～a,~b,~c
		output *na,*nb,*nc;
		link *lna,*lnb,*lnc;
		nand dab,dac,dbc; // a&b,a&c,b&c
		output *ab,*ac,*bc;
		link *lab,*lac,*lbc;
		nand3 dnanbc,dnabnc,danbnc,dabc; // ~a&~b&c , ~a&b&~c , a&~b&~c , a&b&c
		output *nanbc,*nabnc,*anbnc,*abc;
		link *lnanbc,*lnabnc,*lanbnc,*labc;
		nand3 dco; // cout = ~(~(a&b) & ~(b&c) & ~(a&c))
		nand4 ds;  // s = ～( ~(~a&~b&c) & ~(~a&b&~c) & ~(a&~b&~c) & ~(a&b&c) )
	public:
		input *getA() const;

		input *getB() const;

		input *getCi() const;

		output *getCo() const;

		void setCo(output *co);

		output *getS() const;

		void setS(output *s);

	}fadd;

}


#endif //LOGICMONITOR_FULL_ADDER_H
