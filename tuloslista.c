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
#include "tuloslista.h"

/* Tuhoaa tuloslistan 
   parametrit: osoitin tuloslistaan
*/
void deleteResultList(resultitem *head){
    resultitem *temp;
    
    // Käy läpi alkiot ja vapauttaa muistin
    while(head != NULL) {
        temp = head;
        head = temp -> next;
        free(temp);        
    }
}

/* Tallentaa analyysin tulokset käyttäjän määräämään tiedostoon 
   parametrit: osoitin tuloslistaan
*/
void saveResults(resultitem *head){
    char fileName[LEN];
    FILE *resultFile;
    resultitem *temp;

    // Kysyy tiedostonimen käyttäjältä
    printf("Anna tallennettavan tulostiedoston nimi: ");
    scanf("%s", &fileName); 

    // Avaa tiedoston
    resultFile = fopen(fileName, "w");
    if(resultFile == NULL) {
        printf("Tiedoston avaus ei onnistu.\n");
        return;
    }
    
    
    temp = head;
    // Käy läpi tuloslistan 
	fprintf(resultFile, "Datasetti Nimiä MinPit MaxPit KA Muistinkäyttö\n");
    while(temp != NULL){
        // Tallentaa tulokset riveinä tiedostoon
        fprintf(resultFile, "%s %d %d %d %.0f %.0f kB / %.0f%%\n",
            temp -> dataSetName,
			temp -> counter,	          
            temp -> shortest,
            temp -> longest,
            temp -> average,
            temp -> roundedTotal,
            temp -> usedMemory);
    	temp = temp -> next;
    }
    // Sulkee tiedoston
    printf("Tiedosto tallennettu.\n");
    fclose(resultFile);
}


/* Tulostaa analyysin tuloksen näytölle
   parametrit: osoitin tuloslistaan
*/
void displayAnalysis(resultitem *head){
    resultitem *temp;   
    temp = head;
	
    // Käy läpi tuloslistan ja tulostaa kaikki alkiot
	printf("Datasetti Nimiä MinPit MaxPit KA Muistinkäyttö\n");
    while(temp != NULL){
        printf("%s", temp -> dataSetName);
		printf(" %d", temp -> counter);      
        printf(" %d", temp -> shortest);
        printf(" %d", temp -> longest);
        printf(" %.0f", temp -> average);
        printf(" %.0fkB /", temp -> roundedTotal);
        printf(" %.0f%c\n", temp -> usedMemory, '%');

        temp = temp -> next;
    }
}

/* Lisää alkion tuloslistaan
   parametrit: osoitin tuloslistaan, osoitin uuteen alkioon
   palauttaa: osoitin tuloslistaan
*/
resultitem* appendResultSet(resultitem *head, resultitem *item) {
    resultitem *temp;
    
    // Tarkistaa, onko lista tyhjä
    if(head != NULL) {
        temp = head;
        // Menee viimeiseen alkioon
        while(temp -> next != NULL) {
            temp = temp -> next;
            }
        // Lisää uuden alkion listan perään
        temp -> next = item;

    } else {
        // Lisää uuden alkion ensimmäiseksi
        temp = item;
    }
    // Palauttaa listan
    return temp;
}

/* Analysoi datan ja tallentaa tuloksen tuloslistaan
   parametrit: osoitin nimilistaan, osoitin tuloslistaan
   palauttaa: osoitin tuloslistaan
*/
resultitem* analyzeDataSet(nameitem *head, resultitem *start){
    char dataSetName[LEN];
    int shortest = 100;
    int longest = 0;
    int counter = 0;
    long int namecount = 0;
    long int charcount = 0;
    long int totalChar = 0;
    double average;
    double totalSize;
    double roundedTotal; 
    double freeMemory;
    double usedMemory;
    nameitem *temp;
    
    // Pyytää käyttäjältä nimen listalle
    printf("Anna analysoitavalle datasetille nimi: ");
    scanf("%s", &dataSetName);
    printf("Analysoidaan listassa olevat tiedot.\n");
            
    // Asettaa tilapäisen osoittimen
    temp = head;
    
    // Käy läpi nimilistan
    while(temp != NULL){  
        // Laskee nimen pituuden
        charcount = strlen(temp->name); 
        // Päivittää kokonaispituuden keskiarvoa varten
        totalChar = totalChar + charcount;
        // Tarkastaa onko nimi lyhin
        if (charcount < shortest ){
            shortest = charcount;
        } 
        // Tarkastaa onko nimi pisin
        if (charcount > longest ){
            longest = charcount;
        }       
        counter = counter + 1;
        temp = temp -> next;
    }
    // Laskee keskiarvon ja kokonaismuistin
    average = (double)totalChar/(double)counter;
    totalSize = sizeof(nameitem) * counter;   
    roundedTotal = floor(totalSize);
    
    // Laskee käytetyn muistin vapaan muistin avulla
    freeMemory = (30.0 - (average + 1.0)) * counter;
    usedMemory = (1.0-(freeMemory/roundedTotal))* 100.0;
    
    // Kääntää muistinkäytön kB:ksi
    roundedTotal = floor(roundedTotal/1000.0); 
    
    // Tulostaa analyysin tuloksen
	printf("Datasetti Nimiä MinPit MaxPit KA Muistinkäyttö\n");
    printf("%s", &dataSetName);
    printf(" %d", counter);
    printf(" %d", shortest);
    printf(" %d", longest);
    printf(" %.0f", floor(average));
    printf(" %.0fkB /", roundedTotal);
    printf(" %.0f%c \n", ceil(usedMemory),'%');
    
    // Varaa muistin uudelle tuloslistan alkiolle
    resultitem *new;
    new = malloc(sizeof(resultitem));
    
    // Asettaa arvot alkioon
    strcpy (new -> dataSetName, dataSetName);
    new -> counter = counter;
    new -> shortest = shortest;
    new -> longest = longest;
    new -> average = floor(average);
    new -> roundedTotal = roundedTotal;
    new -> usedMemory = ceil(usedMemory);
    new -> next = NULL;

    // Lisää alkion listaan ja palauttaa listan
    return appendResultSet(start, new);
}


