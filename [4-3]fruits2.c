
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// �Ʒ� ����ü ���Ǵ� �ܺ� ������ �Ȱ��� ��� �Լ����� ����� �� �ִ�
// ����ü �����̴�.
struct Node // ���� ������ �����ϴ� ��带 �����ϴ� ����ü ����
{
   char name[20]; // ���� �̸� ���� �ʵ�
   int price; // ���� ���� ���� �ʵ�
   struct Node *next; // �ڱ� ���� ������
};

struct Node head; // �� ����Ʈ ����
int count = 0; // ���� ����Ʈ�� ������ ���� ���� ����, �ʱ⿡�� 0�̴�.

struct Node *getnode() // ���ο� ��� ������ �����Ҵ����� Ȯ���� �ִ� �Լ�
{                      // �������� �Ҵ��� ����� ���� �ּҸ� ��ȯ�� �ش�.
   struct Node *p;
   p = (struct Node*)malloc(sizeof(struct Node));
   return(p);
}

void retnode(struct Node* ptr)
{
   free(ptr); // ���� �Ҵ� ��ȯ
}

void addnode(char f[], int p) // ����Ʈ�� ���� ���� �Լ�
{
   int i;
   struct Node *ptr; // ���� �Ҵ���� ���� ��� �ּҸ� ������ ����ü ������
   struct Node *current, *previous; // �۾��� ������
   current = head.next;
   previous = &head;

   for(i = 0; i < count; i++) // ���� ����� ���� ��ġ�� ã�´�.
   {
      if(strcmp(f, current->name) > 0) // ���� current ��ġ���� �� �ڿ� �����ؾ� �Ѵ�.
      {
         previous = current; // previous�� ���� ������ ���� ���� �ʿ�.
         current = current->next;
         continue;
      }
      else
         break; // ���� current ��ġ�� ���� ��ġ�̴�.
   }

   // ���ο� ��带 �����ϴ� �۾�
   ptr = getnode(); // ���ο� ��� �Ҵ� �ް�,
   strcpy(ptr->name, f); // ���� �̸� ����,
   ptr->price = p; // ���� ���� ����,
   ptr->next = previous->next;
   previous->next = ptr; // ���ο� ��带 �����ϴ� �۾�
   count = count + 1;
}

void delnode(char f[]) // ����Ʈ���� ���� ���� �Լ�
{
   int i;
   struct Node *current, *previous; // �۾��� ������
   current = head.next;
   previous = &head;

   for(i = 0; i < count; i++) // ������ ���� ��ġ ã��
   {
      if(strcmp(f, current->name) == 0) // ���� ��ġ ã�� ���,
         break;
      else
      {
        previous = current; // previous�� ���� ������ ���� ���� �ʿ�.
        current = current->next;
        continue;
      }
   }

   if(current == NULL)
      printf("\n������ ������ ��ϵǾ� ���� �ʽ��ϴ�.\n");
   else
   {
      // ã�� ��带 �����ϴ� �۾�
      previous->next = current->next;
      retnode(current);
   }
   count = count - 1;
}

void prn() // ���� ��ϵǾ� �ִ� ���� ��ü ����ϱ�
{
   int i;
   struct Node *current = head.next;
   if(count == 0)
   {
      printf("\n----- ���� ��ϵ� ������ �����ϴ�. -----\n\n");
      return;
   }
   printf("\n----- ���� ��ϵ� ������ �Ʒ��� �����ϴ�. -----\n\n");
   for(i = 0; i < count; i++)
   {
      printf("%2d��° ���� : %10s - ���� %4d\n\n", i+1, current->name, current->price);
      current = current->next;
   }
   printf("-----------------------------------------------\n\n");
}

void main()
{
   int choice;
   char name[20]; // ������ ���� �̸� �Է¹޴� �뵵
   int p; // ������ ���� ���� �Է¹޴� �뵵
   int i;

   head.next = NULL; // ���� �� ����Ʈ�� ����
   printf("����� ��ϵ� ������ �����ϴ�.\n");

   do
   {
      choice=0;
      printf("���ϴ� �۾� ���� : 1-����, 2-����, 3-����Ʈ ���� ���, 4-���α׷� ������ : ");
      scanf("%d", &choice);
      switch(choice)
      {
      case 1 :
         printf("\n������ ���� �̸��� �Է��ϼ��� : ");
         scanf("%s", name);
         printf("������ ������ ������ �Է��ϼ��� : ");
         scanf("%d", &p);
         getchar();
         addnode(name, p); // ���� �Լ� ȣ��
         prn(); // ���� ����Ʈ ���� ��ü ����ϱ�
         break;
      case 2:
         printf("������ ���� �̸��� �Է��ϼ��� : ");
         scanf("%s", name);
         delnode(name);
         prn(); // ���� ����Ʈ ���� ��ü ����ϱ�
         break;
      case 3:
         prn(); // ���� ����Ʈ ���� ��ü ����ϱ�
         break;
      case 4:
      default:
            printf("���α׷��� �������ϴ�.\n");
            exit(0);
      }
   } while(1); // ���� �ݺ�
}
