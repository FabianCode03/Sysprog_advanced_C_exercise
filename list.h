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
en Eintrag in der Liste zurück, oder NULL im Fehlerfall.Bei
einem Fehler wird zudem errno auf einen entsprechen-
den Wert gesetzt: EEXIST, falls der schon ein Eintrag mit
dem übergebenen name existiert; oderENOMEM, falls nicht
genügend Speicher zur Verfügung steht.*/

void listForEach(void (*func)(ListNode *));
/*Iteriert über die komplette Liste und führt dabei die per
Zeigerfunc übergebene Funktion für jeden Eintrag in der
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
errno auf ENOENT gesetzt und -1 zurückgegeben.Im Erfolgsfall
ist der Rückgabewert 0.*/

void listRemoveAll(void);
/*Löscht alle Einträge aus der Liste. Diese Funktion wird
beim Beenden des Programms aufgerufen, um den kompletten
Speicher für die Liste wieder freizugeben.*/