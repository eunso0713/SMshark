#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"



#define MAX_CHARNAME		200 
#define N_PLAYER			3
//�÷��̾� ��� ����  
#define MAX_DICE			6
//�ֻ��� max�� ����  

#define PLAYERSTATUS_LIVE		0
#define PLAYERSTATUS_DIE		1
#define PLAYERSTATUS_END		2
//������ ��Ƴ��Ƽ� �� ��==END . �÷��̾��� ���� ������ �ο� 

int player_position[N_PLAYER];
//�÷��̾� ��ġ 
char player_name[N_PLAYER][MAX_CHARNAME];
//�÷��̾� �̸� 
int player_coin[N_PLAYER];
//�÷��̾� ���� ��
int player_status[N_PLAYER];
//player_status[0] = PLAYERSTATUS_DIE; : 0�� �÷��̾ �׾���  
//0: live, 1: die, 2: end
char player_statusString[3][MAX_CHARNAME] = {"ALIVE", "DEAD", "END"};


int game_end(void)
{
	int i;
	int flag_end = 1;
	
	//if all the players are dead
	for (i=0; i<N_PLAYER; i++)
	{
		if (player_status[i] == PLAYERSTATUS_LIVE)
		{
			flag_end = 0;
			break;
		}
	}
	
	return flag_end;
}


int getAlivePlayer(void)
{
	int i;
	int cnt = 0;
	for (i=0; i<N_PLAYER; i++)
	{
		if (player_status[i] == PLAYERSTATUS_END)
			cnt++;
	}
	
	return cnt;
}


int getWinner(void)
{
	int i;
	int winner = 0;
	int max_coin =-1;
	
	for (i=0;i<N_PLAYER;i++)
	{
		if (player_coin[i] > max_coin)
		{
			max_coin = player_coin[i];
			winner = i;
		}
	}
	
	return winner;
}
//opening �Լ� ����� 
void opening(void)
{
	printf("==================================\n");
	printf("=========Shark Game Start=========\n");
	printf("==================================\n\n\n\n\n\n");
	
}

int rolldice(void)
{
	int r;
	r=rand()%MAX_DICE+1;
	printf("%d\n", r);
	return r;
	//return rand()%MAX_DICE + 1;
	//1~6
}

void printPlayerPosition(int player)
{
	int i;
	for (i=0; i<N_BOARD; i++)
	{
		printf("|");
		if (i == player_position[player])//������ġ = �÷��̾���ġ 
			printf("%c", player_name[player][0]);
			//�÷��̾� �̸��� ù��°���� ����Ʈ 
		else
		{
			if (board_getBoardStatus(i) == BOARDSTATUS_NOTOK)
				printf("X");
			else
				printf(" ");
		}
	}
	printf("|\n");
} 


void printPlayerStatus(void)
{
	int i = 0;
	printf("--- player status ---\n");
	
	for (i=0; i<N_PLAYER; i++)
	{
		printf("%s: pos %i, coin %i, status: %s\n", player_name[i], player_position[i], player_coin[i], player_statusString[player_status[i]]);	
	}
	printf("-----------------------------\n");
}





void checkDie(void)
{
	int i, no_alive = 0;
	for (i=0; i<N_PLAYER; i++)
		if (board_getBoardStatus(player_position[i]) == BOARDSTATUS_NOTOK)
			player_status[i] = PLAYERSTATUS_DIE;
}

int main(int argc, char *argv[])
{
	int i;
	int turn = 0;
	//���° ������  
	//random �ҷ����� 
	srand((unsigned)time(NULL));
	

	
	//0. opening
	opening();
	
	//1. �ʱ�ȭ & �÷��̾� �̸� ����
	board_initBoard();
	//1-2. �÷��̾� �ʱ�ȭ
	for (i=0;i<N_PLAYER;i++)
	{
		player_position[i] = 0;
		player_coin[i] = 0;
		player_status[i] = PLAYERSTATUS_LIVE;
		//player ����ֵ��� 
		printf("Player %i's name: ", i);
		scanf("%s", player_name[i]);
		//player name �缳��  . & �ʿ����: player_name ��ü�� �����Ϳ� �ش��ϱ� ���� 
	}
	
	
	
	//2. �ݺ��� (�÷��̾� ��)
	do {
		int step;
		int coinResult;
		char c;
		
		if (player_status[turn] != PLAYERSTATUS_LIVE)
		{
			turn = (turn + 1)%N_PLAYER;
			continue;
		}
		//2-1. board & �÷��̾��� ���� ���
		board_printBoardStatus();
		for (i=0; i<N_PLAYER; i++)
			printPlayerPosition(i);
		printPlayerStatus();
		
		
		//2-2. �ֻ��� ������
		printf("%s turn!", player_name[turn]);
		printf("press any key to continue");
		scanf("%d", &c);
		fflush(stdin);
		step = rolldice();
		
		
		//2-3. �̵�
		player_position[turn] += step;
		if (player_position[turn] >= N_BOARD)
		{
			player_position[turn] = N_BOARD - 1;
			player_status[turn] = PLAYERSTATUS_END;
		}
		if (player_position[turn] == N_BOARD - 1)
			player_status[turn] = PLAYERSTATUS_END;
//		printf("position: %d\n", player_position[turn]);
			
		
		printf("%d��ŭ �̵��� %d�� ��ġ�� �̵��߽��ϴ�.\n", step, player_position[turn]);
		
		
		//2-4. ���� �ݱ�
		
		coinResult = board_getBoardCoin(player_position[turn]);
		player_coin[turn] += coinResult;
		printf("coin: %d\n", player_coin[turn]);
		
		//2-5. ���� �� 
		
		turn = (turn + 1)%N_PLAYER; //wrap around�� ��Ŵ: N_PLAYER��ŭ �Ǵ� ���� 0���� ���ư���
		 
		//2-6. if (����: ��� �÷��̾ �� ���� ���� ����)
		if (turn == 0)
		{
			//��� ����
			 int shark_pos = board_stepShark();
			 printf("�� �̵��߽��ϴ�.\n");
			 //�׾��� �� ��Ҵ� �� �Ǵ� 
			 checkDie();
			// �� �׾��ų� �������� Ȯ��..
			 
		}
	 if (game_end() == 1) break;
	// else printf("No End\n");
		
	} while (1);
	
	//3. ���� (���� ���, ��� ��) 
	
	if (getAlivePlayer()==0) printf("No Winner!!!\n");
	else printf("Winner is %s !!!\n", player_name[getWinner()]);
	
	system("PAUSE");
	return 0;
}
