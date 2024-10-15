#ifndef DECK_HPP
# define DECK_HPP
#include "Card.hpp"
// Custom class: Deck
#include <vector>
class	Deck
{
	public:
		// Constructor
		Deck	(	void	);

		// Destructor
		~Deck	(void);

		// Display all current cards
		void	display(void)const;

		// Get random card
		Card	randomCard(void);

		// Add Card to deck
		void	addCard(Card);

		// Getters and Setter

	protected:
		/*_*/;

	private:
		std::vector<Card>	_cards;
		int			_nu;
		/*_*/;
};

#endif

