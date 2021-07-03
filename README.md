# Controle Backup
Script para automatizar a remoção de arquivos após N dias

## Requisitos 

* ferramentas de desenvolvedor (compilador, glibc etc)

# Iniciando

antes de compilar e rodar o script é necessario fazer 2 alterações no codigo
a primeira alteração a ser feita é na data limite (essa variavel armazena 
a quantidade limite de dias que um arquivo ou pasta devera ficar no sistema.), para isso altere a variavel limitDay (linha 38) e insira o tempo desejado em dias

a proxima alteração é no caminho do diretorio a ser controlado, para isso basta inserir ele na variavel path (linha 34)

feito isso basta compilar `g++ controle_backup.cpp -o controle_backup`

e adicionar o mesmo ao cron ou a alguma rotina do sistema
