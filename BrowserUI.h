#ifndef _BROWSERUI_H_
#define _BROWSERUI_H_

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "ChooseQuestions.h"
#include "FillInBlankQuestions.h"
#include "JudgmentQuestions.h"
#include "ProgramQuestions.h"


/*********************
 * @brief 该结构体里存储的是不同类型结构体初始化后返回的地址
 *************************************************/
typedef struct QuestionsDataHead
{
    ChooseQuestion * ChoiceHead;
    FillQuestion * FillHead;
    JudgQuestion * JudgHead;
    ProgQuestion * ProgHead;

}DataHead;

int MainUI();

void InitQuestions(DataHead * headCollection);

void ExamQuestionCheck(DataHead * headCollection);

void ExamQuestionAdmin(DataHead * headCollection);




// printf("\033[8;24H");  可以将光标重新定位 8：行号。24：列号
#endif