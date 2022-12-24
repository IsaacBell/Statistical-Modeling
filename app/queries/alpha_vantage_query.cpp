#include <string>

const std::string AlphaVantageQuery::url() {
	std::string url = "https://www.alphavantage.co/query?";
	url += "function=TIME_SERIES_DAILY_ADJUSTED";
	url += "&symbol=" + symbol;
	url += "&start_date=" + startDate;
	url += "&end_date=" + endDate;
	url += "&apikey=" + api_key();

	return url;
}

const std::string AlphaVantageQuery::api_key() {
	return getenv("ALPHAVANTAGE_API_KEY");
}
