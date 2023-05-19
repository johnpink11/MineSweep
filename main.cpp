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
        start_menu(); // ��ʼ�˵�
        char choice;
        while (cin >> choice && !(choice >= '1' && choice <= '3')) // ����ģʽѡ��
            cout << "�����������������롣" << endl;
        if (choice == '1') // �����Զ���ģʽ
        {
            Choice0:
            DIY_menu();
            char choice;
            while (cin >> choice && !(choice >= '1' && choice <= '4'))
                cout << "�����������������롣" << endl;
            if (choice == '1') // ��������
            {
                setboard(board, dis_board);
                goto Choice0;
            }
            else if (choice == '2') // ����
            {
                resetBoard(board, dis_board);
                placeMine(board);
                goto Choice0;
            }
            // else if (choice == '3') // ��ʼ��Ϸ
            //     break;
            else if (choice == '4') // ����ѡ�� ע��������������
            {
                delete[] board;
                delete[] dis_board;
                continue;
            }
        }
        else if (choice == '2') // ������ͨģʽ
        {
            Choice1:
            normal_menu();
            char choice;
            while (cin >> choice && !(choice >= '1' && choice <= '3'))
                cout << "�����������������롣" << endl;
            if (choice == '1') // �����Ѷ�
            {
                setDifficult(board, dis_board);
                goto Choice1;
            }
            // else if (choice == '2') // ��ʼ��Ϸ
            //     break;
            else if (choice == '3') // ����ѡ�� ע��������������
            {
                delete[] board;
                delete[] dis_board;
                continue;
            }
        }
        else if (choice == '3')
        {
            cout << "лл���棡" << endl;
            exit(0);
        }
    // �����ǿ�ʼ��Ϸ�Ĵ���
    while(true)
    {
        displayBoard(dis_board);
        int row, col;
        cout << "��������ѡ����������У� ";
        cin >> row >> col;
        if(row < 1 || row > ROW || col < 1 || col > COL)
        {
            cout << "���������������������룡";
            cout << "��������ѡ����������У� \n";
            continue;
        }
        char elem = board[(row - 1) * COL + col - 1];
        if(elem ==  '#')
        {
            cout << "������:(" << endl;
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
    cout << "���¿�ʼ��(Y/N)";
    char if_restart;
    cin >> if_restart;
    if(if_restart == 'Y'|| if_restart == 'y')
        continue;
    else
    {
        cout << "лл���棡" << endl;
        break;
    }
    }
    return 0;
}