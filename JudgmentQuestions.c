/*********************
 * @file JudgmentQuestions.c
 * @brief 试题-判断题单元
 * @author LFG (lfg@.com)
 * @version 1.3
 * @date 2025-05-25
 * 
 * @copyright Copyright (c) 2025  LFG
 * 
 *************************************************/

#include "JudgmentQuestions.h"



/*********************
 * @brief 判断题文本文件加载
 * @param  JudgHead 
 *************************************************/
void LoadJudgQuestionFile(JudgQuestion * JudgHead)
{
    FILE * file = fopen("./JudgmestQuestions.txt","r");
    if(file == NULL)    return;
    char * cur = NULL;
    char linebuffer[512] = {0};
    while( cur = fgets(linebuffer ,512, file) )
    {
        JudgQuestion * Judg = malloc(sizeof(JudgQuestion));
        INIT_LIST_HEAD(&Judg->list);
        // %[^;];  中括号内的分号是作为语法结构组成部分，外面的分号是进行匹配的
        sscanf(linebuffer,"%[^;];%[^;];",Judg->question, Judg->answer);
        // 改用尾插法
        list_add_tail(&Judg->list, &JudgHead->list);
    }
    fclose(file);
}

/*********************
 * @brief 判断题文本文件保存
 * @param  JudgHead 
 *************************************************/
void SaveJudgQuestionFile(JudgQuestion * JudgHead)
{
    FILE * file = fopen("./JudgmestQuestions.txt","w");
    if(file == NULL)    return ;
    struct list_head * head = &JudgHead->list;
    struct list_head * cur = head->next;
    while( cur != head )
    {
        JudgQuestion * JudgHead = list_entry(cur,JudgQuestion, list );
        // 之前的缓冲区小。存在溢出警告
        char linebuffer[4096] = {0};
        // 填空题以分号作为结束分割符
        sprintf(linebuffer,"%s;%s;\n", JudgHead->question, JudgHead->answer);
        // printf("\n");
        fwrite(linebuffer, 1, strlen(linebuffer), file);
        cur = cur->next;
    }
    fclose(file);
}

/*********************
 * @brief 初始化判断题
 * @return JudgQuestion* 
 *************************************************/
JudgQuestion * InitJudgQuestion()
{
    JudgQuestion * JudgHead = malloc(sizeof(JudgQuestion));
    if( JudgHead != NULL )
    {
        JudgHead->list.next = JudgHead->list.prev = &JudgHead->list;
        return JudgHead;
    }
    return NULL;  // 添加错误处理返回值
}

void InsertJudgQuestion(JudgQuestion * JudgHead);

/*********************
 * @brief 向判断题文件写入
 * @param  head 
 * @return true 
 * @return false 
 *************************************************/
bool WriteToJudgFile(JudgQuestion * head)
{
    JudgQuestion * Judgnode = malloc(sizeof(JudgQuestion));
    INIT_LIST_HEAD(&Judgnode->list);
    while(getchar() != '\n');
    printf("请输入判断题题目：");  scanf("%[^\n]", Judgnode->question);
    while(getchar() != '\n');
    printf("请输入答案:");  scanf("%[^\n]", Judgnode->answer);
    while(getchar() != '\n');
    
    list_add_tail(&Judgnode->list, &head->list);
    return true;
}

/*********************
 * @brief 删除
 * @param  Judg 
 *************************************************/
void DeleteJudgQuestion(JudgQuestion * Judg)
{
    list_del(&Judg->list);
    free(Judg);
}

/*********************
 * @brief 检视
 * @param  JudgHead 
 *************************************************/
void JudgQuestionCheck(JudgQuestion * JudgHead)
{
    system("clear");
    int index = 0;
    struct list_head * cur = JudgHead->list.next;         // 为什么给ChoiceHead前面加&会有警告
    while(cur != &JudgHead->list)
    {
        system("clear");
        ShowJudgQuestion(list_entry(cur, JudgQuestion, list)); ///
        printf("| 请选择（0-上一题 / 1-下一题 ）：          |\n");
        printf("\033[11;42H");
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
 * @brief 管理
 * @param  JudgHead 
 *************************************************/
void AdminJudgQuestion(JudgQuestion * JudgHead)
{
    system("clear");
    int index = 0;
    // version 1.2
    struct list_head * cur = JudgHead->list.next;         // 为什么给ChoiceHead前面加&会有警告
    while(cur != &JudgHead->list)
    {
        system("clear");
        ShowJudgQuestion(list_entry(cur, JudgQuestion, list)); ///
        printf("| 请选择0-上一题 / 1-下一题 / 2-删除 / 3-添加）：    |\n");
        printf("\033[11;52H");
        scanf("%d", &index);
        switch (index)
        {
            case 0: cur = cur->prev; continue;      // 若是直接从第一道题返回上一道会返回上一层。有待改良          
            case 1: cur = cur->next; continue;
            // version 1.2 功能-
            case 2: 
            ;
                JudgQuestion * p = list_entry(cur,JudgQuestion,list);
                cur = cur->next;
                DeleteJudgQuestion(p);
                break;
            case 3:
            ;
                WriteToJudgFile(JudgHead);
                break;
            default:    break;
        }
    }
    SaveJudgQuestionFile(JudgHead);

}

/*********************
 * @brief 展示
 * @param  Judg 
 *************************************************/
void ShowJudgQuestion( JudgQuestion * Judg )
{
    printf("*********************************************\n");
    printf("*                   判断题                  \n");
    printf("*                                                \n");
    printf("* 题目:%s\n", Judg->question);
    printf("* 答案:%s                                    \n", Judg->answer);
    printf("*                                            \n");
    printf("*                                            \n");
    printf("*                                            \n");
    printf("*                                            \n");
    printf("*********************************************\n");

}


