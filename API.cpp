#include <stdlib.h>
#include <iostream>
#include <curl/curl.h>
#include <jsoncpp/json/json.h>

int main(void) {
  // Define the terms and parameters of the API call
  const std::string apiKey = getenv("ALPHAVANTAGE_API_KEY"); // Replace with your RapidAPI API key
  const std::string symbol = "AAPL"; // Stock symbol to retrieve data for
  const std::string startDate = "2022-01-01"; // Start date for data range
  const std::string endDate = "2022-12-31"; // End date for data range

  // Build the URL for the API call

  std::string url = "https://www.alphavantage.co/query?";
  url += "function=TIME_SERIES_DAILY_ADJUSTED";
  url += "&symbol=" + symbol;
  url += "&start_date=" + startDate;
  url += "&end_date=" + endDate;
  url += "&apikey=" + apiKey;

  // Use cURL to make the API call and retrieve the JSON response

  CURL *curl = curl_easy_init();
  CURLcode res;
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);

    res = curl_easy_perform(curl);
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
    
    // always clean up
    curl_easy_cleanup(curl);
  }
}