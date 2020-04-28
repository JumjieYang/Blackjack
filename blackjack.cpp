#include "blackjack.h"
#include <iostream>
#include <algorithm> //std::shuffle
#include <random> //std::default_random_engine
#include <chrono> //std::chrono::system_clock

Card::Card(rank pRank, type pType)
{
    aRank = pRank;
    aType = pType;
}

int Card::getValue()
{
    if (aRank < 11)
        return aRank;
    return 10;
}

void Card::displayCard()
{
    char num;
    char type;
    switch(aRank)
    {
        case ACE:
            num='1';
            break;
        case TWO:
            num='2';
            break;
        case THREE:
            num='3';
            break;
        case FOUR:
            num='4';
            break;
        case FIVE:
            num='5';
            break;
        case SIX:
            num='6';
            break;
        case SEVEN:
            num='7';
            break;
        case EIGHT:
            num='8';
            break;
        case NINE:
            num='9';
            break;
        case TEN:
            num='T';
            break;
        case JACK:
            num='J';
            break;
        case QUEEN:
            num='Q';
            break;
        case KING:
            num='K';
            break;
        default:
            break;

    }
    switch (aType)
    {
        case CLUBS:
            type = 'C';
            break;
        case DIAMONDS:
            type = 'D';
            break;
        case HEARTS:
            type = 'H';
            break;
        default:
            type = 'S';
            break;
    }
    if (num != 'T')
        std::cout<<num<<type<<"\t";
    else
        std::cout<<"10"<<type<<"\t";
}


void Hand::add(Card pCard)
{
    aCards.emplace_back(pCard);
}

void Hand::clear()
{
    aCards.clear();
}

int Hand::getTotal() const {
    int sum = 0;
    int Ace = 0;
    for (Card c : aCards)
    {
        if (c.getValue()!= 1) {
            sum += c.getValue();
        }
        else
            Ace ++;
    }
    for (; Ace > 0; Ace --)
    {
        if (21 > sum +11)
            sum += 11;
        else
            sum +=1;
    }
    return sum;
}

void Hand::getCards() {
    for (Card c: aCards)
        c.displayCard();
}

void Deck::populate()
{
    aCards.clear();
    for(Card::rank r= Card::ACE; r<=Card::KING;r= (Card::rank)(r+1))
    {
        for (Card::type t=Card::CLUBS; t<=Card::SPADES; t = (Card::type)(t+1))
        {
            aCards.emplace_back(Card(r,t));
        }
    }
}

void Deck::shuffle()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine e(seed);
    std::shuffle(aCards.begin(),aCards.end(),e);
}

Card Deck::deal()
{
    Card card = aCards.back();
    aCards.pop_back();
    return card;
}

bool AbstractPlayer::isBusted()
{
    return getTotal()>21;
}


bool HumanPlayer::isDrawing() const
{
    char choice;
    std::cout<<"Do you want to drow? (y/n):";
    std::cin>>choice;
    switch(choice)
    {
        case 'y':
        case 'Y':
            return true;
        case 'n':
        case 'N':
            return false;
        default:
            std::cout<<"Invalid Input"<<std::endl;
            return false;
    }
}

void HumanPlayer::announce(ComputerPlayer pCasino)
{
    if(pCasino.getTotal() == getTotal())
        std::cout<<"Push: No one wins"<<std::endl;
    else if(pCasino.getTotal()< getTotal())
        std::cout<<"Player wins"<<std::endl;
    else if(pCasino.getTotal()>getTotal())
        std::cout<<"Casino wins"<<std::endl;
}

bool ComputerPlayer::isDrawing() const {
    return getTotal()<=16;
}


void BlackJackGame::play()
{
    m_deck.populate();
    m_deck.shuffle();
    m_casino.clear();
    HumanPlayer human;
    human.clear();
    bool cont;
    m_casino.add(m_deck.deal());
    human.add(m_deck.deal());
    human.add(m_deck.deal());
    std::cout<<"Casino: ";
    m_casino.getCards();
    std::cout<<"["<<m_casino.getTotal()<<"]"<<std::endl;
    std::cout<<"Player: ";
    human.getCards();
    std::cout<<"["<<human.getTotal()<<"]"<<std::endl;
    cont = human.isDrawing();
    while(cont)
    {
        human.add(m_deck.deal());
        std::cout<<"Player: ";
        human.getCards();
        std::cout<<"["<<human.getTotal()<<"]"<<std::endl;
        if (human.isBusted())
        {
            std::cout<<"Player busts"<<std::endl<<"Casino wins"<<std::endl;
            return;
        }
        cont = human.isDrawing();
    }
    cont = m_casino.isDrawing();
    while(cont)
    {
        m_casino.add(m_deck.deal());
        std::cout<<"Casino: ";
        m_casino.getCards();
        std::cout<<"["<<m_casino.getTotal()<<"]"<<std::endl;
        if (m_casino.isBusted())
        {
            std::cout<<"Player wins"<<std::endl<<"Casino busts"<<std::endl;
            return;
        }
        cont = m_casino.isDrawing();
    }
    human.announce(m_casino);
}

