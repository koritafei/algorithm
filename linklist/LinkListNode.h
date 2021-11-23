#ifndef __LINKLISTNODE_H__
#define __LINKLISTNODE_H__

struct LinkListNode {
  int           val;
  LinkListNode *next;
  LinkListNode(int v) : val(v), next(nullptr) {
  }

  LinkListNode(int v, LinkListNode *next) : val(v), next(next) {
  }
};

#endif /* __LINKLISTNODE_H__ */
