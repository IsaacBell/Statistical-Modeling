void init(bool production = false) {
  // https://www.boost.org/doc/libs/1_56_0/libs/log/doc/html/log/tutorial/trivial_filtering.html
  
  if (production)
    logging::core::get()->set_filter(
      logging::trivial::severity >= logging::trivial::info
    );
}

int main(int, char*[]) {
  init();

  // BOOST_LOG_TRIVIAL(trace) << "A trace severity message";
  // BOOST_LOG_TRIVIAL(debug) << "A debug severity message";
  // BOOST_LOG_TRIVIAL(info) << "An informational severity message";
  // BOOST_LOG_TRIVIAL(warning) << "A warning severity message";
  // BOOST_LOG_TRIVIAL(error) << "An error severity message";
  // BOOST_LOG_TRIVIAL(fatal) << "A fatal severity message";

  return 0;
}