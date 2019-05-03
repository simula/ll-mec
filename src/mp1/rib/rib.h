
#ifndef RIB_H_
#define RIB_H_

#include <map>
#include <set>

#include <memory>
#include <set>
#include <chrono>
#include "json.h"
namespace llmec {
namespace mp1 {

namespace rib {

class Rib {
public:

	/**
	 * @brief Get RAN statistics from this agent and update to the DB
	 * @param [agentAddr] address of the FlexRAN agent
	 * @param [port] port of the agent
	 * @return true if successful, else return false
	 */
	bool update_ran_statistics(const std::string& agentAddr, int port);

private:
	std::map<int, nlohmann::json> m_ranStatistics;

};

}

}
}
#endif
