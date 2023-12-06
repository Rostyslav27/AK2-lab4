#include <linux/list.h>
#include <linux/ktime.h>

struct hello_data {
	struct list_head list;
	ktime_t timestamp_start;
	ktime_t timestamp_end;
};

void print_hello(unsigned int counter_h1);