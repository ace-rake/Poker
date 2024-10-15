#ifndef GAME_HPP
# define GAME_HPP

// Custom class: Game
#include "Deck.hpp"
#include "User.hpp"
#include <vector>
class	Game
{
	public:
		// Constructor
		Game	(	void	);

		// Destructor
		~Game	(void);

		int	startGame(std::vector<User *>);
		void	addToQueu(User &);
		void	addQueuToGame();

		void	sendToAllGame(std::string);
		void	update(User & user, std::vector<std::string> words);

		// Getters and Setter

	private:
		// Game logic commands
		void	commandHandler(User &, std::vector<std::string> &);
		// 
		// See
		void	see(User & user)const;
		// Fold
		void	fold(User & user)const;
		// Check
		void	check(User & user)const;
		// Raise
		void	raise(User & user, int);
		// Call
		void	call(User & user);


		void	updateNextActive(void);
	
	protected:
		/*_*/;

	private:
		std::vector<User *>	_participants;
		std::vector<User *>	_queu;
		Deck			_deck;
		std::vector<Card>	_field;
		int			_pot;
		bool			_gameIsRunning;
		bool			_inRound;

		/*_*/;
};

#endif

