#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"

#define MAX_DICE		6
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

//opening �Լ� ����� 
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
	//random �ҷ����� 
	srand((unsigned)time(NULL));
	
	//0. opening
	opening();
	
	//1. �ʱ�ȭ & �÷��̾� �̸� ����
	board_initBoard();
	
	//2. �ݺ��� (�÷��̾� ��)
	do {
		int step = rolldice();
		int coinResult;
		char c;
		
		board_printBoardStatus();
		
		pos += step;
		printf("��𿡼� ���� ��ġ�� �̵��޽��ϴ�");
		coinResult = board_getBoardCoin (pos);
		
		printf("press any key to continue");
		scanf("%d", &c);
		fflush(stdin);
	
		//2-1. �÷��̾��� ���� ���
		//2-2. �ֻ��� ������
		//2-3. �̵�
		//2-4. ���� �ݱ�
		//2-5. ���� �� 
		//2-6. if (����: ��� �÷��̾ �� ���� ���� ����)
			//��� ����
	} while (1);
	
	
	//3. ���� (���� ���, ��� ��) 
	
	
	system("PAUSE");
	return 0;
}
