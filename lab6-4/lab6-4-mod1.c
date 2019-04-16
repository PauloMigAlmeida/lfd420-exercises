#include <linux/module.h>
#include <linux/init.h>

static int __init my_init(void)
{
	pr_info("lab6-4-mod1: Hello");
	return 0;
}

static void __exit my_exit(void)
{
	pr_info("lab6-4-mod1: Bye");
}

static int sum(int n1, int n2){
	return n1 + n2;
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("Paulo");
MODULE_LICENSE("GPL v2");
EXPORT_SYMBOL(sum);
