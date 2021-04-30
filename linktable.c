//
// Created by admin on 2021/4/29.
//

#include "linktable.h"
#include <stdio.h>
#include <stdlib.h>


/*
 * LinkTableNode Type
 */
struct LinkTableNode
{
    tLinkTableNode *pNext;
};

/*
 * LinkTable Type
 */
struct LinkTable
{
    tLinkTableNode *pHead;
    tLinkTableNode *pTail;
    int SumOfNode;
};

/*
 * Create a LinkTable
 */
tLinkTable *CreateLinkTable()
{
    tLinkTable *pLinkTable = (tLinkTable *)malloc(sizeof(tLinkTable)); // 申请连表头节点
    if (pLinkTable == NULL)
    {
        return NULL;
    }
    // 初始化头节点信息
    pLinkTable->pHead = NULL;
    pLinkTable->pTail = NULL;
    pLinkTable->SumOfNode = 0;

    return pLinkTable;
}

/*
 * Delete a LinkTable
 */
int DeleteLinkTable(tLinkTable *pLinkTable)
{
    if (pLinkTable == NULL)
    {
        return FAILURE;
    }
    // 循环释放链表所有节点
    while (pLinkTable->pHead != NULL)
    {
        tLinkTableNode *p = pLinkTable->pHead;

        pLinkTable->pHead = pLinkTable->pHead->pNext; // 设置头节点指针指向链表首节点之后的部分
        pLinkTable->SumOfNode -= 1;                   // 修改链表长度

        free(p);                                      // 释放删除节点的空间
    }
    // 将头节点数据恢复初始化
    pLinkTable->pHead = NULL;
    pLinkTable->pTail = NULL;
    pLinkTable->SumOfNode = 0;

    free(pLinkTable);                            // 释放头节点空间
    return SUCCESS;
}

/*
 * Add a LinkTableNode to LinkTable
 */
int AddLinkTableNode(tLinkTable *pLinkTable, tLinkTableNode *pNode)
{
    if (pLinkTable == NULL || pNode == NULL)
    {
        return FAILURE;
    }
    pNode->pNext = NULL; // 初始化待添加节点的next指针

    // 添加第一个节点
    if (pLinkTable->pHead == NULL)
    {
        pLinkTable->pHead = pNode;
    }
    if (pLinkTable->pTail == NULL)
    {
        pLinkTable->pTail = pNode;
    }
    else
    { // 在链表末尾添加新元素(尾插法)
        pLinkTable->pTail->pNext = pNode;
        pLinkTable->pTail = pNode;
    }
    pLinkTable->SumOfNode += 1; // 更新链表长度

    return SUCCESS;
}

/*
 * Delete a LinkTableNode from LinkTable
 */
int DelLinkTableNode(tLinkTable *pLinkTable, tLinkTableNode *pNode)
{
    if (pLinkTable == NULL || pNode == NULL)
    {
        return FAILURE;
    }

    // 删除节点位于链表首部
    if (pLinkTable->pHead == pNode)
    {
        pLinkTable->pHead = pLinkTable->pHead->pNext;
        pNode->pNext = NULL; // 将删除的节点从链表上拆下来
        pLinkTable->SumOfNode -= 1;
        if (pLinkTable->SumOfNode == 0) // 链表只有一个节点
        {
            pLinkTable->pTail = NULL;
        }

        return SUCCESS;
    }
    tLinkTableNode *pTempNode = pLinkTable->pHead;
    while (pTempNode != NULL) // 遍历链表寻找符合条件节点的前一个节点。
    {
        if (pTempNode->pNext == pNode)
        {
            pTempNode->pNext = pTempNode->pNext->pNext;
            pNode->pNext = NULL; // 将删除的节点从链表上拆下来
            pLinkTable->SumOfNode -= 1;
            if (pTempNode->pNext == NULL) // 删除的节点为链表的最后一个元素，则修改头节点尾指针指向
            {
                pLinkTable->pTail = pTempNode;
            }

            return SUCCESS;
        }
        pTempNode = pTempNode->pNext;
    }

    return FAILURE; // 删除节点不在链表中
}

/*
 * Search a LinkTableNode from LinkTable
 * int Conditon(tLinkTableNode * pNode);
 */
tLinkTableNode *SearchLinkTableNode(tLinkTable *pLinkTable, int Conditon(tLinkTableNode *pNode, void *args), void *args)
{
    if (pLinkTable == NULL || Conditon == NULL)
    {
        return NULL;
    }
    tLinkTableNode *pNode = pLinkTable->pHead; // 遍历节点
    while (pNode != NULL)
    {
        if (Conditon(pNode, args) == SUCCESS) // Conditon 用于定义节点的比较方式
        {
            return pNode;
        }
        pNode = pNode->pNext;
    }
    return NULL;
}

/*
 * get LinkTableHead
 */
tLinkTableNode *GetLinkTableHead(tLinkTable *pLinkTable)
{
    if (pLinkTable == NULL)
    {
        return NULL;
    }
    return pLinkTable->pHead;
}