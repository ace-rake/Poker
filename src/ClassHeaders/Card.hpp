#ifndef CARD_HPP
# define CARD_HPP

#include <ostream>
enum	type
{
	HEARTS,
	CLUBS,
	SPADES,
	DIAMONDS
};

// Custom class: Card
class	Card
{
	public:
		// Constructor
		Card	(	type, int	);

		// Destructor
		~Card	(void);

		friend std::ostream & operator << (std::ostream &, const Card &other);

		// Getters and setters
		type	getType(void)const{return _type;}
		void	setType(type type){_type = type;}

		int	getNu(void)const{return _nu;}
		void	setNu(int nu){_nu = nu;}

	protected:
		/*_*/;

	private:
		type	_type;
		int	_nu;
		/*_*/;
};

#endif

