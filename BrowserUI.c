/*********************
 * @file BrowserUI.c
 * @brief UI页面管理
 * @author LFG (lfg@.com)
 * @version 1.3
 * @date 2025-05-25
 * 
 * @copyright Copyright (c) 2025  LFG
 * 
 *************************************************/

#include "BrowserUI.h"
#include "ChooseQuestions.h"
#include "FillInBlankQuestions.h"
#include "ProgramQuestions.h"
#include <unistd.h>
#include <stdlib.h>


extern DataHead * headCollection;


void InitQuestions(DataHead * headCollection)
{
    
}

/*********************
 * @brief 主界面
 * @param index 选择序号
 * @param exitFlag 退出标志变量
 *************************************************/
int MainUI()
{
    /*********************
     * @note 使用结构体存储不同类型的初始化的值，使用结构体成员进行具体的传值
     * 能否将Init函数抽离封装，不用每个函数都写一遍，功能是类似的
     *********************/
    headCollection = malloc(sizeof(DataHead));
    headCollection->ChoiceHead = InitChooseQuestion();
    headCollection->FillHead = InitFillQuestion();
    headCollection->JudgHead = InitJudgQuestion();
    headCollection->ProgHead = InitProgQuestion();
  
    int exitFlag = 1;
    LoadFile(headCollection->ChoiceHead);
    LoadFillQuestionFile(headCollection->FillHead);
    LoadJudgQuestionFile(headCollection->JudgHead);
    LoadProgQuestionFile(headCollection->ProgHead);
    
    while(exitFlag)
    {
        int index = 0;
        system("clear");
        printf("\n");
        printf("*********************************************\n");
        printf("*               试题管理系统                *\n");
        printf("*                                           *\n");
        printf("*                                           *\n");
        printf("*                1、试题                    *\n");
        printf("*                2、管理                    *\n");
        printf("*                0、退出                    *\n");
        printf("*                                           *\n");
        printf("*            请输入（0、1、2）：            *\n");
        printf("*                                           *\n");
        printf("*********************************************\n");
        printf("\n");
        printf("\033[10;32H");
        scanf("%d", &index);
        switch (index)
        {
            case 0: exitFlag = 0;   break;
            case 1: ExamQuestionCheck(headCollection);  break;
            case 2: ExamQuestionAdmin(headCollection);  break;
            default:
                break;
        }
        system("clear");
        printf("主程序界面!\n"); 
    }
    free(headCollection);
    return 0;
}

/*********************
 * @brief 试题查看界面
 * @param exitFlag 标志变量，决定是否退出循环状态
 * 
 * @note  标志变量的方法可以使用return 代替，但是会退出整个函数
 *************************************************/
void ExamQuestionCheck(DataHead * headCollection)
{
    int exitFlag = 1;
    while(exitFlag)
    {
        system("clear");
        printf("\n");
        printf("*********************************************\n");
        printf("*                试题检视                   *\n");
        printf("*                                           *\n");
        printf("*                1、选择题                  *\n");
        printf("*                2、填空题                  *\n");
        printf("*                3、编程题                  *\n");
        printf("*                4、判断题                  *\n");
        printf("*                0、返回                    *\n");
        printf("*                 请输入序号：              *\n");
        printf("*                                           *\n");
        printf("*********************************************\n");
        printf("\n");
        printf("\033[10;32H");      // 光标定位
        scanf("%d", &exitFlag);
        getchar();
        switch(exitFlag)
        {   // 等于0 时退出
            case 0: exitFlag = 0;   break;
            // 进入不同题型的检视面板
            case 1: ChooseQuestionCheck(headCollection->ChoiceHead);  break;
            case 2: FillQuestionCheck(headCollection->FillHead);    break;
            case 3: ProgQuestionCheck(headCollection->ProgHead);    break;
            case 4: JudgQuestionCheck(headCollection->JudgHead);    break;
        }
    }
}

/*********************
 * @brief 试题管理（增/删）
 * @param  ChoiceHead  要操作的数据头
 *************************************************/
void ExamQuestionAdmin(DataHead * headCollection)
{
    int exitFlag = 1;
    while(exitFlag)
    {
        system("clear");
        printf("\n");
        printf("*********************************************\n");
        printf("*                试题管理                   *\n");
        printf("*                                           *\n");
        printf("*                1、选择题                  *\n");
        printf("*                2、填空题                  *\n");
        printf("*                3、编程题                  *\n");
        printf("*                4、判断题                  *\n");
        printf("*                0、返回                    *\n");
        printf("*                 请输入序号：              *\n");
        printf("*                                           *\n");
        printf("*********************************************\n");
        printf("\n");
        printf("\033[10;34H");
        scanf("%d", &exitFlag);
        getchar();
        switch(exitFlag)
        {
            case 0: exitFlag = 0;   break;
            // 进入不同题型的管理面板
            case 1: AdminChooseQuestion(headCollection->ChoiceHead);  break;
            case 2: AdminFillQuestion(headCollection->FillHead);    break;
            case 3: AdminProgQuestion(headCollection->ProgHead);    break;
            case 4: AdminJudgQuestion(headCollection->JudgHead);    break;
        }
    }

}