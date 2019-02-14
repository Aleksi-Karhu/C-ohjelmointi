/*****************************************************************************/
/* CT60A0220 C-ohjelmoinnin ja testauksen periaatteet 
 * Tekijä: Aleksi Karhu
 * Opiskelijanumero: #######
 * Päivämäärä:31.3.2018
 * Yhteistyö ja lähteet, nimi ja yhteistyön muoto:
 */
/*****************************************************************************/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "nimilista.h"
#include "tuloslista.h"
#define TRUE 1

/* Pääohjelma, ylläpitää käyttöliittymää 
   palauttaa: 0 kun päättyy normaalisti
*/
int main(void) {
    char fileName[LEN];
    int choice;
    // Muuttujat linkityille listoille
    nameitem *nameList = NULL;
    resultitem *resultList = NULL;
	//resultFirst muuttujaan tallennetaan listan alku
	resultitem *resultFirst = NULL;
    int count = 0;
    
    printf("Tämä ohjelma tutkii nimitietoja sisältäviä tiedostoja.\n");
    while (TRUE){
        // Tulostaa valikon
        printf("1) Lue nimitiedosto\n");
        printf("2) Tulosta listassa olevat tiedot\n");
        printf("3) Analysoi tiedot\n");
        printf("4) Tulosta kaikki tulostiedot\n");
        printf("5) Tallenna kaikki tulostiedot tiedostoon\n");
        printf("6) Tyhjennä tuloslista\n");
        printf("0) Lopeta\n");
        printf("Anna valintasi: ");
        // Lukee käyttäjän valinnan ja suorittaa toiminnon
		scanf("%d", &choice);
		switch (choice){
            // Lukee data-tiedoston
	    	case 1:
                // Kysyy luettavan tiedoston nimen
                printf("Anna luettavan tiedoston nimi: ");
				scanf("%s",&fileName);
                // Lukee tiedoston ja asettaa tiedot nimilistaan 			
				nameList = readDataFile(fileName, nameList); 
				
            	break; 
            // Tulostaan nimilistan
            case 2: 
           	displayNames(nameList);
            	break; 
            // Analysoi nimilistan
            case 3: 
            	if (count < 1){
                    resultList = analyzeDataSet(nameList, resultList);
                    count = count + 1;
                    resultFirst = resultList;
                } else {
                    resultList = analyzeDataSet(nameList, resultFirst); 
                } 
            	break; 
            // Tulostaa analyysin tuloksen
            case 4: 
            	displayAnalysis(resultFirst); 
                break; 
            // Tallentaa analyysin tulokset tiedostoon    
            case 5:
            	saveResults(resultFirst);
            	break; 
            // Tyhjentää tulokset    
            case 6: 
            	deleteResultList(resultFirst); 
				count = 0;
				printf("Tuloslista tyhjennetty.");
            	break;
            // Lopettaa ohjelman
            case 0: 
            	printf("Kiitos ohjelman käytöstä.\n"); 
            	exit(0);  
            default: 
            	printf("Väärä valinta.\n"); 
            	break; 
    	} 
    }
	
return 0;
}



/*****************************************************************************/
/* eof */
