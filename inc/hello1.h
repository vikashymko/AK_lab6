#ifndef HELLO1_H
#define HELLO1_H

#include <linux/list.h>
#include <linux/ktime.h>

struct hello_data {
	struct list_head list;
	ktime_t start_time;
	ktime_t end_time;
};

void print_hello(int count);

#endif
