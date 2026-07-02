#ifndef __ST_DATA_H
#define __ST_DATA_H

#define MAX_STUDENTS 100
#define MAX_NAME 50
#define DATA_FILE "students.txt"

typedef struct {
    int id;
    char name[MAX_NAME];
    float chinese;
    float math;
    float english;
} st;
extern st sts[];
extern int student_count;

int find_id(int id);
int add_student(int id, const char *name, float chi, float math, float eng);
int delete_student(int id);
int modify_student(int id, const char *name, float chi, float math, float eng);
int query_student(const char *keyword);
void show_all(void);
void sort_students(void);
void show_statistics(void); 

#endif