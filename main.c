#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"

#define MAX_DICE		6
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

//opening 함수 만들기 
void opening(void)
{
	printf("==================================\n");
	printf("=========Shark Game Start=========\n");
	printf("==================================\n");
	
}

int rolldice(void)
{
	return rand()%MAX_DICE + 1;
	//1~6
}

int main(int argc, char *argv[])
{
	int pos = 0;
	//random 불러오기 
	srand((unsigned)time(NULL));
	
	//0. opening
	opening();
	
	//1. 초기화 & 플레이어 이름 결정
	board_initBoard();
	
	//2. 반복문 (플레이어 턴)
	do {
		int step = rolldice();
		int coinResult;
		char c;
		
		board_printBoardStatus();
		
		pos += step;
		printf("어디에서 어디로 위치가 이동햇습니다");
		coinResult = board_getBoardCoin (pos);
		
		printf("press any key to continue");
		scanf("%d", &c);
		fflush(stdin);
	
		//2-1. 플레이어의 상태 출력
		//2-2. 주사위 던지기
		//2-3. 이동
		//2-4. 동전 줍기
		//2-5. 다음 턴 
		//2-6. if (조건: 모든 플레이어가 한 번씩 턴을 돈다)
			//상어 동작
	} while (1);
	
	
	//3. 정리 (승자 계산, 출력 등) 
	
	
	system("PAUSE");
	return 0;
}
