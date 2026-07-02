#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "st_data.h"

/*保存至文件，成功返回 1，失败返回 0*/
int save_to_file(const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("文件打开失败");
        return 0;
    }
    for (int i = 0; i < student_count; i++) {
        st *s = &sts[i];
        fprintf(fp, "%d,%s,%.1f,%.1f,%.1f\n",
                s->id, s->name, s->chinese, s->math, s->english);
    }
    fclose(fp);
    printf("成功保存 %d 条记录到 %s\n", student_count, filename);
    return 1;
}

/*文件加载恢复，成功返回 1，失败返回 0*/
int load_from_file(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("文件打开失败");
        return 0;
    }
    int count = 0;
    char line[200];
    while (count < MAX_STUDENTS && fgets(line, sizeof(line), fp)) {
        int id;
        char name[MAX_NAME];
        float chi, math, eng;
        if (sscanf(line, "%d,%49[^,],%f,%f,%f", &id, name, &chi, &math, &eng) == 5) {
            sts[count].id = id;
            strncpy(sts[count].name, name, MAX_NAME - 1);
            sts[count].name[MAX_NAME - 1] = '\0';
            sts[count].chinese = chi;
            sts[count].math = math;
            sts[count].english = eng;
            count++;
        }
    }
    fclose(fp);
    student_count = count;
    printf("成功从 %s 加载 %d 条记录\n", filename, count);
    return 1;
}