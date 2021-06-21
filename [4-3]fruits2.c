
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 아래 구조체 정의는 외부 변수와 똑같이 모든 함수에서 사용할 수 있는
// 구조체 정의이다.
struct Node // 과일 정보를 보관하는 노드를 정의하는 구조체 정의
{
   char name[20]; // 과일 이름 보관 필드
   int price; // 과일 가격 보관 필드
   struct Node *next; // 자기 참조 포인터
};

struct Node head; // 빈 리스트 정의
int count = 0; // 현재 리스트에 보관된 과일 정보 개수, 초기에는 0이다.

struct Node *getnode() // 새로운 노드 공간을 동작할당으로 확보해 주는 함수
{                      // 동적으로 할당한 노드의 시작 주소를 반환해 준다.
   struct Node *p;
   p = (struct Node*)malloc(sizeof(struct Node));
   return(p);
}

void retnode(struct Node* ptr)
{
   free(ptr); // 동적 할당 반환
}

void addnode(char f[], int p) // 리스트에 과일 삽입 함수
{
   int i;
   struct Node *ptr; // 새로 할당받을 동적 노드 주소를 보관할 구조체 포인터
   struct Node *current, *previous; // 작업용 포인터
   current = head.next;
   previous = &head;

   for(i = 0; i < count; i++) // 새로 등록할 과일 위치를 찾는다.
   {
      if(strcmp(f, current->name) > 0) // 현재 current 위치보다 더 뒤에 삽입해야 한다.
      {
         previous = current; // previous는 나중 삽입을 위해 보관 필요.
         current = current->next;
         continue;
      }
      else
         break; // 현재 current 위치가 삽입 위치이다.
   }

   // 새로운 노드를 연결하는 작업
   ptr = getnode(); // 새로운 노드 할당 받고,
   strcpy(ptr->name, f); // 과일 이름 보관,
   ptr->price = p; // 과일 가격 보관,
   ptr->next = previous->next;
   previous->next = ptr; // 새로운 노드를 연결하는 작업
   count = count + 1;
}

void delnode(char f[]) // 리스트에서 과일 삭제 함수
{
   int i;
   struct Node *current, *previous; // 작업용 포인터
   current = head.next;
   previous = &head;

   for(i = 0; i < count; i++) // 삭제할 과일 위치 찾기
   {
      if(strcmp(f, current->name) == 0) // 과일 위치 찾은 경우,
         break;
      else
      {
        previous = current; // previous는 나중 삽입을 위해 보관 필요.
        current = current->next;
        continue;
      }
   }

   if(current == NULL)
      printf("\n삭제할 과일이 등록되어 있지 않습니다.\n");
   else
   {
      // 찾은 노드를 삭제하는 작업
      previous->next = current->next;
      retnode(current);
   }
   count = count - 1;
}

void prn() // 현재 등록되어 있는 과일 전체 출력하기
{
   int i;
   struct Node *current = head.next;
   if(count == 0)
   {
      printf("\n----- 현재 등록된 과일이 없습니다. -----\n\n");
      return;
   }
   printf("\n----- 현재 등록된 과일은 아래와 같습니다. -----\n\n");
   for(i = 0; i < count; i++)
   {
      printf("%2d번째 과일 : %10s - 가격 %4d\n\n", i+1, current->name, current->price);
      current = current->next;
   }
   printf("-----------------------------------------------\n\n");
}

void main()
{
   int choice;
   char name[20]; // 삽일할 과일 이름 입력받는 용도
   int p; // 삽입할 과일 가격 입력받는 용도
   int i;

   head.next = NULL; // 최초 빈 리스트를 만듬
   printf("현재는 등록된 과일이 없습니다.\n");

   do
   {
      choice=0;
      printf("원하는 작업 선택 : 1-삽입, 2-삭제, 3-리스트 내용 출력, 4-프로그램 끝내기 : ");
      scanf("%d", &choice);
      switch(choice)
      {
      case 1 :
         printf("\n삽입할 과일 이름을 입력하세요 : ");
         scanf("%s", name);
         printf("삽입할 과일의 가격을 입력하세요 : ");
         scanf("%d", &p);
         getchar();
         addnode(name, p); // 삽입 함수 호출
         prn(); // 현재 리스트 내용 전체 출력하기
         break;
      case 2:
         printf("삭제할 과일 이름을 입력하세요 : ");
         scanf("%s", name);
         delnode(name);
         prn(); // 현재 리스트 내용 전체 출력하기
         break;
      case 3:
         prn(); // 현재 리스트 내용 전체 출력하기
         break;
      case 4:
      default:
            printf("프로그램이 끝났습니다.\n");
            exit(0);
      }
   } while(1); // 무한 반복
}
