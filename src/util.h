#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <util.h>
#include <map>

int error_output(int error_num,string error_info);

void read_config(const char* path);
