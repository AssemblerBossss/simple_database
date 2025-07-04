#include "../include/table.h"

Pager *pager_open(const char *filename) {
    int _file_descriptor = open(
            filename,
            O_RDWR          // Read/Write mode
            | O_CREAT,      // Crete file if note exists
            S_IRUSR         // User read permission
            | S_IWUSR      // User read permission

            );

    if (_file_descriptor == -1) {
        printf("Unable to open file\n");
        exit(EXIT_FAILURE);
    }

    off_t _file_length = lseek(_file_descriptor, 0, SEEK_END);

    Pager *pager = (Pager*)malloc(sizeof(Pager));
    pager->file_descriptor = _file_descriptor;
    pager->file_length = _file_length;
    pager->num_pages = (_file_length / PAGE_SIZE);

    if (_file_length % PAGE_SIZE != 0) {
        printf("database file is not a whole number of pages. Corrupt file!");
        exit(EXIT_FAILURE);
    }

    for (uint32_t i =0; i < TABLE_MAX_PAGES; i++) {
        pager->pages[i] = NULL;
    }

    return pager;
}

Table *db_open(const char *filename) {
    Pager *pager = pager_open(filename);

    // Выделение памяти для структуры Table
    Table *table = (Table*)malloc(sizeof(Table));
    table->pager = pager;
    // Корень дерева всегда в странице 0
    table->root_page_num = 0;
    if (pager->num_pages == 0) {
        void* root_node = get_page(pager, 0);
        initialize_leaf_node(root_node);
    }
    return table;
}

void db_close(Table *table) {
    Pager *pager = table->pager;

    // Flush all full pages to disk
    for(uint32_t i = 0; i < pager->num_pages; i++) {
        if (pager->pages[i] == NULL) { continue; }

        // Write full page to disk and free memory
        pager_flush(pager, i);
        free(pager->pages[i]);
        pager->pages[i] = NULL;
    }

    // Close database file
    int result = close(pager->file_descriptor);
    if (result == -1) {
        printf("Error closing db file.\n");
        exit(EXIT_FAILURE);
    }

    // Free any remaining pages in cache
    for (uint32_t i = 0; i < TABLE_MAX_PAGES; i++) {
        void *page = pager->pages[i];
        if (page) {
            free(page);
            pager->pages[i] = NULL;
        }
    }
    free(pager);
    free(table);
}

void *get_page(Pager *pager, uint32_t page_number) {
    if (page_number >= TABLE_MAX_PAGES) {
        printf("Tried to fetch page_number out of bounds. %d", TABLE_MAX_PAGES);
        exit(EXIT_FAILURE);
    }

    if (pager->pages[page_number] == NULL) {
        // Cache miss. Allocate memory and load from file
        void *page = malloc(PAGE_SIZE);
        if (!page) {
            printf("Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }

        uint32_t num_pages = pager->file_length / PAGE_SIZE;

        // We might save a partial page at the end of the file
        if (pager->file_length % PAGE_SIZE) {
            num_pages += 1;
        }

        if (page_number <= num_pages) {
            lseek(pager->file_descriptor, page_number * PAGE_SIZE, SEEK_SET);
            ssize_t bytes_read = read(pager->file_descriptor, page, PAGE_SIZE);
            if (bytes_read == -1) {
                printf("Error reading file.");
                free(page);
                exit(EXIT_FAILURE);
            }
        }

        pager->pages[page_number] = page;

        if (page_number >= pager->num_pages) {
            pager->num_pages = page_number + 1;
        }
    }
    return pager->pages[page_number];
}

void pager_flush(Pager *pager, uint32_t page_num) {
    // Validate page pointer
    if (pager->pages[page_num] == NULL){
        printf("Tried to flush null page\n");
        exit(EXIT_FAILURE);
    }

    // Position file pointer at the correct offset
    off_t offset = lseek(pager->file_descriptor, page_num * PAGE_SIZE, SEEK_SET);
    if (offset == -1) {
        printf("Error seeking: %d\n", errno);
        exit(EXIT_FAILURE);
    }

    // Write page data to disk
    ssize_t bytes_written = write(pager->file_descriptor, pager->pages[page_num], PAGE_SIZE);
    if (bytes_written == -1) {
        printf("Error flushing(writing): %d", errno);
        exit(EXIT_FAILURE);
    }
}
