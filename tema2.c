#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

//TASK1/2
typedef struct tree_node {
    char sisau;
    char jucator;
    bool is_end;
    char stare[3][3];
    struct tree_node *children[9];
    struct tree_node *parent;
} tree_node_t;

int verificare( char m[3][3], char x, int *ok){
    int i;
    for (i=0; i<3; i++){
        if(m[i][0] == m[i][1] && m[i][0] == m[i][2] && m[i][0] != '-'){
            if( m[i][0] == x)
              *ok = 1;
            return 1;
        }
    }
    for (i=0; i<3; i++){
        if(m[0][i] == m[1][i] && m[0][i] == m[2][i] && m[0][i] != '-'){
            if( m[0][i] == x)
              *ok = 1;
            return 1;
        }
    }
    if(m[0][0] == m[1][1] && m[0][0] == m[2][2] && m[0][0] != '-'){
        if( m[0][0] == x)
              *ok = 1;
        return 1;
    }
    if(m[0][2] == m[1][1] && m[0][2] == m[2][0] && m[0][2] != '-'){
        if( m[0][2] == x)
              *ok = 1;
        return 1;
    }
    return 0;
}

void create( tree_node_t *n, int k, char x){
  int m=0;
while( k > m){
        tree_node_t *new_node = (tree_node_t *)malloc(sizeof(tree_node_t));
        new_node->is_end = false;
        if( n->jucator == 'X')
            new_node->jucator = 'O';
        else
            new_node->jucator = 'X';
        int j;
        for( j = 0; j<9; j++)
            new_node->children[j] = NULL;
         new_node->parent = n;
         n->children[m] = new_node;
         new_node->sisau = 'F';
      m++;
      int l=1, i;
      for (i=0; i<3; i++){
        for (j=0; j<3; j++){
           if( new_node->parent->stare[i][j] != '-')
              new_node->stare[i][j] = new_node->parent->stare[i][j];
            else
            {  if(l==m ){
                  new_node->stare[i][j] = new_node->parent->jucator;
                  l++;
                }else{
                  new_node->stare[i][j] = new_node->parent->stare[i][j];   
                  l++;
                }
            }
        }
      }
      int ok = 0;
      if(verificare(new_node->stare, x, &ok) == 0){
       new_node->is_end = false;
       int z = k-1;
        create(new_node, z, x);
      }else
      {
         new_node->is_end = true;
      }
   }
}

void save_task1( tree_node_t *n, FILE *out, int m){
  int i,j,k;
  for (i=0; i<3; i++){
        if(m != 0)
          for( k=0; k<m; k++){
            fputc('\t', out);
          }
        for (j=0; j<3; j++){
            fputc(n->stare[i][j], out);
            if(j != 2)
              fputc(' ', out);
        }
        fputc('\n', out);
    }
    fputc('\n', out);
  for( k=0; k<9; k++){
      if(n->children[k] != NULL){
  
     save_task1(n->children[k], out, m+1);
      }
  }
}

void free_node_task1_2( tree_node_t *n){
  int k;
  for( k=0; k<9; k++){
      if(n->children[k] != NULL){
     free_node_task1_2(n->children[k]);
     free(n->children[k]);
      }
  }
}
// TASK2
void task2(tree_node_t *n, char x){
  int k;
  for( k=0; k<9; k++){
  int i=0;
  
  if(n->is_end == true){ //daca este nod frunza
    int ok = 0;
    if(verificare(n->stare, x, &ok) == 1){
        if(ok == 1)
          n->sisau = 'T';
    }
    else
      n->sisau = 'F';
  }

  if(n->children[0] != NULL && n->children[1] == NULL) //daca are un singur fiu
      n->sisau = n->children[0]->sisau;
   else
   {  if(n->children[0] != NULL && n->children[1] != NULL){

      if(n->jucator == x){
          n->sisau = 'F';
          while(n->children[i] != NULL){
              if(n->children[i]->sisau == 'T'){
                n->sisau = 'T';
                break;
              }
              i++;
          }
        }

        if(n->jucator != x){
          n->sisau = 'F';
          int k=0;
          while(n->children[i] != NULL){
              if(n->children[i]->sisau == 'T'){
                k++;
              }
              i++;
          }
          if( i == k){
            n->sisau = 'T';
          }
        }
   } 
   }
      if(n->children[k] != NULL){
        task2(n->children[k], x);
      } 
}
}

void save_task2( tree_node_t *n, FILE *out, int m){
  int k;
  if(m != 0)
    for( k=0; k<m; k++){
      fputc('\t', out);
    }
  fputc(n->sisau, out);
  fputc('\n', out);
  for( k=0; k<9; k++){
      if(n->children[k] != NULL){
        save_task2(n->children[k], out, m+1);
      }
  }
}

//TASK3 

typedef struct tree_node_3 {
    char jucator[3];
    bool is_end;
    int val;
    int nr_copii;
    struct tree_node_3 **children;
    struct tree_node_3 *parent;
} tree_node_3_t;

void free_node_task3( tree_node_3_t *n){
  int k;
  if( n->nr_copii == 0){
    return;
  }else{
  for( k=0; k<n->nr_copii; k++){  
     free_node_task3(n->children[k]);
     free(n->children[k]);
  }
  if( k == n->nr_copii)
       free(n->children);
  }
}

void save_task3( tree_node_3_t *n, FILE *out, int m){
  int k;
  if(m != 0)
    for( k=0; k<m; k++){
      fputc('\t', out);
    }
  fprintf(out, "%d", n->val);
  fputc('\n', out);
  if( n->nr_copii == 0)
     return;
  else{
  for( k=0; k<n->nr_copii; k++){
     save_task3(n->children[k], out, m+1);
  }
  }
}

int min( tree_node_3_t *n){
    int min = n->children[0]->val;
    int i;
    for( i = 1; i<n->nr_copii; i++)
       if(n->children[i]->val <= min)
         min = n->children[i]->val;
    return min;
}

int max( tree_node_3_t *n){
    int max = n->children[0]->val;
    int i;
    for( i = 1; i<n->nr_copii; i++)
       if(n->children[i]->val >= max)
         max = n->children[i]->val;
    return max;
}

void calc( tree_node_3_t *n){
  int k;
  if( n->nr_copii == 0){
    return;
  }else{
        for( k=0; k<n->nr_copii; k++){   
            calc(n->children[k]);
            if(strcmp(n->jucator, "max") == 0 )
                n->val = max(n);
            else
                n->val = min(n);
        }
  }
}


int main(int argc, char **argv)
{
    FILE *in = fopen(argv[2], "r"); 
/////////////////////////////////////// TASK 1 SI 2 /////////////////////////////////
   if ( strcmp(argv[1], "-c1") == 0 || strcmp(argv[1], "-c2") == 0){
    tree_node_t *root = (tree_node_t*)malloc(sizeof(tree_node_t));
    char c = fgetc(in), x;
    root->jucator = c;
    int j;
    for( j = 0; j<9; j++)
        root->children[j] = NULL;
    root->is_end = false;
    root->sisau =  'T';
    int k=0;
    fgetc(in);
    int i=0;
    for (i=0; i<3; i++){
        for (j=0; j<3; j++){
            x = fgetc(in);
            if( x != ' ' && x != '\n' && x != '\0' && x != '\r'){
              root->stare[i][j] = x;
            if( x == '-')
               k++;
            }else
                j--;
        }
    } 
    fclose(in);
    create(root, k, c);

    if ( strcmp(argv[1], "-c1") == 0){  // TASK 1
      FILE *out = fopen(argv[3], "w");
      save_task1(root, out, 0);
      fclose(out); 
      free_node_task1_2(root);
      free(root);
    }
    
    if ( strcmp(argv[1], "-c2") == 0){   //  TASK 2
      task2(root, c);
      FILE *out = fopen(argv[3], "w");
      save_task2(root, out, 0);
      fclose(out); 
      free_node_task1_2(root);
      free(root);
    }
   }
    
///////////////////////////////////////// TASK3 ///////////////////////////////////////////
if ( strcmp(argv[1], "-c3") == 0){
     tree_node_3_t ***v1; 
     tree_node_3_t ***v2;
    int l1, l2;

    tree_node_3_t *root = (tree_node_3_t*)malloc(sizeof(tree_node_3_t));
    char aux[1000];
    fgets(aux, 1000, in);
    int h = atoi(aux);
    fgetc(in);
    int o = 1;    
    char s[100];
    s[0] = fgetc(in);
    char x = fgetc(in);
    while(isdigit(x)){
      s[o++] = x;
      x = fgetc(in);
    }
    s[o] = '\0';
    int c = atoi(s);
    fgetc(in);

    strcpy(root->jucator,"max");
    root->nr_copii = c;
    root->val = 0;
    root->children = (tree_node_3_t**)calloc(c, sizeof(tree_node_3_t*));
    
    v1 = (tree_node_3_t***)malloc(sizeof(tree_node_3_t**));
    v1[0] = (tree_node_3_t**)malloc(sizeof(tree_node_3_t*));
    *v1[0] = root;
    l1 = 1;
    int i;
    for( i = 2; i<=h; i++){
      l2 = 0;
      v2 = (tree_node_3_t***)malloc(sizeof(tree_node_3_t**));
      int m;
      for( m = 0; m<l1; m++){
        tree_node_3_t *node = *v1[m];
        int j;
        for( j = 0; j<node->nr_copii; j++){
                fgetc(in);
                int o = 1;
                char s[100];
                s[0] = fgetc(in);
                char x = fgetc(in);
                while(isdigit(x)){
                    s[o++] = x;
                    x = fgetc(in);
                }
                s[o] = '\0';
                int c = atoi(s);
                fgetc(in);
              if( x == ')'){
                tree_node_3_t *new_node = (tree_node_3_t*)malloc(sizeof(tree_node_3_t));
                node->children[j] = new_node;
                if( i % 2 != 0)
                  strcpy(new_node->jucator,"max");
                else
                  strcpy(new_node->jucator,"min");
                new_node->nr_copii = c;
                new_node->children = (tree_node_3_t**)malloc(c* sizeof(tree_node_3_t*));
                new_node->parent = node;
                new_node->val = 0;
                new_node->is_end = false;
                 v2[l2] = (tree_node_3_t**)malloc(sizeof(tree_node_3_t*));
                *v2[l2] = new_node;
                l2++;
                v2 = (tree_node_3_t***)realloc(v2, (l2+1)* sizeof(tree_node_3_t**));
             }
             if( x == ']'){
               tree_node_3_t *new_node = (tree_node_3_t*)malloc(sizeof(tree_node_3_t));
                node->children[j] = new_node;
                if( i % 2 != 0)
                  strcpy(new_node->jucator,"max");
                else
                  strcpy(new_node->jucator,"min");
                new_node->nr_copii = 0;
                new_node->parent = node;
                new_node->val = c;
                new_node->is_end = true;
                 v2[l2] = (tree_node_3_t**)malloc(sizeof(tree_node_3_t*));
                *v2[l2] = new_node;
                l2++;
                v2 = (tree_node_3_t***)realloc(v2, (l2+1)* sizeof(tree_node_3_t**));
             }
        }
      }
      int j;
      for ( j=0; j<l1; j++){
       free(v1[j]);
      }
      free(v1);
      v1 = (tree_node_3_t***)malloc(l2* sizeof(tree_node_3_t**));
      for ( j=0; j<l2; j++){
        v1[j] = (tree_node_3_t**)malloc(sizeof(tree_node_3_t*));
      }
      l1 = l2;
      for ( j=0; j<l2; j++){
        *v1[j] = *v2[j];
      }
    for ( j=0; j<l2; j++){
         free(v2[j]);
      }
      free(v2);
}   
    int j;
    for ( j=0; j<l1; j++){
      free(v1[j]);
    }
    free(v1);
    fclose(in);

    calc(root);
    FILE *out = fopen(argv[3], "w");
    save_task3(root, out, 0);
    fclose(out); 
    free_node_task3(root);
    free(root);

}
    return 0;
}