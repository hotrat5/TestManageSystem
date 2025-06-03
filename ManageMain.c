/*********************
 * @file ManageMain.c
 * @brief 试题管理系统主程序
 * @author LFG (lfg@.com)
 * @version 1.2
 * @date 2025-05-21
 * 
 * @copyright Copyright (c) 2025  LFG
 * 
 *************************************************/

#include "BrowserUI.h"
#include "ChooseQuestions.h"

DataHead * headCollection = NULL;

int main()
{ 
    MainUI();     
    printf("全局界面!\n"); 
    return 0;
}