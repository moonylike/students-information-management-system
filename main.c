#include <stdio.h>
#include "st_data.h"
#include "ReadAndWrite.h"
#include "UI.h"

int main(void) {
    printf("中文\n");
    /* 启动时尝试加载数据文件 */
    printf("正在加载数据文件 %s ...\n", DATA_FILE);
    if (!load_from_file(DATA_FILE)) {
        printf("未找到数据文件，将创建新文件。\n");
    }

    /*定义状态机*/
    int m;

    /*死循环*/
    while (1) {
        ui_menu();
        if (scanf("%d", &m) != 1) {
            printf("输入无效，请重新选择。\n");
            continue;
        }
        switch (m) {
            case 1: ui_add(); break;
            case 2: ui_delete(); break;
            case 3: ui_modify(); break;
            case 4: ui_query(); break;
            case 5: show_all(); break;
            case 6: show_statistics(); break;
            case 7: sort_students(); break;
            case 8: save_to_file(DATA_FILE); break;
            case 9: load_from_file(DATA_FILE);break;
            case 0: printf("程序结束\n");return 0;          //退出死循环
            default: printf("无效选项，请重新输入。\n"); break;
        }
    } 
}