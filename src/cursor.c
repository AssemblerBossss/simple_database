#include "../include/cursor.h"

Cursor *table_start(Table *table) {
    Cursor *cursor = (Cursor*)malloc(sizeof(Cursor));
    cursor->table = table;
    cursor->page_num = table->root_page_num;
    cursor->cell_num = 0;

    void* root_node = get_page(table->pager, table->root_page_num);
    uint32_t num_cells = *leaf_node_num_cells(root_node);
    cursor->end_of_table = (num_cells == 0);

    return cursor;
}

Cursor *table_end(Table *table) {
    Cursor *cursor = (Cursor*)malloc(sizeof(Cursor));
    cursor->table = table;
    cursor->page_num = table->root_page_num;

    void *root_node = get_page(table->pager, table->root_page_num);
    uint32_t num_cells = *leaf_node_num_cells(root_node);
    cursor->cell_num = num_cells;
    cursor->end_of_table = true;

    return cursor;
}

void *cursor_value(Cursor *cursor) {
    // Получаем указатель на страницу, где находится текущая позиция курсора
    void *page = get_page(cursor->table->pager, cursor->page_num);
    // Возвращаем указатель на конкретное значение в листовом узле
    return leaf_node_value(page, cursor->cell_num);
}


void cursor_advance(Cursor *cursor) {
    void *node = get_page(cursor->table->pager, cursor->page_num);
    cursor->cell_num += 1;

    // Если текущая позиция (cell_num) >= количества ячеек, значит достигли конца
    if (cursor->cell_num >= (*leaf_node_num_cells(node))) {
        cursor->end_of_table = true;
    }
}
