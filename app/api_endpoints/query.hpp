#include <string>
#include <cstdio>

struct Query {
  std::string id = "";
  std::string result;
  std::string symbol;
  std::string start_date;
  std::string end_date;
  std::string api_key;

  Query();
  Query(std::string id_) : id(id_) {};
  ~Query();

  Query(Query&& rhs) : id(rhs.id) {};
  Query(const Query& rhs) : Query(rhs.id) {};

  Query& operator=(const Query& rhs);
  Query& operator=(Query&& rhs) noexcept;

  void connect();

  std::size_t static Query::write_callback(
    void* buffer,
    std::size_t size,
    std::size_t nmemb,
    void* userp
  );
};
