#include <iostream>

//custom class for returning an end
struct EndState {

	bool isEnd;
	char winner;

	EndState(bool end, char win) {

		isEnd = end;
		winner = win;

	}

	~EndState() {



	}

};

//game class for storing & manipulating board
struct Game {

	//board array
	char board[3][3];

	//constructer sets board to empty
	Game() {

		Reset();

	}

	~Game() {



	}

	//sets board to empty
	void Reset() {

		int index = 0;

		char dispNum[9] = { '7', '8', '9', '4', '5', '6', '1', '2', '3' };

		for (int i = 0; i < 3; i++) {


			for (int j = 0; j < 3; j++) {

				board[i][j] = dispNum[index];

				index++;

			}

		}

	}

	//tries to make a move and return weather it has succeeded or not
	bool Move(char pos, char player) {

		for (int i = 0; i < 3; i++) {

			for (int j = 0; j < 3; j++) {

				if (board[i][j] == char(pos)) {

					board[i][j] = player;

					return true;

				}

			}

		}

		return false;

	}

	//sets the board to another board
	void SetBoard(char newBoard[3][3]) {

		for (int i = 0; i < 3; i++) {

			for (int j = 0; j < 3; j++) {

				board[i][j] = newBoard[i][j];

			}

		}

	}

	//checks if the game has ended outputting the custom class
	static EndState CheckEnd(char board[3][3]) {

		bool check = 0;
		char lineCheck[3];
		bool boardCheck = 1;

		//check for horizontal lines
		for (int i = 0; i < 3; i++) {

			for (int j = 0; j < 3; j++) {

				lineCheck[j] = board[i][j];

			}

			if (lineCheck[0] == lineCheck[1] && lineCheck[0] == lineCheck[2]) {

				return EndState(1, lineCheck[0]);

			}

		}

		//check for vertical lines
		for (int i = 0; i < 3; i++) {

			for (int j = 0; j < 3; j++) {

				lineCheck[j] = board[j][i];

			}

			if (lineCheck[0] == lineCheck[1] && lineCheck[0] == lineCheck[2]) {

				return EndState(1, lineCheck[0]);

			}

		}

		//check for diagonal lines
		if (board[0][0] == board[1][1] && board[0][0] == board[2][2]) return EndState(1, board[0][0]);
		else if (board[0][2] == board[1][1] && board[0][2] == board[2][0]) return EndState(1, board[0][2]);

		//check for tie
		for (int i = 0; i < 3; i++) {

			if (boardCheck == 0) break;

			for (int j = 0; j < 3; j++) {

				if (board[i][j] != 'X' && board[i][j] != 'O') {

					boardCheck = 0;
					break;

				}

			}

		}

		if (boardCheck) return EndState(1, 'T');

		return EndState(0, 'N');

	}

	//print a board
	static void PrintBoard(char board[3][3]) {

		for (int i = 0; i < 3; i++) {

			std::cout << "    ";

			for (int j = 0; j < 3; j++) {

				if (j != 2) {

					std::cout << board[i][j] << " | ";

				}
				else {

					std::cout << board[i][j];

				}

			}

			if (i != 2) {

				std::cout << std::endl << "   -----------" << std::endl;

			}
			else {

				std::cout << std::endl;

			}

		}

	}

	//checks to see if a position is free or not
	static bool IsValidInput(char pos, char player, char board[3][3]) {

		for (int i = 0; i < 3; i++) {

			for (int j = 0; j < 3; j++) {

				if (board[i][j] == pos) {

					return false;

				}

			}

		}

		return true;

	}

};

//holds all the ai functions
struct Ai {

	//minimax algorithm
	static int MiniMax(char board[3][3], bool isMaximizing, bool player, char playerChars[2]) {

		/*//print every newly generated board by the algorithm (for debugging)
		system("CLS");
		Game::PrintBoard(board);
		*/

		EndState result = Game::CheckEnd(board);

		int score;
		int bestScore = -100;

		if (result.isEnd) {

			if (result.winner == 'T') {

				score = 0;

			}
			else if (result.winner == playerChars[player]) {

				score = 1;

			}
			else {

				score = -1;

			}

			return score;

		}

		if (isMaximizing) {

			char emptyBoard[3][3] = { '7', '8', '9', '4', '5', '6', '1', '2', '3' };

			for (int i = 0; i < 3; i++) {

				for (int j = 0; j < 3; j++) {

					if (board[i][j] != 'X' && board[i][j] != 'O') {

						board[i][j] = playerChars[!player];
						score = MiniMax(board, 0, player, playerChars);
						board[i][j] = emptyBoard[i][j];

						if (score > bestScore) {

							bestScore = score;

						}

					}

				}

			}

			return bestScore;

		}
		else {

			char emptyBoard[3][3] = { '7', '8', '9', '4', '5', '6', '1', '2', '3' };

			for (int i = 0; i < 3; i++) {

				for (int j = 0; j < 3; j++) {

					if (board[i][j] != 'X' && board[i][j] != 'O') {

						board[i][j] = playerChars[player];
						score = MiniMax(board, 1, player, playerChars);
						board[i][j] = emptyBoard[i][j];

						if (score < bestScore) {

							bestScore = score;

						}

					}

				}

			}

			return bestScore;

		}

	}

	//gets a move for the ai of a spesific dificulty
	static char AiMove(char board[3][3], int dificulty, bool player) {

		char move = '1';

		char freeSlots[9] = { '1', '2', '3', '4', '5', '6', '7', '8' };
		int freeSlotsLen = 0;

		char emptyBoard[3][3] = { '7', '8', '9', '4', '5', '6', '1', '2', '3' };
		char playerChars[2] = { 'X', 'O' };
		int bestScore = -100;
		char bestMove = '1';
		int score;

		switch (dificulty) {

		//if noob dificulty, output a random free space
		case 0:
			

			for (int i = 0; i < 3; i++) {

				for (int j = 0; j < 3; j++) {

					if (board[i][j] != 'X' && board[i][j] != 'O') {

						freeSlots[freeSlotsLen] = board[i][j];
						freeSlotsLen++;

					}

				}

			}

			move = freeSlots[rand() % freeSlotsLen];
			break;

		//if FULL POWER dificulty, run minimax algorithm on the current board
		case 5:


			for (int i = 0; i < 3; i++) {

				for (int j = 0; j < 3; j++) {

					if (board[i][j] != 'X' && board[i][j] != 'O') {

						board[i][j] = playerChars[player];
						score = MiniMax(board, 1, player, playerChars);
						board[i][j] = emptyBoard[i][j];

						if (score > bestScore) {

							bestScore = score;
							bestMove = board[i][j];

						}

					}

				}

			}

			move = bestMove;

		}

		return move;

	}

};

//user input class and functions
struct Inputs {

	int mode;
	int dificulty;
	bool aiPlayer;

	//constructer that sets all varialbes
	Inputs(int Mode, int Dificulty, bool AiPlayer) {

		mode = Mode;
		dificulty = Dificulty;
		aiPlayer = AiPlayer;

	}

	//gets the user's desired settings
	static Inputs GetSetup() {

		int mode;
		int dificulty = 0;
		bool aiPlayer = 0;

		char inputCashe;
		bool isDone = 0;

		system("CLS");

		while (!isDone) {

			std::cout
				<< "    0: Single-Player" << std::endl
				<< "    1: Multi-player" << std::endl
				<< "    2: Zero-Player" << std::endl
				<< std::endl
				<< "Select a mode (0-2): ";
			std::cin >> inputCashe;

			switch (inputCashe) {

			case '0':

				mode = 0;
				isDone = 1;
				break;

			case '1':

				mode = 1;
				isDone = 1;
				break;

			case '2':

				mode = 2;
				isDone = 1;
				break;

			default:

				system("CLS");
				std::cout << "Please enter a valid input." << std::endl << std::endl;
				break;

			}

		}

		if (mode == 0 || mode == 2) {

			isDone = 0;
			system("CLS");

			while (!isDone) {

				std::cout
					<< "    0: Idiot" << std::endl
					<< "    1: Noob" << std::endl
					<< "    2: Intermediate" << std::endl
					<< "    3: Expert" << std::endl
					<< "    4: Master" << std::endl
					<< "    5: FULL POWER" << std::endl
					<< std::endl
					<< "Select a dificulty (0-5): ";
				std::cin >> inputCashe;

				switch (inputCashe) {

				case '0':

					dificulty = 0;
					isDone = 1;
					break;


				case '1':

					dificulty = 1;
					isDone = 1;
					break;

				case '2':

					dificulty = 2;
					isDone = 1;
					break;

				case '3':

					dificulty = 3;
					isDone = 1;
					break;

				case '4':

					dificulty = 4;
					isDone = 1;
					break;

				case '5':

					dificulty = 5;
					isDone = 1;
					break;

				default:

					system("CLS");
					std::cout << "Please enter a valid input." << std::endl << std::endl;
					break;

				}

			}

			if (mode == 0) {

				isDone = 0;
				system("CLS");

				while (!isDone) {

					std::cout
						<< "    0: Player 1 (X)" << std::endl
						<< "    1: Player 2 (O)" << std::endl
						<< std::endl
						<< "Select a player (0-1): ";
					std::cin >> inputCashe;

					switch (inputCashe) {

					case '0':

						aiPlayer = 1;
						isDone = 1;
						break;

					case '1':

						aiPlayer = 0;
						isDone = 1;
						break;

					default:

						system("CLS");
						std::cout << "Please enter a valid input." << std::endl << std::endl;
						break;

					}

				}

			}

		}

		return Inputs(mode, dificulty, aiPlayer);

	}

	//gets player input for the game
	static char GetPlayerInput(char playerChars[2], bool activePlayer, char board[3][3]) {

		char inputCashe;
		bool isDone = 0;

		char move;

		isDone = 0;

		while (!isDone) {

			std::cout << std::endl << playerChars[activePlayer] << "'s turn. Move (0-9): ";
			std::cin >> inputCashe;

			if (inputCashe == '1' || inputCashe == '2' || inputCashe == '3' || inputCashe == '4' || inputCashe == '5' || inputCashe == '6' || inputCashe == '7' || inputCashe == '8' || inputCashe == '9') {

				move = inputCashe;

				if (Game::IsValidInput(move, playerChars[activePlayer], board)) {

					system("CLS");
					Game::PrintBoard(board);
					std::cout << std::endl << "That slot has allready been taken." << std::endl;

				}
				else {

					isDone = 1;
					break;

				}

			}
			else {

				system("CLS");
				Game::PrintBoard(board);
				std::cout << std::endl << "Please enter a valid input." << std::endl;

			}

		}

		return move;

	}



};

//main function
int main() {

	bool isDone = 0;

	bool activePlayer = 0;
	char playerChars[2] = { 'X', 'O' };

	//creates a game
	Game game;

	//gets the users settings
	Inputs setupInputs = Inputs::GetSetup();

	/*// sets the board to sm (for debugging)
	char presetBoard[3][3] = { '7', '8', 'X',
							   '4', 'O', '6',
							   'X', '2', 'O' };

	game.SetBoard(presetBoard);
	*/

	//main game loop
	while (1) {

		//prints board
		system("CLS");
		Game::PrintBoard(game.board);

		//checks for game end
		EndState endState = Game::CheckEnd(game.board);

		//if game ended, print the winnder and pause
		if (endState.isEnd) {

			if (endState.winner == 'T') {

				std::cout << std::endl << "Tie!" << std::endl << std::endl;

			}
			else {

				std::cout << std::endl << endState.winner << " Wins!" << std::endl << std::endl;

			}

			system("pause");
			activePlayer = 0;
			game.Reset();

			system("CLS");
			Game::PrintBoard(game.board);

			endState.~EndState();

		}
		
		//depending on mode, ask for input from human or ai
		switch (setupInputs.mode) {

		case 0:

			if (activePlayer == setupInputs.aiPlayer) {

				game.Move(Ai::AiMove(game.board, setupInputs.dificulty, setupInputs.aiPlayer), playerChars[activePlayer]);

			}
			else {

				game.Move(Inputs::GetPlayerInput(playerChars, activePlayer, game.board), playerChars[activePlayer]);

			}
			break;

		case 1:

			game.Move(Inputs::GetPlayerInput(playerChars, activePlayer, game.board), playerChars[activePlayer]);
			break;

		case 2:

			game.Move(Ai::AiMove(game.board, setupInputs.dificulty, setupInputs.aiPlayer), playerChars[activePlayer]);
			break;

		}

		//switch active player
		activePlayer = !activePlayer;

	}

	return 0;

}