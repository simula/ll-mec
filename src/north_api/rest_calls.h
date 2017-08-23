#ifndef __REST_CALLS_H__
#define __REST_CALLS_H__

#include <pistache/router.h>

namespace llmec {
namespace north_api {

class Rest_calls {
	public:
		virtual void register_calls(Pistache::Rest::Router& router) = 0;
};

} // namespace north_api
} // namespace llmec

#endif
