char* copia(char string1[], char string2[]){
    int i=0;

    while(string1[i] != '\0'){
        string2[i] = string1[i];
        i++;
    }
    string2[i] = '\0';
    return string2;
}

int lunghezza(char string[]){
    int i=0;
    while(string[i] != '\0')
        i++;
    return i-1;
}

int compara(char string1[], char string2[]){
    int i = 0;
    int l1 = lunghezza(string1);
    int l2 = lunghezza(string2);
    if(l1 != l2)
        return -1;
    while(string1[i] != '\0'){
        if(string1[i] != string2[i])
            return -1;
        i++;
    }
    return 0;
}

char* concatena(char string1[], char string2[]){
    int j;
    int dim = lunghezza(string1);

    for (j = 0; string2[j] != '\0'; ++j, ++dim)
        string1[dim] = string2[j];
    string1[dim] = '\0';
    return string1;
}

int contaChar(char string1[], char c){
  int dim = lunghezza(string1);
  int count = 0;
  for(int i=0; i<dim; ++i)
    if(string1[i] == c)
      ++count;
  return count;
}

void trovaChar(char string1[], char c){
  int dim = lunghezza(string1);
  int count[dim];
  int j=0;
  int k=0;
  for(int i=0; i<dim; ++i)
      if(string1[i] == c){
        count[j] = i;
        ++j;
      }
    printf("Carattere trovato in posizione: ");
    for(k = 0; k < j; ++k)
      printf( "[%i]", count[k]);
}

int strpos(char string1[], char string2[]){
  if(lunghezza(string1) < lunghezza(string2)){
    puts("La prima stringa deve essere più lunga!");
    return -1;
  }
  int dim1 = lunghezza(string1);
  int dim2 = lunghezza(string2);
  int count = 0;
  int k=0;
  printf("str1: %i  str2: %i\n", dim1, dim2);
  for(int i = 0; i < dim1; ++i){
    k = i;
    for(int j = 0; j < dim2; ++j){
      if(string1[k] == string2[j]){
        count++;
        k++;
      }
    }
  }
  printf("Count = %i\n", count);
  if(count == dim2)
    return 0;
  return -1;
}
