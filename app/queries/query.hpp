#include <string>
#include <cstdio>

struct Query
{
  std::string id = "";
  std::string result;
  std::string symbol;
  std::string start_date;
  std::string end_date;
  std::string api_key;

  Query();
  Query(std::string id_) : id(id_){};
  virtual ~Query();

  Query(Query &&rhs) : id(rhs.id){};
  Query(const Query &rhs) : Query(rhs.id){};

  Query &Query::operator=(const Query &rhs)
  {
    return *this = Query(rhs);
  };

  Query &Query::operator=(Query &&rhs) noexcept
  {
    std::swap(id, rhs.id);
    return *this;
  }

  bool Query::connect()
  {
    CURL *curl = curl_easy_init();
    CURLcode res;
    if (curl)
    {
      curl_easy_setopt(curl, CURLOPT_URL, url().c_str());
      curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);

      res = curl_easy_perform(curl);
      if (res != CURLE_OK)
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));
      else
        result = res;

      // always clean up
      curl_easy_cleanup(curl);
    }

    curl_global_cleanup();

    // wait until CURL is cleaned up to log results
    if (curl && res == CURLE_OK)
    {
      std::string log = "API:CURLE_OK:" + result;
      BOOST_LOG_TRIVIAL(trace) << log;
    }

    return res == CURLE_OK;
  }

  size_t Query::write_callback(
      void *buffer,
      size_t size,
      size_t nmemb,
      void *userp)
  {
    // char** response_ptr = (char**)userp;

    // /* assuming the response is a string */
    // *response_ptr = strndup(buffer, (size_t)(size * nmemb));
  }
};
