int main(int argc, char **argv)
{
    // Printing everything into a file!
    FILE *file_ct;
    FILE *file_st;
    FILE *file_td;
    FILE *file_tdWpersons;
    // freopen("multi_ordered_tree_times.txt", "w", stdout);
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

    dt = cpu_time() - dt;
    file_ct = fopen("creation_time.txt", "a"); // output tree creation time
    printf("Tree creation time (%d persons): %.3es\n", n_persons, dt);
    fprintf(file_ct, "%d %.3es\n", n_persons, dt);
    fclose(file_ct);
    // search the tree

    // print to a file
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
        file_st = fopen("search_time.txt", "a"); // output tree creation time
        printf("Tree search time (%d persons, index %d): %.3es\n", n_persons, main_index, dt);
        fprintf(file_st, "%d %d %.3es\n", n_persons, main_index, dt);
        fclose(file_st);
    }

    // compute the largest tree depdth
    for (int main_index = 0; main_index < 4; main_index++)
    {
        file_tdWpersons = fopen("treeDepth_timeWpersons.txt", "a"); // output tree creation time
        file_td = fopen("treeDepth_time.txt", "a");                 // output tree creation time

        dt = cpu_time();
        int depth = tree_depth(&(roots[main_index]), main_index); // place your code here to compute the depth of the tree with number main_index
        dt = cpu_time() - dt;

        printf("Tree depth for index %d: %d (done in %.3es)\n", main_index, depth, dt);
        fprintf(file_td, "%d %d %.3es\n", main_index, depth, dt);
        fclose(file_td);

        fprintf(file_tdWpersons, "%d %d %d %.3es\n", n_persons, main_index, depth, dt);
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

        // 0 for zip code
        // 1 for niss
        // 2 for name

        if (strncmp(argv[i], "-zip", 5) == 0 && argc > 4)
        {
            int len1 = strlen(argv[i + 1]) + 1;
            char zipcode[len1];
            strcpy(zipcode, argv[i + 1]); // copy string from argv[i+1] to variable
            printf("\n --Desired zip %s--- \n", zipcode);

            (void)list_find(&persons[0], 0, zipcode, 0);
        }
        if (strncmp(argv[i], "-niss", 5) == 0 && argc > 4)
        {
            printf("\n --Desired niss %s--- \n", argv[i + 1]);
            (void)list_find(&persons[0], 0, argv[i + 1], 1);
        }
        if (strncmp(argv[i], "-name", 5) == 0 && argc > 4)
        {
            printf("\n --Desired name %s--- \n", argv[i + 1]);

            (void)list_find(&persons[0], 0, argv[i + 1], 2);
        }
    }
    free(persons);
    return 0;
}