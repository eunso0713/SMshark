#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"



#define MAX_CHARNAME		200 
#define N_PLAYER			3
//플레이어 명수 설정  
#define MAX_DICE			6
//주사위 max값 설정  

#define PLAYERSTATUS_LIVE		0
#define PLAYERSTATUS_DIE		1
#define PLAYERSTATUS_END		2
//끝까지 살아남아서 간 거==END . 플레이어의 상태 정수로 부여 

int player_position[N_PLAYER];
//플레이어 위치 
char player_name[N_PLAYER][MAX_CHARNAME];
//플레이어 이름 
int player_coin[N_PLAYER];
//플레이어 코인 수
int player_status[N_PLAYER];
//player_status[0] = PLAYERSTATUS_DIE; : 0번 플레이어가 죽었음  
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
//opening 함수 만들기 
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
		if (i == player_position[player])//현재위치 = 플레이어위치 
			printf("%c", player_name[player][0]);
			//플레이어 이름의 첫번째글자 프린트 
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
	//몇번째 턴인지  
	//random 불러오기 
	srand((unsigned)time(NULL));
	

	
	//0. opening
	opening();
	
	//1. 초기화 & 플레이어 이름 결정
	board_initBoard();
	//1-2. 플레이어 초기화
	for (i=0;i<N_PLAYER;i++)
	{
		player_position[i] = 0;
		player_coin[i] = 0;
		player_status[i] = PLAYERSTATUS_LIVE;
		//player 살아있도록 
		printf("Player %i's name: ", i);
		scanf("%s", player_name[i]);
		//player name 재설정  . & 필요없음: player_name 자체가 포인터에 해당하기 때문 
	}
	
	
	
	//2. 반복문 (플레이어 턴)
	do {
		int step;
		int coinResult;
		char c;
		
		if (player_status[turn] != PLAYERSTATUS_LIVE)
		{
			turn = (turn + 1)%N_PLAYER;
			continue;
		}
		//2-1. board & 플레이어의 상태 출력
		board_printBoardStatus();
		for (i=0; i<N_PLAYER; i++)
			printPlayerPosition(i);
		printPlayerStatus();
		
		
		//2-2. 주사위 던지기
		printf("%s turn!", player_name[turn]);
		printf("press any key to continue");
		scanf("%d", &c);
		fflush(stdin);
		step = rolldice();
		
		
		//2-3. 이동
		player_position[turn] += step;
		if (player_position[turn] >= N_BOARD)
		{
			player_position[turn] = N_BOARD - 1;
			player_status[turn] = PLAYERSTATUS_END;
		}
		if (player_position[turn] == N_BOARD - 1)
			player_status[turn] = PLAYERSTATUS_END;
//		printf("position: %d\n", player_position[turn]);
			
		
		printf("%d만큼 이동해 %d로 위치가 이동했습니다.\n", step, player_position[turn]);
		
		
		//2-4. 동전 줍기
		
		coinResult = board_getBoardCoin(player_position[turn]);
		player_coin[turn] += coinResult;
		printf("coin: %d\n", player_coin[turn]);
		
		//2-5. 다음 턴 
		
		turn = (turn + 1)%N_PLAYER; //wrap around를 시킴: N_PLAYER만큼 되는 순간 0으로 돌아가긔
		 
		//2-6. if (조건: 모든 플레이어가 한 번씩 턴을 돈다)
		if (turn == 0)
		{
			//상어 동작
			 int shark_pos = board_stepShark();
			 printf("상어가 이동했습니다.\n");
			 //죽었는 지 살았는 지 판단 
			 checkDie();
			// 다 죽었거나 끝났는지 확인..
			 
		}
	 if (game_end() == 1) break;
	// else printf("No End\n");
		
	} while (1);
	
	//3. 정리 (승자 계산, 출력 등) 
	
	if (getAlivePlayer()==0) printf("No Winner!!!\n");
	else printf("Winner is %s !!!\n", player_name[getWinner()]);
	
	system("PAUSE");
	return 0;
}
