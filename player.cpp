#include "player.h"

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish 
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    this->testingMinimax = false;
    this->b = Board();
    this->side = side;

}

/*
 * Destructor for the player.
 */
Player::~Player() {
}

/*
 * Sets the Board 'b' to a given Board 'b1'.
 */
void Player::mysetBoard(Board b1)
{
	this->b = b1;
}
/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be NULL.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return NULL.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    /* 
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */
    
    Side side_opp;
    if (side == WHITE)
    {
		side_opp = BLACK;
	}
	else // side == BLACK
	{
		side_opp = WHITE;
	}
    b.doMove(opponentsMove, side_opp);
    
    if (!b.hasMoves(side))
    {
		return NULL;
	}
	
	vector<int> myMoves = b.validMoves(side);
	/* This is the first working AI. It chooses a random valid move. */
    /*
	int m = rand() % myMoves.size();
	int x = myMoves[m] % 8;
	int y = myMoves[m] / 8;
	Move *mymove = new Move(x, y);
	b.doMove(mymove, side);
	return mymove;
	*/
	
    // testingMinimax = true;
	if (!testingMinimax) // This is an AI only using the heuristic function to beat SimplePlayer.
	{
		Move *mymove = new Move(0, 0);
		int i_max, s, s_max = (-5) * 64;
		vector<int> scores;
		/* find the optimal valid move */
		for (unsigned int i = 0; i < myMoves.size(); i++)
		{
			mymove->setX(myMoves[i] % 8);
			mymove->setY(myMoves[i] / 8);
			Board *b_test = b.copy();
			/* do the move and calculate the score on the copied board */
			b_test->doMove(mymove, side);
			s = b_test->score(side);
			if (s > s_max)
			{
				s_max = s;
				i_max = i;
			}
			delete b_test;
		}
		mymove->setX(myMoves[i_max] % 8);
		mymove->setY(myMoves[i_max] / 8);
		b.doMove(mymove, side);
		return mymove;
	}
	else // This is an AI which uses 2-ply depth minimax and the heuristic function.
	{
		vector<int> yourMoves;
		Move *mymove = new Move(0, 0);
		Move *yourmove = new Move(0, 0);
		int i_max, s1, s2, s_max = (-5) * 64, s_min;
		vector<int> myScores, yourScores;
		for (unsigned int i = 0; i < myMoves.size(); i++)
		{
			mymove->setX(myMoves[i] % 8);
			mymove->setY(myMoves[i] / 8);
			Board *b1 = b.copy();
			b1->doMove(mymove, side);
			s1 = b1->score(side);     // score after mymove is done
			
			/* Initialize s_min. If there is no valid moves for the opponent,
			   then s_min = s1. */
			s_min = s1; 
			yourMoves = b1->validMoves(side_opp); // opponent's valid moves
			/* find the minimal score when oppenent tries to
			 * minimize the score, assign it to s_min */
			for (unsigned int j = 0; j < yourMoves.size(); j++)
			{
				yourmove->setX(yourMoves[j] % 8);
				yourmove->setY(yourMoves[j] / 8);
				Board *b2 = b1->copy();
				b2->doMove(yourmove, side_opp);
				s2 = b2->score(side);
				if (s2 < s_min)
				{
					s_min = s2;
				}
				delete b2;
			}
			yourMoves.clear();
			
			/* find the maximum score between s_min */
			if (s_min > s_max)
			{
				s_max = s_min;
				i_max = i;
			}
			delete b1;
		}
		mymove->setX(myMoves[i_max] % 8);
		mymove->setY(myMoves[i_max] / 8);
		b.doMove(mymove, side);
		return mymove;
	}
}
