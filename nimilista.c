/*****************************************************************************/
/* CT60A0220 C-ohjelmoinnin ja testauksen periaatteet 
 * Tekijä: Aleksi Karhu
 * Opiskelijanumero: 0452237
 * Päivämäärä:31.3.2018
 * Yhteistyö ja lähteet, nimi ja yhteistyön muoto:
 */
/*****************************************************************************/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "nimilista.h"

/* Tuhoaa nimilistan 
   parametrit: osoitin nimilistaan
*/
void deleteNameList(nameitem *head){
    nameitem *temp;
    
    // Käy läpi alkiot ja vapauttaa muistin
    while(head != NULL) {
        temp = head;
        head = temp -> next;
        free(temp);        
    }
}

/* Lukee käyttäjän antaman data-tiedoston ja luo linkitetyn nimilistan 
   parametrit: tiedostonimi ja osoitin nimilistaan
   palauttaa: osoitin nimilistaan 
 */
nameitem* readDataFile(char *fileName, nameitem *head) {
    char row[60];
    FILE *dataFile;
    int counter = 0;
    // Listan apumuuttujat, osoitin ja viimeinen alkio 
    nameitem *temp = NULL;
    nameitem *tail = NULL;
    
    // Avaa tiedoston
    dataFile = fopen(fileName, "r");
    if(dataFile == NULL) {
        printf("Tiedoston avaus ei onnistu.\n");
        return NULL;
    }
    
    // Varaa muistin dynaamisesti uudelle alkiolle
    temp = malloc(sizeof(nameitem));
    // Tyhjentää mahdollisen vanhan listan ja aloittaa uuden
    if(head != NULL) {
        printf("Poistetaan aiemmat tiedot ja luetaan uudet.\n");
        deleteNameList(head);
    }
    head = temp;
   	printf("Luetaan tiedosto %s.\n", fileName);
    // Lukee otsikkorivin, hylätään
    fgets(row, 59, dataFile);
    
    // Lukee kaikki rivit datatiedostosta
    while (fgets(row, 59, dataFile) != NULL){        
        // Asettaa luetut arvot muuttujiin
        sscanf(row, "%59[^;]; %d", temp -> name, &temp -> count);
        temp -> next = NULL;
        //printf("%s %d\n",temp -> name, temp -> id);
        counter = counter + 1;
        // Päivittää viimeisen alkion ja varaa tilaa seuraavalle.
        tail = temp;
        temp -> next = malloc(sizeof(nameitem));
        temp = temp -> next;
    }
    // Poistaa ylimääräisen alkion ja vapautaa muistin
    free(tail->next);
    tail->next = NULL;
    
    printf("Tiedosto %s luettu, %d nimiriviä.\n", fileName, counter);    
    
    // Sulkee tiedoston ja palauttaa listan
    fclose(dataFile);
    return head;
}


/* Tulostaa nimilistan näytölle
   parametrit: osoitin nimilistaan
*/
void displayNames(nameitem *head){
    nameitem *temp;
    
    temp = head;
    // Käy läpi listan ja tulostaa sen näytölle
    while(temp != NULL){
    	printf("%s %d\n",temp -> name, temp -> count);
    	temp = temp -> next;
    }
}

