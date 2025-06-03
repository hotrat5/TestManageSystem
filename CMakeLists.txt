cmake_minimum_required(VERSION 3.22.1)

project(TestManageSystemV1_3 )

add_executable(ManageMain ManageMain.c BrowserUI.c ChooseQuestions.c FillInBlankQuestions.c JudgmentQuestions.c ProgramQuestions.c)