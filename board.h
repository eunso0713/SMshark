#include <stdio.h>
#include <stdlib.h>
//board�� ���¸� ���ϱ�: ok or not ok
#define BOARDSTATUS_OK		1
#define BOARDSTATUS_NOTOK	0
#define N_BOARD				15
//board ũ�⸦ ���ϱ�: 15ĭ


int board_initBoard(void);

int board_printBoardStatus(void);

int board_getBoardCoin(int pos);
//pos: position

int board_getBoardStatus(int pos);
//Ư�� position�� �ļյǾ����� Ȯ���ؾ��ؼ� ������ �޾ƾ� ��
 
 
 


int board_stepShark(void);


