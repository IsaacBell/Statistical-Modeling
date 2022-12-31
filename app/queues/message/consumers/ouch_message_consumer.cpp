#include <cstdint>
#include <string>
#include <vector>

#include "ouch_message_consumer.hpp"

namespace TPF
{
  bool OUCHMessage::parseOUCHMessage(const std::vector<uint8_t> &buffer, OUCHMessage &message)
  {
    if (buffer.size() < 8)
      return false;

    OUCHMessage::OuchMessageType type = static_cast<OUCHMessage::OuchMessageType>(buffer[7]);

    switch (type)
    {
    case OuchMessageType::OrderNew:
    {
      const uint8_t *data = buffer.data() + 8;
      message.orderNew.session = std::string(data, data + 4);
      data += 4;
      message.orderNew.sequence = std::string(data, data + 8);
      data += 8;
      message.orderNew.orderToken = std::string(data, data + 12);
      data += 12;
      message.orderNew.side = std::string(data, data + 1);
      data += 1;
      message.orderNew.orderQuantity = std::string(data, data + 8);
      data += 8;
      message.orderNew.price = std::string(data, data + 8);
      data += 8;
      message.orderNew.timeInForce = std::string(data, data + 1);
      data += 1;
      message.orderNew.firm = std::string(data, data + 4);
      data += 4;
      message.orderNew.display = std::string(data, data + 1);
      data += 1;
      message.orderNew.minimumQuantity = std::string(data, data + 8);
      data += 8;
      message.orderNew.crossType = std::string(data, data + 1);
      data += 1;
      message.orderNew.account = std::string(data, data + 6);
      data += 6;
      message.orderNew.freeFormText = std::string(data, data + 15);
      break;
    }
    case OuchMessageType::OrderCancel:
    {
      const uint8_t *data = buffer.data() + 8;
      message.orderCancel.session = std::string(data, data + 4);
      data += 4;
      message.orderCancel.sequence = std::string(data, data + 8);
      data += 8;
      message.orderCancel.orderToken = std::string(data, data + 12);
      data += 12;
      message.orderCancel.cancelQuantity = std::string(data, data + 8);
      break;
    }
    case OuchMessageType::OrderReplaceRejected:
    {
      const uint8_t *data = buffer.data() + 8;
      message.orderReplaceRejected.session = std::string(data, data + 4);
      data += 4;
      message.orderReplaceRejected.sequence = std::string(data, data + 8);
      data += 8;
      message.orderReplaceRejected.orderToken = std::string(data, data + 12);
      data += 12;
      message.orderReplaceRejected.reason = std::string(data, data + 4);
      break;
    }
    case OuchMessageType::OrderPendingCancel:
    {
      const uint8_t *data = buffer.data() + 8;
      message.orderPendingCancel.session = std::string(data, data + 4);
      data += 4;
      message.orderPendingCancel.sequence = std::string(data, data + 8);
      data += 8;
      message.orderPendingCancel.orderToken = std::string(data, data + 12);
      break;
    }
    case OuchMessageType::OrderPendingReplace:
    {
      const uint8_t *data = buffer.data() + 8;
      message.orderPendingReplace.session = std::string(data, data + 4);
      data += 4;
      message.orderPendingReplace.sequence = std::string(data, data + 8);
      data += 8;
      message.orderPendingReplace.orderToken = std::string(data, data + 12);
      data += 12;
      message.orderPendingReplace.side = std::string(data, data + 1);
      data += 1;
      message.orderPendingReplace.orderQuantity = std::string(data, data + 8);
      data += 8;
      message.orderPendingReplace.price = std::string(data, data + 8);
      data += 8;
      message.orderPendingReplace.timeInForce = std::string(data, data + 1);
      data += 1;
      message.orderPendingReplace.originalOrderToken = std::string(data, data + 12);
      data += 12;
      message.orderPendingReplace.cancelQuantity = std::string(data, data + 8);
      break;
    }
    case OuchMessageType::OrderBookDirectory:
    {
      const uint8_t *data = buffer.data() + 8;
      message.orderBookDirectory.session = std::string(data, data + 4);
      data += 4;
      message.orderBookDirectory.sequence = std::string(data, data + 8);
      data += 8;
      message.orderBookDirectory.symbol = std::string(data, data + 6);
      data += 6;
      message.orderBookDirectory.financialStatusIndicator = *data;
      data += 1;
      message.orderBookDirectory.lotSize = std::string(data, data + 8);
      data += 8;
      message.orderBookDirectory.tick = std::string(data, data + 8);
      data += 8;
      message.orderBookDirectory.tradingStatus = *data;
      data += 1;
      message.orderBookDirectory.marketMaker = *data;
      data += 1;
      message.orderBookDirectory.minCabPrice = std::string(data, data + 8);
      data += 8;
      message.orderBookDirectory.minCabSize = std::string(data, data + 8);
      data += 8;
      message.orderBookDirectory.maxFloorPrice = std::string(data, data + 8);
      data += 8;
      message.orderBookDirectory.maxFloorSize = std::string(data, data + 8);
      break;
    }
    case OuchMessageType::OrderBookTradingAction:
    {
      const uint8_t *data = buffer.data() + 8;
      message.orderBookTradingAction.session = std::string(data, data + 4);
      data += 4;
      message.orderBookTradingAction.sequence = std::string(data, data + 8);
      data += 8;
      message.orderBookTradingAction.symbol = std::string(data, data + 6);
      data += 6;
      message.orderBookTradingAction.tradingStatus = *data;
      data += 1;
      message.orderBookTradingAction.reason = std::string(data, data + 4);
      break;
    }
    default:
      return false;
    }

    return true;
  }
}
