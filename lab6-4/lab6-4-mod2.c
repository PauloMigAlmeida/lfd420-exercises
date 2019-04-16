#include <linux/module.h>
#include <linux/init.h>

extern int sum(int n1, int n2);

static int __init my_init(void)
{
	pr_info("lab6-4-mod2: Hello");
	pr_info("lab6-4-mod2: sum 2+2=%d", sum(2,2));
	return 0;
}

static void __exit my_exit(void)
{
	pr_info("lab6-4-mod2: Bye");
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("Paulo");
MODULE_LICENSE("GPL v2");
