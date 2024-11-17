# KriptoX

![KriptoX Banner](https://i.postimg.cc/TPCTT8nQ/kriptox.png)

**KriptoX** é uma **exchange de criptomoedas sandbox** desenvolvida em **C**, projetada para simular operações de compra, venda e gerenciamento de criptomoedas de forma segura e educativa. Ideal tanto para aprendizado quanto para entretenimento, o KriptoX permite que os usuários explorem o funcionamento de uma exchange real sem riscos financeiros.

- [Replit do projeto](https://replit.com/@unifksantos/KriptoXCAdmin)

## 🎯 Objetivo

O principal objetivo do **KriptoX** é ensinar de uma forma divertida as pessoas como funciona o sistema de uma exchange de criptomoedas. Isso permite que os usuários:

- **Aprendizado**: Ensinar os conceitos básicos de uma exchange funciona, incluindo operações financeiras, taxas, transações e gerenciamento de criptomoedas.
- **Entretenimento**: Fornecer um ambiente onde você pode utilizar valores fictícios sem qualquer risco de perda de valores e utilizar da criatividade para realizar qualquer operação.

### 🖥️ Uso

**KriptoX** é extremamente fácil de usar! Após iniciar o programa, todas as informações necessárias são carregadas automaticamente. As opções são apresentadas diretamente no terminal, e para interagir, basta digitar o número correspondente à opção desejada e pressionar **Enter**. Em caso de erro, o programa solicitará a inserção de um valor válido, informando o formato correto.
Para poder logar como administrador é preciso usar o CPF **12345678900** e a senha **63423594**.

### 🚀 Funcionalidades

#### Para Usuários

- **Registrar Usuário**: Registre uma nova conta com CPF único e uma senha.
- **Login**: Entre em uma conta usando CPF e senha.
- **Depositar/Sacar**: Adicione ou remova reais de sua conta virtual.
- **Comprar/Vender Criptomoedas**: Compre ou venda criptomoedas.
- **Transferir Saldo**: Transfira saldo para outros usuários cadastrados.
- **Consultar Saldo e Extrato**: Verifique seu saldo atual e suas transações.
- **Atualizar Cotação**: Atualize a cotação das criptomoedas de forma aleatória.

![Operações do User](https://i.postimg.cc/CMfds1Gg/image.png)

#### Para Administradores

- **Cadastrar/Excluir Investidor**: Adicione ou remova usuários no KriptoX.
- **Cadastrar Criptomoeda**: Crie novas criptomoedas do seu jeito.
- **Excluir Criptomoeda**: Remova criptomoedas que não te interessam.
- **Consultar Saldo**: Verifique o saldo de um usuário.
- **Consultar Extrato**: Acesse o histórico de transações de um usuário.
- **Atualizar Cotação**: Atualize a cotação das criptomoedas de forma aleatória.

![Operações do Admin](https://i.postimg.cc/RFWh8C2w/image.png)

## 🛠️ Compilar / Usar

### Requisitos

- **Compilador C**: Compilador para gerar o executavel, GCC é o recomendado.
- **CMake(Opcional)**: Para compilação alternativa.
- **Ambiente de Desenvolvimento(Opcional)**: Pode ser utilizado no Replit para uma maior versatilidade.

### Passo a Passo

#### Usando Replit

1. **Configurar o Repositório no Replit**
   - Acesse o [Replit](https://replit.com/).
   - Crie um novo Repl e escolha a linguagem **C**.
   - Faça upload de todos os arquivos do repositório **KriptoX** para o Repl.

2. **Alterar configuracoes do Replit**
   - Coloque os arquivos da pasta Replit-config nos arquivos do Repl.
   - Pode sobrescrever ou deletar os arquivos anteriores (.replit e replit.nix).

3. **Executar o Projeto**
   - Clique em **Run** para compilar e executar o programa automaticamente.
   - Para rodar no modo **Usuário** abra o arquivo **.replit** e altere a segunda linha para "**run = "/tmp/build/KriptoX_C_User"**"
   - Para rodar no modo **Admin** abra o arquivo **.replit** e altere a segunda linha para "**run = "/tmp/build/KriptoX_C_Admin"**"

#### Compilando Localmente no Windows

Você pode compilar o **KriptoX** localmente utilizando **CMake** ou comandos **gcc** separados para as versões de **Admin** e **Usuário**.

##### Usando CMake

1. **Clonar o Repositório do KriptoX**
    ```bash
    git clone https://github.com/oKaio122/KriptoX-C-Adm
    cd KriptoX-C-Adm
    ```

2. **Criar o Diretório da Build do CMake**
    ```bash
    mkdir build
    cd build
    ```

3. **Configurar o Projeto com CMake**
    ```bash
    cmake ..
    ```

4. **Compilar o Projeto e gerar executáveis**
    ```bash
    cmake --build . --config Release
    ```

   - Isso irá compilar ambos os executáveis: `KriptoX_Admin.exe` e `KriptoX_User.exe`.

##### Usando Comandos GCC

Se preferir não usar o CMake, você pode compilar as versões de **Admin** e **Usuário** separadamente utilizando comandos **gcc**. Siga os passos abaixo:

1. **Clonar o Repositório**
    ```bash
    git clone https://github.com/oKaio122/KriptoX-C-Adm
    cd KriptoX
    ```

2. **Compilar a Versão de Usuário**
    ```bash
    gcc kutils.c main.c -o KriptoX_User.exe
    ```

3. **Compilar a Versão de Administrador**
    ```bash
    gcc kutils.c kadm.c -o KriptoX_Admin.exe
    ```

## 👤 Criador

**Kaio Angelo Posansky Santos**  
**R.A.** 24124058-9

![Kaio Angelo](./images/kaio-angelo.png)

  

