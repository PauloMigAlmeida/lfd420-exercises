#include <linux/module.h>
#include <linux/init.h>
#include <linux/mutex.h>

extern struct mutex counter;
extern int my_incr;

static int __init my_init(void)
{
	pr_info("[%s] :: Init\n", KBUILD_MODNAME);
	pr_info("[%s] :: Acquiring mutex lock\n", KBUILD_MODNAME);
	mutex_lock(&counter);
	pr_info("[%s] :: Mutex lock acquired\n", KBUILD_MODNAME);
	my_incr +=1;
	pr_info("[%s] :: Releasing mutex lock\n", KBUILD_MODNAME);
	mutex_unlock(&counter);
	pr_info("[%s] :: Mutex lock released. my_incr value is: %d\n", KBUILD_MODNAME, my_incr);
	return 0;
}

static void __exit my_exit(void)
{
	pr_info("[%s] :: Bye\n", KBUILD_MODNAME);
}

module_init(my_init);
module_exit(my_exit);
MODULE_AUTHOR("Paulo Almeida");
MODULE_LICENSE("GPL v2");
