//
// Created by sworddestiny on 17-12-6.
//

#include "include/document.h"
using namespace lm;

namespace lm {
	logic_document::~logic_document() = default;

	const string &logic_document::getTitle() const {
		return title;
	}

	void logic_document::setTitle(const string &title) {
		logic_document::title = title;
	}

	logic_document::logic_document(const string &title) : title(title) {

	}

	void logic_document::update_document() {
		for (logic_device *&device:devices) {
			device->update_signal();
		}
		for (clock *&clock:clocks) {
			clock->update_signal();
		}
		for (iface *&iface:ifaces) {
			switch (iface->getType()) {
				case CLOCK_IFACE:
					((clock_iface *) iface)->update_signal();
					break;
				case LINK_IFACE:
					((link_iface *) iface)->update_signal();
					break;
				case OUTPUT_IFACE:
					break;
				case INPUT_IFACE:
					break;
			}
		}
	}


}
