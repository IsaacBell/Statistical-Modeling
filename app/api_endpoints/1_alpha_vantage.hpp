namespace TPF {
  template<typename T>
  struct AlphaVantageQuery : Query {
    const T id = 1;

    AlphaVantageQuery<T> (T type, std::string url): id(type) {}

    auto get_alpha_vantage_historical_data() {
      
    }
  };
}
