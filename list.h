typedef struct ListNode
{
    char name[32];
    char number[32];
    struct ListNode *prev;
    struct ListNode *next;
} ListNode;

ListNode *listAdd(const char *name);
/*Hängt einen neuen Eintrag mit dem übergebenen name
an das Ende der Liste. Die Telefonnummer wird auf den
leeren String initialisiert. Gibt einen Zeiger auf den neu-
enEintraginderListezurück,oderNULLimFehlerfall.Bei
einem Fehler wird zudem errno auf einen entsprechen-
den Wert gesetzt: EEXIST, falls der schon ein Eintrag mit
demübergebenennameexistiert;oderENOMEM,fallsnicht
genügend Speicher zur Verfügung steht.*/

void listForEach(void (*func)(ListNode *));
/*Iteriert über die komplette Liste und führt dabei die per
Zeigerfunc übergebeneFunktionfürjedenEintraginder
Liste aus. Dabei wird in jedem Iterationsschritt ein Zei-
ger auf das jeweilige ListNode-Element an die Funktion
übergeben. Für eine Liste mit nElementen ergeben sich
dadurch nAufrufe von func. Durch diesen Mechanismus
können beispielsweise alle Elemente der Liste auf der
Konsole ausgegeben werden.*/

int listRemoveByName(const char *name);
/*Löscht den Eintrag mit dem übergebenen name aus der
Liste und gibt den Speicher für den Eintrag frei. Falls es
keinen Eintrag mit dem übergebenen Namen gibt, wird
errno auf ENOENT gesetztund-1 zurückgegeben.ImEr-
folgsfall ist der Rückgabewert 0.*/

void listRemoveAll(void);
/*Löscht alle Einträge aus der Liste. Diese Funktion wird
beim Beenden des Programms aufgerufen, um den kom-
pletten Speicher für die Liste wieder freizugeben.*/