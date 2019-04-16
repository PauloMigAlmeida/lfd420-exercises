#include <linux/module.h>
#include <linux/init.h>
#include <linux/list.h>

typedef struct island
{
	char* name;
	struct list_head list;
} island;

extern void iterate_list(struct list_head* list);

static int __init my_init(void)
{
	pr_info("lab6-5: Hello");

	pr_info("lab6-5: Creating a doubly linked-list and adding 3 items");
	LIST_HEAD(mylinkedlist) ;
	island rangitoto ={ .name="Rangitoto", .list=LIST_HEAD_INIT(rangitoto.list) };
	island tiritiri ={ .name="tiritiri", .list=LIST_HEAD_INIT(tiritiri.list) };
	island waiheke ={ .name="waiheke", .list=LIST_HEAD_INIT(waiheke.list) };

	list_add(&rangitoto.list, &mylinkedlist);
	list_add_tail(&tiritiri.list, &mylinkedlist);
	list_add_tail(&waiheke.list, &mylinkedlist);

	iterate_list(&mylinkedlist);
	return 0;
}

static void __exit my_exit(void)
{
	pr_info("lab6-5: Bye");
}

void iterate_list(struct list_head* list)
{
	struct list_head* pos;
	island *ptr;
	list_for_each(pos,list){
		pr_info("lab6-5: surfing the linked list next = %p and prev = %p\n" ,
				pos->next,
				pos->prev);
		ptr = list_entry(pos, island, list);
		pr_info("lab6-5: name: %s", ptr->name);
	}
	pr_info("lab6-5: name: %s", ptr->name);
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("Paulo");
MODULE_LICENSE("GPL v2");
