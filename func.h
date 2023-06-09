// func.h -- statement of functions and static ver
#include <vector>
static int ROW = 9, COL = 9; //默认为9*9
enum difficult {Eazy = 10, Middle = 40, Hard = 99}; // 难度系数

int randint(int min, int max);//返回min~max之间的随机值
void initset(char * board);//初始化棋盘
void initset_dis(char * dis_board);//初始化展示棋盘
void displayBoard(char * board);//展示棋盘
void start_menu();//输出菜单
void DIY_menu();//自定义模式菜单
void normal_menu();//普通模式菜单
void gameover_dis(char * board, char * dis_board);//游戏结束棋盘 在现有棋盘的基础上展示所有的雷
void calcBoard(int row, int col, char * board);//执行埋雷操作
void setBomb(char * board, int bombnum);//随机生成雷
void trriger(char * board,char * dis_board, int row, int col);//玩
void setboard(char * &board, char * &dis_board);//设置行列
bool checkWin(char * board, char * dis_board); // 检查游戏是否胜利
bool placeMine(char * board);//放置地雷
void resetBoard(char *&board, char *&dis_board);//重置棋盘
void setDifficult(char *&board, char *&dis_board);//设置难度