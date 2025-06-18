#ifndef DATABASE_NODE_H
#define DATABASE_NODE_H

#include "types.h"

/*
 * WHY uint32_t FOR OFFSETS/SIZES:
 * - Type consistency: All offsets/sizes use uint32_t to prevent implicit casts in pointer arithmetic
 * - Overflow safety: Ensures offsets work even with large pages (>255 bytes)
 * - Page alignment: Naturally fits 4096-byte pages (common in systems)
 * - Future-proof: Allows expansion beyond current page sizes
 */

// Size of the node type field (1 byte, since it's an enum stored as uint8_t)
const uint32_t NODE_TYPE_SIZE = sizeof(uint8_t);
// Offset of the node type field in the header (first field at position 0)
const uint32_t NODE_TYPE_OFFSET = 0;

// Size of the is-root flag (1 byte, stored as uint8_t boolean)
const uint32_t IS_ROOT_SIZE = sizeof(uint8_t);
// Offset of the is-root flag (immediately after node type)
const uint32_t IS_ROOT_OFFSET = NODE_TYPE_OFFSET;

// Size of the parent pointer (4 bytes, stored as uint32_t page number)
const uint32_t PARENT_POINTER_SIZE = sizeof(uint32_t);
// Offset of the parent pointer (after node type and is-root flag)
const uint32_t PARENT_POINTER_OFFSET = IS_ROOT_OFFSET + IS_ROOT_SIZE;

// Total size of the common header shared by all node types (internal and leaf)
// Contains: node type (1) + is-root flag (1) + parent pointer (4) = 6 bytes
const uint8_t COMMON_NODE_HEADER_SIZE = NODE_TYPE_SIZE + IS_ROOT_SIZE + PARENT_POINTER_SIZE;

// The size of a 4-byte cell counter
const uint32_t LEAF_NODE_NUM_CELLS_SIZE = sizeof(uint32_t);
// Offset of the number of cells field (starts immediately after the general node header)
const uint32_t LEAF_NODE_NUM_CELLS_OFFSET = COMMON_NODE_HEADER_SIZE;
// Total size of the leaf node header: [Total header] + [Number of cells]
const uint32_t LEAF_NODE_HEADER_SIZE = COMMON_NODE_HEADER_SIZE + LEAF_NODE_NUM_CELLS_SIZE;

typedef enum {
    NODE_INTERNAL, ///< Node that stores keys and pointers to child nodes
    NODE_LEAF      ///< Leaf node that stores key/value pairs (actual data)
} NodeType;

#endif //DATABASE_NODE_H
