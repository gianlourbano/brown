# Brown Game Engine Documentation
- [classi registe](#component-manager-system-manager)
- [classe entità](#classe-entità)
- [componenti](#componenti)

# Come sono implementate le entità in Brown

Una delle componenti fondamentali di ogni game engine è sicuramente la gestione delle entità. Una soluzione molto semplice, ma relativamente poco efficiente, sarebbe quella di avere una lista di classi entità, che verrebbe iterata tutta ogni ciclo di gioco. Questo ha diversi svantaggi, prima di tutto la poca efficienza, in quanto in memoria i nodi di una lista non sono contigui, e iterare per 200 nodi 60 volte al secondo (supponendo 60 FPS) rallenterebbe di molto il gioco.

Ho scelto invece di implementare le entità con un ECS, Entity Component System. Differisce dalla più semplice implementazione vista sopra per i seguenti motivi:
- a livello del game engine, le entità sono semplici **uint32_t** , ovvero **unsigned int**;
- i componenti delle entità, e.g. la posizione e lo sprite, non sono attributi di una classe entità, ma sono delle strutture indipendenti con i propri campi.

### Component manager & system manager

Data quindi la natura di questa implementazione, ci si potrebbe chiedere come si fanno a ricavare informazioni sulle entità se si dispone solo di un "id". La risposta è l'utilizzo di **component array** (uno per ogni categoria di componente): si utilizza appunto l'id per accedere all'array per modificare o leggere le informazioni riguardanti la singola entità.
>Questo ci permette di migliorare di molto la velocità di un ciclo di gioco, in quanto le informazioni contenute nei component array sono contigue in memoria e quindi possono sfruttare la velocità della cache del calcolatore.

La classe **component manager** si occupa di gestire l'array, mentre il **system manager** gestisce tutte le funzioni che sono implementate o si vogliono implementare per uno specifico tipo di componente.

Segue un esempio di classe che implementa la classe **system**, che è banalmente un set di entity_id(unsigned int come detto sopra).

```c++
class custom_system : public brown::system {
    private:
        /* methods and attributes */
    public:
        static std::shared_ptr<custom_system> register_system(brown::brain* br);
}
```

Per registrazione di un sistema si intende la creazione di una **signature** che rappresenti appunto il tipo del sistema e dei componenti che vengono gestiti all'interno dell'engine. Ad esempio, nell'implementazione è già presente un sistema per il rendering (la cui signature include i componenti *transform* e *sprite*).

La classe **brain** si occupa invece di gestire il "sistema di sistemi", ovvero l'ECS nel suo complesso.

## Classe entità

Ovviamente per lo sviluppatore non è comodo lavorare con le entità a questo livello così basso all'interno degli stati. Si introduce quindi la classe entità, molto simile a quella da implementare per il metodo visto [sopra](#come-sono-implementate-le-entità-in-brown).

L'ultimo grado dell'astrazione dell'ECS si trova proprio nella classe **state**, che contiene proprio i metodi per gestire le entità in una maniera più developer-friendly.

> Si noti bene che le entità posso essere gestite in qualsiasi metodo della classe state, ma è consigliato inizializzarle nella funzione *init()*.


Ecco un esempio di gestione delle entità:
```c++
class custom_state: public state {

/*
    methods...
*/

protected:
    void init(/* args */) {
        /*
            initialization
        */

        brown::entity player = create_entity("player");

        player.add_component<transform>(...);
        player.add_component<...>(...);

        transform ts = player.get_component<transform>();
    }
}
```

> ### Astrazione
>
> L'utilizzo di questo implementazione permette allo sviluppatore che usa Brown di lavorare semplicemente con le entità, semplicemente aggiungendo e rimuovendo componenti: sono le classi a livello dell'ECS come il **brain**, il **system manager** e l'**entity manager** che si occupano di gestire il tutto. Basta infatti aggiungere un componente ad un'entità e la sua signature verrà cambiata, e verrà iscritta quindi a tutti i sistemi che si occupano di gestire entità con quella particolare signature.

# Componenti
L'implementazione di Brown include vari componenti, ovvero:
- transform (posizione e scaling dell'entità);
- sprite (il pattern di caratteri che viene stampato a schermo)
- animation (array di sprite e informazioni sull'animazione)
- animator controller (gestisce le animazioni)
- native script, su cui torneremo dopo.

Nella cartella [components](/src/engine/core/ECS/components/transform.hpp) sono presenti tutte le interfacce dei componenti. Facciamo ora particolare attenzione al native script.

### Native Script

La possibilità di programmare la logica di gioco attraverso l'uso di native script (ovvero script scritti nel linguaggio dell'engine) ci permette di creare molto facilmente giochi più complessi.

Data la natura dell'engine, al programmatore rimane quindi solo da scrivere i propri stati di gioco insieme a questi script che si dovrebbero occupare appunto della logica di gioco, come il movimento del player.

Ecco un esemop di native script:

```c++
custom_state.hpp
#include "custom_script.hpp";

class custom_state: public state {

/* methods... */

protected:
    void init(/* args */) {
        /* initialization */

        brown::entity player = create_entity("player");

        player.add_component<transform>({...});
        player.add_component<native_script>({}).bind<custom_script>();
    }
}

```

```c++
custom_script.hpp

#pragma once
#include "engine/brown.hpp"

class custom_script : public brown::scriptable_entity
{
    void on_create() {
        ts = &get_component<transform>();
    }

    void on_update() {
        if(brown::KEY_PRESSED == 'u')
            ts.pos.x++;
    }

    void on_destroy() {
        /* ... */
    }

    private:
        transform* ts = nullptr;
};

```

> Metodi
> - on_create viene chiamata subito dopo il bind dello script;
> - on_update viene chiamata ogni ciclo di gioco;
> - on_destroy viene chiamata quando l'entità viene distrutta.