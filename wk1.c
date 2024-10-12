#include <stdio.h>
#include <strings.h>
#define NAME_LENGTH 50
#define ARR_LENGTH 100
#define FILE_NAME "fullnames.txt"

void swap(char *arr[], int idx1, int idx2)
{
        char *temp = arr[idx1];
        arr[idx1] = arr[idx2];
        arr[idx2] = temp;
}

void selection_sort(char *arr[], int n)
{
        int i, j, min_idx;
        for (i = 0; i < n; i++)
        {
                min_idx = i;
                for (j = i + 1; j < n; j++)
                {
                        if (strcasecmp(arr[j], arr[min_idx]) < 0)
                        {
                                min_idx = j;
                        }
                }
                swap(arr, i, min_idx);
        }
}

void merge(char *arr[], int left, int mid, int right)
{
        int i, j, k;
        int n1 = mid - left + 1;
        int n2 = right - mid;
        char *left_arr[n1], *right_arr[n2];
        for (i = 0; i < n1; i++)
                left_arr[i] = arr[left + i];
        for (j = 0; j < n2; j++)
                right_arr[j] = arr[mid + 1 + j];
        i = 0;
        j = 0;
        k = left;
        while (i < n1 && j < n2)
        {
                if (strcasecmp(left_arr[i], right_arr[j]) <= 0)
                {
                        arr[k] = left_arr[i];
                        i++;
                }
                else
                {
                        arr[k] = right_arr[j];
                        j++;
                }
                k++;
        }
        while (i < n1)
        {
                arr[k] = left_arr[i];
                i++;
                k++;
        }
        while (j < n2)
        {
                arr[k] = right_arr[j];
                j++;
                k++;
        }
}

void merge_sort(char *arr[], int left, int right)
{
        if (left < right)
        {
                int mid = left + (right - left) / 2;
                merge_sort(arr, left, mid);
                merge_sort(arr, mid + 1, right);
                merge(arr, left, mid, right);
        }
}
void display_sort_options(int choice, int n, char *fullnames_ptr[])
{
        printf("\nChoose your preferred sorting algorithm:\n");
        printf("1. Selection Sort\n");
        printf("2. Merge Sort\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
                printf("\nYou chose Selection Sort!\n");
                selection_sort(fullnames_ptr, n);
                break;
        case 2:
                printf("\nYou chose Merge Sort!\n");
                merge_sort(fullnames_ptr, 0, n - 1);
                break;
        default:
                break;
        }
}
int main()
{
        int n = 0;
        int choice;
        char name[NAME_LENGTH];
        char add_name_choice;
        char fullnames[ARR_LENGTH][NAME_LENGTH];
        char *fullnames_ptr[ARR_LENGTH];
        FILE *fptr;
        fptr = fopen(FILE_NAME, "r");
        if (fptr == NULL)
        {
                printf("File %s does not exist\n", FILE_NAME);
        }
        while (fgets(fullnames[n], NAME_LENGTH, fptr))
        {
                fullnames_ptr[n] = fullnames[n];
                printf("%s", fullnames_ptr[n]);
                n++;
                continue;
        }
        fclose(fptr);
        printf("\nDo you want to add a new name to the names in the file?\n");
        printf("Enter (y) yes or (n): ");
        scanf("%c", &add_name_choice);

        switch (add_name_choice)
        {
        case 'y':
                printf("\nEnter full name: ");
                getchar();
                fgets(fullnames[n], NAME_LENGTH, stdin);
                fullnames_ptr[n] = fullnames[n];
                n++;
                break;
        default:
                break;
        }
        display_sort_options(choice, n, fullnames_ptr);
        fptr = fopen(FILE_NAME, "w");
        int i;
        for (int i = 0; i < n; i++)
        {
                fputs(fullnames_ptr[i], fptr);
        }
        fclose(fptr);
        printf("\nSorted names have been written to %s.\n", FILE_NAME);
}