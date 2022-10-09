#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#define MAX 1000
#define MAX_NAME 20
#define MAX_PHONE 12
#define MAX_REL 30
 
//枚举：选择功能
enum Choose
{
    EXIT,  //0
    ADD,   //1
    DEL,   //2
    SEARCH,//3
    REVISE,//4
    SHOW,  //5
};
 
//结构体：通讯录中每个成员的信息
typedef struct str
{
    char name[MAX_NAME];
    char phone[MAX_PHONE];
    char rel[MAX_REL];
}str;
 
////////////////////////////////////////////////////////////////////////////////////
struct Contact
{
    struct str data[MAX];
    int size;//结合size和结构体 
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////// 

void menu()//表头 
{
	printf("\t\t*********************************************\n");
	printf("\t\t*****************通讯录**********************\n");
	printf("\t\t*********************************************\n");
	printf("\t\t**               0.退出                    **\n");
	printf("\t\t**               1.增加联系人              **\n");
	printf("\t\t**               2.删除联系人              **\n");
	printf("\t\t**               3.查询联系人              **\n");
	printf("\t\t**               4.修改联系人              **\n");
	printf("\t\t**               5.显示所有联系人************\n");
	printf("\t\t*********************************************\n");
	printf("\t\t*********************************************\n");
	printf("\t\t*********************************************\n");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////// 

//增加一个信息到通讯录
void Add(struct Contact *ps)
{
    if(ps->size == MAX)
    {
        printf("通讯录已满，无法增加\n");
    }
    else
    {
        printf("请输入名字:");
        scanf("%s", ps->data[ps->size].name);
        printf("请输入电话:");
        scanf("%s", ps->data[ps->size].phone);
        printf("请输入关系:");
        scanf("%s", ps->data[ps->size].rel);
 
        ps->size++;
        printf("添加成功\n");
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////// 

static int FindByName(const struct Contact *ps, char name[MAX_NAME])
{
    int i = 0;
    for(i = 0; i < ps->size; i++)
    {
        if(0 == strcmp(ps->data[i].name, name))
        {
            return i;
        }
    }
    return -1;//找不到的情况
}
//////////////////////////////////////////////////////////////////////////////////////////////////////


//删除指定的联系人
void Del(struct Contact *ps)
{
    char name[MAX_NAME];
    printf("请输入要删除人的名字:>");
    scanf("%s", name);
    
    int pos = FindByName(ps, name);
    
    if (pos == -1)
    {
        printf("查询不到要删除的联系人，请重试\n");
    }
    else
    {
        //删除数据
        int j = 0;
        for(j = pos; j < ps->size-1; j++)
        {
            ps->data[j] = ps->data[j + 1];
            //由于删除了这个数据，所以后面的数据会顶替上来
        }
        ps->size--;
        printf("删除成功\n");
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////// /////////

//查找指定的人的信息
void Search(const struct Contact *ps)
{
    char name[MAX_NAME];
    printf("请输入要查找人的名字:>");
    scanf("%s", name);
    int pos = FindByName(ps, name);
    if (pos == -1)
    {
        printf("要查找的人不存在,请重试\n");
    }
    else
    {
        printf("%-20s\t%-12s\t%-20s\n", "名字","电话", "关系");
        printf("%-20s\t%-12s\t%-20s\n",
            ps->data[pos].name,
            ps->data[pos].phone,
            ps->data[pos].rel);
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

//修改指定联系人的信息
void Revise(struct Contact *ps)
{
    char name[MAX_NAME];
    printf("请输入要修改联系人的名字:>");
    scanf("%s", name);
    int pos = FindByName(ps, name);
    if (pos == -1)
    {
        printf("要修改联系人的信息不存在，请重试\n");
    }
    else
    {
        printf("请输入名字:");
        scanf("%s", ps->data[pos].name);
        printf("请输入电话:");
        scanf("%s", ps->data[pos].phone);
        printf("请输入关系:");
        scanf("%s", ps->data[pos].rel);
 
        printf("修改完成\n");
    }
}
 
////////////////////////////////////////////////////////////////////////////////////// ////////////////////////////////////

//展示通讯录中的信息
void ShowContact(const struct Contact *ps)
{
    if(ps->size == 0)
    {
        printf("通讯录为空\n");
    }
    else
    {
        int i = 0;
        
		printf("%-20s\t%-12s\t%-20s\n", "名字","电话", "关系"); //标题
        
        for(i = 0; i < ps->size; i++)
        {
            printf("%-20s\t%-12s\t%-20s\n",
            ps->data[i].name,
            ps->data[i].phone,
            ps->data[i].rel);
        }//数据
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////// 

//初始化通讯录的函数
void InitContact(struct Contact *ps)
{
    memset(ps->data, 0, sizeof(ps->data));
    ps->size = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
int main()
{
    int input = 0;
    //创建通讯录
    struct Contact con;//con就是通讯录，里面包含：1000个元素的数和size
    //初始化通讯录
    InitContact(&con);
    do
    {
        menu();
        printf("请选择:");
        scanf("%d", &input);
        switch(input)
        {
        case ADD:
            Add(&con);
            break;
        case DEL:
            Del(&con);
            break;
        case SEARCH:
            Search(&con);
            break;
        case REVISE:
        	Revise(&con);
        case SHOW:
            ShowContact(&con);
            break;
        case EXIT:
            printf("退出通讯录\n");
            break;
        default:
            printf("选择错误\n");
            break;
        }
    } while (input);
    return 0;
}
