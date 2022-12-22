namespace TPF {
  struct AlphaVantageQuery : Query {
    AlphaVantageQuery(std::string url_) : url(url_);

    auto get_alpha_vantage_historical_data();
  };
}
