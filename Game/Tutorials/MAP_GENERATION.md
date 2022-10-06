# Generazione della mappa di gioco
Usando le funzionalità di Brown, come la possibilità di usare *native_script*, risulta molto facile implementare algoritmi per la generazione della mappa.

Abbiamo scelto di usare il [Wavefunction Collapse Algorithm](https://robertheaton.com/2018/12/17/wavefunction-collapse-algorithm/) per la generazione della mappa del nostro gioco.
 
L'algoritmo è relativamente semplice e si occupa di generare una mappa in modo procedurale seguendo delle regole imposte dal programmatore. In questo modo è possibile, nel nostro caso, generare stanze ogni volta diverse dall'altra, avendo raramente copie.

Il modo in cui dovrebbe essere implementata è quindi:
+ avere un **tileset**, ovvero una collezione di tiles che vengono posizionati dall'algoritmo per formare la mappa;
+ ad ogni tile del tileset corrispondono regole ben definite usate dall'algoritmo.

> Avere a disposizione un tileset aiuta molto il processo di sviluppo del gioco, in quanto nell'evenienza che il programmatore voglia inserire nuovi tiles (lo sprite .spr e le regole per l'algoritmo) basterebbero poche righe di codice.