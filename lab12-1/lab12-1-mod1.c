#include <linux/module.h>
#include <linux/init.h>
#include <linux/mutex.h>

DEFINE_MUTEX(counter);
int my_incr = 0;

static int __init my_init(void)
{
	pr_info("[%s] :: Init\n", KBUILD_MODNAME);
	pr_info("[%s] :: Mutex init\n", KBUILD_MODNAME);
	mutex_init(&counter);
	return 0;
}

static void __exit my_exit(void)
{
	pr_info("[%s] :: Bye\n", KBUILD_MODNAME);
	mutex_destroy(&counter);
}

module_init(my_init);
module_exit(my_exit);
MODULE_AUTHOR("Paulo Almeida");
MODULE_LICENSE("GPL v2");

EXPORT_SYMBOL(counter);
EXPORT_SYMBOL(my_incr);
