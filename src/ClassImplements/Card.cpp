#include "../ClassHeaders/Card.hpp"
#include <iostream>
#include <ostream>

// Constructor
Card::Card(type type, int number): _type(type), _nu(number)
{
	/* std::cout << "Card:\tcreating object\n"; */
}

// Destructor
Card::~Card(void)
{
	/* std::cout << "Card:\tdestroying object\n"; */
}

std::ostream & operator << (std::ostream &os, const Card &other)
{
	os << other.getNu();
	switch(other.getType())
	{
		case HEARTS:
			os << " of Hearts" << std::endl;
			break;
		case CLUBS:
			os << " of Clubs" << std::endl;
			break;
		case DIAMONDS:
			os << " of Diamonds" << std::endl;
			break;
		case SPADES:
			os << " of Spades" << std::endl;
			break;
	}
	return os;
}
