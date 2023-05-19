// main.cpp -- main flame of game
// vesion 3.0
#include <iostream>
#include <ctime>
#include "func.h"

int main()
{
    using namespace std;
    srand((unsigned int)time(NULL));
    while (true)
    {
        char *board = new char[ROW * COL];
        char *dis_board = new char[ROW * COL];
        initset(board);
        initset_dis(dis_board);
        setBomb(board, Eazy);
        start_menu(); // 开始菜单
        char choice;
        while (cin >> choice && !(choice >= '1' && choice <= '3')) // 进行模式选择
            cout << "输入有误，请重新输入。" << endl;
        if (choice == '1') // 进入自定义模式
        {
            Choice0:
            DIY_menu();
            char choice;
            while (cin >> choice && !(choice >= '1' && choice <= '4'))
                cout << "输入有误，请重新输入。" << endl;
            if (choice == '1') // 设置棋盘
            {
                setboard(board, dis_board);
                goto Choice0;
            }
            else if (choice == '2') // 埋雷
            {
                resetBoard(board, dis_board);
                placeMine(board);
                goto Choice0;
            }
            // else if (choice == '3') // 开始游戏
            //     break;
            else if (choice == '4') // 重新选择 注意重置棋盘数据
            {
                delete[] board;
                delete[] dis_board;
                continue;
            }
        }
        else if (choice == '2') // 进入普通模式
        {
            Choice1:
            normal_menu();
            char choice;
            while (cin >> choice && !(choice >= '1' && choice <= '3'))
                cout << "输入有误，请重新输入。" << endl;
            if (choice == '1') // 设置难度
            {
                setDifficult(board, dis_board);
                goto Choice1;
            }
            // else if (choice == '2') // 开始游戏
            //     break;
            else if (choice == '3') // 重新选择 注意重置棋盘数据
            {
                delete[] board;
                delete[] dis_board;
                continue;
            }
        }
        else if (choice == '3')
        {
            cout << "谢谢游玩！" << endl;
            exit(0);
        }
    // 以下是开始游戏的代码
    while(true)
    {
        displayBoard(dis_board);
        int row, col;
        cout << "请输入你选择的坐标行列： ";
        cin >> row >> col;
        if(row < 1 || row > ROW || col < 1 || col > COL)
        {
            cout << "输入坐标有误，请重新输入！";
            cout << "请输入你选择的坐标行列： \n";
            continue;
        }
        char elem = board[(row - 1) * COL + col - 1];
        if(elem ==  '#')
        {
            cout << "踩雷了:(" << endl;
            break;
        }
        else
        {
            trriger(board, dis_board, row - 1, col - 1);
            if(checkWin(board, dis_board))
            {
                break;
            }
            continue;
        }
    }
    cout << "重新开始？(Y/N)";
    char if_restart;
    cin >> if_restart;
    if(if_restart == 'Y'|| if_restart == 'y')
        continue;
    else
    {
        cout << "谢谢游玩！" << endl;
        break;
    }
    }
    return 0;
}