#include "itch_message_consumer.hpp"

namespace TPF
{
  ItchMessage ParseItchMessage(const std::vector<uint8_t> &buffer)
  {
    ItchMessage message;

    // Parse message type
    message.type = static_cast<ItchMessage::Type>(buffer[0]);

    // Parse timestamp
    message.timestamp = std::string(buffer.begin() + 1, buffer.begin() + 9);

    switch (message.type)
    {
    case ItchMessage::Type::TimeStamp:
      // No further data to parse
      break;
    case ItchMessage::Type::StockDirectory:
    {
      // Parse stock directory entries
      const uint8_t *data = buffer.data() + 9;
      const size_t numEntries = (buffer.size() - 9) / 11;
      message.stockDirectoryEntries.resize(numEntries);
      for (size_t i = 0; i < numEntries; ++i)
      {
        ItchMessage::StockDirectoryEntry &entry = message.stockDirectoryEntries[i];
        entry.stock = std::string(data, data + 6);
        data += 6;
        entry.marketCategory = *data++;
        entry.financialStatusIndicator = *data++;
        entry.roundLotSize = std::string(data, data + 4);
        data += 4;
        entry.roundLotsOnly = std::string(data, data + 1);
        data += 1;
      }
      break;
    }
    case ItchMessage::Type::StockTradingAction:
    {
      // Parse stock trading action
      const uint8_t *data = buffer.data() + 9;
      message.stockTradingAction.stock = std::string(data, data + 6);
      data += 6;
      message.stockTradingAction.tradingState = *data++;
      message.stockTradingAction.reserved = *data++;
      message.stockTradingAction.reason = *data++;
      break;
    }
    case ItchMessage::Type::RegSHORestriction:
    {
      // Parse Reg SHO restriction
      const uint8_t *data = buffer.data() + 9;
      message.regSHORestriction.stock = std::string(data, data + 6);
      data += 6;
      message.regSHORestriction.regSHOAction = *data++;
      break;
    }
    case ItchMessage::Type::MarketParticipantPosition:
    {
      // Parse market participant positions
      const uint8_t *data = buffer.data() + 9;
      const size_t numPositions = (buffer.size() - 9) / 11;
      message.marketParticipantPositions.resize(numPositions);
      for (size_t i = 0; i < numPositions; ++i)
      {
        ItchMessage::MarketParticipantPosition &position = message.marketParticipantPositions[i];
        position.mpid = std::string(data, data + 4);
        data += 4;
        position.stock = std::string(data, data + 6);
        data += 6;
        position.primaryMarketMaker = *data++;
        position.marketMakerMode = *data++;
        position.marketParticipantState = *data++;
      }
      break;
    }
    case ItchMessage::Type::MwcbDeclineLevel:
    {
      // Parse MWCB decline level
      const uint8_t *data = buffer.data() + 9;
      message.mwcbDeclineLevel.level1 = std::string(data, data + 8);
      data += 8;
      message.mwcbDeclineLevel.level2 = std::string(data, data + 8);
      data += 8;
      message.mwcbDeclineLevel.level3 = std::string(data, data + 8);
      break;
    }
    case ItchMessage::Type::MwcbStatus:
    {
      // Parse MWCB status
      const uint8_t *data = buffer.data() + 9;
      message.mwcbStatus.breachedLevel = *data++;
      break;
    }
    case ItchMessage::Type::LuldAuctionCollar:
    {
      // Parse LULD auction collar
      const uint8_t *data = buffer.data() + 9;
      const size_t numCollars = (buffer.size() - 9) / 19;
      message.luldAuctionCollars.resize(numCollars);
      for (size_t i = 0; i < numCollars; ++i)
      {
        ItchMessage::LuldAuctionCollar &collar = message.luldAuctionCollars[i];
        collar.stock = std::string(data, data + 6);
        data += 6;
        collar.auctionCollarReferencePrice = std::string(data, data + 8);
        data += 8;
        collar.upperAuctionCollarPrice = std::string(data, data + 8);
        data += 8;
        collar.lowerAuctionCollarPrice = std::string(data, data + 8);
        data += 8;
        collar.auctionCollarExtension = *data++;
      }
      break;
    }
    case ItchMessage::Type::OperationalHalt:
    {
      // Parse operational halt
      const uint8_t *data = buffer.data() + 9;
      message.operationalHalt.stock = std::string(data, data + 6);
      data += 6;
      message.operationalHalt.haltStatus = *data++;
      message.operationalHalt.reserved = *data++;
      break;
    }
    case ItchMessage::Type::ShortSalePriceTestRestriction:
    {
      // Parse short sale price test restriction
      const uint8_t *data = buffer.data() + 9;
      message.shortSalePriceTestRestriction.stock = std::string(data, data + 6);
      data += 6;
      message.shortSalePriceTestRestriction.restriction = *data++;
      break;
    }
    case ItchMessage::Type::QuoteUpdate:
    {
      // Parse quote updates
      const uint8_t *data = buffer.data() + 9;
      const size_t numUpdates = (buffer.size() - 9) / 29;
      message.quoteUpdates.resize(numUpdates);
      for (size_t i = 0; i < numUpdates; ++i)
      {
        ItchMessage::QuoteUpdate &update = message.quoteUpdates[i];
        update.stock = std::string(data, data + 6);
        data += 6;
        update.bidPrice = std::string(data, data + 8);
        data += 8;
        update.bidSize = std::string(data, data + 4);
        data += 4;
        update.askPrice = std::string(data, data + 8);
        data += 8;
        update.askSize = std::string(data, data + 4);
        data += 4;
      }
      break;
    }
    case ItchMessage::Type::Trade:
    {
      // Parse trades
      const uint8_t *data = buffer.data() + 9;
      const size_t numTrades = (buffer.size() - 9) / 17;
      message.trades.resize(numTrades);
      for (size_t i = 0; i < numTrades; ++i)
      {
        ItchMessage::Trade &trade = message.trades[i];
        trade.stock = std::string(data, data + 6);
        data += 6;
        trade.price = std::string(data, data + 8);
        data += 8;
        trade.size = std::string(data, data + 4);
        data += 4;
        trade.tradeType = *data++;
        trade.reserved = *data++;
      }
      break;
    }
    case ItchMessage::Type::CrossTrade:
    {
      // Parse cross trades
      const uint8_t *data = buffer.data() + 9;
      const size_t numCrossTrades = (buffer.size() - 9) / 35;
      message.crossTrades.resize(numCrossTrades);
      for (size_t i = 0; i < numCrossTrades; ++i)
      {
        ItchMessage::CrossTrade &crossTrade = message.crossTrades[i];
        crossTrade.stock = std::string(data, data + 6);
        data += 6;
        crossTrade.crossPrice = std::string(data, data + 8);
        data += 8;
        crossTrade.crossSize = std::string(data, data + 8);
        data += 8;
        crossTrade.crossType = *data++;
        crossTrade.institutionalCrossType = std::string(data, data + 1);
        data += 1;
      }
      break;
    }
    case ItchMessage::Type::BrokenTrade:
    {
      // Parse broken trades
      const uint8_t *data = buffer.data() + 9;
      const size_t numBrokenTrades = (buffer.size() - 9) / 15;
      message.brokenTrades.resize(numBrokenTrades);
      for (size_t i = 0; i < numBrokenTrades; ++i)
      {
        ItchMessage::BrokenTrade &brokenTrade = message.brokenTrades[i];
        brokenTrade.stock = std::string(data, data + 6);
        data += 6;
        brokenTrade.matchNumber = std::string(data, data + 9);
        data += 9;
      }
      break;
    }
    case ItchMessage::Type::NOII:
    {
      // Parse NOII message
      const uint8_t *data = buffer.data() + 9;
      message.noii.pairedShares = std::string(data, data + 8);
      data += 8;
      message.noii.imbalanceShares = std::string(data, data + 8);
      data += 8;
      message.noii.imbalanceDirection = std::string(data, data + 1);
      data += 1;
      message.noii.stock = std::string(data, data + 6);
      data += 6;
      message.noii.farPrice = std::string(data, data + 8);
      data += 8;
      message.noii.nearPrice = std::string(data, data + 8);
      data += 8;
      message.noii.currentReferencePrice = std::string(data, data + 8);
      data += 8;
      message.noii.crossType = *data++;
      message.noii.priceVariationIndicator = std::string(data, data + 1);
      break;
    }
    case ItchMessage::Type::RPII:
    {
      // Parse RPII message
      const uint8_t *data = buffer.data() + 9;
      message.rpii.stock = std::string(data, data + 6);
      data += 6;
      message.rpii.interestFlag = *data++;
      break;
    }
    }

    return message;
  }
} // namespace TPF
