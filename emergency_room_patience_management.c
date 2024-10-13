#include <stdio.h>
#include <string.h>

typedef struct node_s
{
        char name[50];
        int severity;
} node_t;

node_t heap[100];
int heap_size = 0;

int parent(int i);
void heapify(int i);
void display_queue();
int left_child(int i);
int right_child(int i);
void extract_patient();
void swap(int i, int j);
void insert_patient(const char *name, int severity);
void update_patient_severity(const char *name, int severity);

int main()
{
        int option;
        char patient_name[50];
        int severity;

        insert_patient("Danny", 5);
        insert_patient("Jimmy", 7);
        insert_patient("Ishimwe", 3);
        insert_patient("Elise", 9);

        while (1)
        {
                printf("Enter 1 to display patients in the Emergency wait room.\n");
                printf("Enter 2 to extract the next patient for treatment.\n");
                printf("Enter 3 to update a patient's severity.\n");
                printf("Enter 4 to exit: ");
                scanf("%d", &option);
                printf("\n");

                switch (option)
                {
                case 1:
                {
                        display_queue();
                        printf("\n");
                        break;
                }
                case 2:
                {
                        extract_patient();
                        printf("\n");
                        break;
                }
                case 3:
                {
                        printf("Enter patient name: ");
                        scanf("%s", patient_name);
                        printf("Enter severity: ");
                        scanf("%d", &severity);
                        update_patient_severity(patient_name, severity);
                        printf("\n");
                        break;
                }

                default:
                        break;
                }

                if (option == 4)
                {
                        break;
                }
        }

        return 0;
}

void swap(int i, int j)
{
        node_t temp = heap[i];
        heap[i] = heap[j];
        heap[j] = temp;
}

int left_child(int i)
{
        return 2 * i + 1;
}

int right_child(int i)
{
        return 2 * i + 2;
}

int parent(int i)
{
        return (i - 1) / 2;
}

void heapify(int i)
{
        int left = left_child(i);
        int right = right_child(i);
        int largest = i;

        if (left < heap_size && heap[left].severity > heap[largest].severity)
        {
                largest = left;
        }

        if (right < heap_size && heap[right].severity > heap[largest].severity)
        {
                largest = right;
        }

        if (largest != i)
        {
                swap(i, largest);
                heapify(largest);
        }
}

void insert_patient(const char *name, int severity)
{
        node_t new_node;
        strcpy(new_node.name, name);
        new_node.severity = severity;

        heap[heap_size] = new_node;
        int current = heap_size;
        heap_size++;

        while (current != 0 && heap[current].severity > heap[parent(current)].severity)
        {
                swap(current, parent(current));
                current = parent(current);
        }
}

void update_patient_severity(const char *name, int severity)
{
        for (int i = 0; i < heap_size; i++)
        {
                if (strcmp(heap[i].name, name) == 0)
                {
                        heap[i].severity = severity;
                        heapify(i);
                        break;
                }
        }
}

void display_queue()
{
        node_t temp_heap[100];
        memcpy(temp_heap, heap, heap_size * sizeof(node_t));

        for (int i = 0; i < heap_size - 1; i++)
        {
                for (int j = 0; j < heap_size - i - 1; j++)
                {
                        if (temp_heap[j].severity < temp_heap[j + 1].severity)
                        {
                                node_t temp = temp_heap[j];
                                temp_heap[j] = temp_heap[j + 1];
                                temp_heap[j + 1] = temp;
                        }
                }
        }

        for (int i = 0; i < heap_size; i++)
        {
                printf("%s - %d\n", temp_heap[i].name, temp_heap[i].severity);
        }
}

void extract_patient()
{
        if (heap_size == 0)
        {
                printf("No patients in the Emergency room.\n");
                return;
        }

        printf("Patient to treat: %s\n", heap[0].name);
        heap[0] = heap[heap_size - 1];
        heap_size--;
        heapify(0);
}