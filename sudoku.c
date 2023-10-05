#include "list.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int sudo[9][9];
} Node;

Node *createNode() {
  Node *n = (Node *)malloc(sizeof(Node));
  return n;
}

Node *copy(Node *n) {
  Node *new = (Node *)malloc(sizeof(Node));
  *new = *n;
  return new;
}

Node *read_file(char *file_name) {
  Node *n = createNode();
  FILE *file = fopen(file_name, "r");
  int i, j;
  for (i = 0; i < 9; i++) {
    for (j = 0; j < 9; j++) {
      if (!fscanf(file, "%d", &n->sudo[i][j]))
        printf("failed to read data!");
    }
  }

  fclose(file);
  return n;
}

void print_node(Node *n) {
  int i, j;
  for (i = 0; i < 9; i++) {
    for (j = 0; j < 9; j++)
      printf("%d ", n->sudo[i][j]);
    printf("\n");
  }
  printf("\n");
}

int is_valid(Node *n) {
  for (int i = 0; i < 9; i++) {
    int row_check[10] = {0};
    int col_check[10] = {0};
    for (int j = 0; j < 9; j++) {
      int row_num = n->sudo[i][j];
      int col_num = n->sudo[j][i];
      // check row
      if (row_num != 0 && row_check[row_num] == 1) {
        return 0;
      }
      row_check[row_num] = 1;

      // Check column
      if (col_num != 0 && col_check[col_num] == 1) {
        return 0;
      }
      col_check[col_num] = 1;
    }
  }

  for (int row_offset = 0; row_offset < 9; row_offset += 3) {
    for (int col_offset = 0; col_offset < 9; col_offset += 3) {
      int subgrid_check[10] = {0};
      for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
          int num = n->sudo[row_offset + i][col_offset + j];

          // Check subgrid
          if (num != 0 && subgrid_check[num] == 1) {
            return 0;
          }
          subgrid_check[num] = 1;
        }
      }
    }
  }

  return 1;
}

List *get_adj_nodes(Node *n) {
  List *adj_nodes = (createList());

  int row = -1; // Initialize to an invalid row
  int col = -1; // Initialize to an invalid col

  // Find the first empty cell (0) in the Sudoku board
  for (int i = 0; i < 9 && row == -1; i++) {
    for (int j = 0; j < 9 && col == -1; j++) {
      if (n->sudo[i][j] == 0) {
        row = i;
        col = j;
        break;
      }
    }
  }

  if (row == -1 || col == -1) {
    // If there are no empty cells, return an empty list (no adjacent nodes)
    return adj_nodes;
  }

  for (int num = 1; num <= 9; num++) {
    n->sudo[row][col] = num;
    if (is_valid(n)) {
      // If it's a valid placement, create a new node and add it to the linked
      // list
      Node *new_node = copy(n);
      pushBack(adj_nodes, new_node);
    }
    n->sudo[row][col] = 0; // Reset the cell back to empty
  }

  return adj_nodes;
}

int is_final(Node *n) { return 0; }

Node *DFS(Node *initial, int *cont) { return NULL; }

/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/