struct node {
    char value;
    struct node *next;
    struct node *prev;
};

void push(char newItem);

char pop();

void insertAt(char newItem, int position);

void removeAt(int position);

void print();