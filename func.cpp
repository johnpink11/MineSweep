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
    cout << "\t      ɨ����Ϸ\n";
    cout << "\
***********************************\n\
*          1.�Զ���ģʽ           *\n\
*          2.��ͨģʽ             *\n\
*          3.������Ϸ             *\n\
***********************************\n\
";
    cout << "���������ѡ��";
}

void DIY_menu()
{
    using namespace std;
    cout << "\t      ɨ����Ϸ\n";
    cout << "\
***********************************\n\
*          1.��������������       *\n\
*          2.����                 *\n\
*          3.��ʼ��Ϸ             *\n\
*          4.����ѡ��             *\n\
***********************************\n\
";
    cout << "���������ѡ��";
}

void normal_menu()
{
    using namespace std;
    cout << "\t      ɨ����Ϸ\n";
    cout << "\
***********************************\n\
*          1.�Ѷ�����             *\n\
*          2.��ʼ��Ϸ             *\n\
*          3.����ѡ��             *\n\
***********************************\n\
";
    cout << "���������ѡ��";
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

void trriger(char *board, char *dis_board, int row, int col) // ��������������-1
{
    if (dis_board[row * COL + col] != ' ' && !(dis_board[row * COL + col] >= '1' && dis_board[row * COL + col] <= '8')) // ������ǿո������
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
        if (col) // ���ǵ�һ��
        {
            trriger(board, dis_board, row, col - 1);
            if (row) // �������Ͻ�
                trriger(board, dis_board, row - 1, col - 1);
        }
        if (row) // ���ǵ�һ��
        {
            trriger(board, dis_board, row - 1, col);
            if (COL - col - 1) // �������Ͻ�
                trriger(board, dis_board, row - 1, col + 1);
        }
        if (COL - col - 1) // �������һ��
        {
            trriger(board, dis_board, row, col + 1);
            if (ROW - row - 1) // �������½�
                trriger(board, dis_board, row + 1, col + 1);
        }
        if (ROW - row - 1) // �������һ��
        {
            trriger(board, dis_board, row + 1, col);
            if (col)//�������½�
                trriger(board, dis_board, row + 1, col - 1);
        }
    }
    return;
}

void setboard(char *&board, char *&dis_board)
{
    cout << "���������̵������������� ";
    while (cin >> ROW >> COL && (ROW < 1 || ROW > 99 || COL < 1 || COL > 99))
        cout << "������������,������1~99֮������֡�\n";
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
    cout << "��ϲ�㣬��Ϸʤ����" << endl;
    return true;
}

bool placeMine(char *board)
{
    displayBoard(board);
    int row = 0, col = 0;
    char input;
    while (true)
    {
        cout << "����������Ҫ�����׵�����(�к���): (����q�˳�)";
        cin >> input;
        // ����û��Ƿ����˳�
        if (input == 'q' || input == 'Q')
            break;

        row = input - '0';
        cin >> col;
        // ��������Ƿ�Խ��
        if (row > ROW || col > COL || row < 1 || col < 1)
        {
            cout << "������߽��ڵ����꣡\n";
            continue;
        }
        if (board[(row - 1) * COL + col - 1] == '#')
        {
            cout << "����ط��Ѿ����������\n";
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

    cout << "��ѡ���Ѷȵȼ���\n";
    cout << "1 - ��\n";
    cout << "2 - �е�\n";
    cout << "3 - ����\n";

    while(cin >> difficulty && !(difficulty == 1 || difficulty == 2 || difficulty == 3))
        cout << "�����������������롣";
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

