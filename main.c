#include <stdio.h>
#include <stdlib.h>
#define MAX 20
#define OPENING_BALANCE 100000

// 구조체 정의
typedef struct VENDING_MACHINE
{
    char name[10];
    int price;
    int qty;

}MACHINE;

// 함수 프로토타입
void print_interface(MACHINE *goods);
void management(MACHINE *goods);
void add_stock(MACHINE *goods);
void pay_card(MACHINE *goods);
void pay_cash(MACHINE *goods);
int select_goods(MACHINE *goods);
int calculation(MACHINE *goods, int cash, int num);

// 자판기에 저장될 금액
int total_cash = OPENING_BALANCE;
int total_card = 0;

// 선택하는 상품의 인덱스
int select = 0;

int main()
{
    // 구조체 멤버 변수 선언
    MACHINE goods[8] = {
        {"물", 500, 1},
        {"옥수수차", 1000, 20},
        {"박카스", 1000, 20},
        {"커피", 1500, 20},
        {"밀크티", 1500, 20},
        {"콜라", 500, 20},
        {"사이다", 500, 20},
        {"이온음료", 1500, 20}
    };

    int flag = 0;
    int menu = 0;

    while(!flag){
        print_interface(goods);

        // 메뉴 선택
        printf(">> ");
        scanf("%d", &menu);

        switch(menu){
            case 0: printf("프로그램 종료");
                    flag=1; break;
            case 10: management(goods); break;  // 관리 모드
            case 1: pay_card(goods);            // 카드 결제
                    getchar(); getchar();
                    system("cls");
                    break;
            case 2: pay_cash(goods);           // 현금 결제
                    getchar(); getchar();
                    system("cls");
                    break;
            default: printf("- 다시 선택하세요 -");
                      getchar(); getchar();
                      system("cls");
                      break;
        }// end of switch
    }// end of while

    return 0;
}

// 인터페이스 함수 정의
void print_interface(MACHINE *goods)
{
    printf("*****************************************\n");
    printf("\t \t 자판기 \t \n");
    printf("*****************************************\n");
    printf("\t 상품 \t \t 가격 \t 재고\n");

    for(int i=0; i<8; i++){
        printf("%2d. %12s \t %d \t %3d \n", i+1, goods[i].name, goods[i].price, goods[i].qty);
    }

    printf("*****************************************\n");
    printf("\t \t 종료 : 0\n");
    printf("\t 자판기 관리 모드 : 10 \n");
    printf("\t 신용카드 결제 : 1 \n");
    printf("\t 현금 결제 : 2 \n");
    printf("*****************************************\n");

    return;
}

// 관리 모드 함수 정의
void management(MACHINE *goods)
{
    int menu = 0;

    printf("\t- 관리 모드 -\n");
    printf("\t 자판기 보유 금액 %d원 \n", total_card+total_cash);
    printf("\t 재고 추가 : 1 \n");
    printf("\t 관리 모드 종료 : 0 \n");
    printf(">> ");
    scanf("%d", &menu);

    switch(menu){
        case 1: add_stock(goods); break; // 재고 추가 함수 호출
        case 0: break;                   // 관리 모드 종료
        }

    system("cls");

    return;
}

// 재고 추가 함수 정의
void add_stock(MACHINE *goods)
{
    int flag = 0;

    while(!flag){
        printf("\t 추가할 상품을 선택하세요 >> ");
        scanf("%d", &select);

        if(select==0){
            flag = 1;
        }else if(select<0 || select>8){         // 없는 상품 번호를 입력했을 경우 재요청
            printf("\t 다시 선택하세요 \n");
            flag = 0;
        }else if(goods[select-1].qty==MAX){     // 재고가 최대치인 경우 충당 불가 안내
            printf("\t %s의 수량은 최대한도입니다\n\n", goods[select-1].name);
        }else{
            goods[select-1].qty = MAX;          // 재고가 줄어있을 경우 충당 후 안내
            printf("\t %s의 재고를 채웠습니다\n\n", goods[select-1].name);
            }
    }// end of while
    return;
}

// 카드 결제 함수 정의
void pay_card(MACHINE *goods)
{
    printf("\t- 신용카드 결제 -\n");
    select_goods(goods);                    // 상품 선택 함수 호출
    total_card += goods[select-1].price;    // 결제된 카드 금액 누적
    goods[select-1].qty-=1;                 // 결제된 상품 수량-1
    printf("\n\t- %s 결제 완료-", goods[select-1].name);

    return;
}

// 현금 투입 함수
void pay_cash(MACHINE *goods)
{
    int cash = 0;
    int flag = 0;

    printf("\t- 현금 결제 -\n");
    printf("\t 500원, 1000원, 5000원, 10000원 \n>> ");

    while(!flag){
        scanf("%d", &cash);
        if(cash>10000 || cash%500!=0){          // 투입 불가능한 금액일 경우 재요청
            printf("\t 다시 시도하세요\n>> ");
        }else{
            printf("\t %d원 투입 완료\n", cash);
            select_goods(goods);                // 상품 선택 함수 호출
            calculation(goods, cash, select-1); // 현금 계산 함수 호출
            flag = 1;
        }
    }

    return;
}

// 상품 선택 함수 정의
int select_goods(MACHINE *goods)
{
    int flag = 0;

    while(!flag){
        printf("\t 상품을 선택하세요 >> ");
        scanf("%d", &select);

        if(select<=0 || select>8){          // 없는 상품 번호를 입력했을 경우 재요청
            flag = 0;
        }else if(goods[select-1].qty!=0){   // 선택한 상품의 재고가 있을 경우 계속
            flag = 1;
        }else{
            printf("\n\t- 해당 상품은 품절되었습니다 -\n\n");
            }
    }//end of while

    return select;
}

// 현금 계산 함수 정의
int calculation(MACHINE *goods, int cash, int num)
{
    int flag = 0;
    int change = 0;
    int menu = 0;

    while(!flag){
        // 금액이 부족할 경우
        if(goods[num].price>cash){
            printf("\n\t- 금액 부족으로 결제 실패 -\n");
            printf("\t 현금 다시 투입하기 : 0\n");
            printf("\t 상품 다시 선택하기 : 1\n>> ");
            scanf("%d", &menu);

            // 뒤로가기 선택
            switch(menu){
                // 현금을 다시 투입하는 경우
                case 0: getchar(); getchar();
                        system("cls");
                        print_interface(goods);              // 화면 초기화 후 인터페이스 재표시
                        pay_cash(goods);                     // 현금 투입 함수(내부에 현금 계산 함수 포함) 호출
                        flag = 1; break;

                // 상품을 다시 선택하는 경우
                case 1: getchar(); getchar();
                        system("cls");
                        print_interface(goods);              // 화면 초기화 후 인터페이스 재표시
                        printf("\t %d원 투입\n", cash);      // 투입된 현금 표시
                        select_goods(goods);                 // 상품 선택 함수 호출
                        calculation(goods, cash, select-1);  // 현금 계산 함수 호출
                        flag = 1;
                        break;
            }//end of switch

        // 금액이 알맞을 경우
        }else{
            printf("\n\t- %s 결제 완료-\n", goods[num].name);
            total_cash += cash;     // 결제된 현금 누적
            goods[select-1].qty-=1; // 결제된 상품 수량-1
            flag = 1;
        }
    }// end of while

    // 거스름돈 계산
    change = cash-goods[num].price;

    if(change>0){
        printf("\t 거스름돈은 %d입니다\n", change);
        total_cash -= change;   // 자판기 보유 금액-거스름돈
    }

    return 0;
}
