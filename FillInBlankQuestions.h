#ifndef _FILLINBLANKQUEATIONS_H_
#define _FILLINBLANKQUEATIONS_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "list.h"


typedef struct FillBlankQuestion
{
    char question[512];     ///< 题干      
    char answer[512];       // 答案
    struct list_head list;     
}FillQuestion;

void LoadFillQuestionFile(FillQuestion * FillHead);

void SaveFillQuestionFile(FillQuestion * FillHead);

FillQuestion * InitFillQuestion();

void InsertFillQuestion(FillQuestion * FillHead);

bool WriteToFillFile(FillQuestion * head);

void DeleteFillQuestion(FillQuestion * Fill);

void FillQuestionCheck(FillQuestion * FillHead);

void AdminFillQuestion(FillQuestion * FillHead);

void ShowFillQuestion( FillQuestion * Fill );



#endif
