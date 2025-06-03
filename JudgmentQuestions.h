#ifndef _JUDGMENTQUESTIONS_H_
#define _JUDGMENTQUESTIONS_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "list.h"


typedef struct JudgmentQuestions
{
    char question[512];
    char answer[4];
    struct list_head list;
}JudgQuestion;



void LoadJudgQuestionFile(JudgQuestion * JudgHead);

void SaveJudgQuestionFile(JudgQuestion * JudgHead);

JudgQuestion * InitJudgQuestion();

void InsertJudgQuestion(JudgQuestion * JudgHead);

bool WriteToJudgFile(JudgQuestion * head);

void DeleteJudgQuestion(JudgQuestion * Judg);

void JudgQuestionCheck(JudgQuestion * JudgHead);

void AdminJudgQuestion(JudgQuestion * JudgHead);

void ShowJudgQuestion( JudgQuestion * Judg );




#endif