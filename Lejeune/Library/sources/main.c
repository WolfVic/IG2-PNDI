#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "../headers/classificationStatistics.h"
#include "../headers/library.h"

#define NB_MAX NB_USERS * NB_FOLDERS

void displayClassName();

void main(void)
{
  // Phase 1
  printf("Debut phase 1\n");
  errno_t err = extractData();

  if (err == 0) 
  {
    // Phase 2
    printf("\n\n");
    printf("Debut phase 2\n");
    err = createModels();

    if (err == 0) 
    {
      // Phase 3
      printf("\n\n");
      printf("Debut phase 3\n");
      int realClasses[NB_MAX];
      int estimateClasses[NB_MAX];
      int nbTests = 0;

      err = useModel(&nbTests, realClasses, estimateClasses);
      if (err == 0) 
      {
        printf("\n\n");
        displayClassName();
        printf("\n");
        printf("Statistiques: \n");
        displayResultForEachClass(realClasses, estimateClasses, nbTests);
        printf("\n");
        displayAccuracy(realClasses, estimateClasses, nbTests);
        printf("\n");
        displayClass(realClasses, estimateClasses, nbTests);
      }
      else 
      {
        printf("Erreur: %d", err);
      }
    }
    else 
    {
      printf("Erreur: %d", err);
    }
  }
  else 
  {
    printf("Erreur: %d", err);
  }
}

void displayClassName() {
  char movements[][11] = { "Downstairs", "Upstair", "Jogging", "Sitting", "Standing", "Walking" };
  printf("Correspondance des classes : \n");
  for (int i = 0; i < NB_MODELS; i++) {
    printf(" - Classe %d : %s\n", i + 1, movements[i]);
  }
}