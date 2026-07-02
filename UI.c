#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "st_data.h"

/*添加学生*/
void ui_add(void) {
    int id;
    char name[MAX_NAME];
    float chi, math, eng;
    printf("请输入学号：");
    scanf("%d", &id);
    if (find_id(id) != -1) {
        printf("学号已存在，添加失败。\n");
        return;
    }
    printf("请输入姓名：");
    scanf("%s", name);
    printf("请输入语文成绩：");
    scanf("%f", &chi);
    printf("请输入数学成绩：");
    scanf("%f", &math);
    printf("请输入英语成绩：");
    scanf("%f", &eng);
    if (add_student(id, name, chi, math, eng)) {
        printf("添加成功。\n");
    } else {
        printf("添加失败，可能达到最大容量。\n");
    }
}

/*删除学生*/
void ui_delete(void) {
    int id;
    printf("请输入要删除的学号：");
    scanf("%d", &id);
    if (delete_student(id)) {
        printf("删除成功。\n");
    } else {
        printf("未找到该学号。\n");
    }
}

/*修改学生*/
void ui_modify(void) {
    int id;
    char name[MAX_NAME];
    float chi, math, eng;
    printf("请输入要修改的学号：");
    scanf("%d", &id);
    if (find_id(id) == -1) {
        printf("未找到该学号。\n");
        return;
    }
    printf("请输入新的姓名：");
    scanf("%s", name);
    printf("请输入新的语文成绩：");
    scanf("%f", &chi);
    printf("请输入新的数学成绩：");
    scanf("%f", &math);
    printf("请输入新的英语成绩：");
    scanf("%f", &eng);
    if (modify_student(id, name, chi, math, eng)) {
        printf("修改成功。\n");
    }
}

/*查找学生*/
void ui_query(void) {
    char keyword[MAX_NAME];
    printf("请输入学号或姓名关键字：");
    scanf("%49s", keyword);
    int cnt = query_student(keyword);
    if (cnt == 0) {
        printf("无匹配记录。\n");
    }
}

/*交互主页菜单*/
void ui_menu(void) {
    printf("\n==================== 学生信息管理系统 ====================\n");
    printf("添加学生：1\n");
    printf("删除学生：2\n");
    printf("修改学生：3\n");
    printf("查询学生：4\n");
    printf("显示全部：5\n");
    printf("统计分析：6\n");
    printf("排序输出：7\n");
    printf("保存至文件：8\n");
    printf("从文件加载：9\n");
    printf("退出：0\n");
    printf("-----------------------------------------------------------------\n");
    printf("请选择：");
}