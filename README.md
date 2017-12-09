# logic_monito
***
逻辑电路模拟
这是一个用于模拟逻辑电路信号的程序
***
##使用方法
***
参照main.cpp的test\_not/test\_nand2/test\_full\_adder/test\_carry4函数
1. 定义一个logic\_document
2. 定义需要的时钟信号\(periodic\_clock\*,constant\_clock\*\)
3. 定义一系列输入接口\(input\_iface\*/input\*\),输入接口可以是一个时钟接口\(clock\_iface\*,即信号来自于时钟\),也可以是一个link接口\(link\*,link\_iface\*,即信号来自于其他逻辑器件的输出\)
4. 定义逻辑器件\(logic\_device\*/lgc\_dev\*\)
5. 定义输出端口\(output\_iface\*/output\*\)
6. 设置输出端口
7. 将所有的你定义的时钟,端口和器件都添加到logic\_document里面
8. 调用logic\_document的update\_document函数,每调用一次,时钟就会经过一个延迟,逻辑器件会经过一级门延迟,端口会更新一次
9. 调用逻辑器件,端口或者时钟的get\_signal函数获取当前的信号\(carry64和adder64有我自定义的print函数\)\
***
```
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
```
***
##注意事项
***
上述顺序不一定要完全遵守,但是谨记
1. input\_iface是虚类,应该使用其子类clock\_iface或者link\_iface
2. 必须先定义输入端口,然后是逻辑器件,然后是输出端口,最后给逻辑器件设置输出端口,因为逻辑器件的构造函数要用input作为参数,output的构造函数使用器件作为参数
3. 即使一个器件的某个输出端口未被使用,也要定义输出端口并且设置,不然的话在update的时候会出错
4. 器件可以复用,将两个器件连接起来的方式是: 器件一\->output端口\->link端口\->器件二 (link\_iface继承自input\_iface所以可以当作输入端口使用)
***
##使用现成的逻辑器件构成新的逻辑器件的方式,我们以二输入与门(and2)为例
计算机是反逻辑,与门使用的是与非门和非门连接 o = ~ \(~\(a&b\)\)
1. 继承lgc\_dev
`
#include "logic_device.h"
#include "iface.h"
namespace lm {
    class and_device : public lgc_dev{
    };
}
`
2. 定义输入端口,输出端口和逻辑器件 
`
	input *a;
	input *b;
	output *o; //总输出端口
    
	nand2 dnand; // dnand = ~(a&b) ,nand2是与非门
	output onand; // nand2的输出端口 ~(a&b)
	link lnand; // link端口连接nand2的输出端口,作为非门的输入端口
	nd dn; // ~(dnand) ,dn是非门
`
3. 实现父类虚函数和构造函数,注意构造函数只应该把输入端口作为参数
`
    signal get_signal(output *out_iface) override;
    void update_signal() override;
    and_device(const string &name, input *a, input *b);
`
4. 构造函数的实现
`
    logic_monitor::and_device::and_device(const string &name, logic_monitor::input *a, logic_monitor::input *b)
    		: logic_device(name), a(a), b(b), dnand("dnand", a, b), onand("onand", &dnand), lnand("lnand", &onand),
    		  dn("dn", &lnand)
    {
	    dnand.setO(&onand);
    }
`
    与非门dnand将a和b作为输入,输出端口为onand,然后是lnand,最后是dn将lnand作为自己的输入,
    别忘了dnand将onand作为自己的输出端口是需要调用setter函数的,
    由于c++类成员变量的初始化顺序是按照头文件定义顺序而不是构造函数头写的顺序,所以定义顺序一定不能错,
    为了避免由于定义顺序导致初始化顺序出错,建议成员变量使用指针的形式,这里没有使用指针是因为比较简单,具体可以参考carry64和adder64的实现,
    使用指针之后就要注意释放空间的问题,要实现析构函数,一般是本着谁申请谁释放的原则,
    比如这里a,b,o都是整体的输入和输出端口,都是通过参数获取,不应该由本类申请和释放空间,
    而dnand,onand,lnand,dn则是自己内部的结构,如果使用指针,则需要由本类管理释放,
    使用指针的好处就是不用在构造函数头部写的那么臃肿,也不用担心c++成员变量的默认初始化顺序问题.
    这里非门dn的输出端口没有设置,因为当这个逻辑器件初始化的时候,还不知道整体的输出端口是什么,所以要放到setter函数里面.
5. update\_signal函数的实现
    先update所有的逻辑器件,然后update所有的link_iface端口
	`
    dnand.update_signal();
	dn.update_signal();
	lnand.update_signal();
	`
6. get\_signal的实现
`
	if (out_iface == o) {
		return o->get_signal();
	}
	return false;
`
6)setter函数
    setter函数除了设置自己的成员变量之外,别忘了设置相关的内部器件的成员变量
    比如setO函数,除了自己的output设置成o之外,dn这个非门的输出端口也是o
`
    and_device::o = o;
	dn.setOutput(o);
`
7)通过以上的6步,我们就利用基本的器件与非门和非门构造出了与门,其他的复杂器件也是这么构造的
