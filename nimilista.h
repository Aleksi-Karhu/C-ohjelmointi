/*****************************************************************************/
/* CT60A0220 C-ohjelmoinnin ja testauksen periaatteet 
 * Tekijä: Aleksi Karhu
 * Opiskelijanumero: 0452237
 * Päivämäärä:31.3.2018
 * Yhteistyö ja lähteet, nimi ja yhteistyön muoto:
 */
/*****************************************************************************/

// Vakio nimitietueen pituutta varten
#define LEN 30

/* Rakenne nimitietuetta varten, linkitetty lista */
struct namedata{
    char name[LEN];
    long int count;
    struct namedata *next;
};

/* Tyypinmäärittely nimitietueelle */
typedef struct namedata nameitem;

/* Tuhoaa nimilistan 
   parametrit: osoitin nimilistaan
*/
void deleteNameList(nameitem *head);

/* Lukee käyttäjän antaman data-tiedoston ja luo linkitetyn nimilistan 
   parametrit: tiedostonimi ja osoitin nimilistaan
   palauttaa: osoitin nimilistaan 
 */
nameitem* readDataFile(char *fileName, nameitem *head);

/* Tulostaa nimilistan näytölle
   parametrit: osoitin nimilistaan
*/
void displayNames(nameitem *head);



