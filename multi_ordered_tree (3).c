//
// AED, January 2022
//
// Solution of the second practical assignement (multi-ordered tree)
//
// Victor Melo 101099   Airton Moreira 100480
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AED_2021_A02.h"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"
//
// the custom tree node structure
//
// we want to maintain three ordered trees (using the same nodes!), so we need three left and three right pointers
// so, when inserting a new node we need to do it three times (one for each index), so we will end upo with 3 three roots
//

int PERSON_COUNTER = 1;

typedef struct tree_node_s
{
  char name[MAX_NAME_SIZE + 1];                         // index 0 data item
  char zip_code[MAX_ZIP_CODE_SIZE + 1];                 // index 1 data item
  char telephone_number[MAX_TELEPHONE_NUMBER_SIZE + 1]; // index 2 data item
  char nif[MAX_TELEPHONE_NUMBER_SIZE - 1];              // index 2 data item
  struct tree_node_s *left[4];                          // left pointers (one for each index) ---- left means smaller
  struct tree_node_s *right[4];                         // right pointers (one for each index) --- right means larger
} tree_node_t;

//
// the node comparison function (do not change this)
//

int compare_tree_nodes(tree_node_t *node1, tree_node_t *node2, int main_idx)
{
  int i, c;

  for (i = 0; i < 4; i++)
  {
    if (main_idx == 0)
      c = strcmp(node1->name, node2->name); // strcmp compare to sterings if they are iqual this function return 0
    else if (main_idx == 1)
      c = strcmp(node1->zip_code, node2->zip_code);
    else if (main_idx == 2)
      c = strcmp(node1->telephone_number, node2->telephone_number);
    else
      c = strcmp(node1->nif, node2->nif);

    if (c != 0)
      return c;                                    // different on this index, so return
    main_idx = (main_idx == 3) ? 0 : main_idx + 1; // advance to the next index
  }
  return 0;
}

//
// tree insertion routine (place your code here)
//

// inputs
// no return value,
// root , usinng call by pointer , pointer to the node we add to the tree
// order criterion index

void tree_insert(tree_node_t **link, tree_node_t *parent, int tree_index) // parent here could be the tree_node *node (just name ch)
{
  if (*link == NULL)
  {                 // verifica se a arvore esta vazia (criada corretamente)
    *link = parent; // executada somente no inicio da funcao, ou quando vamos juntar um novo no!
    return;
  }
  int c = compare_tree_nodes(*link, parent, tree_index); // c give us the order
  // link==node
  // c==0 node is equal , cant appen
  // C<0 node 1  aparece antes de node 2 na sequencia
  // C>0 node1 aparece depois de node 2 na sequencia
  //  else if (tree_index <= (*link)->tree_index)
  if (c > 0)                                                       // TESTAR SE FUNCIONA~
    tree_insert(&((*link)->left[tree_index]), parent, tree_index); // call by pointer - aceder o valor da variavel apontada no interior da funcao.
  else
    tree_insert(&((*link)->right[tree_index]), parent, tree_index);
}

//
// tree search routine (place your code here)
//

tree_node_t *find(tree_node_t **link, tree_node_t *data, int tree_index)
{
  int c = compare_tree_nodes(*link, data, tree_index);
  if (*link == NULL || c == 0)
    return *link;
  if (c > 0)
    return find(&((*link)->left[tree_index]), data, tree_index);
  else
    return find(&((*link)->right[tree_index]), data, tree_index);
}

//
// tree depdth
//

int tree_depth(tree_node_t **link, int tree_index)
{

  if (*link == NULL)
    return 0;
  if (link == NULL)
    return 0;

  int altesq = tree_depth(&((*link)->left[tree_index]), tree_index);
  int altdire = tree_depth(&((*link)->right[tree_index]), tree_index);

  if (altesq > altdire)
    return (altesq + 1);
  else
    return (altdire + 1);
}

//
// list, i,e, traverse the tree (place your code here)
//

// versao 1 imput things
// primeiro argumento (pointeiro para a raiz  (pointer to root node)) ?
// criterio de ordem (0,1,2 ) nome , zip code or telefone number ( inteiro )
// versao completa---
// alll of version 1 and an interger to helo with the position index in order sequence  (return value ?)
//
/// quais argumentos, o que devolve , como imprime , (como temos o numero de ordem pode ser feito numa versao final )
void list(tree_node_t *link, int tree_index)
{
  if (link == NULL)
    return;

  list(link->left[tree_index], tree_index);                    // visita o filho esq
  printf("\n Person #%d \n", PERSON_COUNTER++);                // imprime a pessoa
  printf("Name ------ %s\n", link->name);                      // imprime a info nome da link
  printf("Zip code ------ %s\n", link->zip_code);              // imprime a info zip_code da link
  printf("Telephone number --- %s\n", link->telephone_number); // imprime a info telephone_number da link
  printf("NISS --- %s\n", link->nif);                          // imprime a info niss da link
  list(link->right[tree_index], tree_index);                   // visita o filho dir
}

void list_find(tree_node_t *link, int tree_index, char *search,int option)
{
  if (link == NULL)
    return;

  
  list_find(link->left[tree_index], tree_index, search,option);                    // visita o filho esq
  
  int comp;
  if (option==1){
    comp = strcmp (link->nif,search);
  }
  else if(option==0){
      comp = strcmp (link->zip_code,search);
  }
  else{
    char copiedname[strlen(link->name)];
    strcpy(copiedname,link->name);
    char test[strlen(search)];
    comp = strcmp (link->name,search);

    if (comp!=0)
    {
      for (int  i = 0; i < strlen(search); i++)
    {
      test[i]=copiedname[i];
    
    }
     comp=strcmp (test,search); 
    }

  }
 
  
  if (comp==0)
    {
      
      printf("\n Person #%d \n", PERSON_COUNTER++);                // imprime a pessoa
      
       if (option==2){
        printf("Name ------ "ANSI_COLOR_RED  "%s\n" ANSI_COLOR_RESET , link->name);

      }
      else
      {
        printf("Name ------ %s\n", link->name);                      // imprime a info nome da link

      }
      
      
       if (option==0){
        printf("Zip code------ "  ANSI_COLOR_RED  "%s\n" ANSI_COLOR_RESET , link->zip_code);
      }
      else  {
         printf("Zip code --- %s\n", link->zip_code);
      }
      //printf("Zip code ------ %s\n", link->zip_code);              // imprime a info zip_code da link
      printf("Telephone number --- %s\n", link->telephone_number); // imprime a info telephone_number da link
      if (option==1){
        printf("NISS --- " ANSI_COLOR_RED  "%s \n" ANSI_COLOR_RESET , link->nif);
      }
      else{
         printf("NISS --- %s\n", link->nif);
      }
      
                  
    }
 
  list_find(link->right[tree_index], tree_index, search,option);                   // visita o filho dir
}

//
// main program
//

int main(int argc, char **argv)
{
  // Printing everything into a file!
  
  FILE *file_ct;
  FILE *file_st;
  FILE *file_td;
  FILE *file_tdWpersons;
  //freopen("multi_ordered_tree_times.txt", "w", stdout);

  double dt;

  // process the command line arguments
  if (argc < 3)
  {
    fprintf(stderr, "Usage: %s student_number number_of_persons [options ...]\n", argv[0]);
    fprintf(stderr, "Recognized options:\n");
    fprintf(stderr, "  -list[N]            # list the tree contents, sorted by key index N (the default is index 0)\n");
    // place a description of your own options here
    fprintf(stderr, "  -zip [N]             # list all person with a given zip code\n");
    fprintf(stderr, "  -name [N]             # list people with the given name \n");
    fprintf(stderr, "  -nif [N]             # list the  person who has the given nif code\n");
    return 1;
  }
  int student_number = atoi(argv[1]);
  if (student_number < 1 || student_number >= 1000000)
  {
    fprintf(stderr, "Bad student number (%d) --- must be an integer belonging to [1,1000000{\n", student_number);
    return 1;
  }
  int n_persons = atoi(argv[2]);
  if (n_persons < 3 || n_persons > 10000000)
  {
    fprintf(stderr, "Bad number of persons (%d) --- must be an integer belonging to [3,10000000]\n", n_persons);
    return 1;
  }
  // generate all data
  tree_node_t *persons = (tree_node_t *)calloc((size_t)n_persons, sizeof(tree_node_t)); // calloc arguments 0- numerber of elements(i.e,nodes )  1 size in bytes of each elements
                                                                                        // this creat all nodes we need and put zero to not have trash
  if (persons == NULL)
  {
    fprintf(stderr, "Output memory!\n");
    return 1;
  }
 
  aed_srandom(student_number);
  for (int i = 0; i < n_persons; i++)
  {
    random_name(&(persons[i].name[0]));
    random_zip_code(&(persons[i].zip_code[0]));
    random_telephone_number(&(persons[i].telephone_number[0]));
    random_nif(&(persons[i].nif[0]));
    for (int j = 0; j < 4; j++)
      persons[i].left[j] = persons[i].right[j] = NULL; // make sure the pointers are initially NULL
  }
  // create the ordered binary trees
  dt = cpu_time();
  tree_node_t *roots[4]; // three indices, three roots
  for (int main_index = 0; main_index < 4; main_index++)
    roots[main_index] = NULL;
  for (int i = 0; i < n_persons; i++)
    for (int main_index = 0; main_index < 4; main_index++)
      tree_insert(&(roots[main_index]), &(persons[i]), main_index);

  // place your code here to insert &(persons[i]) in the tree with number main_index
  dt = cpu_time() - dt;
  
  file_ct = fopen("creation_time.txt", "a"); //output tree creation time
  printf("Tree creation time (%d persons): %.3es\n", n_persons, dt);
  fprintf(file_ct,"%d %.3es\n", n_persons, dt);
  fclose(file_ct);
  // search the tree

  //print to a file


  for (int main_index = 0; main_index < 4; main_index++)
  {
    dt = cpu_time();
    for (int i = 0; i < n_persons; i++)
    {
      tree_node_t n = persons[i]; // make a copy of the node data

      if (find(&roots[main_index], &n, main_index) != &(persons[i])) // place your code here to find a given person, searching for it using the tree with number main_index
      {
        fprintf(stderr, "person %d not found using index %d\n", i, main_index);
        return 1;
      }
    }
    dt = cpu_time() - dt;
     file_st = fopen("search_time.txt", "a"); //output tree creation time
    printf("Tree search time (%d persons, index %d): %.3es\n", n_persons, main_index, dt);
    fprintf(file_st,"%d %d %.3es\n", n_persons, main_index, dt);
    fclose(file_st);
  }
   
  // compute the largest tree depdth
  for (int main_index = 0; main_index < 4; main_index++)
  {
    file_tdWpersons = fopen("treeDepth_timeWpersons.txt", "a"); //output tree creation time
    file_td = fopen("treeDepth_time.txt", "a"); //output tree creation time

    dt = cpu_time();
    int depth = tree_depth(&(roots[main_index]), main_index); // place your code here to compute the depth of the tree with number main_index
    dt = cpu_time() - dt;
    
     printf("Tree depth for index %d: %d (done in %.3es)\n", main_index, depth, dt);
    fprintf(file_td,"%d %d %.3es\n", main_index, depth, dt);
    fclose(file_td);

    fprintf(file_tdWpersons,"%d %d %d %.3es\n",n_persons, main_index, depth, dt);
    fclose(file_tdWpersons);
    
  }
  // process the command line optional arguments


  for (int i = 3; i < argc; i++)
  {
   
    
    if (strncmp(argv[i], "-list", 5) == 0)
    { // list all (optional)
      int main_index = atoi(&(argv[i][5]));
      // main_index=mostrar por orden de :: 0-por nome 1-pelo zip code e 2-por telefone number 3- pelo NISS
      if (main_index < 0)
        main_index = 0;
      if (main_index > 3)
        main_index = 3;

      switch (main_index)
      {
      case 0:
        printf("\n          .....Ordered by Name.....\n ");
        break;
      case 1:
        printf("\n          .....Ordered by Zip Code.....\n ");
        break;
      case 2:
        printf("\n          .....Ordered by Telephone Number.....\n ");
        break;
      case 3:
        printf("\n          .....Ordered by NISS.....\n ");
        break;

      default:
        printf("\n          .....Ordered by NISS.....\n");
        break;
      }

   
       (void)list(&persons[0], main_index);
  
    }

    //0 for zip code
    //1 for niss
    //2 for name
   
    if (strncmp(argv[i], "-zip", 5) == 0 && argc >4)
    {
      int len1 = strlen( argv[i+1]) + 1;
      char zipcode[len1];
      strcpy (zipcode, argv[i+1]);   // copy string from argv[i+1] to variable
      printf("\n --Desired zip %s--- \n",zipcode);

       (void)list_find(&persons[0], 0, zipcode,0);
    }
    if (strncmp(argv[i], "-niss", 5) == 0 && argc >4)
    {
     printf("\n --Desired niss %s--- \n",argv[i+1]);
      (void)list_find(&persons[0], 0, argv[i+1],1);
    }
    if (strncmp(argv[i], "-name", 5) == 0 && argc >4)
    {
     printf("\n --Desired name %s--- \n",argv[i+1]);
      (void)list_find(&persons[0], 0, argv[i+1],2);
    }

   
  }
  // clean up --- don't forget to test your program with valgrind, we don't want any memory leaks
  free(persons);
  return 0;
}
