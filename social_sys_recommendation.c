#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100

typedef struct user_s
{
        int id;
        char name[50];
        struct user_s *connections[MAX_USERS];
} user_t;

user_t *users[MAX_USERS];
int user_count = 0;

user_t *create_user(const char *name);
void add_connection(user_t *user1, user_t *user2);
void display_connections(user_t *user);
void draw_tree(user_t *user, int depth);
void dfs(user_t *user, user_t *new_connections[]);
void recommend_connections(user_t *user);
user_t *search_user_by_name(const char *name);

int main()
{
        user_t *Sam = create_user("Sam");
        user_t *Pius = create_user("Pius");
        user_t *Magot = create_user("Magot");
        user_t *David = create_user("David");
        user_t *Pascal = create_user("Pascal");
        user_t *Isaiah = create_user("Isaiah");
        user_t *Abissa = create_user("Abissa");
        user_t *Jubril = create_user("Jubril");

        add_connection(Sam, Pius);
        add_connection(Sam, Magot);
        add_connection(Sam, Abissa);
        add_connection(Pius, David);
        add_connection(Pius, Jubril);
        add_connection(David, Isaiah);
        add_connection(Isaiah, Abissa);
        add_connection(Magot, Pascal);
        add_connection(Pascal, David);
        add_connection(Pascal, Isaiah);
        add_connection(Jubril, Abissa);

        printf("User Connections Graph:\n\n");
        draw_tree(Sam, 0);

        printf("\n");

        while (1)
        {
                printf("Enter a user to recommend connections for (e.g: Sam, Pius): \n");
                printf("NB: Start your input with capital letter\n");
                printf("Enter 'exit' to exit: ");
                char username[50];
                scanf("%s", username);
                if (strcmp(username, "exit") == 0)
                {
                        break;
                }

                printf("You entered user %s.\n", username);

                user_t *current_user = search_user_by_name(username);
                if (current_user == NULL)
                {
                        printf("User not found!\n");
                        continue;
                }

                recommend_connections(current_user);
                printf("\n");
        }

        return 0;
}

user_t *create_user(const char *name)
{
        user_t *new_user = (user_t *)malloc(sizeof(user_t));
        new_user->id = user_count;
        strcpy(new_user->name, name);
        for (int i = 0; i < MAX_USERS; i++)
        {
                new_user->connections[i] = NULL;
        }
        users[user_count] = new_user;
        user_count++;
        return new_user;
}

void add_connection(user_t *user1, user_t *user2)
{
        for (int i = 0; i < MAX_USERS; i++)
        {
                if (user1->connections[i] == NULL)
                {
                        user1->connections[i] = user2;
                        break;
                }
        }
}

void display_connections(user_t *user)
{
        printf("Connections for user %s:\n", user->name);
        for (int i = 0; i < MAX_USERS; i++)
        {
                if (user->connections[i] != NULL)
                {
                        printf("%s\n", user->connections[i]->name);
                }
        }
}

void draw_tree(user_t *user, int depth)
{
        for (int i = 0; i < depth; i++)
        {
                printf("   ");
        }
        printf("|-- %s\n", user->name);
        for (int i = 0; i < MAX_USERS; i++)
        {
                if (user->connections[i] != NULL)
                {
                        draw_tree(user->connections[i], depth + 1);
                }
        }
}

void dfs(user_t *user, user_t *new_connections[])
{
        for (int i = 0; i < MAX_USERS; i++)
        {
                if (user->connections[i] != NULL)
                {
                        for (int j = 0; j < MAX_USERS; j++)
                        {
                                if (new_connections[j] == NULL)
                                {
                                        new_connections[j] = user->connections[i];
                                        break;
                                }
                        }
                        dfs(user->connections[i], new_connections);
                }
        }
}

void recommend_connections(user_t *user)
{
        user_t *new_connections[MAX_USERS];
        for (int i = 0; i < MAX_USERS; i++)
        {
                new_connections[i] = NULL;
        }
        dfs(user, new_connections);
        printf("Recommendations for user %s:\n", user->name);
        for (int i = 0; i < MAX_USERS; i++)
        {
                if (new_connections[i] != NULL)
                {
                        int found = 0;
                        for (int j = 0; j < MAX_USERS; j++)
                        {
                                if (user->connections[j] == new_connections[i])
                                {
                                        found = 1;
                                        break;
                                }
                        }
                        if (!found)
                        {
                                printf("%s\n", new_connections[i]->name);
                        }
                }
        }
}

user_t *search_user_by_name(const char *name)
{
        for (int i = 0; i < MAX_USERS; i++)
        {
                if (users[i] != NULL && strcmp(users[i]->name, name) == 0)
                {
                        return users[i];
                }
        }
        return NULL;
}