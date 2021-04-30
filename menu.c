//
// Created by admin on 2021/4/29.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linktable.h"
#include "menu.h"

tLinkTable *head = NULL; // 定义全局头节点指针

int Help(); // 帮助; 展示所有命令信息

#define CMD_MAX_LEN 1024
#define CMD_MAX_ARGV_NUM 32


/* data struct and its operations */

typedef struct DataNode // 链表实际节点域
{
    tLinkTableNode *pNext;
    char *cmd;                              //指向命令字符串
    char *desc;                             // 命令描述
    int (*handler)(int argc, char *argv[]); // 命令对应的处理方法
} tDataNode;

int SearchConditon(tLinkTableNode *pLinkTableNode, void *arg)
{
    char *cmd = (char *)arg; // 获取目标字符串的地址
    tDataNode *pNode = (tDataNode *)pLinkTableNode;
    if (strcmp(pNode->cmd, cmd) == 0) // 比较命令字符串是否相等
    {
        return SUCCESS;
    }
    return FAILURE;
}

/* show all cmd in listlist */
int ShowAllCmd(tLinkTable *head)
{
    tDataNode *pNode = (tDataNode *)GetLinkTableHead(head); // 获取链表首部
    while (pNode != NULL)
    {
        printf("%s - %s\n", pNode->cmd, pNode->desc);
        pNode = (tDataNode *) pNode->pNext;
    }
    return 0;
}

int Help(int argc, char *argv[])
{
    ShowAllCmd(head);
    return 0;
}

/* add cmd to menu */
int MenuConfig(char *cmd, char *desc, int (*handler)(int argc, char *argv[]))
{
    tDataNode *pNode = NULL;
    if (head == NULL) // 添加第一条命令: help 指令 (只添加一次)
    {
        head = CreateLinkTable();
        pNode = (tDataNode *)malloc(sizeof(tDataNode));
        pNode->cmd = "help";
        pNode->desc = "Menu List:";
        pNode->handler = Help;
        AddLinkTableNode(head, (tLinkTableNode *)pNode);
    }
    pNode = (tDataNode *)malloc(sizeof(tDataNode));
    pNode->cmd = cmd;
    pNode->desc = desc;
    pNode->handler = handler;
    AddLinkTableNode(head, (tLinkTableNode *)pNode);
    return 0;
}

/* Menu Engine Execute */
int ExecuteMenu()
{
    /* cmd line begins */
    while (1)
    {
        int argc = 0;
        char *argv[CMD_MAX_ARGV_NUM];
        char cmd[CMD_MAX_LEN];
        char *pcmd = NULL;
        printf("Input a cmd > ");
        /* scanf("%s", cmd); */
        pcmd = fgets(cmd, CMD_MAX_LEN, stdin); // 从标准输入获取命令及参数
        if (pcmd == NULL)
        {
            continue;
        }
        /* convert cmd to argc/argv */
        pcmd = strtok(pcmd, " "); // 以空格分割成字符串,并获取第一个字符串指针
        while (pcmd != NULL && argc < CMD_MAX_ARGV_NUM)
        {
            argv[argc] = pcmd;
            argc++;
            pcmd = strtok(NULL, " ");
        }
        if (argc == 1)
        {
            int len = strlen(argv[0]);
            *(argv[0] + len - 1) = '\0'; // 为命令字符串添加尾零
        }
        tDataNode *p = (tDataNode *)SearchLinkTableNode(head, SearchConditon, (void *)argv[0]);
        if (p == NULL)
        {
            printf("This is a wrong cmd!\n ");
            continue;
        }

        if (p->handler != NULL)
        {
            p->handler(argc, argv);
        }
    }
}