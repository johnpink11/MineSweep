// func.h -- statement of functions and static ver
#include <vector>
static int ROW = 9, COL = 9; //Ĭ��Ϊ9*9

int randint(int min, int max);//����min~max֮������ֵ
void initset(char * board);//��ʼ������
void initset_dis(char * dis_board);//��ʼ��չʾ����
void displayBoard(char * board);//չʾ����
void start_menu();//����˵�
void start_menu2();//����˵�2
void DIY_menu();//�Զ���ģʽ�˵�
void normal_menu();//��ͨģʽ�˵�
void gameover();//��Ϸ����
void calcBoard(int row, int col, char * board);//ִ�����ײ���
void setBomb(char * board, int bombnum);//���������
void trriger(char * board,char * dis_board, int row, int col);//��
void setboard(char * &board, char * &dis_board);//��������
bool checkWin(char * board, char * dis_board); // �����Ϸ�Ƿ�ʤ��
bool placeMine(char * board);//���õ���
void resetBoard(char *&board, char *&dis_board);//��������
int setDifficult(char *&board, char *&dis_board);//�����Ѷ�