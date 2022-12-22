#include <stdlib.h>
#include <iostream>
#include <jsoncpp/json/json.h>

#include "./constants.hpp"

namespace TPF {
  class AlphaVantageQuery : Query {
		const std::string url();

	private:

		const std::string api_key;
  }
}