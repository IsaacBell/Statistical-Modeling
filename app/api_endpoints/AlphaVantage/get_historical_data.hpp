#include "../../common/constants.hpp"

namespace TPF {
	struct AlphaVantageGetHistoricalData : Query {
		const std::string AlphaVantageQuery::url() {
			std::string url = "https://www.alphavantage.co/query?";
			url += "function=TIME_SERIES_DAILY_ADJUSTED";
			url += "&symbol=" + symbol;
			url += "&start_date=" + startDate;
			url += "&end_date=" + endDate;
			url += "&apikey=" + api_key();

			return url;
		}
	};
}