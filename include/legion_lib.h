typedef struct node_t
{
	int val;
	struct node_t* head;
	struct node_t* next;
}node;

void init_legion_linked_list(node* list);
void legion_print_list(node * head);
void legion_push_to_end(node* head, int val);
void legion_push_to_front(node** head, int val);
int legion_pop(node** head);
int legion_remove_last(node* head);
int legion_remove_by_index(node** head, int n);
int legion_remove_by_value(node* list, void* val);