# minishell
O minishell é uma simples versão do shell, feito com o objetivo de aprender mais sobre processos e *file descriptors*. Executar um comando dentro de um shell implica em criar um novo processo "filho", no qual sua execução e estado final serão monitorados pelo processo "pai".

### Como compilar?
Utilizando o Makefile você pode criar o arquivo executável *minishell*
```
make
```

Pode ser necessário instalar as bibliotecas de desenvolvimento *readline*.
Em plataformas baseadas em Debian, como o Ubuntu, você pode executar:
```
sudo apt-get install libreadline-dev
```

Em plataformas com o *yum*, o comando deve ser:
```
yum install readline-devel
```

### Como executar?
Rode o executável *minishell*, como no exemplo:
```
./minishell
```
Isso iniciará, dentro do próprio terminal, o minishell, no qual é possível utilizar vários comandos disponíveis no shell padrão.

#### Builtins implementados:
* echo
* pwd
* cd
* export
* unset
* env
* exit


#### More about School 42 you can find here: https://en.wikipedia.org/wiki/42_(school)
