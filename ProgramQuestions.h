#ifndef _PROMGRAMQUESTIONS_H_
#define _PROMGRAMQUESTIONS_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "list.h"

typedef struct ProgmentQuestions
{
    char question[1024];
    char answer[1024];
    struct list_head list;
}ProgQuestion;



void LoadProgQuestionFile(ProgQuestion * ProgHead);

void SaveProgQuestionFile(ProgQuestion * ProgHead);

ProgQuestion * InitProgQuestion();

void InsertProgQuestion(ProgQuestion * ProgHead);

bool WriteToProgFile(ProgQuestion * head);

void DeleteProgQuestion(ProgQuestion * Prog);

void ProgQuestionCheck(ProgQuestion * ProgHead);

void AdminProgQuestion(ProgQuestion * ProgHead);

void ShowProgQuestion( ProgQuestion * Prog );


#endif