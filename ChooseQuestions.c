/*********************
 * @file ChooseQuestions.c
 * @brief 试题-选择题单元
 * @author LFG (lfg@.com)
 * @version 1.3
 * @date 2025-05-25
 * 
 * @copyright Copyright (c) 2025  LFG
 * 
 *************************************************/

#include "ChooseQuestions.h"
#include <string.h>
#include "list.h"


// v1.2 从函数内抽离
static char problem[3][512] = {
    // 经过逗号转义
    "1、以下关于C语言的说法错误的是, A.C程序的工作过程是编辑、编译、链接、运行,B.C语言不区分大小写,C.C程序的三种基本结构是顺序、选择、循环,D.C程序从main函数开始运行",
    "2、下列命令或语句中，正确的是（）,A.#define MYNAME=”ABC”,B.#include stdio.h,C.for(i=0; i<10; i++);,D.struct int stu{int name};",
    "3、为了判断两个字符串s1和s2是否相等，应当使用（）,A.if(s1==s2),B.if(s1=s2),C.if(strcmp(s1，s2)),D.if(strcmp(s1，s2)==0)"
};


/*********************
 * @brief 加载文件
 * @details 使用文件io函数，以特定权限打开文件并进行操作：
 *          可读权限打开文件，并将选定的内容读取后写入到链表中
 *************************************************/
void LoadFile(ChooseQuestion * ChoiceHead)
{
    FILE * file = fopen("./question.txt","r");
    if(file == NULL)    return;
    char * cur = NULL;
    char linebuffer[512] = {0};
    while( cur = fgets(linebuffer ,512, file) )
    {
        ChooseQuestion * choice = malloc(sizeof(ChooseQuestion));

        INIT_LIST_HEAD(&choice->list);
        // 格式化扫描集写入
        sscanf(linebuffer,"%[^,],%[^,],%[^,],%[^,],%[^,],%d",choice->question, choice->option[0],choice->option[1],choice->option[2],choice->option[3],&choice->answer);
        // 改用尾插法
        list_add_tail(&choice->list, &ChoiceHead->list);
    }
    fclose(file);
} 

/*********************
 * @brief 文本文件保存
 * @param  ChoiceHead 
 *************************************************/
void SaveFile(ChooseQuestion * ChoiceHead)
{
    FILE * file = fopen("./question.txt","w");
    if(file == NULL)    return ;
    struct list_head * head = &ChoiceHead->list;
    struct list_head * cur = head->next;

    while( cur != head )
    {
        ChooseQuestion * cqHead = list_entry(cur,ChooseQuestion, list );
        // 之前的缓冲区小。存在溢出警告
        char linebuffer[4096] = {0};
        sprintf(linebuffer,"%s,%s,%s,%s,%s,%d\n",
            cqHead->question, 
            cqHead->option[0],
            cqHead->option[1],
            cqHead->option[2],
            cqHead->option[3],
            cqHead->answer);
        fwrite(linebuffer, 1, strlen(linebuffer), file);
        cur = cur->next;
    }
    fclose(file);
}

/*********************
 * @brief 初始化一个选择题链表头，表头不存储数据
 * @return ChooseQuestion* 返回选择题链表的表头
 *************************************************/
ChooseQuestion * InitChooseQuestion()
{
    // ChooseQuestion * 
    ChooseQuestion * ChoiceHead = malloc(sizeof(ChooseQuestion));
    if( ChoiceHead != NULL )
    {
        ChoiceHead->list.next = ChoiceHead->list.prev = &ChoiceHead->list;
        return ChoiceHead;
    }
    return NULL;  // 添加错误处理返回值
}


ChooseQuestion * InitChooseQuestionxuanze()
{
    ChooseQuestion * ChoiceHead = malloc(sizeof(ChooseQuestion));
    if( ChoiceHead != NULL )
    {
        ChoiceHead->list.next = ChoiceHead->list.prev = &ChoiceHead->list;
        return ChoiceHead;
    }
}


/*********************
 * @brief 向表头插入选择题
 * @param  ChoiceHead 选择题链表表头
 * @details 在函数内部有一个预定义好的选择题数组，使用sscanf输入到指定的数据结构体
 * 
 * @note 可以将选择题数组抽离单独进行封装成函数或者文件，不仅适用于选择题也适用于其它类型的题目
 * @note 可以将文件向程序写和程序向文件写合并，通过参数选择,但是在经过从程序写入文件功能的剥离，该功能事实上已经成了从文件向程序写
 *************************************************/
void InsertChooseQuestion(ChooseQuestion * ChoiceHead)  // 头插法
{

    for( int i = 0; i < 4; i++ )           // 插入的数量
    {
        ChooseQuestion *choice = malloc(sizeof(ChooseQuestion));
        if( choice != NULL )
        {
            // 内核链表法 
            // 指针不用进行分配内存
            // 自环初始化
            choice->list.next = choice->list.prev = &choice->list;
            // INIT_LIST_HEAD(&choice->list);
            sscanf(problem[i],"%[^,],%[^,],%[^,],%[^,],%[^,]",choice->question, choice->option[0],choice->option[1],choice->option[2],choice->option[3]);

            list_add_tail(&choice->list, &ChoiceHead->list);

            // 尾插法

        }   
    }
}

/*********************
 * @brief 向文本文件写入
 * @param  head 
 * @return true 
 * @return false 
 *************************************************/
bool WriteToFile(ChooseQuestion * head)
{
    ChooseQuestion * node = malloc(sizeof(ChooseQuestion));
    INIT_LIST_HEAD(&node->list);
    while(getchar() != '\n');
    printf("请输入选择题题目：");  scanf("%[^\n]", node->question);
    while(getchar() != '\n');
    printf("请输入A选项:");  scanf("%[^\n]", node->option[0]);
    while(getchar() != '\n');
    printf("请输入B选项:");  scanf("%[^\n]", node->option[1]);
    while(getchar() != '\n');
    printf("请输入C选项:");  scanf("%[^\n]", node->option[2]);
    while(getchar() != '\n');
    printf("请输入D选项:");  scanf("%[^\n]", node->option[3]);
    while(getchar() != '\n');
    printf("请输入参考答案（A0 / B1 / C2 / D3）:"); scanf("%d", &node->answer);

   list_add_tail(&node->list, &head->list);
    return true;
}

/*********************
 * @brief 选择题删除
 * @param  choice 
 *************************************************/
void DeleteQuestion(ChooseQuestion * choice)
{
    list_del(&choice->list);
    free(choice);
}

/*********************
 * @brief 遍历展示题目
 * @param  ChoiceHead 选择题链表表头
 * @param cur 游标
 * @details 展示框架 通过 0 / 1 选择上一道或者下一道，由于使用尾插法
 * 
 * @warning 进入展示界面后，如果从第一道题目选择 0 ，由于cur指针前移，指向head，不满足循环条件，会直接退出循环
 * @note 可以将展示函数与管理函数分开
 *************************************************/


 /*********************
  * @brief 选择题检视
  * @param  ChoiceHead 
  *************************************************/
void ChooseQuestionCheck(ChooseQuestion * ChoiceHead)
{
    system("clear");
    int index = 0;
    // version 1.2
    struct list_head * cur = ChoiceHead->list.next;         // 为什么给ChoiceHead前面加&会有警告
    while(cur != &ChoiceHead->list)
    {
        system("clear");
        ShowChoiceQuestion(list_entry(cur, ChooseQuestion, list)); ///
        printf("| 请选择（0-上一题 / 1-下一题 ）：          |\n");
        printf("\033[11;35H");
        scanf("%d", &index);
        switch (index)
        {
            case 0: cur = cur->prev; continue;      // 若是直接从第一道题返回上一道会返回上一层。有待改良          
            case 1: cur = cur->next; continue;
            // version 1.2 功能
            default:    break;
        }
    }
}

/*********************
 * @brief 选择题管理
 * @param  ChoiceHead 
 *************************************************/
void AdminChooseQuestion(ChooseQuestion * ChoiceHead)
{
    system("clear");
    int index = 0;
    // version 1.2
    struct list_head * cur = ChoiceHead->list.next;         // 为什么给ChoiceHead前面加&会有警告
    while(cur != &ChoiceHead->list)
    {
        system("clear");
        ShowChoiceQuestion(list_entry(cur, ChooseQuestion, list)); ///
        printf("| 请选择0-上一题 / 1-下一题 / 2-删除 / 3-添加）：    |\n");
        printf("\033[11;52H");
        scanf("%d", &index);
        // while(getchar() != '\n');
        switch (index)
        {
            case 0: cur = cur->prev; continue;      // 若是直接从第一道题返回上一道会返回上一层。有待改良          
            case 1: cur = cur->next; continue;
            // version 1.2 功能-
            case 2: 
            ;
                ChooseQuestion * p = list_entry(cur,ChooseQuestion,list);
                cur = cur->next;
                DeleteQuestion(p);
                // struct list_head * p = cur;
                // cur = cur->next;
                // DeleteQuestion(list_entry(p,ChooseQuestion,list));
                break;
            case 3:
            ;
                WriteToFile(ChoiceHead);
                break;
            default:    break;
        }
    }
    SaveFile(ChoiceHead);
}


/*********************
 * @brief 选择题展示
 * @param  choice 
 *************************************************/
void ShowChoiceQuestion( ChooseQuestion * choice )
{
    printf("*********************************************\n");
    printf("*                   选择题                  \n");
    printf("*                                                \n");
    printf("* 题目:%s\n", choice->question);
    printf("* A.%s %s\n", choice->option[0], (choice->answer==0)?"答案":"");
    printf("* B.%s %s\n", choice->option[1], (choice->answer==1)?"答案":"");
    printf("* C.%s %s\n", choice->option[2], (choice->answer==2)?"答案":"");
    printf("* D.%s %s\n", choice->option[3], (choice->answer==3)?"答案":"");
    printf("*                                           \n");
    printf("*********************************************\n");

}


