#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student
{
    int     id;
    char    name[20];
    int     kor, math, eng, com;
} student;

typedef struct Dnode
{
    struct Dnode    *llink;
    student         data;
    struct Dnode    *rlink;
} Dnode;

void init(Dnode *head)
{
    if (head == NULL)
        return; //null guard
    head->llink = head;
    head->rlink = head;
}

void dinsert_node(Dnode *before, Dnode *new_node)
{
    if (before == NULL || new_node == NULL)
        return;//guard
    new_node->rlink = before->rlink;
    new_node->llink = before;
    before->rlink->llink = new_node;
    before->rlink = new_node;
}

void search(Dnode* head, student data) 
{
    if (head == NULL)
        return;//guard
    Dnode* p;
    for (p = head->rlink; p != head; p = p->rlink) 
    {
        if (p->data.id == data.id) 
        {
            printf("%6d %10s %6d %6d %6d %6d\n",p->data.id, p->data.name, p->data.kor, p->data.math, p->data.eng, p->data.com);
            return;
        }
    }
    printf("%d번 학생의 번호 검색 실패\n\n", data.id);
}

void sort_dinsert(Dnode* head)
{
    if (head == NULL)
        return; //gurad
    Dnode* p, * q;
    student tmp;
    for (p = head->rlink; p->rlink != head;p = p->rlink) 
    {
        for (q = p->rlink; q != head; q = q->rlink) 
        {
            if (q->data.id < p->data.id)
            {
                tmp = p->data;
                p->data = q->data;
                q->data = tmp;
            }
        }
    }
}

void display(Dnode* phead)
{
    if (phead == NULL)
        return; //gurad
    printf("=====================================================\n");
    printf("| 번호 |   이름   | 언어 | 수리 | 영어 | 컴퓨터 |\n");
    printf("=====================================================\n");
    for (Dnode* p = phead->rlink; p != phead; p = p->rlink) 
        printf("|%3d  | %9s | %4d | %4d | %4d |  %4d |\n",p->data.id, p->data.name, p->data.kor, p->data.math, p->data.eng, p->data.com);
    printf("=====================================================\n");
}

void free_node(Dnode* phead)
{
    if (phead == NULL)
        return;
    Dnode* p = phead->rlink;
    Dnode* next;
    while (p != phead)
    {
        next = p;
        free(p);
        p = p->rlink;
    }
    free(p); // head free
}

void del_Dnode(Dnode *phead, char* studentname)
{
    if (phead == NULL)
        return;//guard
    for (Dnode* p = phead->rlink; p != phead; p = p->rlink) 
    {
        if (!strcmp(p->data.name, studentname)) 
        {
            p->llink->rlink = p->rlink;
            p->rlink->llink = p->llink;
            free(p);
            printf("%s 삭제완료!\n\n", studentname);
            return;
        }
    }
    printf("%s라는 학생은 존재하지 않습니다\n\n", studentname);
}

int main(void)
{
    FILE*   fp;
    Dnode*  head = malloc(sizeof(Dnode));
    Dnode*  tmp;
    student student_tmp;
    int     flag;

    init(head);

    fp= fopen("data.txt", "rt");

    if (fp == NULL)
    {
        printf("File not found\n");
        return 0;
    }

    while (!feof(fp))
    {
        fscanf(fp, "%d %s %d %d %d %d",&student_tmp.id, student_tmp.name, &student_tmp.kor, &student_tmp.math, &student_tmp.eng, &student_tmp.com);
        printf("%6d %10s %6d %6d %6d %6d\n",student_tmp.id, student_tmp.name, student_tmp.kor, student_tmp.math, student_tmp.eng, student_tmp.com);
        tmp = (Dnode*)malloc(sizeof(Dnode));
        tmp->data = student_tmp;
        dinsert_node(head, tmp);
    }

    while (1)
    {
        printf("\n종료(0) 학생 데이터 입력(1) 학생 검색(2) 목록 보기(3) 삭제(4)\n");
        printf("메뉴 입력 : ");
        scanf("%d", &flag);
        if (flag==0)
            break;
        else if (flag==1)
        {
            tmp= (Dnode*)malloc(sizeof(Dnode));
            printf("추가할 학생 번호 : ");
            scanf("%d", &student_tmp.id);
            printf("이름 : ");
            scanf("%s", student_tmp.name);
            printf("국어 : ");
            scanf("%d", &student_tmp.kor);
            printf("수학 : ");
            scanf("%d", &student_tmp.math);
            printf("영어 : ");
            scanf("%d", &student_tmp.eng);
            printf("컴퓨터 : ");
            scanf("%d", &student_tmp.com);
            tmp->data = student_tmp;
            dinsert_node(head, tmp);
        }
        else if (flag==2)
        {
            printf("검색할 학생 번호: ");
            scanf("%d", &student_tmp.id);
            search(head, student_tmp); 
        }
        else if (flag==3)
        {
            printf("\n<정렬된 목록 보기>\n\n");
            sort_dinsert(head);
            display(head);
        }
        else if (flag==4)
        {
            char studentname[20];
            printf("삭제할 학생 이름 : ");
            scanf("%s", studentname);
            del_Dnode(head, studentname);
        }
        else
            printf("잘못된 입력입니다\n");
    }
    free_node(head);
    fclose(fp);
    return (0);
}