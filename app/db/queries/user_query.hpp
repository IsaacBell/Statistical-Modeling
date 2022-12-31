#include <cassandradb/cassandradb.h>
#include <iostream>

#include "../../declarations.hpp"

using namespace cassandradb;

namespace TPF {
  class UserQuery {
  public:
  
  template <const char* KEYSPACE = "test">
  CassandraQuery() : cluster_(Cluster(getenv("CASSANDRA_CLUSTER_HOST") || "127.0.0.1"), session_(cluster_.connect()))
  {
    session_.execute("CREATE KEYSPACE IF NOT EXISTS " + KEYSPACE + " WITH REPLICATION = { 'class': 'SimpleStrategy', 'replication_factor': 1 }");
    session_.execute("CREATE TABLE IF NOT EXISTS " + KEYSPACE + ".users (id int PRIMARY KEY, name text, email text)");
  
    insert_stmt_ = session_.prepare("INSERT INTO " + KEYSPACE + ".users (id, name, email) VALUES (?, ?, ?)");
    select_stmt_ = session_.prepare("SELECT * FROM " + KEYSPACE + ".users WHERE id = ?");
  }
  
  void insert_user(const User& user) {
    session_.execute(insert_stmt_.bind(user.id, user.name, user.email));
  }
  
  User get_user(int id) {
    Result result = session_.execute(select_stmt_.bind(id));
    Row row = result.one();
    
    User user;
    user.id = row.get<int>("id");
    user.name = row.get<std::string>("name");
    user.email = row.get<std::string>("email");
    return user;
  }

  private:
    Cluster cluster_;
    Session session_;
    PreparedStatement insert_stmt_;
    PreparedStatement select_stmt_;
  };
}
