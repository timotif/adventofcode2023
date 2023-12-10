/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfregni <tfregni@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 09:26:23 by tfregni           #+#    #+#             */
/*   Updated: 2023/12/10 09:26:50 by tfregni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <algorithm>

typedef struct s_hand {
    std::string cards;
    int stake;
    int rank;
} t_hand;

int timesInStr(std::string str, char c) {
    int ret = 0;
    for (size_t i = 0; i < str.size(); i++) {
        if (str[i] == c)
            ret++;
    }
    return (ret);
}

int handStr(std::string str) {
    std::unordered_map<char, int> m;
    for (auto ch : str) 
        m[ch]++;
    if (m.size() == 1) // Five of a kind
        return (6);
    else if (m.size() == 5) // High card
        return (0);
    else if (m.size() == 4) // One pair
        return (1);
    else if (m.size() == 3) {
        for (auto k : m) {
            if (k.second == 3)
                return (3); // Three of a kind
        }
        return (2); // Two pairs       
    }
    else { // m.size == 2
        for (auto k : m) {
            if (k.second == 4)
                return (5); // Four of a kind
        }
        return (4); // Full house
    }
    return (0);
}

int cardStr(char c) {
    std::string cards = "23456789TJQKA";
    for (size_t i = 0; i < cards.length(); i++)
        if (c == cards[i])
            return (i);
    return (-1);
}

int cmpCards(t_hand a, t_hand b) {
    if (a.rank == b.rank) {
        for (int i = 0; i < 5; i++) {
            int value_a = cardStr(a.cards[i]);
            int value_b = cardStr(b.cards[i]);
            if (value_a != value_b)
                return (value_a < value_b);
        }
        return (0);
    }
    else
        return (a.rank < b.rank);
}

int main(void) {
    std::ifstream file;
    file.open("input.txt");
    std::string line;
    std::vector<t_hand> game;
    while (std::getline(file, line)) {
        t_hand hand;
        hand.cards = line.substr(0, 5);
        hand.stake = std::stoi(line.substr(6));
        game.push_back(hand);
    }
    for (size_t i = 0; i < game.size(); i++)
        game[i].rank = handStr(game[i].cards);
    std::sort(game.begin(), game.end(), cmpCards);
    int ret = 0;
    for (size_t i = 0; i < game.size(); i++) {
        std::cout << i + 1 << ": " << game[i].cards << " Rank: " << game[i].rank << std::endl;
        ret += game[i].stake * (i + 1);
    }
    std::cout << ret << std::endl;
}