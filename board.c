#include <stdio.h>
#include <stdlib.h>

#include "board.h"

#define N_BOARD				15
//board 크기를 정하기: 15칸

#define N_COINPOS			12
#define MAX_COIN			4
 
static int board_status[N_BOARD];
static int board_coin[N_BOARD];

static int board_sharkPosition;

int board_initBoard(void)
{
	int i;
	for (i=0; i < N_BOARD; i++)
	{
		board_status[i] = BOARDSTATUS_OK;
		board_coin[i] = 0;
	}
	//coin 할당
	
	for (i=0;i<N_COINPOS;i++)
	{
		int flag = 0;
		while(flag == 0)
		{
			int allocPos = rand()%N_BOARD;
			//N_BOARD부터 0까지 숫자 중 하나 랜덤 할당 
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
	printf("---------BOARD STATUS--------");
	for (i=0; i<N_BOARD; i++)
	{
		printf("|");
		if (board_status[i] == BOARDSTATUS_NOTOK)
			printf("X");
		else
			printf("O");
	}
	printf("|\n");
	printf("------------------------------\n");
}

int board_getBoardCoin(int pos)
{
	int coin = board_coin[pos];
	board_coin[pos] = 0;
	return coin;
}
//pos: position

int board_getBoardStatus(int pos)
{
	return board_status[pos];
}
//특정 position이 파손되었는지 확인해야해서 포지션 받아야 함

 
 
int board_getSharkPosition(void);

int board_stepShark(void);


