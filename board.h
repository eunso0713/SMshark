#include <stdio.h>
#include <stdlib.h>
#define BOARDSTATUS_OK		1
#define BOARDSTATUS_NOTOK	0
//board의 상태를 정하기: ok or not ok
int board_initBoard(void);

int board_printBoardStatus(void);

int board_getBoardCoin(int pos);
//pos: position

int board_getBoardStatus(int pos);
//특정 position이 파손되었는지 확인해야해서 포지션 받아야 함
 
 
 
int board_getSharkPosition(void);

int board_stepShark(void);


