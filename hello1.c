#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/slab.h>
#include <linux/list.h>
#include <linux/ktime.h>
#include "hello1.h"

MODULE_AUTHOR("IO-24 Viktoriia Shymko");
MODULE_DESCRIPTION("Hello1 Module");
MODULE_LICENSE("Dual BSD/GPL");

static LIST_HEAD(hello_list);
static int fail = 0;

void print_hello(int count)
{
    struct hello_data *data;
    int i;

    for (i = 0; i < count; i++) {
	fail++;
	if (fail == 5) {
		pr_err("Simulated kmalloc error on 5 iteration");
		return;
	}

	data = kmalloc(sizeof(*data), GFP_KERNEL);
	if (!data) {
            pr_err("Failed to allocate memory\n");
            return;
        }

        data->start_time = ktime_get();
        pr_info("Hello, world!\n");
	data->end_time = ktime_get();
	list_add_tail(&data->list, &hello_list);
    }
}

EXPORT_SYMBOL(print_hello);

static void __exit hello1_exit(void) {
	struct hello_data *data, *tmp;

	list_for_each_entry_safe(data, tmp, &hello_list, list) {
		pr_info("Time for printing: %lld ns\n", ktime_to_ns(data->end_time) - ktime_to_ns(data->start_time));
		list_del(&data->list);
		kfree(data);
	}
}

module_exit(hello1_exit);
