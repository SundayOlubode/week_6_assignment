#include <stdio.h>

int unique_key = 0;

typedef struct product_s
{
	int id;
	char name[50];
	int price;
	int quantity;
	struct product_s *parent;
	struct product_s *left;
	struct product_s *right;
} product_t;

product_t *root = NULL;

int main()
{
	int choice;
	root = add_product("Iyange Apple", 1000, 2);
	add_product("Mineche", 50, 3);
	add_product("Imizuzu", 150, 2);
	add_product("Grape", 5000, 1);
	add_product("Samboza", 500, 2);

	while (1)
	{
		printf("Enter 1 to add a new product.\n");
		printf("Enter 2 to search for a product by name.\n");
		printf("Enter 3 to buy a product.\n");
		printf("Enter 4 to stock a product.\n");
		printf("Enter 5 to display all products in ascending order.\n");
		scanf("%d", &choice);

		switch (choice)
		{
		case 1:
		{
			char name[50];
			int price;
			int quantity;
			printf("Enter product name: ");
			scanf("%s", name);
			printf("Enter product price: ");
			scanf("%d", &price);
			printf("Enter product quantity: ");
			scanf("%d", &quantity);
			add_product(name, price, quantity);
			break;
		}
		case 2:
		{
			char name[50];
			printf("Enter product name: ");
			scanf("%s", name);
			product_t *product = search_product_by_name(name);
			if (product != NULL)
			{
				printf("Product ID: %d\n", product->id);
				printf("Product Name: %s\n", product->name);
				printf("Product Price: RFW %d\n", product->price);
				printf("Product Quantity: %d\n", product->quantity);
			}
			else
			{
				printf("Product not found!\n");
			}
			break;
		}
		case 3:
		{
			char name[50];
			int quantity;
			printf("Enter product name: ");
			scanf("%s", name);
			printf("Enter quantity: ");
			scanf("%d", &quantity);
			product_t *product = decrement_product_quantity(name, quantity);
			if (product != NULL)
			{
				printf("Product ID: %d\n", product->id);
				printf("Product Name: %s\n", product->name);
				printf("Product Price: RFW %d\n", product->price);
				printf("Product Quantity: %d\n", product->quantity);
			}
			else
			{
				printf("Product not found!\n");
			}
			break;
		}
		case 4:
		{
			char name[50];
			int quantity;
			printf("Enter product name: ");
			scanf("%s", name);
			printf("Enter quantity: ");
			scanf("%d", &quantity);
			product_t *product = update_product_quantity(name, quantity);
			if (product != NULL)
			{
				printf("Product ID: %d\n", product->id);
				printf("Product Name: %s\n", product->name);
				printf("Product Price: RFW %d\n", product->price);
				printf("Product Quantity: %d\n", product->quantity);
			}
			else
			{
				printf("Product not found!\n");
			}
			break;
		}
		case 5:
		{
			display_product_asc(root);
			break;
		}

		default:
			break;
		}
	}
}

product_t *add_product(const char *name, const int price, const int quantity)
{
	product_t *new_product = (product_t *)malloc(sizeof(product_t));
	new_product->id = unique_key++;
	strcpy(new_product->name, name);
	new_product->price = price;
	new_product->quantity = quantity;
	new_product->parent = NULL;
	new_product->left = NULL;
	new_product->right = NULL;

	if (root == NULL)
	{
		root = new_product;
	}
	else
	{
		product_t *current = root;
		product_t *parent = NULL;
		while (current != NULL)
		{
			parent = current;
			if (strcmp(name, current->name) < 0)
			{
				current = current->left;
			}
			else
			{
				current = current->right;
			}
		}
		new_product->parent = parent;
		if (strcmp(name, parent->name) < 0)
		{
			parent->left = new_product;
		}
		else
		{
			parent->right = new_product;
		}
	}

	return root;
}

product_t *search_product_by_name(const char *name)
{
	product_t *current = root;
	while (current != NULL && strcmp(name, current->name) != 0)
	{
		if (strcmp(name, current->name) < 0)
		{
			current = current->left;
		}
		else
		{
			current = current->right;
		}
	}

	return strcmp(name, current->name) != 0 ? NULL : current;
}

product_t *update_product_quantity(const char *name, const int quantity)
{
	product_t *product = search_product_by_name(name);
	if (product != NULL)
	{
		product->quantity = quantity;
	}

	return product;
}

product_t *decrement_product_quantity(const char *name, const int quantity)
{
	product_t *product = search_product_by_name(name);
	if (product != NULL)
	{
		if (product->quantity <= 0)
		{
			printf("Product already out of stock.\n");
			return product;
		}
		if (product->quantity < quantity)
		{
			printf("Quantity to buy is more than the available quantity.\n");
			printf("Available quantity: %d\n", product->quantity);
			return product;
		}
		product->quantity -= quantity;
	}

	return product;
}

product_t *update_product_price(const char *name, const int price)
{
	product_t *product = search_product_by_name(name);
	if (product != NULL)
	{
		product->price = price;
	}

	return product;
}

void display_product_asc(product_t *root)
{
	if (root != NULL)
	{
		display_product_asc(root->left);
		printf("Product ID: %d\n", root->id);
		printf("Product Name: %s\n", root->name);
		printf("Product Price: %d\n", root->price);
		printf("Product Quantity: %d\n", root->quantity);
		display_product_asc(root->right);
	}
}

void display_out_of_stock_products(product_t *root)
{
	if (root != NULL)
	{
		display_out_of_stock_products(root->left);
		if (root->quantity <= 0)
		{
			printf("Product ID: %d\n", root->id);
			printf("Product Name: %s\n", root->name);
			printf("Product Price: %d\n", root->price);
			printf("Product Quantity: %d\n", root->quantity);
		}
		display_out_of_stock_products(root->right);
	}
}