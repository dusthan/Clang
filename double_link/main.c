#include <stdio.h>
#include <stdlib.h>
static struct link *head=NULL;
static int node_cnt = 0;
static int uniq_id = 0;

struct link
{
    int id;
    char *data;
    struct link *prev;
    struct link *next;
};

void menu();
void list_add(struct link *node);

char *input(const char *tips)
{
    unsigned int len_max = 128;
    unsigned int current_size = 0;

    char *pStr = (char *)malloc(len_max);
    current_size = len_max;

    printf("\n%s",tips);

    if (pStr != NULL)
    {
        int c = EOF;
        unsigned int i = 0;
        //accept user input until hit enter or end of file
        while ((c = getchar()) != EOF)
        {
            pStr[i++] = (char)c;

            //if i reached maximize size then realloc size
            if (i == current_size)
            {
                current_size = i + len_max;
                pStr = (char *)realloc(pStr, current_size);
            }
        }

        pStr[i] = '\0';
        printf("\n");
    }
    return &pStr[0];
}

void add()
{
    struct link  *node = (struct link *) malloc(sizeof(struct link));
    char * pStr = input("Please input data you want to add:");

    node->data = pStr;
    node->id = uniq_id++;
    node->next=NULL;

    if(node_cnt==0 || head==NULL) 
    {
        head = node;
        head->prev = NULL;
        head->next = NULL;
        node_cnt++;
    } 
    else 
    {
        list_add(node);
        node_cnt++;
    }
}

void list_add(struct link *node)
{
    struct link *temp = head;

    while(temp->next) {
        temp = temp->next;
    }
    temp->next = node;
    node->prev = temp;

}


void update()
{
    int id=-1;
    struct link *temp = head;
    unsigned char found=0;

    if(node_cnt==0) {
        printf("list empty!\n");
        return;
    }

    printf("please input id you want to update:\n");
    scanf("%d",&id);
    getchar();
    char *pStr = input("Please new data:");

    while(temp) {
        if(id == temp->id) {
            temp->data = pStr;
            found=1;
            break;
        }
        temp = temp->next;
    }
    if(found==0) {
        printf("not found!\n");
    }
}
void delete_node (int id)
{
    struct link *curr = head;
    struct link *temp = head;
    unsigned char found=0;
    
    if(node_cnt==0) {
        printf("list empty!\n");
        return;
    }

    while(curr) {
        if(id == curr->id) {
            found=1;
            if(curr->prev == NULL && curr->next == NULL) 
            {
                head = NULL;
                break;
            }
            if(curr == head) 
            {
                curr->next->prev = NULL;
                break;
            }
            if(curr->next==NULL) {
                curr->prev->next = NULL;
                break;
            }

            temp = curr;

            curr->prev->next = temp->next;
            temp->next->prev = temp->prev;

            break;
        }
        curr = curr->next;
    }
    if(node_cnt>0) node_cnt--;
    if(found==0) {
        printf("not found!\n");
    }
}
void query(int id)
{
    struct link *curr = head;
    unsigned char found=0;
    
    if(node_cnt==0) {
        printf("list empty!\n");
        return;
    }

    while(curr) {
        if(id == curr->id) {
            found=1;
            printf("id=%d,data:%s\n",curr->id, curr->data);
            break;
        }
        curr = curr->next;
    }
    if(found==0) {
        printf("not found!\n");
    }
}
void print_all()
{
    struct link *temp = head;

    if(node_cnt==0) {
        printf("list empty!\n");
        return;
    }

    while(temp) {
        printf("id=%d,data:%s\n",temp->id, temp->data);
        temp = temp->next;
    }
}

void count()
{
    printf("count: %d\n",node_cnt);
}

void reverse()
{
    struct link *curr = head;
    struct link *pre=NULL;
    struct link *next = NULL;

    while (curr != NULL)
    {
        next = curr->next;
        curr->next = pre;
        curr->prev = next;
        pre=curr;
        curr = next;
    }
    head = pre;
}

void list_swap(struct link** node1, struct link** node2){
    struct link* prev1 = (*node1)->prev;
    struct link* next1 = (*node1)->next;
    struct link* prev2 = (*node2)->prev;
    struct link* next2 = (*node2)->next;


if((*node1)->next == *node2) {
    prev1->next = next1;
    (*node2)->prev = prev1;
    (*node2)->next = *node1;

    next2->prev = *node1;
    (*node1)->next = next2;
    (*node1)->prev = *node2;
}
else {

    if(prev1) prev1->next = *node2;
    (*node2)->prev = prev1;
    (*node2)->next = next1;
    if(next1) next1->prev = *node2;

    if(prev2) prev2->next = *node1;
    (*node1)->prev = prev2;
    (*node1)->next = next2;
    if(next2) next2->prev = *node1;
}
}


void swap()
{
    struct link *curr = head;
    struct link* node1;
    struct link* node2;
    int id1,id2;
    int found=0;

    printf("please input first node id:\n");
    scanf("%d",&id1);
    getchar();

    printf("please input second node id:\n");
    scanf("%d",&id2);
    getchar();


    while(curr){
        if(id1==curr->id || id2 == curr->id) {
            found++;
            if(found==1) node1 = curr;
            else if(found==2) {
                node2 = curr;
                list_swap(&node1, &node2);
                if(node1==head) head=node2;
                break;
            }
        }
        curr = curr->next;
    }

    if(found<2) {
        printf("cant swap, because not found or only one founded\n");
    }
}

void menu()
{
    int choice = -1;
    int id =-1;

    printf("--------menu---------------\n");
    printf("--------1. add-------------\n");
    printf("--------2. update----------\n");
    printf("--------3. delete----------\n");
    printf("--------4. query-----------\n");
    printf("--------5. reverse---------\n");
    printf("--------6. show all--------\n");
    printf("--------7. count-----------\n");
    printf("--------8. swap------------\n");
    printf("--------9. exit------------\n");
    printf("---plese input your choice:---\n");

    scanf("%d", &choice);

    getchar();

    switch (choice)
    {
    case 1:
        add();
        break;
    case 2:
        update();
        break;
    case 3:
        printf("please input the id you want to delete:\n");
        scanf("%d", &id);
        getchar();
        delete_node(id);
        break;
    case 4:
        printf("please input the id you want to query:\n");
        scanf("%d", &id);
        getchar();
        query(id);
        break;
    case 5:
        reverse();
        break;
    case 6:
        print_all();
        break;
    case 7:
        count();
        break;
    case 8:
        swap();
        break;
    case 9:
        exit(0);
        break;
    default:
        break;
    }
    menu();
}



int main()
{
    menu();
    getchar();
    return 0;
}