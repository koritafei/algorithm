#include <iostream>

#include "LinkListNode.h"

LinkListNode *josephusKill(LinkListNode *head, int m) {
  if (m == 0 || head == nullptr) {
    return head;
  }

  LinkListNode *last = head;

  while (last->next != head) {
    last = last->next;
  }

  int count = 0;
  // last 指向第m-1个位置，head指向m+1个节点
  while (last != head) {
    if (++count == m) {  // 先++在使用保证last指向第m-1个节点
      last->next = head->next;
      count      = 0;
    } else {
      last = last->next;
    }

    head = last->next;
  }

  return head;
}
