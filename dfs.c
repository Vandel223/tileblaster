#include <stdlib.h>

#include "state.h"
#include "stack.h"
#include "dfs.h"


State *makePlay(State *stt) {

	State *newStt = stateCopy(stt);

	stateRmvBlock(newStt);
	stateBlocks(newStt);

	return newStt;

}

Coords *backTrack(State *stt) {

	Coords *coords = (Coords *) calloc(grRows(stateWall(stt)) * grCols(stateWall(stt)) / 2, sizeof(Coords));

	int i = 0;

	while (statePrev(stt) != NULL) {

		if (statePlay(stt)) {
			coords[i].x = blkX(statePlay(stt));
			coords[i++].y = blkY(statePlay(stt));
		}
		else {
			coords[i].x = 0;
			coords[i++].y = 0;
		}
		stt = statePrev(stt);

	}

	Coords aux;
	i--; // i is pointing to last element now

	/* This part inverts the array, since we were going from final state to starting state */
	for (int j = 0; j < i; i--, j++) {

		aux = coords[i];
		coords[i] = coords[j];
		coords[j] = aux;

	}

	return coords;

}

Coords *dfs(State *stt, int max, int *numPlays, int *score) {

	int max_score = -1, num_play = 1;
	State *currState;
	Coords *coords = NULL;

	Stack *stk = stInit(grCols(stateWall(stt)) * grRows(stateWall(stt)) / 2);

	push((Item) stt, stk);

	/* Var 1/2 */
	if (max >= 0) {

		while (1) {

			if ((currState = (State *) pop(stk)) == NULL) break;

			while (1) {

				if (stateClear(currState) == 1) {

					if (stateScore(currState) >= max) {

						*numPlays = num_play; 
						coords = backTrack(currState);
						*score = stateScore(currState);
						stFree(stk, stateFree);
						stateFree(currState);
						return coords;

					}

					else {

						num_play--;
						stateFree((Item) currState);
						break;

					}

				}

				else if (num_play >= 5 && !thereIsHope(currState, max, stateColor(currState))) {

					num_play--;
					stateFree((Item) currState);
					break;

				}

				else {

					num_play++;
					push((Item) currState, stk);
					currState = makePlay(currState);

				}

			}

		}


		stFree(stk, stateFree);
		return NULL;

	}

	if (max == -3) {

		while (1) {

			if ((currState = (State *) pop(stk)) == NULL) break;

			while (1) {

				if (stateClear(currState) == 1) {

					if (stateScore(currState) > max_score) {

						*numPlays = num_play;
						max_score = stateScore(currState);
						if (coords != NULL) free(coords);
						coords = backTrack(currState);

					}

					num_play--;
					stateFree((Item) currState);
					break;

				}

				else if (num_play >= 5 && !thereIsHope(currState, max_score, stateColor(currState))) {

					num_play--;
					stateFree((Item) currState);
					break;

				}

				else {

					num_play++;
					push((Item) currState, stk);
					currState = makePlay(currState);

				}

			}

		}

		stFree(stk, stateFree);
		*score = max_score;
		if (max_score == -1) return NULL;
		else return coords;

	}

	return NULL;

}

