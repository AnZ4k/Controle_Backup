# TKV Controle
Ferramenta remover automaticamente arquivos / diretorios após N dias

# Requisitos do sistema
  * sistema operacional Linux
  * permissão de super-usuario

## Instalando requisitos para a compilação
`apt install build-essential make cmake`

# Instruções de compilação
Na raiz do projeto gere a pasta "build" e entre na mesma <br>
`mkdir build && cd build` <br>
logo em seguida gere o makefile <br>
`cmake ..` <br>
após isso compile o projeto <br>
`make`

# Guia de execução
para executar basta rodar <br>
`./tkv_controle -p <path> -d <dlim>` <br>
onde `<path>` é o/os diretorios a serem controlados e `<dlim>` é o tempo limite em dias <br>
exemplo<br>
`./tkv_controle -p /home/foo /home/bar -d 5`<br>
o comando acima controla o diretorio "/home/foo e /home/bar" removendo deles arquivos que ja estão lá
à 5 dias ou mais

# Recomendações
para facilitar as coisas você pode adicionar o programa ao cron.
a sintaxe recomendada é <br>
`30  *	* * *	root 	/scripts/tkv_controle > /var/log/tkv-controle.log` <br>

## NÂO É RECOMENDADO O USO DE PATH RELATIVO
