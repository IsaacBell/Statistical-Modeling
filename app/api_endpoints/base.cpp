#include <curl/curl.h>


Query& Query::operator=(const Query& rhs) {
  return *this = Query(rhs);
};

Query& Query::operator=(Query&& rhs) noexcept {
  std::swap(url, rhs.url);
  return *this;
}

void Query::connect() {
  CURL* curl = curl_easy_init();
  CURLcode res;
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
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
}

size_t static Query::write_callback(
  void* buffer,
  size_t size,
  size_t nmemb,
  void* userp
) {
  char** response_ptr = (char**)userp;

  /* assuming the response is a string */
  *response_ptr = strndup(buffer, (size_t)(size * nmemb));
}
