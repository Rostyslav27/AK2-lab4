#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/moduleparam.h>
#include <linux/errno.h>
#include "hello1.h"

MODULE_AUTHOR("Rostyslav Kunchiy <roctik4x@gmail.com>");
MODULE_DESCRIPTION("Hello, world in Linux Kernel Training");
MODULE_LICENSE("Dual BSD/GPL");

static unsigned int counter = 1;
module_param(counter, uint, 0644);
MODULE_PARM_DESC(counter, "How many times 'Hello, world!' will be displayed");

static int __init hello2_init(void)
{

	if (counter == 0 || (counter >= 5 && counter <= 10)) {
		pr_warn("Bad parameter. Continuing...\n");
	} else if (counter > 10) {
		pr_err("Parameter is too big.\n");
		return -EINVAL;
	}

	print_hello(counter);

	return 0;
}

static void __exit hello2_exit(void)
{
	pr_info("hello2 module removed\n");
}

module_init(hello2_init);
module_exit(hello2_exit);