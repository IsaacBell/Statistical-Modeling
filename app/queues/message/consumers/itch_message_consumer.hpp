#include <cstdint>
#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace TPF
{
  class ItchMessage // TODO: change to snake case
  {
  public:
    enum class Type : uint8_t
    {
      TimeStamp = 'T',
      StockDirectory = 'R',
      StockTradingAction = 'H',
      RegSHORestriction = 'Y',
      MarketParticipantPosition = 'L',
      MwcbDeclineLevel = 'V',
      MwcbStatus = 'W',
      LuldAuctionCollar = 'J',
      OperationalHalt = 'h',
      ShortSalePriceTestRestriction = 'A',
      QuoteUpdate = 'Q',
      Trade = 'P',
      CrossTrade = 'X',
      BrokenTrade = 'B',
      NOII = 'I',
      RPII = 'N',
    };

    struct StockDirectoryEntry
    {
      std::string stock;
      char marketCategory;
      char financialStatusIndicator;
      std::string roundLotSize;
      std::string roundLotsOnly;
    };

    struct StockTradingAction
    {
      std::string stock;
      char tradingState;
      char reserved;
      char reason;
    };

    struct RegSHORestriction
    {
      std::string stock;
      char regSHOAction;
    };

    struct MarketParticipantPosition
    {
      std::string mpid;
      std::string stock;
      char primaryMarketMaker;
      char marketMakerMode;
      char marketParticipantState;
    };

    struct MwcbDeclineLevel
    {
      std::string level1;
      std::string level2;
      std::string level3;
    };

    struct MwcbStatus
    {
      char breachedLevel;
    };

    struct LuldAuctionCollar
    {
      std::string stock;
      std::string auctionCollarReferencePrice;
      std::string upperAuctionCollarPrice;
      std::string lowerAuctionCollarPrice;
      char auctionCollarExtension;
    };

    struct OperationalHalt
    {
      std::string stock;
      char haltStatus;
      char reserved;
    };

    struct ShortSalePriceTestRestriction
    {
      std::string stock;
      char restriction;
    };

    struct QuoteUpdate
    {
      std::string stock;
      std::string bidPrice;
      std::string bidSize;
      std::string askPrice;
      std::string askSize;
    };

    struct Trade
    {
      std::string stock;
      std::string price;
      std::string size;
      char tradeType;
      char reserved;
    };

    struct CrossTrade
    {
      std::string stock;
      std::string crossPrice;
      std::string crossSize;
      char crossType;
      std::string institutionalCrossType;
    };

    struct BrokenTrade
    {
      std::string stock;
      std::string matchNumber;
    };

    struct NOII
    {
      std::string pairedShares;
      std::string imbalanceShares;
      std::string imbalanceDirection;
      std::string stock;
      std::string farPrice;
      std::string nearPrice;
      std::string currentReferencePrice;
      char crossType;
      std::string priceVariationIndicator;
    };

    struct RPII
    {
      std::string stock;
      char interestFlag;
    };

    Type type;
    std::string timestamp;

    std::vector<StockDirectoryEntry> stockDirectoryEntries;
    StockTradingAction stockTradingAction;
    RegSHORestriction regSHORestriction;
    std::vector<MarketParticipantPosition> marketParticipantPositions;
    MwcbDeclineLevel mwcbDeclineLevel;
    MwcbStatus mwcbStatus;
    std::vector<LuldAuctionCollar> luldAuctionCollars;
    OperationalHalt operationalHalt;
    ShortSalePriceTestRestriction shortSalePriceTestRestriction;
    std::vector<QuoteUpdate> quoteUpdates;
    std::vector<Trade> trades;
    std::vector<CrossTrade> crossTrades;
    std::vector<BrokenTrade> brokenTrades;
    NOII noii;
    RPII rpii;
  };

  // Parses an ITCH message from a binary buffer
  ItchMessage ParseItchMessage(const std::vector<uint8_t> &buffer);
}