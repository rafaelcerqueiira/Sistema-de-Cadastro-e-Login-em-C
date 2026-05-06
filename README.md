# 🖥️ Sistema de Cadastro em C

Um sistema simples de gerenciamento de usuários desenvolvido em linguagem **C**, com funcionalidades de criação de conta, login com controle de tentativas e painel administrativo protegido por token.

---

## 📋 Índice

- [Sobre o Projeto](#-sobre-o-projeto)
- [Funcionalidades](#-funcionalidades)
- [Como Compilar e Executar](#-como-compilar-e-executar)
- [Estrutura do Menu](#-estrutura-do-menu)
- [Detalhes das Funcionalidades](#-detalhes-das-funcionalidades)
- [Armazenamento de Dados](#-armazenamento-de-dados)
- [Segurança](#-segurança)
- [Limitações e Observações](#-limitações-e-observações)

---

## 📖 Sobre o Projeto

Este projeto é um **sistema de cadastro e autenticação de usuários** via terminal, desenvolvido inteiramente em C. Ele utiliza arquivos `.txt` como banco de dados para persistir as informações entre execuções do programa. É ideal para fins educacionais e para compreender conceitos como manipulação de arquivos, controle de fluxo e autenticação básica em C.

---

## ✅ Funcionalidades

| Funcionalidade         | Descrição                                                  |
|------------------------|------------------------------------------------------------|
| 📝 Criar conta         | Cadastra um novo usuário com nome e senha                  |
| 🔐 Login               | Autentica o usuário com até 3 tentativas                   |
| 🚪 Sair                | Encerra o programa                                         |
| 🛡️ Painel Admin        | Acesso protegido por token para gerenciar usuários         |
| ✏️ Editar usuário      | Altera o nome de um usuário cadastrado                     |
| 🔑 Editar senha        | Altera a senha de um usuário cadastrado                    |
| 🗑️ Excluir usuário     | Remove um usuário do sistema                               |

---

## ⚙️ Como Compilar e Executar

### Pré-requisitos

- Compilador GCC (ou qualquer compilador C compatível com C99+)
- Terminal / Prompt de Comando

### Compilação

```bash
gcc sistema_cadastro.c -o sistema_cadastro
```

### Execução

```bash
./sistema_cadastro
```

> 💡 No Windows, o executável será `sistema_cadastro.exe` e pode ser executado com `sistema_cadastro.exe` no terminal.

---

## 🗂️ Estrutura do Menu

```
==== Sistema de Cadastro ====

1. Criar conta
2. Login
3. Sair
4. Acesso administrativo
```

Ao selecionar a opção **4 (Acesso administrativo)**, é necessário informar o **token de acesso**. Após autenticação bem-sucedida, um submenu é exibido:

```
==== Painel de Controle ====

1. Editar usuário
2. Editar senha
3. Excluir usuário
4. Sair do painel de controle
```

---

## 🔍 Detalhes das Funcionalidades

### 📝 1. Criar Conta

- Solicita um **nome de usuário** (até 59 caracteres) e uma **senha** (até 59 caracteres).
- Os dados são salvos no arquivo `cadastros.txt` no formato:
  ```
  nome_usuario senha
  ```
- Múltiplos usuários podem ser cadastrados, cada um em uma linha.

---

### 🔐 2. Login

- O usuário tem até **3 tentativas** para inserir as credenciais corretas.
- O sistema lê o arquivo `cadastros.txt` e compara o usuário e senha digitados com cada registro.
- Se as credenciais baterem, o login é confirmado ✅.
- Após 3 tentativas falhas, o acesso é **bloqueado** ❌.

---

### 🛡️ 4. Painel Administrativo

- Protegido por um **token numérico** (verificado internamente no código).
- O administrador também tem até **3 tentativas** para inserir o token correto.
- Após autenticação, todos os usuários e senhas cadastrados são listados na tela.
- Em seguida, é apresentado o submenu de gerenciamento.

#### ✏️ Editar Usuário
- Localiza um usuário pelo nome atual e permite definir um **novo nome de usuário**.
- O restante dos dados (senha) é preservado.

#### 🔑 Editar Senha
- Localiza um usuário pelo nome e permite definir uma **nova senha**.
- O nome do usuário permanece inalterado.

#### 🗑️ Excluir Usuário
- Remove completamente o registro de um usuário do arquivo.
- Caso o usuário não seja encontrado, nenhuma alteração é feita.

> 🔄 As operações de edição e exclusão funcionam criando um arquivo temporário (`temp.txt`), reescrevendo os dados válidos e substituindo o arquivo original ao final.

---

## 💾 Armazenamento de Dados

Os dados são armazenados no arquivo `cadastros.txt`, gerado automaticamente na mesma pasta do executável. O formato é simples:

```
joao senha123
maria abc456
pedro qwerty
```

> ⚠️ **Atenção:** Este arquivo é criado em modo `append` (`"a"`), então os dados são acumulados entre execuções. Não apague o arquivo manualmente a menos que queira reiniciar todos os cadastros.

O arquivo temporário `temp.txt` é usado internamente durante edições e exclusões, sendo apagado automaticamente ao final de cada operação.

---

## 🔒 Segurança

> ⚠️ Este sistema foi desenvolvido para fins **didáticos**. Algumas práticas aqui utilizadas **não são recomendadas em ambientes de produção**:

- 🔓 **Senhas armazenadas em texto puro** — sem nenhum tipo de hash ou criptografia.
- 🔓 **Token administrativo fixo** no código-fonte — qualquer pessoa com acesso ao código saberá o token.
- 📂 **Arquivo de texto como banco de dados** — sem controle de acesso ao arquivo no sistema operacional.
- 👁️ **Senhas visíveis na listagem do painel admin** — expostas diretamente no terminal.

Para um sistema real, recomenda-se o uso de **hash de senhas** (ex: bcrypt), **banco de dados seguro** e **autenticação baseada em sessões ou tokens criptografados**.

---

## ⚠️ Limitações e Observações

- O sistema **não valida caracteres especiais** nos campos de usuário e senha.
- Nomes de usuário e senhas com **espaços** não são suportados, pois o `fscanf` usa espaço como delimitador.
- Não é possível **listar usuários** sem entrar no modo administrativo.
- O programa executa **apenas uma ação por execução** — não há loop principal que retorne ao menu após concluir uma operação.
- Campos de texto limitados a **59 caracteres** (tamanho do buffer menos 1).

---

## 🧱 Bibliotecas Utilizadas

| Biblioteca   | Uso                                              |
|--------------|--------------------------------------------------|
| `<stdio.h>`  | Entrada/saída padrão (`printf`, `scanf`, `FILE`) |
| `<stdlib.h>` | Funções de arquivo (`fopen`, `fclose`, etc.)     |
| `<string.h>` | Comparação de strings (`strcmp`)                 |

---

## 👨‍💻 Autor

Desenvolvido como projeto educacional em linguagem C. Sinta-se à vontade para modificar, melhorar e expandir as funcionalidades! 🚀