#ifndef _TPF_LIB_INSTRUMENTS_BITCOIN_HPP_
#define _TPF_LIB_INSTRUMENTS_BITCOIN_HPP_

#include <cstdint>
#include <string>
#include <vector>

struct bitcoin_msg_header
{
  int32_t magic;
  std::string command;
  uint32_t length;
  uint32_t checksum;
};

struct BitcoinSocket
{
  int sock;
  int port = 8333;
  bool connected;
  bool proxy;
  std::string proxy_type;
  std::string proxy_ip;
  std::string proxy_auth;

public:
  BitcoinSocket();
  bool Connect(const std::string &ip, unsigned short port);
  bool Send(const std::vector<uint8_t> &data);
  std::vector<uint8_t> Receive(size_t size = 0);
  void Disconnect();
  bool IsConnected();
  void SetProxy(const std::string &type,
                const std::string &ip,
                const std::string &auth = "");
};

// Contains all the information for a given exchange,
// like fees and wether we can short on that exchange.
// FIXME: short selling should depend on the currency.
class Bitcoin
{
private:
  unsigned id;
  std::string exch_name_;
  double fees;
  bool hasShort;
  bool isImplemented;
  double bid, ask;
  std::unique_ptr<BitcoinSocket> socket_;

public:
  Bitcoin(unsigned id, std::string n, double f, bool h, bool m);
  // void updateData(quote_t quote);
  unsigned GetId() const;
  double GetAsk() const;
  double GetBid() const;
  double GetMidPrice() const;
  std::string GetExchName() const;
  double GetFees() const;
  bool GetHasShort() const;
  bool GetIsImplemented() const;
};

#endif
