// Assessment Goals:

// Implement heaps (max-heap)
// Traverse the heap
// Heapify the heap

// Tasks:

// Store patients in a max-heap based on the severity of their condition.
// Extract the patient with the highest severity for treatment.
// Update the severity as conditions change.
// Display the current queue of patients waiting for treatment.

// The program uses max-heap to store patients' details
// (name and severity at the scale of 0 to 10, whereby 0 is the minimum and 10 as the maximum).
// The program organizes patient's information in a maximum heap.
// The program allows to take the next patient from the heap (with highest severity).
// The next highest severity patient will be the root of the maximum heap.
// The submission contains the option that allows to update patients severity and every time the severity is updated, the maximum heap will be heapfyied.
// The program will equally be presenting the queue for patients in the order of how they are supposed to be attended.

// The program will be using the following functions:
// insert_patient - to insert a new patient into the heap
// update_patient_severity - to update the severity of a patient
// display_queue - display the current queue of patients waiting for treatment
// extract_patient - extract the patient with the highest severity for treatment
// heapify - to heapify the heap
// swap - to swap two elements in the heap
// left_child - to get the left child of a node
// right_child - to get the right child of a node
// parent - to get the parent of a node

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
        for (int i = 0; i < heap_size; i++)
        {
                printf("%s - %d\n", heap[i].name, heap[i].severity);
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