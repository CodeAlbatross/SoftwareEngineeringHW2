/********************************************************************/
/* Copyright (C) SSE-USTC, 2012-2021                                */
/*                                                                  */
/*  FILE NAME             :  linktabe.h                             */
/*  PRINCIPAL AUTHOR      :  Mengning                               */
/*  SUBSYSTEM NAME        :  LinkTable                              */
/*  MODULE NAME           :  LinkTable                              */
/*  LANGUAGE              :  C                                      */
/*  TARGET ENVIRONMENT    :  ANY                                    */
/*  DATE OF FIRST RELEASE :  2012/12/30                             */
/*  DESCRIPTION           :  interface of Link Table                */
/********************************************************************/

/*
 * Revision log:
 *
 * Created by Mengning,2012/12/30
 * modified by Mengning, 2021/04/23
 *
 */
#ifndef SOFTWARE2_LINKTABLE_H
#define SOFTWARE2_LINKTABLE_H
#define SUCCESS 0
#define FAILURE (-1)

/*
 * LinkTable Node Head Type, example as below:
 * typedef struct UserNode
 * {
 *     tLinkTableNode head;
 *     tUserData data;
 * }tUserNode;
 */
typedef struct LinkTableNode tLinkTableNode;

/*
 * LinkTable Type
 */
typedef struct LinkTable tLinkTable;

/*
 * Create a LinkTable
 */
tLinkTable * CreateLinkTable();
/*
 * Delete a LinkTable
 */
int DeleteLinkTable(tLinkTable *pLinkTable);
/*
 * Add a LinkTableNode to LinkTable
 */
int AddLinkTableNode(tLinkTable *pLinkTable,tLinkTableNode * pNode);
/*
 * Delete a LinkTableNode from LinkTable
 */
int DelLinkTableNode(tLinkTable *pLinkTable,tLinkTableNode * pNode);
/*
 * Search a LinkTableNode from LinkTable
 * int Conditon(tLinkTableNode * pNode,void * args);
 */
tLinkTableNode * SearchLinkTableNode(tLinkTable *pLinkTable, int Conditon(tLinkTableNode * pNode, void * args), void * args);

/*
 * get LinkTableHead
 */
tLinkTableNode *GetLinkTableHead(tLinkTable *pLinkTable);
#endif //SOFTWARE2_LINKTABLE_H
