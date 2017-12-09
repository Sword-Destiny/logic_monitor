#include "include/common.h"
using namespace lm;

uuid id = 0;
uuid lm::get_uuid()
{
	return id++;
}
