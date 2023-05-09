#include <iostream>
#include <ctime>
#include "func.h"

int main()
{
    using namespace std;
restart:
    srand((unsigned int)time(NULL));
    int difficult = 3;
    char *board = new char[ROW * COL];
    char *dis_board = new char[ROW * COL];
    initset(board);
    initset_dis(dis_board);
    // displayBoard(board);
    // displayBoard(dis_board);
start:
    start_menu(); // 开始菜单
    char choice1;
    while (cin >> choice1 && !(choice1 >= '1' && choice1 <= '5'))
        ;
    switch (choice1)
    {
    case '1':
        goto start2;
        break;
    case '2':
        cout << "谢谢游玩！ " << endl;
        exit(0);
    default:
        goto start;
        break;
    }
        goto start;
start2:
    start_menu2();
    char choice2;
    while (cin >> choice2 && !(choice2 >= '1' && choice2 <= '5'))
            ;
    switch (choice2)
        {
        case '1':
            goto DIY;
        case '2':
            goto normal;
        case '3':
            goto start;
        default:
            goto start2;
            break;
        }
        goto start2;
DIY:
        DIY_menu();
        char choice3;
        while (cin >> choice3 && !(choice3 >= '1' && choice3 <= '5'))
            ;
        switch (choice3)
        {
        case '1':
            setboard(board, dis_board);
            displayBoard(board);
            goto DIY;
        case '2':
            placeMine(board);
            goto DIY;
        case '3':
            while (true)
            {
                // system("cls");
                displayBoard(dis_board);
                int x, y;
                cout << "请输入你选择的行和列： ";
                while (!(cin >> x >> y)) {};
                trriger(board, dis_board, x - 1, y - 1);
                displayBoard(board);
                if (board[(x - 1) * COL + y - 1] == '#')
                {
                    cout << "很遗憾，踩雷了:(" << endl;
                    goto end;
                }
                if (checkWin(board, dis_board))
                    goto end;
            }
        case '4':
            goto restart;
        default:
            goto DIY;
            break;
        }
normal:
        normal_menu();
        char choice4;
        while (cin >> choice4 && !(choice4 >= '1' && choice4 <= '5'))
            ;
        switch (choice4)
        {
        case '1':
            difficult = setDifficult(board, dis_board);
            if (difficult == 3)
                setBomb(board, 10);
            if (difficult == 5)
                setBomb(board, 40);
            if (difficult == 7)
                setBomb(board, 99);
            goto normal;
        case '2':
            while (true)
            {
                // system("cls");
                displayBoard(dis_board);
                int x, y;
                cout << "请输入你选择的行和列： ";
                while (!(cin >> x >> y)) {};
                if (x > ROW || y > COL || x < 1 || y < 1)
                {
                    cout << "请输入边界内的坐标！\n";
                    continue;
                }
                else {
                    trriger(board, dis_board, x - 1, y - 1);
                    displayBoard(board);
                    if (board[(x - 1) * COL + y - 1] == '#')
                    {
                        cout << "很遗憾，踩雷了:(" << endl;
                        goto end;
                    }
                    if (checkWin(board, dis_board))
                        goto end;
                }
            }
        case '3':
            goto restart;
        default:
            goto normal;
            break;
        }

   
end:
    delete[] board;
    delete[] dis_board;
    cout << "重新开始？(Y/N)" << endl;
    char end_chr;
    do
    {
        cin.get(end_chr);
    }while (end_chr == '\n');
    if(end_chr == 'Y' || end_chr == 'y')
        goto restart;
    cout << "谢谢游玩！" << endl;
    return 0;
}