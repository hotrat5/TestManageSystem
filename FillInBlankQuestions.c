/*********************
 * @file FillInBlankQuestions.c
 * @brief  试题-填空题单元
 * @author LFG (lfg@.com)
 * @version 1.3
 * @date 2025-05-23
 * 
 * @copyright Copyright (c) 2025  LFG
 * 
 *************************************************/
#include "FillInBlankQuestions.h"
#include <string.h>
#include "list.h"


static char problem[3][512] = {};

/*********************
 * @brief 填空题文本文件加载
 * @param  FillHead 
 *************************************************/
void LoadFillQuestionFile(FillQuestion * FillHead)
{
    FILE * file = fopen("./FillInBlankQuestions.txt","r");
    if(file == NULL)    return;
    char * cur = NULL;
    char linebuffer[512] = {0};
    while( cur = fgets(linebuffer ,512, file) )
    {
        FillQuestion * Fill = malloc(sizeof(FillQuestion));

        INIT_LIST_HEAD(&Fill->list);
        // %[^;];  中括号内的分号是作为语法结构组成部分，外面的分号是进行匹配的
        sscanf(linebuffer,"%[^;];%[^;];",Fill->question, Fill->answer);
        // 改用尾插法
        list_add_tail(&Fill->list, &FillHead->list);
    }
    fclose(file);
}
/*********************
 * @brief 保存数据到文件
 * @param  FillHead
 * @note 为什么设置的读取到分号截止，但是写入文件时又改成了分号？ 
 *************************************************/
void SaveFillQuestionFile(FillQuestion * FillHead)
{
    FILE * file = fopen("./FillInBlankQuestions.txt","w");
    if(file == NULL)    return ;
    struct list_head * head = &FillHead->list;
    struct list_head * cur = head->next;
    while( cur != head )
    {
        FillQuestion * fillHead = list_entry(cur,FillQuestion, list );
        // 之前的缓冲区小。存在溢出警告
        char linebuffer[4096] = {0};
        // 填空题以分号作为结束分割符
        sprintf(linebuffer,"%s;%s;\n", fillHead->question, fillHead->answer);
        // printf("\n");
        fwrite(linebuffer, 1, strlen(linebuffer), file);
        cur = cur->next;
    }
    fclose(file);
}

/*********************
 * @brief 填空题链表初始化 
 * @return FillQuestion* 
 *************************************************/
FillQuestion * InitFillQuestion()
{
    // ChooseQuestion * 
    FillQuestion * FillHead = malloc(sizeof(FillQuestion));
    if( FillHead != NULL )
    {
        FillHead->list.next = FillHead->list.prev = &FillHead->list;
        return FillHead;
    }
    return NULL;  // 添加错误处理返回值
}

void InsertFillQuestion(FillQuestion * FillHead)
{
    
}

/*********************
 * @brief 写入文件
 * @param  head 
 * @return true 
 * @return false 
 *************************************************/
bool WriteToFillFile(FillQuestion * head)
{
    FillQuestion * fillnode = malloc(sizeof(FillQuestion));
    INIT_LIST_HEAD(&fillnode->list);
    while(getchar() != '\n');
    printf("请输入填空题题目：");  scanf("%[^;\n]", fillnode->question);
    while(getchar() != '\n');
    printf("请输入答案:");  scanf("%[^;\n]", fillnode->answer);
    
    list_add_tail(&fillnode->list, &head->list);
    return true;
}

/*********************
 * @brief 删除
 * @param  Fill 
 *************************************************/
void DeleteFillQuestion(FillQuestion * Fill)
{
    list_del(&Fill->list);
    free(Fill);
}

/*********************
 * @brief 填空题检视
 * @param  FillHead 
 *************************************************/
void FillQuestionCheck(FillQuestion * FillHead)
{
    system("clear");
    int index = 0;
    struct list_head * cur = FillHead->list.next;         // 为什么给ChoiceHead前面加&会有警告
    while(cur != &FillHead->list)
    {
        system("clear");
        ShowFillQuestion(list_entry(cur, FillQuestion, list)); ///
        printf("| 请选择（0-上一题 / 1-下一题 ）：          |\n");
        printf("\033[13;42H");
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
 * @brief 填空题管理
 * @param  FillHead 填空题链表头
 *************************************************/
void AdminFillQuestion(FillQuestion * FillHead)
{
    system("clear");
    int index = 0;
    // version 1.2
    struct list_head * cur = FillHead->list.next;         // 为什么给ChoiceHead前面加&会有警告
    while(cur != &FillHead->list)
    {
        system("clear");
        ShowFillQuestion(list_entry(cur, FillQuestion, list)); ///
        printf("| 请选择0-上一题 / 1-下一题 / 2-删除 / 3-添加）：    |\n");
        printf("\033[14;52H");
        scanf("%d", &index);
        switch (index)
        {
            case 0: cur = cur->prev; continue;      // 若是直接从第一道题返回上一道会返回上一层。有待改良          
            case 1: cur = cur->next; continue;
            case 2: 
                FillQuestion * p = list_entry(cur,FillQuestion,list);
                cur = cur->next;
                DeleteFillQuestion(p);
                break;
            case 3:
                WriteToFillFile(FillHead);
                break;
            default:    break;
        }
    }
    SaveFillQuestionFile(FillHead);
}

/*********************
 * @brief 填空题展示
 * @param  Fill 
 *************************************************/
void ShowFillQuestion( FillQuestion * Fill )
{
    printf("*********************************************\n");
    printf("*                   填空题                  \n");
    printf("*                                                \n");
    printf("* 题目:%s\n", Fill->question);
    printf("* 答案:%s                                    \n", Fill->answer);
    printf("*                                            \n");
    printf("*                                            \n");
    printf("*                                            \n");
    printf("*                                            \n");
    printf("*********************************************\n");
}