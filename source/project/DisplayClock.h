//
// Created by Phan Linh on 1/12/2024.
//

#ifndef DISPLAYCLOCK_H
#define DISPLAYCLOCK_H

#include "ProjectPrivate.h"
#include <stdio.h>

static char hour = HOUR;
static char minute = MINUTE;
static char second = SECOND;
char buffer[100];

void ProjectDisplayClock(void);
void InitDisplayClock(long timer1_period);
void DisplayClock(void);

#endif //DISPLAYCLOCK_H
