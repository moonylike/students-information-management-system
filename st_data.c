#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "st_data.h"

/*全局学生数组与计数*/
st sts[MAX_STUDENTS];
int student_count = 0;

/*计算平均分*/
float avg(const st *s) {
    return (s->chinese + s->math + s->english) / 3.0f;
}

/*查找学号对应的下标，返回学号对应的数组值，未找到返回 -1*/
int find_id(int id) {
    for (int i = 0; i < student_count; i++) {
        if (sts[i].id == id) return i;
    }
    return -1;
}

/*添加学生，依次输入学号、姓名、语文成绩、数学成绩、英语成绩，成功返回 1*/
int add_student(int id, const char *name, float chi, float math, float eng) {
    if (student_count >= MAX_STUDENTS) return -1;   // 数组已满返回 -1
    if (find_id(id) != -1) return 0;             // 学号重复返回 0
    st *s = &sts[student_count];
    s->id = id;
    strncpy(s->name, name, MAX_NAME - 1);
    s->name[MAX_NAME - 1] = '\0';
    s->chinese = chi;
    s->math = math;
    s->english = eng;
    student_count++;
    return 1;
}

/*删除学生，输入学生学号，成功返回 1，未找到返回 0*/
int delete_student(int id) {
    int i = find_id(id);
    if (i == -1) return 0;
    /* 将后续元素前移 */
    for (int i = i; i < student_count - 1; i++) {
        sts[i] = sts[i + 1];
    }
    student_count--;
    return 1;
}

/*修改学生信息，依次输入学号、新姓名、新语文成绩、新数学成绩、新英语成绩，成功返回 1，未找到返回 0*/
int modify_student(int id, const char *name, float chi, float math, float eng) {
    int idx = find_id(id);
    if (idx == -1) return 0;
    st *s = &sts[idx];
    strncpy(s->name, name, MAX_NAME - 1);
    s->name[MAX_NAME - 1] = '\0';
    s->chinese = chi;
    s->math = math;
    s->english = eng;
    return 1;
}

/* 查询学生：按学号或姓名匹配，打印结果并返回匹配个数 */
int query_student(const char *keyword) {
    int found = 0;
    int id_keyword = 0;
    /*学号匹配*/
    if (sscanf(keyword, "%d", &id_keyword) == 1) {
        int i = find_id(id_keyword);
        if (i != -1) {
            printf("%-10s %-12s %-6s %-6s %-6s %-6s\n", "学号", "姓名", "语文", "数学", "英语", "平均");
            st *s = &sts[i];
            printf("%-10d %-12s %-6.1f %-6.1f %-6.1f %-6.1f\n",s->id, s->name, s->chinese, s->math, s->english, avg(s));
            return 1;
        }
    }
    /*姓名匹配*/
    printf("%-10s %-12s %-6s %-6s %-6s %-6s\n", "学号", "姓名", "语文", "数学", "英语", "平均");
    for (int i = 0; i < student_count; i++) {
        if (strstr(sts[i].name, keyword) != NULL) {
            st *s = &sts[i];
            printf("%-10d %-12s %-6.1f %-6.1f %-6.1f %-6.1f\n",
                   s->id, s->name, s->chinese, s->math, s->english, avg(s));
            found++;
        }
    }
    return found;
}

/* 打印全部学生 */
void show_all(void) {
    if (student_count == 0) {
        printf("无学生数据\n");
        return;
    }
    printf("%-10s %-12s %-6s %-6s %-6s %-6s\n",
           "学号", "姓名", "语文", "数学", "英语", "平均");
    for (int i = 0; i < student_count; i++) {
        st *s = &sts[i];
        printf("%-10d %-12s %-6.1f %-6.1f %-6.1f %-6.1f\n",
               s->id, s->name, s->chinese, s->math, s->english, avg(s));
    }
}

/*排序*/
static int sort_mode;
int cmp_student(const void *a, const void *b) {
    const st *s1 = (const st *)a;
    const st *s2 = (const st *)b;
    switch (sort_mode) {
        case 1: return s1->id - s2->id;
        case 2: return (s1->chinese > s2->chinese) - (s1->chinese < s2->chinese);
        case 3: return (s1->math > s2->math) - (s1->math < s2->math);
        case 4: return (s1->english > s2->english) - (s1->english < s2->english);
        case 5: {
            float a1 = avg(s1), a2 = avg(s2);
            return (a1 > a2) - (a1 < a2);
        }
        default: return 0;
    }
}

void sort_students(void) {
    int choice;
    printf("排序维度：1-学号 2-语文 3-数学 4-英语 5-平均分\n");
    printf("请选择：");
    scanf("%d", &choice);
    if (choice < 1 || choice > 5) {
        printf("无效选项。\n");
        return;
    }
    sort_mode = choice;
    qsort(sts, student_count, sizeof(st), cmp_student);
    printf("排序完成，当前数据为：\n");
    show_all();
}

/* 统计分析 */
void show_statistics(void) {
    if (student_count == 0) {
        printf("无数据，无法统计。\n");
        return;
    }

    float sum_ch = 0, sum_ma = 0, sum_en = 0;
    float max_ch = sts[0].chinese, min_ch = sts[0].chinese;
    float max_ma = sts[0].math, min_ma = sts[0].math;
    float max_en = sts[0].english, min_en = sts[0].english;

    /*计算平均分，最高分、最低分*/
    for (int i = 0; i < student_count; i++) {
        st *s = &sts[i];
        sum_ch += s->chinese;
        sum_ma += s->math;
        sum_en += s->english;

        if (s->chinese > max_ch) max_ch = s->chinese;
        if (s->chinese < min_ch) min_ch = s->chinese;
        if (s->math > max_ma) max_ma = s->math;
        if (s->math < min_ma) min_ma = s->math;
        if (s->english > max_en) max_en = s->english;
        if (s->english < min_en) min_en = s->english;
    }

    /*输出*/
    int cnt = student_count;
    printf("\n======================= 统计信息 =======================\n");
    printf("语文: 平均 %.2f  最高 %.2f  最低 %.2f\n", sum_ch/cnt, max_ch, min_ch);
    printf("数学: 平均 %.2f  最高 %.2f  最低 %.2f\n", sum_ma/cnt, max_ma, min_ma);
    printf("英语: 平均 %.2f  最高 %.2f  最低 %.2f\n", sum_en/cnt, max_en, min_en);
    printf("---------------------------------------------------------\n");
    printf("%-10s %-12s %-6s\n", "学号", "姓名", "平均分");
    for (int i = 0; i < student_count; i++) {
        st *s = &sts[i];
        printf("%-10d %-12s %-6.1f\n", s->id, s->name, avg(s));
    }
    printf("=========================================================\n");
}