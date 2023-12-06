#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/moduleparam.h>
#include <linux/errno.h>
#include <linux/ktime.h>
#include <linux/list.h>
#include <linux/slab.h>
#include "hello1.h"

MODULE_AUTHOR("Rostyslav Kunchiy <roctik4x@gmail.com>");
MODULE_DESCRIPTION("Hello, world in Linux Kernel Training");
MODULE_LICENSE("Dual BSD/GPL");

static LIST_HEAD(hello_data_head);

void print_hello(unsigned int counter_h1)
{

	int i;

	for (i = 0; i < counter_h1; i++) {
		struct hello_data *ptr = kmalloc(sizeof(*ptr), GFP_KERNEL);

		ptr->timestamp_start = ktime_get();
		pr_info("Hello, world!\n");
		ptr->timestamp_end = ktime_get();
		list_add(&ptr->list, &hello_data_head);
	}
}
EXPORT_SYMBOL(print_hello);

static int __init hello1_init(void)
{
	pr_info("hello1 module loded\n");

	return 0;
}

static void __exit hello1_exit(void)
{
	struct hello_data *ptr, *tmp;

	list_for_each_entry_safe(ptr, tmp, &hello_data_head, list) {
		ktime_t dur = ktime_sub(ptr->timestamp_end, ptr->timestamp_start);

		pr_info("Print duration: %lld ns\n", ktime_to_ns(dur));
		list_del(&ptr->list);
		kfree(ptr);
	}
}

module_init(hello1_init);
module_exit(hello1_exit);