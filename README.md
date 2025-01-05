# gamemode-open

Uma gamemode base de c�digo aberto, simples, por�m completa e em dia com as boas pr�ticas de c�digo e seguran�a.

[![Licen�a](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/license/mit)

---

## Estrutura do Projeto

| **Nome**            | **Descri��o**                                                                                 |
|---------------------|-----------------------------------------------------------------------------------------------|
| `compiler/include/` | Cont�m as bibliotecas necess�rias                                                             |
| `components/`       | Cont�m os componentes (plugins que foram migrados para o open.mp)                             |
| `plugins/`          | Cont�m os plugins SA-MP (plugins legado que ainda n�o foram migrados para o open.mp)           |
| `gamemodes/`        | Cont�m o arquivo compilado e o c�digo fonte do script                                          |
| `.env`              | Cont�m as vari�veis de ambiente contendo as credenciais do banco de dados MySQL                |
| `config.json`       | Cont�m as configura��es do servidor open.mp. Para mais informa��es, veja a [documenta��o oficial](https://www.open.mp/docs/server/config.json) |
| `omp-server`        | Execut�vel que inicia o servidor                                                              |
| `scheme.sql`        | Cont�m a estrutura da tabela SQL de jogadores e suas colunas                                   |

---

## Vantagens

- **Escalabilidade**  
- **Criptografia de todas as senhas utilizando bcrypt**  
- **C�digo limpo e bem documentado**  
- **F�cil de configurar, exigindo apenas conhecimento extremamente b�sico em gerenciamento de banco de dados e Pawn**


## Fun��es

- Tela de login simples em `dialog`
- Sistema de escolha de g�nero do personagem
- Salvamento da �ltima posi��o do jogador no servidor

## Compila��o

### Pr�-requisitos
As vers�es pr�-compiladas podem ser encontradas na [p�gina de releases](https://github.com/spc-samp/gamemode-openmp/releases/latest).

Nas vers�es distribu�das, o servidor inclui uma pasta chamada **Qawno**, que � o ambiente de desenvolvimento padr�o do open.mp, equivalente ao **Pawno** do SA-MP. 

### Passo-a-passo para compilar usando Qawno:

#### Abra o **Qawno**
Execute o arquivo `qawno.exe` que est� na pasta baixada.

#### Abra o arquivo do script
No **menu superior**, clique em `File > Open` e navegue at� a pasta `gamemodes/`. Selecione o arquivo **Main.pwn**.

![qawno](https://i.imgur.com/zybzJxD.png)

#### Compile o script
Clique em `Build > Compile` ou pressione **F5** no teclado.

![qawno](https://i.imgur.com/pLII7sm.png)

### Nota sobre Warnings
Se voc� optar por usar **Qawno** e **sampvoice**, pode ignorar os dois *warnings* que surgirem devido � vers�o do compilador do open.mp.  

Caso prefira, adicione a linha abaixo no topo do script para suprimir esses *warnings* (embora eu n�o recomende esta abordagem uma vez que encoraja m�s pr�ticas):

```pawn
#pragma warning disable 239
```

## Para Desenvolvedores Avan�ados
Recomendamos o uso do Visual Studio Code como ambiente de desenvolvimento.

Confira este tutorial para configurar o Visual Studio Code para compilar scripts Pawn: https://youtu.be/jITcf95XGgA

## Escolhendo a Vers�o da Gamemode
Se voc� est� confuso sobre qual vers�o escolher para o seu sistema operacional, veja abaixo:

### Vers�es Dispon�veis
- **`gamemode-win-x86`**
  - **Descri��o:** Esta vers�o � para sistemas Windows.
  - **Detalhes:** Roda o servidor e seus plugins na arquitetura x86, que � o padr�o para a maioria dos plugins.

- **`gamemode-x86-centos`**
  - **Descri��o:** Esta vers�o � destinada � distribui��o CentOS.
  - **Detalhes:** Certifique-se de que seu servidor utiliza o CentOS antes de escolher esta vers�o.

- **`gamemode-x86-debian`**
  - **Descri��o:** Esta vers�o � para a distribui��o Debian e distribui��es baseadas em Debian.
  - **Detalhes:** Inclui suporte para distribui��es como Ubuntu (a mais popular) e outras variantes baseadas em Debian.

## Como Identificar Sua Distribui��o Linux
Se voc� n�o tem certeza sobre qual distribui��o Linux seu servidor est� utilizando:

1. Consulte seu provedor de hospedagem.
2. Rode o comando abaixo no terminal para obter informa��es:
```
lsb_release -a
```
Esse comando exibir� a distribui��o e a vers�o do sistema operacional.

## Estrutura SQL

### Tabela `jogadores`

| **Nome**            | **Descri��o**                                                                                 |
|---------------------|-----------------------------------------------------------------------------------------------|
| `ID` | ID n�merico �nico gerado pelo banco de dados ao jogador se registrar (segue come�ando a partir de 0)                                                             |
| `Nome`       | Nome/apelido do jogador                             |
| `Hash`          | Hash gerado a partir da senha do jogador pelo bcrypt           |
| `X_Pos`        | Eixo X da �ltima posi��o salva do jogador antes de se desconectar                                         |
| `Y_Pos`              | Eixo Y da �ltima posi��o salva do jogador antes de se desconectar                |
| `Z_Pos`       | Eixo Z da �ltima posi��o salva do jogador antes de se desconectar |
| `Angle`        | �ltimo �ngulo/rota��o do jogador registrado antes de se desconectar                                                              |
| `Skin`        | ID da skin/roupa do jogador                                   |
| `Genero`        | G�nero do jogador (0 para masculino | 1 para feminino)                                   |

