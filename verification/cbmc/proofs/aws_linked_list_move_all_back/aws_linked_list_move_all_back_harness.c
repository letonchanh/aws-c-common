/**
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0.
 */

#include <aws/common/linked_list.h>
#include <proof_helpers/make_common_data_structures.h>

void aws_linked_list_move_all_back_harness() {
    /* data structure */
    struct aws_linked_list dst, src;

    ensure_linked_list_is_allocated(&dst, MAX_LINKED_LIST_ITEM_ALLOCATION);
    ensure_linked_list_is_allocated(&src, MAX_LINKED_LIST_ITEM_ALLOCATION);

    bool src_is_empty = aws_linked_list_empty(&src);
    size_t old_dst_length = dst.length;
    size_t old_src_length = src.length;
    struct aws_linked_list_node *old_dst_back = dst.tail.prev;
    struct aws_linked_list_node *old_src_front = src.head.next;
    struct aws_linked_list_node *old_src_back = src.tail.prev;

    /* perform operation under verification */
    aws_linked_list_move_all_back(&dst, &src);

    /* assertions */
    assert(aws_linked_list_is_valid(&dst));
    assert(aws_linked_list_is_valid(&src));
    assert(dst.length == old_dst_length + old_src_length);
    assert(src.length == 0);

    if (src_is_empty) {
        assert(dst.tail.prev == old_dst_back);
    } else {
        assert(dst.tail.prev == old_src_back);
        assert(old_dst_back->next == old_src_front);
        assert(old_dst_back == old_src_front->prev);
    }
}
