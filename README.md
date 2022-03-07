# 자판기 프로그램
카드나 현금으로 음료를 구매하고, 자판기의 누적 금액 확인 및 재고를 관리하는 프로그램

## Environment
Codeblocks 20.3.0.0
GNU GCC Complier

## Description
> 함수 목록
자판기 인터페이스 print_interface
관리 모드 management
재고 추가 add_stock
카드 투입 pay_card
현금 투입 pay_cash
상품 선택 select_goods
현금 계산 calculation

> 진행 과정
1. 인터페이스 출력
2. 결제 수단 선택
2-1. 현금 결제 선택 시 현금 투입
2-2. 카드 결제 선택 시 바로 다음 단계
3. 상품 선택
3-1. 선택한 상품의 재고가 없을 시 상품 다시 선택
3-2. 투입된 현금이 부족할 때 현금 다시 투입 또는 상품 다시 선택
4. 결제 완료
5. 결제된 상품의 수량이 줄어듦
6. 자판기 보유 금액에 결제 금액 누적

> 관리 모드
1. 자판기 보유 금액 출력
2. 재고 추가
0. 관리 모드 종료

> 재고 추가
1 없는 상품 번호를 입력했을 때, 2 재고가 최대치일 때, 3 재고가 줄어있을 때 세 가지로 상황 설정

    if(select==0){
        flag = 1;
    }else if(select<0 || select>8){
        printf("\t 다시 선택하세요 \n");
        flag = 0;
    }else if(goods[select-1].qty==MAX){
        printf("\t %s의 수량은 최대한도입니다\n\n", goods[select-1].name);
    }else{
        goods[select-1].qty = MAX;
        printf("\t %s의 재고를 채웠습니다\n\n", goods[select-1].name);
        }

> 현금 투입
500, 1000, 5000, 10000 단위로 투입 가능, 이에 해당하지 않을 경우 재요청
    scanf("%d", &cash);
    if(cash>10000 || cash%500!=0){
        printf("\t 다시 시도하세요\n>> ");
    }

> 현금 계산
1. 투입된 금액 >= 가격일 경우
- 재고 조정
- 거스름돈이 있을 경우 반환 및 자판기 보유 금액 감소
2. 투입된 금액<가격일 경우 : 결제 실패
- 현금 투입으로 돌아가기 또는 상품 선택으로 돌아가기