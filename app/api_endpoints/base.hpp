struct Query {
  std::string url = "";
  std::string result;

  Query();
  Query(std::string url_) : url(url_);
  ~Query();

  Query(Query&& rhs) : url(rhs.url);
  Query(const Query& rhs) : Query(rhs.url);

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
