#include <stdio.h>
#include <stdlib.h>

struct Link {
    int id;
    char *data;
    struct Link *next;
};

static struct Link *head=NULL;
static int uniq_id=0;
static int cnt= 0;

void print_line(const char* str)
{
    printf(str);
    printf("\n");
}

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

int get_id()
{
    uniq_id++;
    return uniq_id;
}

void add_node()
{
    struct Link *curr = head;

    struct Link *node = (struct Link *) malloc(sizeof(struct Link));
    char *data = input("please input data you want to add:");
    
    node->data = data;
    node->next = NULL;
    node->id = get_id();

    if(curr==NULL) {
        head = node;
        cnt=1;
        return;
    }

    while(curr->next) {
        curr = curr->next;
    }
    curr->next = node;
    cnt++;
}

void delete_node()
{
    int id=-1;
    struct Link *curr = head;
    if(cnt==0) {
        print_line("List is empty");        
        return;
    }
    print_line("Please input the id your want to delete:");
    scanf("%d", &id);


    while(curr) 
    {
        if(curr->id == id)  // delete head
        {
            head = curr->next;
            print_line("Delete successful!");
            return;
        }
        if(curr->next && curr->next->id == id) 
        {
            curr->next = curr->next->next;
            print_line("Delete successful!");
            return;
        }
        curr = curr->next;
    }
    print_line("Delete fail!");
    return;
}

void query()
{
    int id=-1;
    struct Link *curr = head;
    if(cnt==0) {
        print_line("List is empty");        
        return;
    }
    print_line("Please input the id your want to query:");
    scanf("%d", &id);
    while(curr) {
        if(curr->id == id) {
            printf("id=%d,data=%s\n",curr->id, curr->data);
            return;
        }
        curr= curr->next;
    }
    print_line("Not found");
}

// void query()
// {
//     int id=-1;
//     struct Link *curr = head;
//     if(cnt==0) {
//         print_line("List is empty");        
//         return;
//     }
//     print_line("Please input the id your want to query:");
//     scanf("%d", &id);
//     while(curr) {
//         if(curr->id == id) {
//             printf("id=%d,data=%s\n",curr->id, curr->data);
//             return;
//         }
//         curr= curr->next;
//     }
//     print_line("Not found");
// }

void insert_before()
{
    int id=-1;
    struct Link *curr = head;
    if(cnt==0) {
        print_line("List is empty");        
        return;
    }
    print_line("Please input the pos your want to insert before:");
    scanf("%d", &id);

    struct Link *node = (struct Link *) malloc(sizeof(struct Link));
    char *data = input("please input data you want to add:");
    
    node->data = data;
    node->next = NULL;
    node->id = get_id();


    while(curr) {
        if(curr->id == id) { //insert before head;
            node->next = head;
            head = node;
            cnt++;
            print_line("Insert successful");
            return;
        }
        if(curr->next && curr->next->id == id) {
            node->next = curr->next;
            curr->next = node;
            cnt++;
            print_line("Insert successful");
            return;
        }
        curr= curr->next;
    }
    print_line("Insert fail");
}

void print_all()
{
    struct Link *curr = head;
    while(curr) {
        printf("id=%d,data=%s\n",curr->id, curr->data);
        curr = curr->next;
    }
}

void swap_node(int first_id, int second_id)
{
    struct Link *first = NULL;
    struct Link *second = NULL;
    struct Link *preFirst = NULL;
    struct Link *postFirst = NULL;
    struct Link *preSecond = NULL;
    struct Link *postSecond = NULL;

    struct Link *curr = head;
    if(cnt < 2) {
        print_line("List length < 2");        
        return;
    }

    if(curr->id==first_id)
    {
        first = head;
        preFirst= NULL;
        postFirst = head->next;
    }

    if(curr->id==second_id)
    {
        second = head;
        preSecond= NULL;
        postSecond = head->next;
    }

    while(curr->next)
    {
        if(curr->next->id == first_id) 
        {
            first = curr->next;
            preFirst = curr;
            postFirst = first->next;
        }
        if(curr->next->id == second_id) 
        {
            second = curr->next;
            preSecond = curr;
            postSecond = second->next;
        }
        if(first != NULL && second != NULL) break;
        curr = curr->next;     
    }

    if(first == NULL || second == NULL)
    {
        print_line("Please input exist id");
        return;
    }

    if(postFirst == second) 
    {
        if(preFirst!=NULL) {
            preFirst->next = second;
        }
        second->next = first;
        first->next = postSecond;
        if(preFirst==NULL) {
            head = second;
        }
    } else if(postSecond == first) {
        if(preSecond!=NULL) {
            preSecond->next = first;
        }
        first->next = second;
        second->next = postFirst;
        if(preSecond==NULL) {
            head = first;
        }
    }
    else {

        if(preFirst==NULL) 
        {
            second->next = postFirst;
            preSecond->next = first;
            first->next = postSecond;
            head = second;
        } 
        else if(preSecond==NULL) 
        {
            first->next = postSecond;
            preFirst->next = second;
            second->next = postFirst;
            head = first;
        } else {
            preFirst->next = second;
            second->next = postFirst;

            preSecond->next = first;
            first->next = postSecond;
        }
    }
}


void swap()
{
    int first_id=-1;
    int second_id=-1;
    
    if(cnt < 2) {
        print_line("List length < 2");        
        return;
    }
    print_line("Please input the id your want to swap:");
    scanf("%d,%d", &first_id,&second_id);

    if(first_id == second_id)
    {
        print_line("Please input different id");
        return;
    }

    swap_node(first_id,second_id);

    print_all();
}


void sort_list()
{
    struct Link *curr=head;
    struct Link *temp=NULL;
    unsigned char hasSwap=0;

    while(curr)
    {
        temp = curr->next;
        if(temp != NULL && temp->id < curr->id) 
        {
            swap_node(curr->id, temp->id);
            hasSwap = 1;
        }
        else 
        {
            curr = temp;
        }
        if(curr==NULL &&hasSwap==1)
        {
            hasSwap = 0;
            curr=head;
        }
    }
    print_all();
}

void uniq_list()
{

}

void update_node()
{
    int id=-1;
    struct Link *curr = head;
    char *inputStr;
    if(cnt==0) {
        print_line("List is empty");        
        return;
    }
    print_line("Please input the id your want to update:");
    scanf("%d", &id);

    inputStr = input("Please input the new Data:");


    while(curr) 
    {
        if(curr->id == id)
        {
            curr->data = inputStr;
            print_line("Update successful!");
            return;
        }
        
        curr = curr->next;
    }
    print_line("Update fail!");
    return;
}


void menu()
{
    int choice;
    print_line("Single Link Test");
    print_line("1. Add");
    print_line("2. Delete");
    print_line("3. Update");
    print_line("4. Query");
    print_line("5. Show All");
    print_line("6. Insert before");
    print_line("7. Swap");
    print_line("8. Sort List");
    printf("Please input your choice: ");

    scanf("%d",&choice);

    switch(choice) 
    {
        case 1:
            add_node();
            break;
        case 2:
            delete_node();
            break;
        case 3:
            update_node();
            break;
        case 4:
            query();
            break;
        case 5:
            print_all();
            break;
        case 6:
            insert_before();
            break;
        case 7:
            swap();
            break;
        case 8:
            sort_list();
            break;
        default:
            break;
    }

}


int main()
{
    while(1)
    {
        menu();
    }
    getchar();
    return 0;
}