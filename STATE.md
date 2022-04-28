# Come scrivere uno stato di gioco

La classe virtuale astratta **state** è la base di ogni stato di gioco. Fornisce l'interfaccia delle funzioni e delle variabili che devono **necessariamente** essere implementate dalle classi figlie (gli stati appunto). 

Questo pattern è necessario perché la classe **engine** gestisce lo stack degli stati e chiama tutte le funzioni fornite dall'interfaccia, che quindi devono essere tutte implementate.

## Funzioni dell'interfaccia
```c++
void init(engine *game) //inizializza lo stato

void pause() //mette in pausa lo stato
void resume() //riprende lo stato dalla pausa
void cleanup() //funzione che viene chiamata prima di togliere dallo stack lo stato

void handle_events(engine *game) //gestisce gli eventi dello stato
void update(engine *game) //aggiorna lo stato
void draw(engine *game) //stampa a schermo
```

le altre funzioni dell'interfaccia non hanno bisogno di essere implementate.

Ogni stato ha un **entity_controller** che gestisce le entità. Non è necessario invocarlo visto che ci sono già funzioni come *create_entity* o *delete_entity* nella classe *state*.

## Implementazione della classe

L'implementazione dello stato segue il pattern del *singleton*, ovvero per ogni stato può esserci una sola istanza (questo perché non avrebbe senso avere ad esempio due istanze dello stato di gioco, visto che durante tutta l'esecuzione del programma ne useremo una e una sola);

Si procede in questo modo: ogni figlio della classe *state* ha un membro privato statico della classe stessa (Alle variabili static viene assegnata la memoria all'avvio del programma e rimane la stessa per tutta l'esecuzione) e una funzione che ritorna quella variabile.

Ad esempio:
```c++
class prova : public state {
public:
/*
    ... funzioni da implementare viste sopra
*/
private:
    static prova m_stato_di_prova;

public:
    static prova* instance() {
        return &m_stato_di_prova;
    }
};
```

Nel file cpp dell'implementazione va quindi inizializzata questa variabile static, in questo modo:
```c++
prova prova::m_stato_di_prova;
```
oltre all'implementazione delle varie funzioni.

## Init
Nella funzione init va inizializzata la finestra con **set_win** (che prende come argomento una finestra di ncurses, creabile con
```c++
brown::graphics::create_newwin(int height, int width, int y, int x);
```
Vanno poi inizializzate le flag di ncurses (per il controllo della tastiera ecc) con
```c++
brown::graphics::start_curses_flag(WINDOW* win);
```

Infine va settata la finestra principale del gioco con quella dello stato con
```c++
game->set_current_screen(WINDOW* win);
```

Queste sono le operazioni base.
Se si intendono utilizzare sistemi (come quello per renderizzare le sprite delle entità o la UI) allora vanno inizializzate anche queste, non prima di aver inizializzato il brain. (I sistemi vanno inseriti nell'implementazione della classe come variabili private (shared_ptr, utile perché si gestisce la memoria da solo i.e. non ci dobiamo preoccupare di fare delete o altro)).

## Handle_events
In handle_events() vengono normalmente gestiti gli input da tastiera.

## Update()
In update() si gestiscono normalmente gli aggiornamenti eseguiti da sistemi particolari come *script* e *animation*.

## Draw()
draw() gestisce invece cosa viene disegnato sullo schermo. Solitamente vengono inserite qui le funzioni che gestiscono le sprite delle entità, o possono essere stampate stringhe con
```c++
void mvwprintw(WINDOW* win, int y, int x, string str); //n.b. win è la finestra dello stato
```

## Altre funzioni (pause, resume, cleanup)
Non è necessario sempre implementare queste tre funzioni per bene visto che non tutti gli stati verranno messi in pausa o altro (o semplicemente non avremo bisogno di fare cose particolari quando uno stato verrà rimosso dallo stack).

