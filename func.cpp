// func.cpp -- implementing functions 
// vesion 2.0
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <ctime>
#include <vector>
#include "func.h"

using namespace std;

int randint(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

void initset(char *board)
{
    for (int i = 0; i < ROW * COL; i++)
        board[i] = '0';
}

void initset_dis(char *dis_board)
{
    for (int i = 0; i < ROW * COL; i++)
        dis_board[i] = '*';
}

void displayBoard(char *board)
{
    for (int i = 0; i < 50; i++)
        std::cout << "--";
    std::cout << std::endl;
    std::cout << "***";
    for (int j = 0; j < COL; j++)
        std::cout << std::setw(2) << std::setfill('0') << j + 1;
    std::cout << "***";
    std::cout << '\n';
    for (int j = 0; j < 2 * COL + 6; j++)
        std::cout << '*';
    std::cout << '\n';
    for (int i = 0; i < ROW; i++)
    {
        std::cout << '*' << std::setw(2) << std::setfill('0') << i + 1 << ' ';
        for (int j = 0; j < COL; j++)
            std::cout << board[i * COL + j] << ' ';
        std::cout << "**" << '\n';
    }
    for (int j = 0; j < 2 * COL + 6; j++)
        std::cout << '*';
    std::cout << '\n';
}


void start_menu() {
    using namespace std;
    cout << "\t      扫雷游戏\n";
    cout << "\
***********************************\n\
*          1.自定义模式           *\n\
*          2.普通模式             *\n\
*          3.结束游戏             *\n\
***********************************\n\
";
    cout << "请输入你的选择：";
}

void DIY_menu()
{
    using namespace std;
    cout << "\t      扫雷游戏\n";
    cout << "\
***********************************\n\
*          1.设置行数与列数       *\n\
*          2.埋雷                 *\n\
*          3.开始游戏             *\n\
*          4.重新选择             *\n\
***********************************\n\
";
    cout << "请输入你的选择：";
}

void normal_menu()
{
    using namespace std;
    cout << "\t      扫雷游戏\n";
    cout << "\
***********************************\n\
*          1.难度设置             *\n\
*          2.开始游戏             *\n\
*          3.重新选择             *\n\
***********************************\n\
";
    cout << "请输入你的选择：";
}

void calcBoard(int row, int col, char *board)
{
    if (row && board[(row - 1) * COL + col] != '#')
        board[(row - 1) * COL + col]++;
    if (col && board[row * COL + col - 1] != '#')
        board[row * COL + col - 1]++;
    if (ROW - row - 1 && board[(row + 1) * COL + col] != '#')
        board[(row + 1) * COL + col]++;
    if (COL - col - 1 && board[row * COL + col + 1] != '#')
        board[row * COL + col + 1]++;
    if (row && col && board[(row - 1) * COL + col - 1] != '#')
        board[(row - 1) * COL + col - 1]++;
    if (ROW - row - 1 && col && board[(row + 1) * COL + col - 1] != '#')
        board[(row + 1) * COL + col - 1]++;
    if (row && COL - col - 1 && board[(row - 1) * COL + col + 1] != '#')
        board[(row - 1) * COL + col + 1]++;
    if (ROW - row - 1 && COL - col - 1 && board[(row + 1) * COL + col + 1] != '#')
        board[(row + 1) * COL + col + 1]++;
}

void setBomb(char *board, int bombnum)
{
    int number = 0;
    while (number < bombnum)
    {
        int row = randint(0, ROW - 1);
        int col = randint(0, COL - 1);
        if (board[row * COL + col] == '#')
            continue;
        else
        {
            board[row * COL + col] = '#';
            calcBoard(row, col, board);
            number++;
        }
    }
}

void trriger(char *board, char *dis_board, int row, int col) // 传入行数和列数-1
{
    if (dis_board[row * COL + col] != ' ' && !(dis_board[row * COL + col] >= '1' && dis_board[row * COL + col] <= '8')) // 如果不是空格和数字
    {
        char elem = board[row * COL + col];
        if(elem == '#')
            return;
        if (elem >= '1' && elem <= '8')
        {
            dis_board[row * COL + col] = elem;
            return;
        }
        if (elem == '0')
            dis_board[row * COL + col] = ' ';
        if (col) // 不是第一列
        {
            trriger(board, dis_board, row, col - 1);
            if (row) // 不是左上角
                trriger(board, dis_board, row - 1, col - 1);
        }
        if (row) // 不是第一行
        {
            trriger(board, dis_board, row - 1, col);
            if (COL - col - 1) // 不是右上角
                trriger(board, dis_board, row - 1, col + 1);
        }
        if (COL - col - 1) // 不是最后一列
        {
            trriger(board, dis_board, row, col + 1);
            if (ROW - row - 1) // 不是右下角
                trriger(board, dis_board, row + 1, col + 1);
        }
        if (ROW - row - 1) // 不是最后一行
        {
            trriger(board, dis_board, row + 1, col);
            if (col)//不是左下角
                trriger(board, dis_board, row + 1, col - 1);
        }
    }
    return;
}

void setboard(char *&board, char *&dis_board)
{
    cout << "请输入棋盘的行数和列数： ";
    while (cin >> ROW >> COL && (ROW < 1 || ROW > 99 || COL < 1 || COL > 99))
        cout << "您的输入有误,请输入1~99之间的数字。\n";
    resetBoard(board, dis_board);
}

void resetBoard(char *&board, char *&dis_board)
{
    delete[] board;
    delete[] dis_board;
    board = new char[ROW * COL];
    dis_board = new char[ROW * COL];
    initset(board);
    initset_dis(dis_board);
}

bool checkWin(char *board, char *dis_board)
{
    for (int i = 0; i < ROW * COL - 1; i++)
    {
        if (board[i] != '#' && dis_board[i] == '*')
        {
            return false;
        }
    }
    cout << "恭喜你，游戏胜利！" << endl;
    return true;
}

bool placeMine(char *board)
{
    displayBoard(board);
    int row = 0, col = 0;
    char input;
    while (true)
    {
        cout << "请输入你想要埋下雷的坐标(行和列): (输入q退出)";
        cin >> input;
        // 检查用户是否想退出
        if (input == 'q' || input == 'Q')
            break;

        row = input - '0';
        cin >> col;
        // 检查坐标是否越界
        if (row > ROW || col > COL || row < 1 || col < 1)
        {
            cout << "请输入边界内的坐标！\n";
            continue;
        }
        if (board[(row - 1) * COL + col - 1] == '#')
        {
            cout << "这个地方已经埋过雷啦！\n";
            continue;
        }

        board[(row - 1) * COL + col - 1] = '#';
        calcBoard(row - 1, col - 1, board);
        displayBoard(board);
    };
    return true;
}

void setDifficult(char *&board, char *&dis_board)
{
    int difficulty;

    cout << "请选择难度等级：\n";
    cout << "1 - 简单\n";
    cout << "2 - 中等\n";
    cout << "3 - 困难\n";

    while(cin >> difficulty && !(difficulty == 1 || difficulty == 2 || difficulty == 3))
        cout << "输入有误，请重新输入。";
    switch (difficulty)
    {
    case 1:
        ROW = COL = 9;
        resetBoard(board, dis_board);
        setBomb(board, Eazy);
        return;
    case 2:
        ROW = COL = 16;
        resetBoard(board, dis_board);
        setBomb(board, Middle);
        return;
    case 3:
        ROW = 16;
        COL = 30;
        resetBoard(board, dis_board);
        setBomb(board, Hard);
        return;
    }
    return;
}

