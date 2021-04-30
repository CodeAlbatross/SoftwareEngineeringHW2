//
// Created by admin on 2021/4/29.
//

#ifndef SOFTWARE2_MENU_H
#define SOFTWARE2_MENU_H
/* add cmd to menu */
int MenuConfig(char *cmd, char *desc, int (*handler)());

/* Menu Engine Execute */
int ExecuteMenu();
#endif //SOFTWARE2_MENU_H
