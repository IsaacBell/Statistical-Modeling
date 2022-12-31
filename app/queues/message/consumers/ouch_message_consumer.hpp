#include <cstdint>
#include <string>
#include <vector>

namespace TPF
{

  struct OUCHMessage
  {
    struct LoginRequest
    {
      std::string username;
      std::string password;
      std::string newPassword;
      std::string requestTimestamp;
    };

    struct LoginAccepted
    {
      std::string session;
      std::string sequence;
    };

    struct LoginRejected
    {
      std::string reason;
    };

    struct LogoutRequest
    {
      std::string session;
      std::string sequence;
    };

    struct OrderNew
    {
      std::string session;
      std::string sequence;
      std::string orderToken;
      std::string side;
      std::string orderQuantity;
      std::string price;
      std::string timeInForce;
      std::string firm;
      std::string display;
      std::string minimumQuantity;
      std::string crossType;
      std::string account;
      std::string freeFormText;
    };

    struct OrderCancel
    {
      std::string session;
      std::string sequence;
      std::string orderToken;
      std::string cancelQuantity;
    };

    struct OrderReplace
    {
      std::string session;
      std::string sequence;
      std::string orderToken;
      std::string side;
      std::string orderQuantity;
      std::string price;
      std::string timeInForce;
      std::string originalOrderToken;
      std::string cancelQuantity;
    };

    struct OrderExecuted
    {
      std::string session;
      std::string sequence;
      std::string orderToken;
      std::string executedQuantity;
      std::string matchNumber;
      uint8_t printable;
    };

    struct OrderCancelled
    {
      std::string session;
      std::string sequence;
      std::string orderToken;
      std::string cancelledQuantity;
    };

    struct OrderRejected
    {
      std::string session;
      std::string sequence;
      std::string orderToken;
      std::string reason;
    };

    struct OrderReplaceRejected
    {
      std::string session;
      std::string sequence;
      std::string orderToken;
      std::string reason;
    };

    struct OrderPendingCancel
    {
      std::string session;
      std::string sequence;
      std::string orderToken;
    };

    struct OrderPendingReplace
    {
      std::string session;
      std::string sequence;

      // Order token
      std::string orderToken;
      // Side ('B' or 'S')
      std::string side;
      // Order quantity
      std::string orderQuantity;
      // Price
      std::string price;
      // Time in force ('I' or 'G')
      std::string timeInForce;
      // Original order token
      std::string originalOrderToken;
      // Cancel quantity
      std::string cancelQuantity;
    };

    struct OrderBookDirectory
    {
      std::string session;
      std::string sequence;
      std::string symbol;
      uint8_t financialStatusIndicator;
      std::string lotSize;
      std::string tick;
      uint8_t tradingStatus;
      uint8_t marketMaker;
      std::string minCabPrice;
      std::string minCabSize;
      std::string maxFloorPrice;
      std::string maxFloorSize;
    };

    struct OrderBookTradingAction
    {
      std::string session;
      std::string sequence;
      std::string symbol;
      uint8_t tradingStatus;
      std::string reason;
    };

    enum class OuchMessageType : uint8_t
    {
      OrderNew = 'A',
      OrderCancel = 'X',
      OrderReplace = 'U',
      OrderExecuted = 'E',
      OrderCancelled = 'C',
      OrderRejected = 'J',
      OrderReplaceRejected = 'K',
      OrderPendingCancel = 'P',
      OrderPendingReplace = 'Q',
      OrderBookDirectory = 'R',
      OrderBookTradingAction = 'H',
    };

    std::string session_;  // Session identifier
    std::string sequence_; // Sequence number
    uint8_t type_;         // Message type

    LoginRequest loginRequest;
    LoginAccepted loginAccepted;
    LoginRejected loginRejected;
    LogoutRequest logoutRequest;

    OrderNew orderNew;
    OrderCancel orderCancel;
    OrderReplace orderReplace;
    OrderExecuted orderExecuted;
    OrderRejected orderRejected;
    OrderCancelled orderCancelled;
    OrderPendingCancel orderPendingCancel;
    OrderBookDirectory orderBookDirectory;
    OrderPendingReplace orderPendingReplace;
    OrderReplaceRejected orderReplaceRejected;
    OrderBookTradingAction orderBookTradingAction;

    bool parseOUCHMessage(const std::vector<uint8_t> &buffer, OUCHMessage &message);
  };
}
