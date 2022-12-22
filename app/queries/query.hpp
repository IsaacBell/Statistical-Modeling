#include <stdlib.h>
#include <iostream>
#include <jsoncpp/json/json.h>

#include "./constants.hpp"

namespace TPF {
  class Query {
		const std::string url() {
			return "Do not use an instance of the base Query class";
		}

		void execute() {
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

				// always clean up
				curl_easy_cleanup(curl);
			}
		}

		size_t static write_callback_func(
			void* buffer,
			size_t size,
			size_t nmemb,
			void* userp
		) {
			char** response_ptr = (char**)userp;

			/* assuming the response is a string */
			*response_ptr = strndup(buffer, (size_t)(size * nmemb));
		}
  }
}