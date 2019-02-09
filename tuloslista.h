/*****************************************************************************/
/* CT60A0220 C-ohjelmoinnin ja testauksen periaatteet 
 * Tekijä: Aleksi Karhu
 * Opiskelijanumero: 0452237
 * Päivämäärä:31.3.2018
 * Yhteistyö ja lähteet, nimi ja yhteistyön muoto:
 */
/*****************************************************************************/

/* Rakenne analyysitietuetta varten, linkitetty lista */
struct analysis {
    char dataSetName[30];
    int counter;
    int shortest;
    int longest;
    double average;
    double usedMemory;
    double roundedTotal;
    struct analysis *next;  
};

/* Tyypinmäärittely analyysitietueelle */
typedef struct analysis resultitem;

/* Tuhoaa tuloslistan 
   parametrit: osoitin tuloslistaan
*/
void deleteResultList(resultitem *head);

/* Tallentaa analyysin tulokset käyttäjän määräämään tiedostoon 
   parametrit: osoitin tuloslistaan
*/
void saveResults(resultitem *head);

/* Tulostaa analyysin tuloksen näytölle
   parametrit: osoitin tuloslistaan
*/
void displayAnalysis(resultitem *head);

/* Lisää alkion tuloslistaan
   parametrit: osoitin tuloslistaan, osoitin uuteen alkioon
   palauttaa: osoitin tuloslistaan
*/
resultitem* appendResultSet(resultitem *head, resultitem *item);

/* Analysoi datan ja tallentaa tuloksen tuloslistaan
   parametrit: osoitin nimilistaan, osoitin tuloslistaan
   palauttaa: osoitin tuloslistaan
*/
resultitem* analyzeDataSet(nameitem *head, resultitem *start);

