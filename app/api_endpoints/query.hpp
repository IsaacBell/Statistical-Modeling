struct Query {
  std::string id = "";
  std::string result;
  std::string symbol;
  std::string start_date;
  std::string end_date;
  std::string api_key;

  Query();
  Query(std::string id_) : id(id_);
  ~Query();

  Query(Query&& rhs) : id(rhs.id);
  Query(const Query& rhs) : Query(rhs.id);

  Query& operator=(const Query& rhs);
  Query& operator=(Query&& rhs) noexcept;

  static Query<T> lookup(T id);

  void connect();

  size_t static Query::write_callback write_callback(
    void* buffer,
    size_t size,
    size_t nmemb,
    void* userp
  );
};
