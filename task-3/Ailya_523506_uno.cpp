#include "uno.h"
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <sstream>

using namespace std;

enum Color { RED, GREEN, BLUE, YELLOW };
enum Value { 
    ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE,
    SKIP, REVERSE, DRAW_TWO 
};

struct Card {
    Color color;
    Value value;
    Card(Color c, Value v) : color(c), value(v) {}
    
    string toString() const {
        string colorStr, valueStr;
        switch (color) {
            case RED: colorStr = "Red"; break;
            case GREEN: colorStr = "Green"; break;
            case BLUE: colorStr = "Blue"; break;
            case YELLOW: colorStr = "Yellow"; break;
        }
        switch (value) {
            case ZERO: valueStr = "0"; break;
            case ONE: valueStr = "1"; break;
            case TWO: valueStr = "2"; break;
            case THREE: valueStr = "3"; break;
            case FOUR: valueStr = "4"; break;
            case FIVE: valueStr = "5"; break;
            case SIX: valueStr = "6"; break;
            case SEVEN: valueStr = "7"; break;
            case EIGHT: valueStr = "8"; break;
            case NINE: valueStr = "9"; break;
            case SKIP: valueStr = "Skip"; break;
            case REVERSE: valueStr = "Reverse"; break;
            case DRAW_TWO: valueStr = "Draw Two"; break;
        }
        return colorStr + " " + valueStr;
    }
    
    bool matches(const Card& other) const {
        return color == other.color || value == other.value;
    }
    
    bool isActionCard() const {
        return value == SKIP || value == REVERSE || value == DRAW_TWO;
    }
};

// Concrete implementation class
class UNOGameImpl : public UNOGame {
private:
    vector<vector<Card>> players;
    vector<Card> deck;
    vector<Card> discardPile;
    int numPlayers;
    int currentPlayer;
    bool clockwise;
    bool gameOver;
    int winner;
    
    void createDeck() {
        vector<Color> colors = {RED, GREEN, BLUE, YELLOW};
        vector<Value> values = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, SKIP, REVERSE, DRAW_TWO};
        
        for (Color color : colors) {
            for (Value value : values) {
                if (value == ZERO) {
                    deck.push_back(Card(color, value));
                } else {
                    deck.push_back(Card(color, value));
                    deck.push_back(Card(color, value));
                }
            }
        }
    }
    
    void shuffleDeck() {
        std::mt19937 rng(1234);
        std::shuffle(deck.begin(), deck.end(), rng);
    }
    
    void dealCards() {
        for (int i = 0; i < numPlayers; i++) {
            for (int j = 0; j < 7; j++) {
                if (!deck.empty()) {
                    players[i].push_back(deck.back());
                    deck.pop_back();
                }
            }
        }
    }
    
    Card drawCard() {
        if (deck.empty() && discardPile.size() > 1) {
            Card topCard = discardPile.back();
            discardPile.pop_back();
            deck = discardPile;
            discardPile = {topCard};
            shuffleDeck();
        }
        
        if (!deck.empty()) {
            Card card = deck.back();
            deck.pop_back();
            return card;
        }
        return Card(RED, ZERO);
    }
    
    void nextPlayer() {
        if (clockwise) {
            currentPlayer = (currentPlayer + 1) % numPlayers;
        } else {
            currentPlayer = (currentPlayer - 1 + numPlayers) % numPlayers;
        }
    }
    
    void handleActionCard(const Card& card) {
        if (card.value == SKIP) {
            nextPlayer();
        } else if (card.value == REVERSE) {
            clockwise = !clockwise;
            if (numPlayers == 2) nextPlayer();
        } else if (card.value == DRAW_TWO) {
            int next = clockwise ? (currentPlayer + 1) % numPlayers : (currentPlayer - 1 + numPlayers) % numPlayers;
            for (int i = 0; i < 2; i++) players[next].push_back(drawCard());
            nextPlayer();
        }
    }
    
    int findBestPlayableCard() {
        if (discardPile.empty()) return -1;
        Card topCard = discardPile.back();
        vector<int> playableIndices;
        
        for (int i = 0; i < players[currentPlayer].size(); i++) {
            if (players[currentPlayer][i].matches(topCard)) {
                playableIndices.push_back(i);
            }
        }
        if (playableIndices.empty()) return -1;
        
        int bestIndex = playableIndices[0];
        for (int i = 1; i < playableIndices.size(); i++) {
            Card current = players[currentPlayer][playableIndices[i]];
            Card best = players[currentPlayer][bestIndex];
            
            if (current.color == topCard.color && best.color != topCard.color) {
                bestIndex = playableIndices[i];
            } else if (current.isActionCard() && !best.isActionCard()) {
                bestIndex = playableIndices[i];
            } else if (current.isActionCard() && best.isActionCard()) {
                if (current.value == SKIP && best.value != SKIP) bestIndex = playableIndices[i];
                else if (current.value == REVERSE && best.value == DRAW_TWO) bestIndex = playableIndices[i];
            }
        }
        return bestIndex;
    }

public:
    UNOGameImpl(int nPlayers) : numPlayers(nPlayers), currentPlayer(0), clockwise(true), gameOver(false), winner(-1) {
        players.resize(numPlayers);
    }
    
    void initialize() override {
        gameOver = false;
        winner = -1;
        currentPlayer = 0;
        clockwise = true;
        players.clear();
        players.resize(numPlayers);
        deck.clear();
        discardPile.clear();
        
        createDeck();
        shuffleDeck();
        dealCards();
        
        if (!deck.empty()) {
            discardPile.push_back(deck.back());
            deck.pop_back();
        }
    }
    
    void playTurn() override {
        if (gameOver) return;
        
        int cardIndex = findBestPlayableCard();
        
        if (cardIndex != -1) {
            Card playedCard = players[currentPlayer][cardIndex];
            players[currentPlayer].erase(players[currentPlayer].begin() + cardIndex);
            discardPile.push_back(playedCard);
            
            if (players[currentPlayer].empty()) {
                gameOver = true;
                winner = currentPlayer;
                return;
            }
            
            if (playedCard.isActionCard()) {
                handleActionCard(playedCard);
            } else {
                nextPlayer();
            }
        } else {
            Card drawnCard = drawCard();
            players[currentPlayer].push_back(drawnCard);
            
            if (drawnCard.matches(discardPile.back())) {
                players[currentPlayer].pop_back();
                discardPile.push_back(drawnCard);
                
                if (players[currentPlayer].empty()) {
                    gameOver = true;
                    winner = currentPlayer;
                    return;
                }
                
                if (drawnCard.isActionCard()) {
                    handleActionCard(drawnCard);
                } else {
                    nextPlayer();
                }
            } else {
                nextPlayer();
            }
        }
    }
    
    bool isGameOver() const override { return gameOver; }
    int getWinner() const override { return winner; }
    
    string getState() const override {
        stringstream ss;
        ss << "Player " << currentPlayer << "'s turn, Direction: ";
        ss << (clockwise ? "Clockwise" : "Counter-clockwise");
        ss << ", Top: " << (discardPile.empty() ? "None" : discardPile.back().toString());
        ss << ", Players cards: ";
        for (int i = 0; i < numPlayers; i++) {
            ss << "P" << i << ":" << players[i].size();
            if (i < numPlayers - 1) ss << ", ";
        }
        return ss.str();
    }
};

// Factory function implementation
UNOGame* createUNOGame(int numPlayers) {
    return new UNOGameImpl(numPlayers);
}
