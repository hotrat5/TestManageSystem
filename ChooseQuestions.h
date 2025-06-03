#ifndef _CHOOSEQUESTIONS_H_
#define _CHOOSEQUESTIONS_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "list.h"

// extern ChooseQuestion * choiceHead;

/*********************
 * @brief 选择题结构体
 * @details @
 *************************************************/
typedef struct ChooseQuestion
{
    
    char question[512];     ///< 题干             
    char option[4][512];    ///< 选项
    int answer;             ///< 答案
    struct ChooseQuestion * prev;       // 旧方法，使用双向链表
    struct ChooseQuestion * next;
    struct list_head list;              // 新方法，使用内核链表

}ChooseQuestion;

void LoadFile(ChooseQuestion * ChoiceHead);

void SaveFile(ChooseQuestion * ChoiceHead);

ChooseQuestion * InitChooseQuestionxuanze(); 

ChooseQuestion * InitChooseQuestion();

void InsertChooseQuestion(ChooseQuestion * ChoiceHead);

bool WriteToFile(ChooseQuestion * head);

void DeleteQuestion(ChooseQuestion * choice);

void ChooseQuestionCheck(ChooseQuestion * ChoiceHead);

void AdminChooseQuestion(ChooseQuestion * ChoiceHead);

void ShowChoiceQuestion( ChooseQuestion * choice );







#endif