#ifndef BLACKJACK_H_
#define BLACKJACK_H_
#include <vector>
class Card
{
    public:
    enum rank
    {
    ACE = 1,TWO,THREE,FOUR,FIVE,SIX,SEVEN,EIGHT,NINE,TEN,JACK,QUEEN,KING
    };
    enum type
    {
    CLUBS,DIAMONDS,HEARTS,SPADES
    };
    Card(rank, type);
    int getValue();
    void displayCard();
    private:
        rank aRank;
        type aType;
};

class Hand
{
    public:
        void add(Card);
        void clear();

    int getTotal() const;
        void getCards();
    private:
       std::vector<Card> aCards;
};

class Deck
{
    public:
    void populate();
    void shuffle();
    Card deal();
    private:
    std::vector<Card> aCards;
    };

class AbstractPlayer: public Hand
{
    public:
    virtual bool isDrawing() const = 0;
        bool isBusted();
    private:
        std::vector<Card> aCards;
};
class ComputerPlayer: public AbstractPlayer
{
public:
    bool isDrawing() const override;
private:
    std::vector<Card> aCards;
};
class HumanPlayer: public AbstractPlayer
{
    public:
    bool isDrawing() const override;
        void announce(ComputerPlayer);
    private:
        std::vector<Card> aCards;
};

class BlackJackGame
{
    public:
        void play();
    private:
        Deck m_deck;
        ComputerPlayer m_casino;
};
#endif