#include <linux/module.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/kthread.h>
#include <linux/random.h>
#include <linux/slab.h>
#include <linux/kernel.h>
#include <linux/sched/signal.h>

int threads_index = 0;
#define task_max_size 256
struct task_struct* tasks[task_max_size];

static int thread_fn(void *data)
{
	int* thread_id =(int*)data;

	int i;
	get_random_bytes(&i, sizeof(i));
	i = i % (5000 + 1 - 2000) + 2000;

	// Allow the SIGKILL signal
	allow_signal(SIGKILL);
	while (!kthread_should_stop())
	{
		pr_info("[%s]:[thread_fn] Id: %d start\n", KBUILD_MODNAME, *thread_id);

		pr_info("[%s]:[thread_fn] Id: %d thread will sleep for %d ms \n", KBUILD_MODNAME, *thread_id, i);
		msleep(i);
		pr_info("[%s]:[thread_fn] Id: %d finish\n", KBUILD_MODNAME, *thread_id);
	}
	do_exit(0);
	return 0;
}

static int __init my_init(void)
{
	pr_info("[%s]:my_init\n", KBUILD_MODNAME);

	int cpu=0;
	for_each_online_cpu(cpu){
		pr_info("[%s]:my_for_each_cpu: %d \n", KBUILD_MODNAME, cpu);

		int *arg_for_thread=kmalloc(sizeof(int*),GFP_KERNEL);
		*arg_for_thread = cpu;

		struct task_struct *thread = kthread_create(thread_fn,arg_for_thread,"thread_%d\n", cpu);
		if (!IS_ERR(thread)) {

		}else{
			pr_err("[%s]:err when creating thread on cpu: %d\n", KBUILD_MODNAME, cpu);
		}

		tasks[threads_index] = thread;
		threads_index++;
	//	kthread_bind(thread, cpu);
		wake_up_process(thread);
		kfree(arg_for_thread);
	}

	return 0;
}

static void __exit my_exit(void){
	pr_info("[%s]:my_exit\n", KBUILD_MODNAME);
	int i=0;
	for(; i < threads_index; i++)
	{
		kthread_stop(tasks[i]);
	}
}

module_init(my_init);
module_exit(my_exit);
MODULE_AUTHOR("Paulo Almeida");
MODULE_LICENSE("GPL v2");
