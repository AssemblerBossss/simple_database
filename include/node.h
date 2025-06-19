#ifndef DATABASE_NODE_H
#define DATABASE_NODE_H

#include "types.h"
#include "row_serialization.h"


#define TABLE_MAX_PAGES 100
#define PAGE_SIZE       4096
#define ROWS_PER_PAGE   (PAGE_SIZE / ROW_SIZE)
#define TABLE_MAX_ROWS  (ROWS_PER_PAGE * TABLE_MAX_PAGES)


/*
 * WHY uint32_t FOR OFFSETS/SIZES:
 * - Type consistency: All offsets/sizes use uint32_t to prevent implicit casts in pointer arithmetic
 * - Overflow safety: Ensures offsets work even with large pages (>255 bytes)
 * - Page alignment: Naturally fits 4096-byte pages (common in systems)
 * - Future-proof: Allows expansion beyond current page sizes
 */

// Size of the node type field (1 byte, since it's an enum stored as uint8_t)
static const uint32_t NODE_TYPE_SIZE = sizeof(uint8_t);
// Offset of the node type field in the header (first field at position 0)
static const uint32_t NODE_TYPE_OFFSET = 0;

// Size of the is-root flag (1 byte, stored as uint8_t boolean)
static const uint32_t IS_ROOT_SIZE = sizeof(uint8_t);
// Offset of the is-root flag (immediately after node type)
static const uint32_t IS_ROOT_OFFSET = NODE_TYPE_OFFSET;

// Size of the parent pointer (4 bytes, stored as uint32_t page number)
static const uint32_t PARENT_POINTER_SIZE = sizeof(uint32_t);
// Offset of the parent pointer (after node type and is-root flag)
static const uint32_t PARENT_POINTER_OFFSET = IS_ROOT_OFFSET + IS_ROOT_SIZE;

// Total size of the common header shared by all node types (internal and leaf)
// Contains: node type (1) + is-root flag (1) + parent pointer (4) = 6 bytes
static const uint8_t COMMON_NODE_HEADER_SIZE = NODE_TYPE_SIZE + IS_ROOT_SIZE + PARENT_POINTER_SIZE;

/*
* Leaf Node Header Layout
*/
// The size of a 4-byte cell counter
static const uint32_t LEAF_NODE_NUM_CELLS_SIZE = sizeof(uint32_t);
// Offset of the number of cells field (starts immediately after the general node header)
static const uint32_t LEAF_NODE_NUM_CELLS_OFFSET = COMMON_NODE_HEADER_SIZE;
// Total size of the leaf node header: [Total header] + [Number of cells]
static const uint32_t LEAF_NODE_HEADER_SIZE = COMMON_NODE_HEADER_SIZE + LEAF_NODE_NUM_CELLS_SIZE;


/*
* Leaf Node Body Layout
*/
/* Size of the key in bytes (fixed to 4 bytes for uint32_t) */
static const uint32_t LEAF_NODE_KEY_SIZE = sizeof(uint32_t);

/* Key always starts at offset 0 within the cell */
static const uint32_t LEAF_NODE_KEY_OFFSET = 0;

/* Size of the value (serialized row size) */
static const uint32_t LEAF_NODE_VALUE_SIZE = ROW_SIZE;

/* Value starts immediately after the key */
static const uint32_t LEAF_NODE_VALUE_OFFSET = LEAF_NODE_KEY_OFFSET + LEAF_NODE_KEY_SIZE;

/* Total size of a single cell (key + value) */
static const uint32_t LEAF_NODE_CELL_SIZE = LEAF_NODE_KEY_SIZE + LEAF_NODE_VALUE_SIZE;

/* Available space for cells after accounting for header */
static const uint32_t LEAF_NODE_SPACE_FOR_CELLS = PAGE_SIZE - LEAF_NODE_HEADER_SIZE;

/* Maximum number of cells that can fit in a leaf node */
static const uint32_t LEAF_NODE_MAX_CELL = LEAF_NODE_SPACE_FOR_CELLS / LEAF_NODE_CELL_SIZE;


typedef enum {
    NODE_INTERNAL, ///< Node that stores keys and pointers to child nodes
    NODE_LEAF      ///< Leaf node that stores key/value pairs (actual data)
} NodeType;


/**
 * @brief Get a pointer to the number of cells in a leaf node
 *
 * @param node Pointer to the start of the leaf node memory block
 * @return uint32_t* Pointer to the num_cells field (4-byte unsigned integer)
 */
uint32_t* leaf_node_num_cells(void *node);

/**
 * @brief Get a pointer to a definite cell in a leaf node
 *
 * @param node Pointer to the start of the leaf node memory block
 * @param cell_num Zero-based index of the cell to access
 * @return void* Pointer to the beginning of the specified cell
 * @note Does not perform bounds checking - caller must ensure cell_num is valid
 */
void* leaf_node_cell(void *node, uint32_t cell_num);

/**
 * @brief Get a pointer to the key within a specific cell
 *
 * @param node Pointer to the start of the leaf node memory block
 * @param cell_num Zero-based index of the target cell
 * @return void* Pointer to the key (first bytes of the cell)
 * @see leaf_node_cell() The underlying cell access function
 */
void* leaf_node_key(void *node, uint32_t cell_num);

/**
 * @brief Get a pointer to the value within a specific cell
 *
 * @param node Pointer to the start of the leaf node memory block
 * @param cell_num Zero-based index of the target cell
 * @return void* Pointer to the value portion of the cell
 * @note Value starts immediately after the key (offset by LEAF_NODE_KEY_SIZE)
 */
void* leaf_node_value(void *node, uint32_t cell_num);


#endif //DATABASE_NODE_H
