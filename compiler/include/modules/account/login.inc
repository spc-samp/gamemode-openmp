// Incluímos o módulo y_hooks do pacote YSI, para que possamos acessar callbacks dentro de vários módulos e no arquivo principal (main.pwn) simultaneamente
#include <YSI_Coding/y_hooks>

// Criamos um enumerador com várias variáveis que usaremos para armazenar informações do jogador na memória
enum E_PLAYER_DATA {
    pID,
    pName[MAX_PLAYER_NAME],
    pHash[BCRYPT_HASH_LENGTH],
    pLoginAttempts,
    bool:pLoggedin,

    pSkin,
    pSex,
    Float:pPosX,
    Float:pPosY,
    Float:pPosZ,
    Float:pAngle
};
// Criamos uma matriz para acessar as variáveis dentro do enumerador
new PlayerData[MAX_PLAYERS][E_PLAYER_DATA];

// Definimos valores padrões como coordenadas do spawn padrão/novato e skin inicial de cada gênero
#define DEFAULT_POS_X 1480.9602
#define DEFAULT_POS_Y -1745.0508
#define DEFAULT_POS_Z 13.5469
#define DEFAULT_ANGLE 3.2307
#define MASCULINE_DEFAULT_SKIN (18)
#define FEMININE_DEFAULT_SKIN (56)


hook OnPlayerConnect(playerid) {
    // Criamos um buffer para armazenar a query SQL que iremos executar
    new queryBuffer[128];

    // Pegamos o nome/apelido do jogador e armazenamos na variável pName
    GetPlayerName(playerid, PlayerData[playerid][pName]);

    // Aqui colocamos o jogador como espectador 
    // - neste contexto serve apenas como uma "gambiarra" comum para esconder as opções de spawn padrões do SA-MP (>> << Spawn)
    // uma vez que não há outra maneira de desabilitar
    TogglePlayerSpectating(playerid, true);

    // Armazenamos a query SQL no nosso buffer
    // Dica: sempre utilize mysql_format quando for formatar uma query SQL
    // uma vez que permite escaparmos strings e protege contra vulnerabilidades de SQL Injection (https://pt.wikipedia.org/wiki/Inje%C3%A7%C3%A3o_de_SQL)
    mysql_format(Handle, queryBuffer, sizeof(queryBuffer), "SELECT Hash FROM jogadores WHERE Nome = '%e'", PlayerData[playerid][pName]);
    
    // Executamos a query e chamamos a callback CheckAccount por onde poderemos manipular os resultados da query
    // Dica: sempre utilize a função mysql_tquery em vez da mysql_query
    // o "t" em tquery é abreviação de threaded query
    // o que significa que a query vai ser executada em apenas uma thread 
    // enquanto a função mysql_query executará a query em qualquer thread que estiver disponível no momento
    // e isso pode causar problemas de "hanging", ou seja, travamento do servidor
    // uma vez que estará utilizando várias threads ao mesmo tempo, e, portanto, drenando recursos
    mysql_tquery(Handle, queryBuffer, "CheckAccount", "i", playerid);
}

hook OnPlayerDisconnect(playerid, reason) {
    // Tomemos nota nessa expressão, pois certamente tem potencial de causar confusão
    // Aqui nós verificamos se o motivo da saída do jogador é 1 (ou seja, se o jogador crashou)
    // e especificamente fazemos isso aqui porque quando o jogador crasha
    // não é possível recuperar sua posição posteriormente
    // o que significa que caso ele crashe, a função SaveData não vai conseguir recuperar a posição do jogador
    // e isso resultará no jogador sendo spawnado na posição salva antes
    if(reason == 1 && PlayerData[playerid][pLoggedin] == true) {
        GetPlayerPos(playerid, PlayerData[playerid][pPosX], PlayerData[playerid][pPosY], PlayerData[playerid][pPosZ]);
        GetPlayerFacingAngle(playerid, PlayerData[playerid][pAngle]);
    }

    // Atualizamos os dados do jogador ao desconectar
    SaveData(playerid);
    
    // Resetamos as variáveis do jogador
    // - o que é essencial
    // pois caso não fizermos isso, o jogador que conectar e receber o ID do jogador que desconectou
    // irá "herdar" o valor das variáveis associadas àquele ID
    ResetData(playerid);
}

hook OnPlayerRequestClass(playerid, classid) {
    if(PlayerData[playerid][pLoggedin]) {
        SpawnPlayer(playerid);
    }
}

forward CheckAccount(playerid);
public CheckAccount(playerid) {
    // Verificamos se a coluna do jogador é maior que 0 - ou seja, se existe
    // Se sim, significa que a conta já está registrada
    if(cache_num_rows() > 0) {
        // Recuperamos o hash gerado apartir da senha do jogador
        cache_get_value_name(0, "Hash", PlayerData[playerid][pHash], BCRYPT_HASH_LENGTH);

        // Mostramos a dialog de login
        ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_PASSWORD, "Login - Digite sua senha", "{FFFFFF}Conta encontrada no banco de dados\n\nDigite sua senha", "Login", "Sair");
    } else {
        // else, ou seja, caso contrário (i.e caso a conta não esteja registrada), mostramos a dialog de registro
        ShowPlayerDialog(playerid, DIALOG_REGISTRO, DIALOG_STYLE_PASSWORD, "Registro - Digite uma senha para registrar-se", "{FFFFFF}Digite uma senha para registrar-se", "Registrar", "Sair");
    }
    return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]) {
    switch(dialogid) {
        case DIALOG_REGISTRO: {
            // Caso ele clique em sair, o expulsamos
            if(!response) return Kick(playerid);

            // Verficamos se a senha contém ao menos 5 caracteres
            // caso não, mostramos uma mensagem de erro e mostramos a dialog novamente
            if(strlen(inputtext) <= 5) {
                SendClientMessage(playerid, -1, "A senha deve conter pelo menos 5 caracteres");
                return ShowPlayerDialog(playerid, DIALOG_REGISTRO, DIALOG_STYLE_PASSWORD, "Registro - Digite uma senha para registrar-se", "{FFFFFF}Digite uma senha para registrar-se", "Registrar", "Sair");
            }

            // Geramos um hash apartir da senha do jogador
            // Isso é essencial pois armazenar senhas sem nenhuma segurança em texto
            // é um erro de segurança gravíssimo
            // e é contra a maioria das leis de privacidade, como a LGPD no Brasil e GDPR na União Europeia
            bcrypt_hash(playerid, "OnPlayerPasswordHash", inputtext, BCRYPT_COST);
        }

        case DIALOG_LOGIN: {
            if(!response) return Kick(playerid);

            // Verificamos se a senha digitada pelo jogador corresponde ao hash
            // E transmitimos para a callback OnPlayerPasswordVerify onde poderemos manipular os resultados
            bcrypt_verify(playerid, "OnPlayerPasswordVerify", inputtext, PlayerData[playerid][pHash]);
        }


        case DIALOG_SEX: {
            if(response) { // Botão esquerdo, ou seja, masculino
                PlayerData[playerid][pSex] = GENDER_MASCULINE;

                TogglePlayerSpectating(playerid, false);
                SetSpawnInfo(playerid, NO_TEAM, MASCULINE_DEFAULT_SKIN, DEFAULT_POS_X, DEFAULT_POS_Y, DEFAULT_POS_Z, DEFAULT_ANGLE);
                SpawnPlayer(playerid);
            } else { // Botão direito, ou seja, feminino
                PlayerData[playerid][pSex] = GENDER_FEMININE;

                TogglePlayerSpectating(playerid, false);
                SetSpawnInfo(playerid, NO_TEAM, FEMININE_DEFAULT_SKIN, DEFAULT_POS_X, DEFAULT_POS_Y, DEFAULT_POS_Z, DEFAULT_ANGLE);
                SpawnPlayer(playerid);
            }
        }
    }
    return 1;
}

forward OnPlayerPasswordHash(playerid);
public OnPlayerPasswordHash(playerid) {
    // Criamos uma string para armazenar o hash
    new hash[BCRYPT_HASH_LENGTH];

    // Recuperamos o hash e armazenamos em nossa string
    bcrypt_get_hash(hash, sizeof(hash));

    // Inserimos a conta do jogador no banco de dados
    InsertIntoDatabase(playerid, hash);
    return 1;
}

forward OnPlayerPasswordVerify(playerid, bool:success);
public OnPlayerPasswordVerify(playerid, bool:success) {
    // Caso a senha do jogador não corresponda ao hash
    if(!success) {
        // Adiciona uma tentativa de login incorreta
        PlayerData[playerid][pLoginAttempts]++;

        // Aqui criamos uma variável para armazenar quantas tentativas o jogador tem sobrando
        new attempts = MAX_LOGIN_ATTEMPTS - PlayerData[playerid][pLoginAttempts];

        // Caso ele tiver menos que 3 tentativas de 5, mostramos um aviso dizendo que ele possui poucas tentativas sobrando
        if(attempts <= 3) {
            new string[128];
            format(string, sizeof(string), "{FF0000}Senha incorreta!\n\n{FFFFFF}Você agora possui apenas {FF0000}%i{FFFFFF} tentativas restantes", attempts);

            ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_PASSWORD, "Login - Digite sua senha", string, "Login", "Sair");
        } else {
            ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_PASSWORD, "Login - Digite sua senha", "{FF0000}Senha incorreta\n\nTente novamente", "Login", "Sair");
        }

        if(PlayerData[playerid][pLoginAttempts] >= MAX_LOGIN_ATTEMPTS) {
            return Kick(playerid);
        }
    } else {
        new queryBuffer[128];

        mysql_format(Handle, queryBuffer, sizeof(queryBuffer), "SELECT * FROM jogadores WHERE Nome = '%e' LIMIT 1", PlayerData[playerid][pName]);
        mysql_tquery(Handle, queryBuffer, "OnPlayerLogin", "i", playerid);
    }
    return 1;
}

forward OnPlayerLogin(playerid);
public OnPlayerLogin(playerid) {
    PlayerData[playerid][pLoggedin] = true;
    PlayerData[playerid][pLoginAttempts] = 0;

    // Recuperamos os valores das colunas do cachê do banco de dados e armazenamos em suas respectivas variáveis
    cache_get_value_name_int(0, "ID", PlayerData[playerid][pID]);
    cache_get_value_name_int(0, "Skin", PlayerData[playerid][pSkin]);
    cache_get_value_name_int(0, "Genero", PlayerData[playerid][pSex]);
    cache_get_value_name_float(0, "X_pos", PlayerData[playerid][pPosX]);
    cache_get_value_name_float(0, "Y_pos", PlayerData[playerid][pPosY]);
    cache_get_value_name_float(0, "Z_pos", PlayerData[playerid][pPosZ]);
    cache_get_value_name_float(0, "Angle", PlayerData[playerid][pAngle]);

    TogglePlayerSpectating(playerid, false);
    SetSpawnInfo(playerid, NO_TEAM, PlayerData[playerid][pSkin], PlayerData[playerid][pPosX], PlayerData[playerid][pPosY], PlayerData[playerid][pPosZ], PlayerData[playerid][pAngle]);
    SpawnPlayer(playerid);
    return 1;
}

void:InsertIntoDatabase(playerid, const string:hash[]) {
    new queryBuffer[256];

    // Inserimos a recém criada conta do jogador no banco de dados
    mysql_format(Handle, queryBuffer, sizeof(queryBuffer), "INSERT INTO jogadores (Nome, Hash) VALUES ('%e', '%s')", PlayerData[playerid][pName], hash);
    mysql_tquery(Handle, queryBuffer, "OnPlayerRegister", "i", playerid);
}

forward OnPlayerRegister(playerid);
public OnPlayerRegister(playerid) {
    // Mostramos a dialog onde o jogador pode escolher seu gênero
    ShowPlayerDialog(playerid, DIALOG_SEX, DIALOG_STYLE_MSGBOX, "Sexo - Selecione o gênero de seu personagem", "{FFFFFF}Selecione seu gênero", "Masculino", "Feminino");

    PlayerData[playerid][pID] = cache_insert_id();
    
    PlayerData[playerid][pPosX] = DEFAULT_POS_X;
    PlayerData[playerid][pPosY] = DEFAULT_POS_Y;
    PlayerData[playerid][pPosZ] = DEFAULT_POS_Z;
    PlayerData[playerid][pAngle] = DEFAULT_ANGLE;
    
    PlayerData[playerid][pLoggedin] = true;
    PlayerData[playerid][pLoginAttempts] = 0;
    return 1;
}

stock ResetData(playerid) {
    if(!PlayerData[playerid][pLoggedin]) return 1;

    // Aqui resetamos todas as variáveis para seu valor padrão
    // Para evitar que outros jogadores as herdem
    PlayerData[playerid][pID] = -1;
    PlayerData[playerid][pName] = EOS; // EOS = End Of String/fim da string - ou seja, reverte o valor da string para seu valor padrão
    PlayerData[playerid][pHash] = EOS;
    PlayerData[playerid][pLoginAttempts] = 0;
    PlayerData[playerid][pLoggedin] = false;
    PlayerData[playerid][pSkin] = 0;
    PlayerData[playerid][pSex] = -1;
    PlayerData[playerid][pPosX] = 0.0;
    PlayerData[playerid][pPosY] = 0.0;
    PlayerData[playerid][pPosZ] = 0.0;
    PlayerData[playerid][pAngle] = 0.0;
    return 1;
}

stock SaveData(playerid) {
    if(!PlayerData[playerid][pLoggedin]) return 1;

    new queryBuffer[300];


    PlayerData[playerid][pSkin] = GetPlayerSkin(playerid);
    GetPlayerPos(playerid, PlayerData[playerid][pPosX], PlayerData[playerid][pPosY], PlayerData[playerid][pPosZ]);
    GetPlayerFacingAngle(playerid, PlayerData[playerid][pAngle]);

    mysql_format(Handle, queryBuffer, sizeof(queryBuffer), "UPDATE jogadores SET \
    X_Pos = %f, \
    Y_Pos = %f, \
    Z_Pos = %f, \
    Angle = %f, \
    Genero = %i, \
    Skin = %i WHERE ID = %i", PlayerData[playerid][pPosX], PlayerData[playerid][pPosY], PlayerData[playerid][pPosZ], PlayerData[playerid][pAngle], PlayerData[playerid][pSex], PlayerData[playerid][pSkin], PlayerData[playerid][pID]);
    mysql_tquery(Handle, queryBuffer);
    return 1;
}