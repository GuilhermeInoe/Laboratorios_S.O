#ifndef MONITOR_H
#define MONITOR_H

//Operações:

void init_monitor();
void destroy_monitor();
void monitor_write(void* index);
void monitor_read(void* index);

#endif
