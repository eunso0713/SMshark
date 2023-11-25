#include <stdio.h>
#include <stdlib.h>

#include "board.h"


#define N_BOARD				15
#define N_COINPOS			12
#define MAX_COIN			4

#define MAX_SHARKSTEP		6
#define SHARK_INITPOS		-4








static int board_status[N_BOARD];
static int board_coin[N_BOARD];

static int board_sharkPosition;
//int shark_position;

int board_initBoard(void)
{
	int i;
	for (i=0; i < N_BOARD; i++)
	{
		board_status[i] = BOARDSTATUS_OK;
		board_coin[i] = 0;
	}
	board_sharkPosition = SHARK_INITPOS;
	//shark_position = SHARK_INITPOS;
	//coin 할당
	
	for (i=0;i<N_COINPOS;i++)
	{
		int flag = 0;
		while(flag == 0)
		{
			int allocPos = rand()%N_BOARD;
			//0~14 숫자 중 하나 랜덤 할당 
			if (board_coin[allocPos] == 0)
			{
				board_coin[allocPos] = rand()%MAX_COIN + 1;
				flag = 1;
			}
		}
	 }
	return 0;
}

int board_printBoardStatus(void)
{
	int i;
	printf("---------BOARD STATUS--------\n");
	for (i=0; i<N_BOARD; i++)
	{
		printf("|");
		if (board_status[i] == BOARDSTATUS_NOTOK)
			printf("X");
		else
			printf("O");
	}
	printf("|\n");
// Coint status
	printf("---------COIN STATUS--------\n");
	for (i=0; i<N_BOARD; i++)
	{
		printf("|");
		printf("%d", board_coin[i]);
	}
	printf("|\n");
	printf("------------------------------\n");
	
	return 0;
}

int board_getBoardCoin(int pos)
{
	int coin = board_coin[pos];
	board_coin[pos] = 0;
printf("%d coins got\n", coin);
	return coin;
}
//pos: position

int board_getBoardStatus(int pos)
{
	return board_status[pos];
}
//특정 position이 파손되었는지 확인해야해서 포지션 받아야 함

 
 
int board_getSharkPosition(void);

int board_stepShark(void)
{
	int step = rand()%MAX_SHARKSTEP + 1;
	int i;

	for (i=board_sharkPosition + 1; i<=board_sharkPosition + step; i++)
	{
		board_status[i] = BOARDSTATUS_NOTOK;
	}
	board_sharkPosition += step;
	return board_sharkPosition;
}



