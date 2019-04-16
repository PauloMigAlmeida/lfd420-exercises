#include <linux/module.h>
#include <linux/sched.h>
#include <linux/init.h>
#include <linux/oom.h>

static int __init my_init(void)
{
	struct task_struct *p;
	struct task_struct *t;

	for_each_process_thread(p, t) {
		pr_info("tgid=%d, pid=%d, comm=%s, state=%ld\n",
		                        t->tgid, t->pid, t->comm, t->state);

	}
	return 0;
}

static void __exit my_exit(void)
{
	pr_info("Bye");
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("Paulo");
MODULE_LICENSE("GPL v2");
