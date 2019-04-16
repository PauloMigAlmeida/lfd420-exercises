#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

static int __init my_init(void)
{
	pr_info("Lab 6.1: Iterating through processes");

	struct task_struct *p;
	for_each_process(p) {
		pr_info("Process ID is %d state=%ld\n", p->tgid, p->state);
	}
	return 0;
}


static void __exit my_exit(void)
{
	pr_info("Lab 6.1: Done");
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("Paulo");
MODULE_LICENSE("GPL v2");
