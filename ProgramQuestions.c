/*********************
 * @file ProgramQuestions.c
 * @brief 试题-编程题单元
 * @author LFG (lfg@.com)
 * @version 1.3
 * @date 2025-05-25
 * 
 * @copyright Copyright (c) 2025  LFG
 * 
 *************************************************/
#include "ProgramQuestions.h"



/*********************
 * @brief 加载程序文件
 * @param  ProgHead 
 * @details 加载程序文件与之前的文件思路不同，之前的文件都是循环读取文件单行
 * 再逐行进行解析输入之缓冲区，分两次分别读取题目和答案
 * 程序文件需要一次性读取全部目标内容
 * 目标内容可能存在换行符换行，逐行读取再进行拼接，并检查是否有标志字符
 * 如果有标志字符，则输入到缓冲区
 *************************************************/
void LoadProgQuestionFile(ProgQuestion * ProgHead)
{
    FILE * file = fopen("./ProgramQuestions.txt","r");
    if(file == NULL) {
        printf("文件打开失败！\n");
        return;
    }
    char linebuffer[1024] = {0};
    char tempbuffer[1024] = {0};
    // 不能将prog放在循环内，每次循环都重新定义 Prog = NULL，导致上一次循环中分配的内存丢失
    // 应该在循环外定义 Prog，在循环内使用
    // 注意prog指针的生命周期
    ProgQuestion * Prog = NULL;
    /*********************
     * @details 通过逐行读取内容，再进行拼接，检测是否有标志字符，如果有，则写入
     *************************************************/
    // chindex 标志变量 ，标志字符出现第几次
    int chindex = 0;
    printf("开始读取文件...\n"); // 调试输出
    while(fgets(linebuffer ,sizeof(linebuffer), file))
    {
        printf("读取行: %s", linebuffer); // 调试输出
        // 拼接
        strcat(tempbuffer, linebuffer);
        // @ 即标志字符
        char * pos = strchr(tempbuffer, '@');
        if(pos)
        {
            chindex++;
            switch (chindex)
            {
                case 1: 
                    // strcpy(linebuffer2, linebuffer);
                    Prog = malloc(sizeof(ProgQuestion));
                    // 不要随便删减大括号哇你个蠢货！！！！！！！！！！！！！！
                    if(Prog == NULL)
                    {
                        printf("内存分配失败！");        
                        fclose(file);
                        return;
                    }
                    INIT_LIST_HEAD(&Prog->list);
                    sscanf(tempbuffer,"%[^@]@",Prog->question);
                    // strcpy(Prog->question,tempbuffer); 
                    memset(tempbuffer, 0, sizeof(tempbuffer)); 
                    break;
                case 2:
                    sscanf(tempbuffer,"%[^@]@",Prog->answer);
                    // 使用cpy函数会将标志字符也复制过去，也会进行显示，使用sscanf格式化扫描集，则不会存储标志字符
                    // strcpy(Prog->answer, tempbuffer);
                    list_add_tail(&Prog->list, &ProgHead->list);  
                    memset(tempbuffer, 0, sizeof(tempbuffer));    
                    chindex = 0;
                    Prog = NULL;
                    break;
            }
        }
    }
    fclose(file);
}

/*********************
 * @brief 保存数据到程序题目文件
 * @param  ProgHead 
 * @note 写入文件时，在题目末尾添加@，在答案末尾添加@
 *************************************************/
void SaveProgQuestionFile(ProgQuestion * ProgHead)
{
    FILE * file = fopen("./ProgramQuestions.txt","w");
    if(file == NULL)    return ;
    struct list_head * head = &ProgHead->list;
    struct list_head * cur = head->next;
    while( cur != head )
    {
        ProgQuestion * ProgHead = list_entry(cur,ProgQuestion, list );
        // 之前的缓冲区小。存在溢出警告
        char linebuffer[4096] = {0};
        // 填空题以分号作为结束分割符
        // 注意这里的格式问题，sscanf扫描集拿走了匹配的字符，如果想要保持原格式，就要手动添加
        sprintf(linebuffer,"%s@\n%s@\n", ProgHead->question, ProgHead->answer);
        // printf("\n");
        fwrite(linebuffer, 1, strlen(linebuffer), file);
        cur = cur->next;
    }
    fclose(file);
}

/*********************
 * @brief 初始化程序题数据链表头
 * @return ProgQuestion* 
 *************************************************/
ProgQuestion * InitProgQuestion()
{
    ProgQuestion * ProgHead = malloc(sizeof(ProgQuestion));
    if( ProgHead != NULL )
    {
        ProgHead->list.next = ProgHead->list.prev = &ProgHead->list;
        return ProgHead;
    }
    return NULL;  // 添加错误处理返回值
}
void InsertProgQuestion(ProgQuestion * ProgHead)
{

}


/*********************
 * @brief 编程题从控制台向文件写入
 * @param  head 
 * @return true 
 * @return false
 * @note 有多种方法可以实现控制台输入 
 *************************************************/
bool WriteToProgFile(ProgQuestion * head)
{
    ProgQuestion * Prognode = malloc(sizeof(ProgQuestion));
    INIT_LIST_HEAD(&Prognode->list);
    while(getchar() != '\n');
    /*********************
     * @note 使用scanf输入，以标志字符结尾，长度取决于缓冲区大小，没有报警，可能溢出
     *********************/
    printf("请输入编程题题目（以@结尾）：");
    scanf("%1023[^@]", Prognode->question);     
    /*********************
     * @note 使用1023限制最大读取长度，避免缓冲区溢出
     * 只读取前1023个字符，剩余字符留在缓冲区，自动添加'\0'
     *************************************************/
    while(getchar() != '\n');       // 可以清空整个缓冲区直到遇到换行符
    printf("请输入答案（以@结尾）:");
    scanf("%1023[^@]", Prognode->answer);
    while(getchar() != '\n');
    // getchar();      // 一次只读取一个字符，返回读取的字符的ASCII值，遇到EOF返回 -1
    
    list_add_tail(&Prognode->list, &head->list);
    return true;
}

/*********************
 * @brief 删除一道题
 * @param  Prog 
 *************************************************/
void DeleteProgQuestion(ProgQuestion * Prog)
{
    list_del(&Prog->list);
    free(Prog);
}

/*********************
 * @brief 程序题检视
 * @param  ProgHead 
 *************************************************/
void ProgQuestionCheck(ProgQuestion * ProgHead)
{
    system("clear");
    int index = 0;
    struct list_head * cur = ProgHead->list.next;         // 为什么给ChoiceHead前面加&会有警告
    while(cur != &ProgHead->list)
    {
        system("clear");
        ShowProgQuestion(list_entry(cur, ProgQuestion, list)); ///
        printf("| 请选择（0-上一题 / 1-下一题 ）：          |\n");
        printf("\033[15;42H");
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
 * @brief 管理程序题（添加、删除）
 * @param  ProgHead 
 *************************************************/
void AdminProgQuestion(ProgQuestion * ProgHead)
{
    system("clear");
    int index = 0;
    // version 1.2
    struct list_head * cur = ProgHead->list.next;         // 为什么给ChoiceHead前面加&会有警告
    while(cur != &ProgHead->list)
    {
        system("clear");
        ShowProgQuestion(list_entry(cur, ProgQuestion, list)); ///
        printf("| 请选择0-上一题 / 1-下一题 / 2-删除 / 3-添加）：    |\n");
        printf("\033[15;52H");
        scanf("%d", &index);
        switch (index)
        {
            case 0: cur = cur->prev; continue;      // 若是直接从第一道题返回上一道会返回上一层。有待改良          
            case 1: cur = cur->next; continue;
            // version 1.2 功能-
            case 2: 
                ProgQuestion * p = list_entry(cur,ProgQuestion,list);
                cur = cur->next;
                DeleteProgQuestion(p);
                break;
            case 3:
                WriteToProgFile(ProgHead);
                break;
            default:    break;
        }
    }
    SaveProgQuestionFile(ProgHead);
}

/*********************
 * @brief 展示
 * @param  Prog 
 *************************************************/
void ShowProgQuestion( ProgQuestion * Prog )
{
    printf("*********************************************\n");
    printf("*                   编程题                  \n");
    printf("*                                                \n");
    printf("* 题目:%s\n", Prog->question);
    printf("* 答案:%s\n", Prog->answer);
    printf("*                                            \n");
    printf("*                                            \n");
    printf("*                                            \n");
    printf("*                                            \n");
    printf("*********************************************\n");
}