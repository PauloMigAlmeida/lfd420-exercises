#include <linux/module.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/kthread.h>
#include <linux/random.h>
#include <linux/slab.h>
#include <linux/kernel.h>
#include <linux/sched/signal.h>

int threads_index = 0;
/* NR_CPUS is defined in kernel config as maximum possible,
   not the actual numdber */
struct task_struct* tasks[NR_CPUS];

static int thread_fn(void *data)
{
	int* thread_id =(int*)data;

	unsigned int i;
	get_random_bytes(&i, sizeof(i));
	i = i % (50000 + 1 - 20000) + 20000;

	do
	{
		pr_info("[%s]:[thread_fn] Id: %d start\n", KBUILD_MODNAME, *thread_id);

		pr_info("[%s]:[thread_fn] Id: %d thread will sleep for %d ms \n", KBUILD_MODNAME, *thread_id, i);
		msleep_interruptible(i);
		pr_info("[%s]:[thread_fn] Id: %d finish\n", KBUILD_MODNAME, *thread_id);
	}while (!kthread_should_stop());

	return 0;
}

static int __init my_init(void)
{
	pr_info("[%s]:my_init\n", KBUILD_MODNAME);

	int cpu=0;
	for_each_online_cpu(cpu){
		pr_info("[%s]:my_for_each_cpu: %d \n", KBUILD_MODNAME, cpu);

		int *arg_for_thread=kmalloc(sizeof(int),GFP_KERNEL);
		*arg_for_thread = cpu;

		struct task_struct *thread = kthread_create(thread_fn,arg_for_thread,"thread_%d\n", cpu);
		if (!IS_ERR(thread)) {
			tasks[threads_index] = thread;
			threads_index++;
			kthread_bind(thread, cpu);
			wake_up_process(thread);
		}else{
			pr_err("[%s]:err when creating thread on cpu: %d\n", KBUILD_MODNAME, cpu);
		}
	}

	return 0;
}

static void __exit my_exit(void){
	pr_info("[%s]:my_exit\n", KBUILD_MODNAME);
	int i=0;
	for(; i < threads_index; i++)
	{
		struct task_struct* task = tasks[i];
		pr_info("[%s]: trying to stop thread %d -> pid: %d tgid: %d\n", KBUILD_MODNAME, i, task->pid, task->tgid	);
		kthread_stop(tasks[i]);
	}
}

module_init(my_init);
module_exit(my_exit);
MODULE_AUTHOR("Paulo Almeida");
MODULE_LICENSE("GPL v2");
