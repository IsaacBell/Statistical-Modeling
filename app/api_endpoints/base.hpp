#include <curl/curl.h>

namespace TPF {
  template<typename T>
  struct Query {
    T id;
    std::string url = "";
    std::string result;

    static Query<T> lookup(T id) {
      return endpoints[id];
    };

    void connect() {
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
        else
          result = res;
      
        // always clean up
        curl_easy_cleanup(curl);
      }

      curl_global_cleanup();
    }
  };
}
