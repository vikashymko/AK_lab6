#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include "hello1.h"

MODULE_AUTHOR("IO-24 Viktoriia Shymko");
MODULE_DESCRIPTION("Hello2 Module");
MODULE_LICENSE("Dual BSD/GPL");

static int hello_count = 1;
module_param(hello_count, int, 0644);
MODULE_PARM_DESC(hello_count, "Number of times to print 'Hello, world!'");

static int __init hello2_init(void) {
	BUG_ON(hello_count < 0 || hello_count > 10);

	if (hello_count == 0 || (hello_count >= 5 && hello_count <= 10)) {
		pr_warn("Warning! hello_count is 0 or between 5 and 10.\n");
	}

	pr_info("Calling print_hello() from Hello1 Module.\n");
	print_hello(hello_count);
	return 0;
}

static void __exit hello2_exit(void)
{
    pr_info("Hello2 module unloaded.\n");
}

module_init(hello2_init);
module_exit(hello2_exit);
