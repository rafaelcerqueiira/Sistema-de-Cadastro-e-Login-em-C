#include <stdio.h>   // biblioteca para entrada e saída de dados (printf, scanf)
#include <stdlib.h>  // biblioteca para manipulação de arquivos (fopen, fclose, fprintf, fscanf)
#include <string.h>  // biblioteca para manipulação de strings (strcmp)

int main() {

    // ===================== VARIÁVEIS =====================
    int login;
    char usuario[60], senha[60];
    char usuario_arquivo[60], senha_arquivo[60];
    FILE *arquivo, *temp;
    char usuarioeditar[60];
    char novo_usuario[60], nova_senha[60];
    int encontradousuario;
    int encontradasenha;
    int usuarioadmin = 0;
    int opcaoadmin;

    // ===================== MENU PRINCIPAL =====================
    printf("==== Sistema de Cadastro ====\n\n");
    printf("1. Criar conta\n");
    printf("2. Login\n");
    printf("3. Sair\n");
    printf("4. Acesso administrativo\n\n");
    printf("Selecione uma opção (ex: 1, 2, 3 ou 4): ");
    scanf("%d", &login);

    // validação da opção do menu principal
    while (login < 1 || login > 4) {
        printf("Opção inválida!\n");
        printf("Selecione novamente: ");
        scanf("%d", &login);
    }

    // ===================== SWITCH MENU PRINCIPAL =====================
    switch (login) {

        // ===== CASE 1: CRIAR CONTA =====
        case 1: {
            arquivo = fopen("cadastros.txt", "a");
            if (arquivo == NULL) {
                printf("Erro ao abrir o arquivo de cadastros.\n");
                return 1;
            }
            printf("==== Criar Conta ====\n\n");
            printf("Digite um nome de usuário: ");
            scanf("%59s", usuario);
            printf("Digite uma senha: ");
            scanf("%59s", senha);
            fprintf(arquivo, "%s %s\n", usuario, senha);
            fclose(arquivo);
            printf("Conta criada com sucesso!\n");
            break;
        }

        // ===== CASE 2: LOGIN =====
        case 2: {
            int tentativas = 0;
            int max_tentativas = 3;
            int encontrado;

            printf("==== Login ====\n\n");

            while (tentativas < max_tentativas) {
                arquivo = fopen("cadastros.txt", "r");
                if (arquivo == NULL) {
                    printf("Erro ao abrir o arquivo de cadastros.\n");
                    return 1;
                }
                encontrado = 0;
                printf("Digite seu nome de usuário: ");
                scanf("%59s", usuario);
                printf("Digite sua senha: ");
                scanf("%59s", senha);

                while (fscanf(arquivo, "%s %s", usuario_arquivo, senha_arquivo) != EOF) {
                    if (strcmp(usuario, usuario_arquivo) == 0 && strcmp(senha, senha_arquivo) == 0) {
                        encontrado = 1;
                        break;
                    }
                }
                fclose(arquivo);

                if (!encontrado) {
                    printf("Login inválido! Tente novamente.\n");
                    tentativas++;
                } else {
                    printf("Login realizado com sucesso!\n");
                    break;
                }
            }

            if (tentativas >= max_tentativas) {
                printf("Número máximo de tentativas atingido. Acesso bloqueado.\n");
            }
            break;
        }

        // ===== CASE 3: SAIR =====
        case 3:
            printf("Saindo do sistema. Até mais!\n");
            break;

        // ===== CASE 4: PAINEL ADMINISTRATIVO =====
        case 4: {
            int tentativasadmin = 0;
            int maxtentativasadmin = 3;

            printf("==== Painel de Controle ====\n\n");
            printf("Digite o token de acesso administrativo: ");
            scanf("%d", &usuarioadmin);

            while (usuarioadmin != 6767 && tentativasadmin < maxtentativasadmin) {
                printf("Token de acesso inválido! Tente novamente.\n");
                printf("Digite o token de acesso administrativo: ");
                scanf("%d", &usuarioadmin);
                tentativasadmin++;
            }

            if (usuarioadmin == 6767) {
                printf("==== Acesso administrativo concedido! ====\n\n");
                printf("Listar usuários cadastrados...\n");

                arquivo = fopen("cadastros.txt", "r");
                if (arquivo == NULL) {
                    printf("Erro ao abrir o arquivo de cadastros.\n");
                    return 1;
                }
                rewind(arquivo);
                while (fscanf(arquivo, "%s %s", usuario_arquivo, senha_arquivo) == 2) {
                    printf("====================================\n");
                    printf("Usuário: %s\n", usuario_arquivo);
                    printf("Senha:   %s\n", senha_arquivo);
        
                    printf("====================================\n\n");
                }
                fclose(arquivo);

                // menu do painel administrativo
                printf("1. Editar usuário\n");
                printf("2. Editar senha\n");
                printf("3. Excluir usuário\n");
                printf("4. Sair do painel de controle\n\n");
                printf("Selecione uma opção (ex: 1, 2, 3 ou 4): ");
                scanf("%d", &opcaoadmin);

                while (opcaoadmin < 1 || opcaoadmin > 4) {
                    printf("Opção inválida!\n");
                    printf("Selecione novamente: ");
                    scanf("%d", &opcaoadmin);
                }

                // ===================== SWITCH PAINEL ADMIN =====================
                switch (opcaoadmin) {

                    // ===== CASE 1 ADMIN: EDITAR USUARIO =====
                    case 1: {
                        encontradousuario = 0;
                        printf("Digite o nome do usuário que deseja editar: ");
                        scanf("%59s", usuarioeditar);

                        arquivo = fopen("cadastros.txt", "r");
                        temp    = fopen("temp.txt", "w");
                        if (arquivo == NULL || temp == NULL) {
                            printf("Erro ao abrir os arquivos.\n");
                            return 1;
                        }

                        while (fscanf(arquivo, "%s %s", usuario, senha) != EOF) {
                            if (strcmp(usuario, usuarioeditar) == 0) {
                                printf("Digite o novo nome de usuário: ");
                                scanf("%59s", novo_usuario);
                                fprintf(temp, "%s %s\n", novo_usuario, senha);
                                encontradousuario = 1;
                            } else {
                                fprintf(temp, "%s %s\n", usuario, senha);
                            }
                        }
                        fclose(arquivo);
                        fclose(temp);

                        if (!encontradousuario) {
                            printf("Usuário não encontrado. Nenhuma alteração feita.\n");
                            remove("temp.txt");
                        } else {
                            remove("cadastros.txt");
                            rename("temp.txt", "cadastros.txt");
                            printf("Usuário editado com sucesso!\n");
                        }
                        break;
                    }

                    // ===== CASE 2 ADMIN: EDITAR SENHA =====
                    case 2: {
                        encontradasenha = 0;
                        printf("Digite o nome do usuário para editar a senha: ");
                        scanf("%59s", usuarioeditar);

                        arquivo = fopen("cadastros.txt", "r");
                        temp    = fopen("temp.txt", "w");
                        if (arquivo == NULL || temp == NULL) {
                            printf("Erro ao abrir os arquivos.\n");
                            return 1;
                        }

                        while (fscanf(arquivo, "%59s %59s", usuario_arquivo, senha_arquivo) != EOF) {
                            if (strcmp(usuarioeditar, usuario_arquivo) == 0) {
                                printf("Digite a nova senha: ");
                                scanf("%59s", nova_senha);
                                fprintf(temp, "%s %s\n", usuario_arquivo, nova_senha);
                                encontradasenha = 1;
                            } else {
                                fprintf(temp, "%s %s\n", usuario_arquivo, senha_arquivo);
                            }
                        }
                        fclose(arquivo);
                        fclose(temp);

                        if (!encontradasenha) {
                            printf("Usuário não encontrado. Nenhuma alteração feita.\n");
                            remove("temp.txt");
                        } else {
                            remove("cadastros.txt");
                            rename("temp.txt", "cadastros.txt");
                            printf("Senha editada com sucesso!\n");
                        }
                        break;
                    }

                    // ===== CASE 3 ADMIN: EXCLUIR USUARIO =====
                    case 3: {
                        int encontradousuarioexclusao = 0;
                        printf("Digite o nome do usuário que deseja excluir: ");
                        scanf("%59s", usuarioeditar);

                        arquivo = fopen("cadastros.txt", "r");
                        temp    = fopen("temp.txt", "w");
                        if (arquivo == NULL || temp == NULL) {
                            printf("Erro ao abrir os arquivos.\n");
                            return 1;
                        }

                        while (fscanf(arquivo, "%s %s", usuario_arquivo, senha_arquivo) == 2) {
                            if (strcmp(usuario_arquivo, usuarioeditar) == 0) {
                                encontradousuarioexclusao = 1;
                            } else {
                                fprintf(temp, "%s %s\n", usuario_arquivo, senha_arquivo);
                            }
                        }
                        fclose(arquivo);
                        fclose(temp);

                        if (!encontradousuarioexclusao) {
                            printf("Usuário não encontrado. Nenhuma alteração feita.\n");
                            remove("temp.txt");
                        } else {
                            remove("cadastros.txt");
                            rename("temp.txt", "cadastros.txt");
                            printf("Usuário excluído com sucesso!\n");
                        }
                        break;
                    }

                    // ===== CASE 4 ADMIN: SAIR DO PAINEL =====
                    case 4:
                        printf("Saindo do painel de controle.\n");
                        break;

                }

            } else {
                printf("Número de tentativas excedido! Acesso negado.\n");
            }
            break;
        }

    }

    return 0;
}