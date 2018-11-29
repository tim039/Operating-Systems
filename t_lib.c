#include "t_lib.h"

//Running TCB pointer
struct tcb *running;

//Ready queue pointer
struct Queue *ready;


/**
*@brief Performs a swapcontext() between the calling thread and the next thread in ready queue
*
*@return VOID
*/
void t_yield()
{
	//Declare a temporary tcb pointer for swapping
	struct tcb *tmp;
	
	//Set the currently running tcb to temp
	tmp = running;
	
	//Dequeue the next thread in ready
	struct QNode *new_running = deQueue(ready);

	if(new_running != NULL)
	{
		//Set running to point to TCB of the QNode we just dequeued
		running = new_running->tcb;
		
		free(new_running);
		
		//Enqueue the TCB that is pointed to by temp to back of ready queue
		enQueue(ready, tmp);
		
		//Swapcontext between the TCB we just enqueued and the one running points to
		swapcontext(tmp->thread_context, running->thread_context);
	}
}

/**
*@brief Initializes the Thread Library by creating an empty ready queue and the main TCB
*
*@return VOID
*/
void t_init()
{
	//Initialize the ready queue
	ready = createQueue();
	
	//Allocate memory for the main TCB
	tcb *tmp = (tcb *) malloc(sizeof(struct tcb));
	
	//Set its fields
	tmp->thread_id = 0;
	tmp->thread_priority = 0;
	
	//Allocate memory for the context of the main thread
	ucontext_t *uc;
	uc = (ucontext_t *) malloc(sizeof(ucontext_t));
	
	//Get the context of main
	getcontext(uc);
	
	//Set the thread_context field of tmp
	tmp->thread_context = uc;
	
	//Set running to point to tmp
	running = tmp;
}

/**
*@brief Creates a new thread with given pri, id and fct, adding to end of ready queue
*
*@param *fct: a pointer to a void function to be run by the thread
*
*@param id: an integer signifying the id of the thread to be created
*
*@param pri: an integer signifying the priority of the given thread
*
*@return the id of the created thread
*/
void t_create(void (*fct)(int), int id, int pri)
{
	//Size for stack allocation
	size_t sz = 0x10000;

	//Define a new ucontext and tcb for our new thread
	ucontext_t *uc;
	tcb *new_tcb;
	
	//Allocate space on the heap
	uc = (ucontext_t *) malloc(sizeof(ucontext_t));

	//Grab the current context so we can modify it
	getcontext(uc);

	//Set the new thread context appropriately
	uc->uc_stack.ss_sp = malloc(sz);
	uc->uc_stack.ss_size = sz;
	uc->uc_stack.ss_flags = 0;
	uc->uc_link = running; 
	
	//Make the thread context using the ucontext we just set up
	makecontext(uc, (void (*)(void)) fct, 1, id);
	
	//Setup the TCB using the ucontext we just created
	new_tcb = (tcb *) malloc(sizeof(tcb));
	new_tcb->thread_id = id;
	new_tcb->thread_priority = pri;
	new_tcb->thread_context = uc;
	
	//Add the TCB to the back of our queue
	//This simultaneously creates a new QNode with our TCB and adds to the back
	enQueue(ready, new_tcb);
	
	//Return the thread id upon success or errno otherwise
	//Right now we will just return  the thread id always
	//return id;
}

/**
*@brief Frees all memory associated with any structures (TCB, Queue etc)
*
*@return VOID
*/
void t_shutdown()
{
	//Declare a temp TCB, QNode and Queue structure for freeing
	struct tcb *tmp;
	struct QNode *qntmp = ready->front;
	
	//Loop through the ready Queue and free everything associated
	while(qntmp != NULL)
	{
		//Grab the TCB associated with the QNode
		tmp = qntmp->tcb;
		
		//Free the thread context of the TCB and the TCB
		if(tmp->thread_id > 0) {free(tmp->thread_context->uc_stack.ss_sp);}
		free(tmp->thread_context);
		free(tmp);
		
		//Free the QNode
		free(qntmp);
		
		qntmp = qntmp->next;
	}
	
	//Free the TCB associated with whatever thread is pointed to by running
	tmp = running;
	if(tmp->thread_id > 0) {free(tmp->thread_context->uc_stack.ss_sp);}
	free(tmp->thread_context);
	free(tmp);
	
	//Free the Ready Queue itself
	free(ready);
}

/**
*@brief Terminates the calling thread and swaps context to the next thread in running queue
*
*@return VOID
*/
void t_terminate()
{
	//Declare a temporary tcb pointer for swapping
	struct tcb *tmp;
	struct QNode *qntmp;
	
	//Set the currently running tcb to temp
	tmp = running;
	
	//Free the memory associated with the running thread
	free(tmp->thread_context->uc_stack.ss_sp);
	free(tmp->thread_context);
	free(tmp);
	
	//Grab the thread at the head of the queue
	qntmp = deQueue(ready);
	
	//Set running to point to this TCB
	running = qntmp->tcb;
	
	free(qntmp);
	
	//setcontext() to the new running thread
	setcontext(running->thread_context);
}

/**
*@brief Creates a new linked list node to add to the queue of nodes
*
*@param tcb: A Thread control block referencing the thread associated with the node
*
*@return A pointer to the newly created QNode
*/ 
// A utility function to create a new linked list node. 
struct QNode *newNode(tcb *tcb)
{
	//Create a new QNode and allocate space for it
    struct QNode *temp = (struct QNode*)malloc(sizeof(struct QNode)); 
	
	//Set the TCB and next fields
    temp->tcb = tcb; 
    temp->next = NULL; 
	
	//Return the new node
    return temp;  
}

/**
*@brief A utility function that creates an empty Queue and allocates memory for it
*
*@return A pointer to the newly created Queue
*/
struct Queue *createQueue() 
{
	//Allocate memory for a new queue
	struct Queue *q = (struct Queue*)malloc(sizeof(struct Queue)); 
	
	//Set the head and tail pointers to NULL
    q->front = q->rear = NULL; 
	
	//Return the new queue object
    return q; 
}

/**
*@brief Adds a thread control block to the back of the queue
*
*@param *q: A pointer to the queue the user wishes to add to
*
*@param tcb: A Thread control block referencing the thread to add
*
*@return VOID
*/ 
void enQueue(struct Queue *q, tcb *tcb) 
{ 
    //Create a new node to add to the list
    struct QNode *temp = newNode(tcb); 
  
    //Check if the queue is empty, if so front and rear are the same
    if (q->rear == NULL) 
    {
       q->front = q->rear = temp; 
       return; 
    }
  
    //Otherwise add the new node to the end of the queue
    q->rear->next = temp; 
    q->rear = temp; 
}

/**
*@brief Pops a QNode from the front of the queue
*
*@param *q: A pointer to the queue the user wishes to remove from
*
*@return A pointer to the QNode returned
*/ 
struct QNode *deQueue(struct Queue *q) 
{ 
    //If the queue is empty return NULL
    if (q->front == NULL) 
	{
       return NULL; 
	}
  
    //Store previous front and move front one node ahead 
    struct QNode *temp = q->front; 
    q->front = q->front->next; 
  
    //If front becomes NULL, then change rear to NULL as well
    if (q->front == NULL)
	{		
       q->rear = NULL; 
	}
	
	//Return the node we removed
    return temp; 
}

int sem_init(sem_t **sp, int sem_count)
{
	//Allocate space for the semaphore
	*sp = malloc(sizeof(sem_t));
	
	//Set the count field
	(*sp)->count = sem_count;
	
	//Initialize the tcb queue
	(*sp)->q = createQueue();
}

void sem_wait(sem_t *s)
{
	//Inhibit Interrupts
	sighold();
	
	//Declare a temp TCB
	tcb *tmp;
	
	//Decrement the value of s
	s->count--;
	
	//If the value of s is negative, enqueue the calling TCB to s's queue
	//And context switch between the thread at the head of ready and the calling thread
	if(s->count < 0)
	{
		//Grab the TCB of the running thread
		tmp = running;
		
		//Add the calling TCB to the queue of S
		enQueue(s->q, tmp);
		
		//Dequeue the next thread in ready
		struct QNode *new_running = deQueue(ready);

		//Set running to point to TCB of the QNode we just dequeued
		running = new_running->tcb;
		
		//Free the QNode because running is simply a TCB
		free(new_running);
		
		//Swapcontext between the TCB we just enqueued and the one running points to
		swapcontext(tmp->thread_context, running->thread_context);
		
		//Allow Interrupts
		sigrelse();
		
		return;
	}
	
	//Otherwise simply return if the value of s >= 0
	else if(s->count >= 0)
	{
		//Allow Interrupts
		sigrelse();
		
		return;
	}
}

void sem_signal(sem_t *s)
{
	//Inhibit Interrupts
	sighold();
	
	//Increment the value of s
	s->count++;
	
	//Check if any threads are waiting on S
	//If one exists, enqueue it to the back of ready (MESA Semantics)
	//And continue execution with the calling thread
	if(s->count <= 0)
	{
		//Grab the node at the head of S's queue
		struct QNode *now_ready = deQueue(s->q);
		
		//Internal error checking
		if(now_ready == NULL)
		{
			printf("\nError: sem_signal is attempting to add a nonexistent thread to the ready queue. Check conditional logic\n");
		}
		
		//Enqueue now_ready to the back of the ready queue 
		enQueue(ready, now_ready->tcb);
		
		//Free the QNode
		free(now_ready);
		
		//Allow Interrupts
		sigrelse();
		
		return;
	}
	
	//Otherwise if no thread is waiting in S's queue, simply return
	else
	{
		//Allow Interrupts
		sigrelse();
		
		return;
	}

}

void sem_destroy(sem_t **s)
{
	//Loop through the Queue of S and free all nodes inside
	//Declare a temp TCB, QNode and Queue structure for freeing
	struct tcb *tmp;
	struct QNode *qntmp = (*s)->q->front;
	
	//Loop through the ready Queue and free everything associated
	while(qntmp != NULL)
	{
		//Grab the TCB associated with the QNode
		tmp = qntmp->tcb;
		
		//Free the thread context of the TCB and the TCB
		if(tmp->thread_id > 0) {free(tmp->thread_context->uc_stack.ss_sp);}
		free(tmp->thread_context);
		free(tmp);
		
		//Free the QNode
		free(qntmp);
		
		qntmp = qntmp->next;
	}
	
	//Free the queue itself
	free((*s)->q);
	
	//Free the semaphore itself
	free(*s);
	
	//Return
	return;
} 
