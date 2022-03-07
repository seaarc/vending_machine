#include <stdio.h>
#include <stdlib.h>
#define MAX 20
#define OPENING_BALANCE 100000

// ����ü ����
typedef struct VENDING_MACHINE
{
    char name[10];
    int price;
    int qty;

}MACHINE;

// �Լ� ������Ÿ��
void print_interface(MACHINE *goods);
void management(MACHINE *goods);
void add_stock(MACHINE *goods);
void pay_card(MACHINE *goods);
void pay_cash(MACHINE *goods);
int select_goods(MACHINE *goods);
int calculation(MACHINE *goods, int cash, int num);

// ���Ǳ⿡ ����� �ݾ�
int total_cash = OPENING_BALANCE;
int total_card = 0;

// �����ϴ� ��ǰ�� �ε���
int select = 0;

int main()
{
    // ����ü ��� ���� ����
    MACHINE goods[8] = {
        {"��", 500, 1},
        {"��������", 1000, 20},
        {"��ī��", 1000, 20},
        {"Ŀ��", 1500, 20},
        {"��ũƼ", 1500, 20},
        {"�ݶ�", 500, 20},
        {"���̴�", 500, 20},
        {"�̿�����", 1500, 20}
    };

    int flag = 0;
    int menu = 0;

    while(!flag){
        print_interface(goods);

        // �޴� ����
        printf(">> ");
        scanf("%d", &menu);

        switch(menu){
            case 0: printf("���α׷� ����");
                    flag=1; break;
            case 10: management(goods); break;  // ���� ���
            case 1: pay_card(goods);            // ī�� ����
                    getchar(); getchar();
                    system("cls");
                    break;
            case 2: pay_cash(goods);           // ���� ����
                    getchar(); getchar();
                    system("cls");
                    break;
            default: printf("- �ٽ� �����ϼ��� -");
                      getchar(); getchar();
                      system("cls");
                      break;
        }// end of switch
    }// end of while

    return 0;
}

// �������̽� �Լ� ����
void print_interface(MACHINE *goods)
{
    printf("*****************************************\n");
    printf("\t \t ���Ǳ� \t \n");
    printf("*****************************************\n");
    printf("\t ��ǰ \t \t ���� \t ���\n");

    for(int i=0; i<8; i++){
        printf("%2d. %12s \t %d \t %3d \n", i+1, goods[i].name, goods[i].price, goods[i].qty);
    }

    printf("*****************************************\n");
    printf("\t \t ���� : 0\n");
    printf("\t ���Ǳ� ���� ��� : 10 \n");
    printf("\t �ſ�ī�� ���� : 1 \n");
    printf("\t ���� ���� : 2 \n");
    printf("*****************************************\n");

    return;
}

// ���� ��� �Լ� ����
void management(MACHINE *goods)
{
    int menu = 0;

    printf("\t- ���� ��� -\n");
    printf("\t ���Ǳ� ���� �ݾ� %d�� \n", total_card+total_cash);
    printf("\t ��� �߰� : 1 \n");
    printf("\t ���� ��� ���� : 0 \n");
    printf(">> ");
    scanf("%d", &menu);

    switch(menu){
        case 1: add_stock(goods); break; // ��� �߰� �Լ� ȣ��
        case 0: break;                   // ���� ��� ����
        }

    system("cls");

    return;
}

// ��� �߰� �Լ� ����
void add_stock(MACHINE *goods)
{
    int flag = 0;

    while(!flag){
        printf("\t �߰��� ��ǰ�� �����ϼ��� >> ");
        scanf("%d", &select);

        if(select==0){
            flag = 1;
        }else if(select<0 || select>8){         // ���� ��ǰ ��ȣ�� �Է����� ��� ���û
            printf("\t �ٽ� �����ϼ��� \n");
            flag = 0;
        }else if(goods[select-1].qty==MAX){     // ��� �ִ�ġ�� ��� ��� �Ұ� �ȳ�
            printf("\t %s�� ������ �ִ��ѵ��Դϴ�\n\n", goods[select-1].name);
        }else{
            goods[select-1].qty = MAX;          // ��� �پ����� ��� ��� �� �ȳ�
            printf("\t %s�� ��� ä�����ϴ�\n\n", goods[select-1].name);
            }
    }// end of while
    return;
}

// ī�� ���� �Լ� ����
void pay_card(MACHINE *goods)
{
    printf("\t- �ſ�ī�� ���� -\n");
    select_goods(goods);                    // ��ǰ ���� �Լ� ȣ��
    total_card += goods[select-1].price;    // ������ ī�� �ݾ� ����
    goods[select-1].qty-=1;                 // ������ ��ǰ ����-1
    printf("\n\t- %s ���� �Ϸ�-", goods[select-1].name);

    return;
}

// ���� ���� �Լ�
void pay_cash(MACHINE *goods)
{
    int cash = 0;
    int flag = 0;

    printf("\t- ���� ���� -\n");
    printf("\t 500��, 1000��, 5000��, 10000�� \n>> ");

    while(!flag){
        scanf("%d", &cash);
        if(cash>10000 || cash%500!=0){          // ���� �Ұ����� �ݾ��� ��� ���û
            printf("\t �ٽ� �õ��ϼ���\n>> ");
        }else{
            printf("\t %d�� ���� �Ϸ�\n", cash);
            select_goods(goods);                // ��ǰ ���� �Լ� ȣ��
            calculation(goods, cash, select-1); // ���� ��� �Լ� ȣ��
            flag = 1;
        }
    }

    return;
}

// ��ǰ ���� �Լ� ����
int select_goods(MACHINE *goods)
{
    int flag = 0;

    while(!flag){
        printf("\t ��ǰ�� �����ϼ��� >> ");
        scanf("%d", &select);

        if(select<=0 || select>8){          // ���� ��ǰ ��ȣ�� �Է����� ��� ���û
            flag = 0;
        }else if(goods[select-1].qty!=0){   // ������ ��ǰ�� ��� ���� ��� ���
            flag = 1;
        }else{
            printf("\n\t- �ش� ��ǰ�� ǰ���Ǿ����ϴ� -\n\n");
            }
    }//end of while

    return select;
}

// ���� ��� �Լ� ����
int calculation(MACHINE *goods, int cash, int num)
{
    int flag = 0;
    int change = 0;
    int menu = 0;

    while(!flag){
        // �ݾ��� ������ ���
        if(goods[num].price>cash){
            printf("\n\t- �ݾ� �������� ���� ���� -\n");
            printf("\t ���� �ٽ� �����ϱ� : 0\n");
            printf("\t ��ǰ �ٽ� �����ϱ� : 1\n>> ");
            scanf("%d", &menu);

            // �ڷΰ��� ����
            switch(menu){
                // ������ �ٽ� �����ϴ� ���
                case 0: getchar(); getchar();
                        system("cls");
                        print_interface(goods);              // ȭ�� �ʱ�ȭ �� �������̽� ��ǥ��
                        pay_cash(goods);                     // ���� ���� �Լ�(���ο� ���� ��� �Լ� ����) ȣ��
                        flag = 1; break;

                // ��ǰ�� �ٽ� �����ϴ� ���
                case 1: getchar(); getchar();
                        system("cls");
                        print_interface(goods);              // ȭ�� �ʱ�ȭ �� �������̽� ��ǥ��
                        printf("\t %d�� ����\n", cash);      // ���Ե� ���� ǥ��
                        select_goods(goods);                 // ��ǰ ���� �Լ� ȣ��
                        calculation(goods, cash, select-1);  // ���� ��� �Լ� ȣ��
                        flag = 1;
                        break;
            }//end of switch

        // �ݾ��� �˸��� ���
        }else{
            printf("\n\t- %s ���� �Ϸ�-\n", goods[num].name);
            total_cash += cash;     // ������ ���� ����
            goods[select-1].qty-=1; // ������ ��ǰ ����-1
            flag = 1;
        }
    }// end of while

    // �Ž����� ���
    change = cash-goods[num].price;

    if(change>0){
        printf("\t �Ž������� %d�Դϴ�\n", change);
        total_cash -= change;   // ���Ǳ� ���� �ݾ�-�Ž�����
    }

    return 0;
}
