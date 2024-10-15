#include "../ClassHeaders/Deck.hpp"
#include <unistd.h>
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sys/time.h>

// Constructor
Deck::Deck(): _nu(52)
{
	/* std::cout << "Deck:\tcreating object\n"; */
	for (int i = 0; i < 52; i++)
	{
		if (i / 13 == 0)
			_cards.push_back(Card(HEARTS, (i % 13) + 1));
		else if (i / 13 == 1)
			_cards.push_back(Card(CLUBS, (i % 13) + 1));
		else if (i / 13 == 2)
			_cards.push_back(Card(DIAMONDS, (i % 13) + 1));
		else
			_cards.push_back(Card(SPADES, (i % 13) + 1));
	}
}

// Destructor
Deck::~Deck(void)
{
	/* std::cout << "Deck:\tdestroying object\n"; */
}

void	Deck::display()const
{
	for (const Card & card : _cards)
		std::cout << card;
}

Card	Deck::randomCard()
{
	size_t	size = _cards.size();

	struct timeval tv;
	gettimeofday(&tv, nullptr);   // Get current time with microseconds precision
	srand(tv.tv_sec * 1000000 + tv.tv_usec);

	int	index = rand() % size;

	Card card = _cards[index];

	_cards.erase(_cards.begin() + index);

	_nu--;
	usleep(1);

	return card;
}

void	Deck::addCard(Card)
{
	_nu++;
}
