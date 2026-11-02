#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_ESTUDANTES 100
#define MAX_FICHAS 10
#define MAX_EXERCICIOS 10
#define MAX_SUBMISSOES 10000
#define MAX_CARACTERES 60

typedef struct
{
    int dia, mes, ano;
} t_data;

typedef struct
{
    int identificador_unico_exercicios; 
    char nome_exercicio[MAX_CARACTERES];
    int identificador_unico_ficha;
    char grau_de_dificuldade[MAX_CARACTERES]; 
    char tipo_de_solução[MAX_CARACTERES];    

} t_exercicios;

typedef struct
{
    int identificador_unico_ficha; 
    char nome_da_ficha[MAX_CARACTERES];
    int numero_de_exercicios;
    t_data data_de_publicacao; 
    t_exercicios exercicio[MAX_EXERCICIOS];

} t_fichas;

typedef struct
{
    int identificador_unico_estudante; 
    int numero_de_estudante;          
    char nome_do_estudante[MAX_CARACTERES];
    char email_do_estudante[MAX_CARACTERES];

} t_estudante;

typedef struct
{
    int identificador_unico_submissoes; 
    int identificador_unico_estudante;
    int identificador_unico_ficha;
    int identificador_unico_exercicios;
    t_data data_de_submissao; 
    int numero_de_linhas;
    float classificacao_obtida; 

} t_submissoes;
// MENUS
int menu_opcoes();
int display_menus(char tipo_menu[]);
int menu_estudantes(t_estudante estudantes[], int numero_estudantes);
int menu_fichas(int num_fichas, t_fichas ficha[]);
int menu_exercicios(t_fichas ficha[], int num_fichas);
int display_estastisticas();
void menu_estatisticas(t_estudante estudantes[], t_fichas ficha[], t_submissoes submissao[], int num_submissoes, int numero_estudantes);
int menu_submissoes(t_estudante estudantes[], t_submissoes submissao[], t_fichas ficha[], int numero_submissoes, int numero_estudantes, int num_fichas);
char confirmar_saida();

// ESTUDANTES
int registrar_estudante(t_estudante estudantes[], int numero_estudantes);
int procurar_estudante(t_estudante estudantes[], int numero_estudantes, int estudante_escolhido);
void mostrar_dados_estudantes(t_estudante estudantes[], int numero_estudantes);

// FICHAS
int registrar_ficha(int num_fichas, t_fichas ficha[]);
void reunir_dados_fichas(int num_fichas, t_fichas ficha[], int ficha_requerida);
void mostrar_dados_fichas(int num_fichas, t_fichas ficha[]);
void dados_fichas(int num_fichas, t_fichas ficha[]);
int procurar_ficha(int num_fichas, t_fichas ficha[], int ficha_requerida);

// EXERCICIOS
void registrar_exercicios(int num_fichas, t_fichas ficha[]);
void reunir_dados_exercicios(int num_fichas, t_fichas ficha[], int id_ficha);
void grau_dificuldade(char grau[]);
void tipo_de_solucao(char solucao[]);
void mostrar_dados_exercicios(int num_fichas, t_fichas ficha[]);
void dados_exercicios(int num_fichas, t_fichas ficha[], int id_ficha);
int procurar_exercicio(int num_fichas, t_fichas ficha[], int indice_ficha, int exercicio_requerido);

// SUBMISSOES
int registrar_submissao(t_submissoes submissao[], t_estudante estudantes[], t_fichas ficha[], int num_submissoes, int numero_estudantes, int num_fichas);
void reunir_dados_submissao(t_submissoes submissao[], t_estudante estudantes[], t_fichas ficha[], int num_submissoes, int estudante_procurado, int ficha_procurada, int exercicio_procurado);
void mostrar_dados_submissao(t_submissoes submissao[], t_estudante estudantes[], t_fichas ficha[], int num_submissoes);

// ESTATISTICAS
int total_submissoes_estudante(t_submissoes submissao[], t_estudante estudantes[], int num_submissoes, int estudante_id);
float media_classificacao(t_submissoes submissao[], t_estudante estudantes[], int num_submissoes, int estudante_id);
float percentagem_exercicios(t_submissoes submissao[], t_estudante estudantes[], t_fichas ficha[], int num_submissoes, int estudante_id);

// VALIDACOES E FUNCIONALIDADES
int ler_numero_inteiro(char mensagem[], int minimo, int maximo);
float ler_numero_decimal(char mensagem[], int minimo, int maximo);
int id_estudante(t_estudante estudantes[], int numero_estudantes);
int id_ficha(t_fichas ficha[], int num_fichas);
int id_exercicio(t_fichas ficha[], int num_fichas, int id_ficha);
int validador_ano();
int validador_mes();
int validador_dia(int mes, int ano);
void gravar_ficheiro_binario(t_estudante estudantes[], int numero_estudantes);
int ler_ficheiro(t_estudante estudantes[]);
void gravar_dados_binario(t_estudante estudantes[], int numero_estudantes, t_fichas fichas[], int numero_fichas, t_submissoes submissao[], int numero_submissoes);
void ler_dados_binario(t_estudante estudantes[], int *numero_estudantes, t_fichas fichas[], int *numero_fichas, t_submissoes submissao[], int *numero_submissoes);

int main()
{
    t_estudante estudantes[MAX_ESTUDANTES];
    t_submissoes submissao[MAX_SUBMISSOES];
    t_fichas ficha[MAX_FICHAS];
    int num_estudantes = 0, menu, num_submissoes = 0, num_fichas = 0;
    char opcao;

    do
    {
        menu = menu_opcoes();

        switch (menu)
        {
        case 1:
            num_estudantes = menu_estudantes(estudantes, num_estudantes);

            break;
        case 2:
            num_fichas = menu_fichas(num_fichas, ficha);
            break;
        case 3:
            menu_exercicios(ficha, num_fichas);
            break;
        case 4:
            num_submissoes = menu_submissoes(estudantes, submissao, ficha, num_submissoes, num_estudantes, num_fichas);
            break;
        case 5:
            menu_estatisticas(estudantes, ficha, submissao, num_submissoes, num_estudantes);
            break;
        case 6:
            gravar_dados_binario(estudantes, num_estudantes, ficha, num_fichas, submissao, num_submissoes);
            break;
        case 7:
            ler_dados_binario(estudantes, &num_estudantes, ficha, &num_fichas, submissao, &num_submissoes);
            break;
        case 8:
            opcao = confirmar_saida();
            break;

        default:
            break;
        }
    } while (opcao != 's');
    return 0;
}

// MENUS
int menu_opcoes(void)
{
    int acao;

    do
    {
        printf("\nMenu de Opções:\n");
        printf("1 - Registar e consultar dados de um estudante\n");
        printf("2 - Registar e consultar dados das fichas de exercicios\n");
        printf("3 - Registar e consultar dados dos exercicios\n");
        printf("4 - Registar e consultar dados das submissoes\n");
        printf("5 - Consultar Estatisticas\n");
        printf("6 - Gravar dados em ficheiro\n");
        printf("7 - Ler dados de ficheiro\n");
        printf("8 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%i", &acao);
    } while (acao <= 0 || acao > 8);
    return acao;
}
int display_menus(char tipo_menu[])
{
    int opcao;

    printf("\n--- Submenu %s ---\n", tipo_menu);
    printf("1. REGISTRAR %s\n", tipo_menu);
    printf("2. CONSULTAR DADOS DE %s\n", tipo_menu);
    printf("3. Voltar ao menu principal\n");
    printf("Escolha uma opção: ");
    scanf("%i", &opcao);

    return opcao;
}
int menu_estudantes(t_estudante estudantes[], int numero_estudantes)
{
    int opcao;
    char saida = 'n';
    do
    {
        opcao = display_menus("ESTUDANTES");
        switch (opcao)
        {
        case 1:
            numero_estudantes = registrar_estudante(estudantes, numero_estudantes);
            break;
        case 2:
            mostrar_dados_estudantes(estudantes, numero_estudantes);
            break;
        case 3:
            saida = 's';
            break;

        default:
            break;
        }
    } while (saida != 's');
    return numero_estudantes;
}
int menu_fichas(int num_fichas, t_fichas ficha[])
{
    int opcao;
    char saida = 'n';
    printf("%i", num_fichas);
    do
    {
        opcao = display_menus("FICHAS");
        switch (opcao)
        {
        case 1:
            num_fichas = registrar_ficha(num_fichas, ficha);
            break;
        case 2:
            mostrar_dados_fichas(num_fichas, ficha);
            break;
        case 3:
            saida = 's';
            break;

        default:
            break;
        }
    } while (saida != 's');
    return num_fichas;
}
int menu_exercicios(t_fichas ficha[], int num_fichas)
{
    int opcao;
    char saida = 'n';
    do
    {
        opcao = display_menus("EXERCICIOS");
        switch (opcao)
        {
        case 1:
            registrar_exercicios(num_fichas, ficha);
            break;
        case 2:
            mostrar_dados_exercicios(num_fichas, ficha);
            break;
        case 3:
            saida = 's';
            break;
        default:
            break;
        }
    } while (saida != 's');
    return num_fichas;
}
int display_estastisticas()
{
    int opcao;

    printf("\n--- Submenu Fichas ---\n");
    printf("1. TOTAL SUBMISSOES POR ESTUDANTE\n");
    printf("2. MEDIA DE CLASSIFICACOES POR ESTUDANTE\n");
    printf("3. PERCENTAGEM DE EXERCICIOS POR ESTUDANTE EM CADA FICHA\n");
    printf("4. Voltar ao menu principal\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    return opcao;
}

void menu_estatisticas(t_estudante estudantes[], t_fichas ficha[], t_submissoes submissao[], int num_submissoes, int numero_estudantes)
{
    int opcao, total_sub, estudante_id, estudante_escolhido;
    float media, percentagem;
    char saida = 'n';
    do
    {
        opcao = display_estastisticas();
        switch (opcao)
        {
        case 1:
            estudante_id = id_estudante(estudantes, numero_estudantes);
            total_sub = total_submissoes_estudante(submissao, estudantes, num_submissoes, estudante_id);
            printf("O total de submissoes é %i", total_sub);
            break;
        case 2:
            estudante_id = id_estudante(estudantes, numero_estudantes);
            media = media_classificacao(submissao, estudantes, num_submissoes, estudante_id);
            printf(" a media é %.1f", media);
            break;
        case 3:
            estudante_id = id_estudante(estudantes, numero_estudantes);
            percentagem = percentagem_exercicios(submissao, estudantes, ficha, num_submissoes, estudante_id);
            printf(" a percentagem é %.1f", percentagem);
            break;
        case 4:
            saida = 's';
            break;
        default:
            break;
        }
    } while (saida != 's');
}
int menu_submissoes(t_estudante estudantes[], t_submissoes submissao[], t_fichas ficha[], int numero_submissoes, int numero_estudantes, int num_fichas)
{
    int opcao;
    char saida = 'n';
    printf("%i", numero_estudantes);
    do
    {
        opcao = display_menus("SUBMISSOES");
        switch (opcao)
        {
        case 1:
            numero_submissoes = registrar_submissao(submissao, estudantes, ficha, numero_submissoes, numero_estudantes, num_fichas);
            break;
        case 2:
            mostrar_dados_submissao(submissao, estudantes, ficha, numero_submissoes);
            break;
        case 3:
            saida = 's';
            break;
        default:
            break;
        }
    } while (saida != 's');
    return numero_submissoes;
}
char confirmar_saida(void)
{
    char opcao;

    do
    {
        printf("Tem a certeza que deseja sair?\n");
        printf("\n           S/N");
        scanf(" %c", &opcao);
        opcao = tolower(opcao);
    } while (opcao != 's' && opcao != 'n');
    return opcao;
}
// ESTUDANTES
int registrar_estudante(t_estudante estudantes[], int numero_estudantes)
{
    int contador, numero_por_registrar, validador_estudante = -1;

    numero_por_registrar = ler_numero_inteiro("Insira o estudante que deseja", 2230000, 2249999);
    validador_estudante = procurar_estudante(estudantes, numero_estudantes, numero_por_registrar);

    if (validador_estudante == -1 && numero_estudantes < MAX_ESTUDANTES) // Caso -1 sinal que não existe estudante e podemos prosseguir
    {
        contador = numero_estudantes + 1;
        estudantes[numero_estudantes].identificador_unico_estudante = numero_estudantes + 1;
        estudantes[numero_estudantes].numero_de_estudante = numero_por_registrar; // numero de estudante
        printf("Insira o nome do estudante: ");                                   // nome de estudante
        getchar();
        fgets(estudantes[numero_estudantes].nome_do_estudante, MAX_CARACTERES, stdin);
        snprintf(estudantes[numero_estudantes].email_do_estudante, MAX_CARACTERES, "%d@my.ipleiria.pt", estudantes[numero_estudantes].numero_de_estudante);
    }
    else
    {
        printf("\nO estudante que tentou registrar já existe!");
        printf("\n-------------TENTE NOVAMENTE---------------\n");
        contador = numero_estudantes;
    }
    return contador;
}
int procurar_estudante(t_estudante estudantes[], int numero_estudantes, int estudante_escolhido)
{

    int indice, encontrou = -1;

    for (indice = 0; indice < numero_estudantes; indice++)
    {
        if (estudante_escolhido == estudantes[indice].numero_de_estudante)
        {
            encontrou = indice;
        }
    }
    return encontrou;
}
void mostrar_dados_estudantes(t_estudante estudantes[], int numero_estudantes)
{

    int indice;

    for (indice = 0; indice < numero_estudantes; indice++)
    {
        printf("\n\n O id do estudante é %i", estudantes[indice].identificador_unico_estudante);
        printf("\n O numero do estudante é %i", estudantes[indice].numero_de_estudante);
        printf("\n O seu nome é %s", estudantes[indice].nome_do_estudante);
        printf(" O seu email é %s\n", estudantes[indice].email_do_estudante);
    }
}

// FICHAS
int registrar_ficha(int num_fichas, t_fichas ficha[])
{
    int ficha_por_registrar, validador_ficha;

    if (num_fichas < MAX_FICHAS)
    {
        reunir_dados_fichas(num_fichas, ficha, ficha_por_registrar);
        num_fichas++;
    }
    else
    {
        printf("\n      Numero maximo de fichas atingido!");
        printf("\n-------------TENTE NOVAMENTE---------------\n");
    }

    return num_fichas;
}
void reunir_dados_fichas(int num_fichas, t_fichas ficha[], int ficha_requerida)
{
    int ano, mes, indice_ficha;

    indice_ficha = num_fichas;

    ficha[indice_ficha].identificador_unico_ficha = num_fichas + 1;
    printf("\nInsira o nome da ficha: ");
    getchar();
    fgets(ficha[indice_ficha].nome_da_ficha, MAX_CARACTERES, stdin);
    ficha[indice_ficha].numero_de_exercicios = ler_numero_inteiro("Insira o numero de exercicios", 1, MAX_EXERCICIOS);
    printf("Insira a data de publicacao: ");
    ano = validador_ano();
    mes = validador_mes();
    ficha[indice_ficha].data_de_publicacao.dia = validador_dia(mes, ano);
    ficha[indice_ficha].data_de_publicacao.ano = ano;
    ficha[indice_ficha].data_de_publicacao.mes = mes;
}
void mostrar_dados_fichas(int num_fichas, t_fichas ficha[])
{

    if (num_fichas > 0)
    {
        dados_fichas(num_fichas, ficha);
    }
    else
    {
        printf("\n           Não existem fichas!\n");
        printf("\n-------------TENTE NOVAMENTE---------------\n");
    }
}
void dados_fichas(int num_fichas, t_fichas ficha[])
{

    int indice;

    for (indice = 0; indice < num_fichas; indice++)
    {
        printf("\n\n O id da ficha é %i", ficha[indice].identificador_unico_ficha);
        printf("\n O nome da ficha é %s", ficha[indice].nome_da_ficha);
        printf("O numero de exercicios é %i", ficha[indice].numero_de_exercicios);
        printf("\n A data de publicacao %i/%i/%i\n", ficha[indice].data_de_publicacao.dia, ficha[indice].data_de_publicacao.mes, ficha[indice].data_de_publicacao.ano);
    }
}
int procurar_ficha(int num_fichas, t_fichas ficha[], int ficha_requerida)
{

    int indice, encontrou = -1;

    for (indice = 0; indice < num_fichas; indice++)
    {
        if (ficha_requerida == ficha[indice].identificador_unico_ficha)
        {
            encontrou = indice;
        }
    }
    return encontrou;
}
// EXERCICIOS

void registrar_exercicios(int num_fichas, t_fichas ficha[])
{
    int ficha_por_registrar, validador_ficha, id_ex;

    validador_ficha = id_ficha(ficha, num_fichas);
    id_ex = ficha[validador_ficha].exercicio[0].identificador_unico_exercicios;
    if (validador_ficha != -1)
    {
        if (id_ex == 0)
        {
            reunir_dados_exercicios(num_fichas, ficha, validador_ficha);
        }
        else
        {
            printf("\n      Os exercicios ja estão preenchido!");
            printf("\n-------------TENTE NOVAMENTE---------------\n");
        }
    }
    else
    {
        printf("\n           A ficha nao existe!");
        printf("\n-------------TENTE NOVAMENTE---------------\n");
    }
}
void reunir_dados_exercicios(int num_fichas, t_fichas ficha[], int id_ficha)
{
    int indice_exercicio;

    for (indice_exercicio = 0; indice_exercicio < ficha[id_ficha].numero_de_exercicios; indice_exercicio++)
    {
        printf("REGISTRO DO EXERCICIO %i", indice_exercicio + 1);

        ficha[id_ficha].exercicio[indice_exercicio].identificador_unico_exercicios = indice_exercicio + 1;
        snprintf(ficha[id_ficha].exercicio[indice_exercicio].nome_exercicio, MAX_CARACTERES, "Exercicio %i", ficha[id_ficha].exercicio[indice_exercicio].identificador_unico_exercicios);
        // menus
        grau_dificuldade(ficha[id_ficha].exercicio[indice_exercicio].grau_de_dificuldade);

        tipo_de_solucao(ficha[id_ficha].exercicio[indice_exercicio].tipo_de_solução);
    }
}
void grau_dificuldade(char grau[])
{

    int opcao;
    do
    {
        printf("\n1 - Baixo");
        printf("\n2 - Medio");
        printf("\n3 - Elevado");
        printf("\nEscolha um grau de dificuldade: ");
        scanf("%i", &opcao);
    } while (opcao < 1 || opcao > 3);

    switch (opcao)
    {
    case 1:
        strcpy(grau, "Baixo");
        break;
    case 2:
        strcpy(grau, "Medio");
        break;
    case 3:
        strcpy(grau, "Elevado");
        break;

    default:
        break;
    }
}
void tipo_de_solucao(char solucao[])
{

    int opcao;

    do
    {
        printf("\n1 - Algoritmo");
        printf("\n2 - Codigo");
        printf("\nEscolha um tipo de solucao: ");
        scanf("%i", &opcao);
    } while (opcao < 1 || opcao > 2);

    switch (opcao)
    {
    case 1:
        strcpy(solucao, "Algoritmo");
        break;
    case 2:
        strcpy(solucao, "Codigo");
        break;
    default:
        break;
    }
}
void mostrar_dados_exercicios(int num_fichas, t_fichas ficha[])
{
    int ficha_por_registrar, validador_ficha;

    validador_ficha = id_ficha(ficha, num_fichas);
    if (validador_ficha != -1)
    {
        dados_exercicios(num_fichas, ficha, validador_ficha);
    }
    else
    {
        printf("\n           A ficha nao existe!");
        printf("\n-------------TENTE NOVAMENTE---------------\n");
    }
}
void dados_exercicios(int num_fichas, t_fichas ficha[], int id_ficha)
{
    int indice, indice_ficha;

    indice_ficha = id_ficha;
    // Percorre os exercicios da ficha em questao
    for (indice = 0; indice < ficha[id_ficha].numero_de_exercicios; indice++)
    {
        // Mostra os dados da ficha
        printf("\n\n O id do exercicio é %i", ficha[indice_ficha].exercicio[indice].identificador_unico_exercicios);
        printf("\n O nome do exercicio é %s", ficha[indice_ficha].exercicio[indice].nome_exercicio);
        printf("\n O tipo de solução é %s", ficha[indice_ficha].exercicio[indice].tipo_de_solução);
        printf("\n O grau de dificuldade é %s", ficha[indice_ficha].exercicio[indice].grau_de_dificuldade);
    }
}
int procurar_exercicio(int num_fichas, t_fichas ficha[], int indice_ficha, int exercicio_requerido)
{
    int indice_exercicio, encontrou = -1, max_exercicio, validar;

    for (indice_exercicio = 0; indice_exercicio < ficha[indice_ficha].numero_de_exercicios; indice_exercicio++)
    {
        if (exercicio_requerido == ficha[indice_ficha].exercicio[indice_exercicio].identificador_unico_exercicios)
        {
            encontrou = indice_exercicio;
        }
    }
    return encontrou;
}

// SUBMISSAO

int registrar_submissao(t_submissoes submissao[], t_estudante estudantes[], t_fichas ficha[], int num_submissoes, int numero_estudantes, int num_fichas)
{
    int validador_estudante, ficha_procurada, validador_ficha, ex_procurado, validador_ex, num_exercicio;
    validador_estudante = id_estudante(estudantes, numero_estudantes);
    if (validador_estudante != -1) // Caso -1 sinal que existe estudante e podemos prosseguir
    {
        validador_ficha = id_ficha(ficha, num_fichas);
        if (validador_ficha != -1) // Caso -1 sinal que existe ficha e podemos prosseguir
        {
            validador_ex = id_exercicio(ficha, num_fichas, validador_ficha);
            if (validador_ex != -1) // Caso -1 sinal que existe exercicio e podemos prosseguir
            {
                reunir_dados_submissao(submissao, estudantes, ficha, num_submissoes, validador_estudante, validador_ficha, validador_ex);
                num_submissoes = num_submissoes + 1;
            }else
            {
                printf("\nO exercicio nao existe!");
            }
        }else
        {
            printf("\nA ficha nao existe!");
        }
    }else
    {
        printf("\nO estudante que tentou registrar não existe!");
    }
    return num_submissoes;
}
void reunir_dados_submissao(t_submissoes submissao[], t_estudante estudantes[], t_fichas ficha[], int num_submissoes, int estudante_procurado, int ficha_procurada, int exercicio_procurado)
{
    int ano, mes, linhas, indice_sub;
    float classificacao;
    // Id`s
    submissao[num_submissoes].identificador_unico_submissoes = num_submissoes + 1;
    submissao[num_submissoes].identificador_unico_estudante = estudantes[estudante_procurado].identificador_unico_estudante;
    submissao[num_submissoes].identificador_unico_ficha = ficha[ficha_procurada].identificador_unico_ficha;
    submissao[num_submissoes].identificador_unico_exercicios = ficha[ficha_procurada].exercicio[exercicio_procurado].identificador_unico_exercicios;
    // Data
    printf("\nInsira a data de submissao: ");
    ano = validador_ano();
    mes = validador_mes();
    submissao[num_submissoes].data_de_submissao.dia = validador_dia(mes, ano);
    submissao[num_submissoes].data_de_submissao.ano = ano;
    submissao[num_submissoes].data_de_submissao.mes = mes;
    // Numero de linha e classificações
    submissao[num_submissoes].numero_de_linhas = ler_numero_inteiro("\nInsira o numero de linhas usadas no exercicio", 1, 100);
    submissao[num_submissoes].classificacao_obtida = ler_numero_decimal("\nInsira a classificacao do exercicio", 0, 100);
}
void mostrar_dados_submissao(t_submissoes submissao[], t_estudante estudantes[], t_fichas ficha[], int num_submissoes)
{

    int indice, max_submissoes;
    max_submissoes = num_submissoes;
    for (indice = 0; indice < max_submissoes; indice++)
    {
        printf("\nDADOS DA SUBMISSÃO %i!\n", submissao[indice].identificador_unico_submissoes);
        printf("\nO id do estudante é %i.", submissao[indice].identificador_unico_estudante);
        printf("\nO id da ficha é %i.", submissao[indice].identificador_unico_ficha);
        printf("\nO id do exercicio é %i.", submissao[indice].identificador_unico_exercicios);
        printf("\nA sua data de submissão foi %i/%i/%i.", submissao[indice].data_de_submissao.dia, submissao[indice].data_de_submissao.mes, submissao[indice].data_de_submissao.ano);
        printf("\nO numero de linhas usados no exercicio foi %i.", submissao[indice].numero_de_linhas);
        printf("\nA sua classificação foi %.1f.\n", submissao[indice].classificacao_obtida);
    }
}
// Estastiscas

int total_submissoes_estudante(t_submissoes submissao[], t_estudante estudantes[], int num_submissoes, int estudante_id)
{
    int total = 0, indice, identificador;
    identificador = estudante_id + 1;
    for (indice = 0; indice < num_submissoes; indice++)
    {
        if (submissao[indice].identificador_unico_estudante == identificador)
        {
            total = total + 1;
        }
    }
    return total;
}
float media_classificacao(t_submissoes submissao[], t_estudante estudantes[], int num_submissoes, int estudante_id)
{
    int contador = 0, indice, identificador;
    float soma = 0, media = 0;

    identificador = estudante_id + 1;
    for (indice = 0; indice < num_submissoes; indice++)
    {
        if (submissao[indice].identificador_unico_estudante == identificador)
        {
            soma = soma + submissao[indice].classificacao_obtida;
            contador = contador + 1;
        }
    }
    media = soma / contador;

    return media;
}
float percentagem_exercicios(t_submissoes submissao[], t_estudante estudantes[], t_fichas ficha[], int num_submissoes, int estudante_id)
{
    int total_exercicios = 0, exercicios_submetidos = 0, identificador, indice_submetidos, indice_exercicios, percentagem;

    identificador = estudante_id + 1;

    for (int indice_exercicios = 0; indice_exercicios < MAX_FICHAS; indice_exercicios++)
    {
        total_exercicios = total_exercicios + ficha[indice_exercicios].numero_de_exercicios;
    }

    for (indice_submetidos = 0; indice_submetidos < num_submissoes; indice_submetidos++)
    {
        if (submissao[indice_submetidos].identificador_unico_estudante == identificador)
        {
            exercicios_submetidos= exercicios_submetidos + 1;
        }
    }
    percentagem = ((float)exercicios_submetidos / total_exercicios) * 100;

    return percentagem;
}
// VALIDACOES E FUNCIONALIDADES
int ler_numero_inteiro(char mensagem[], int minimo, int maximo)
{
    int valor;
    do
    {
        printf("%s entre %i e %i : ", mensagem, minimo, maximo);
        scanf("%i", &valor);

    } while (valor < minimo || valor > maximo);
    return valor;
}
float ler_numero_decimal(char mensagem[], int minimo, int maximo)
{
    float valor;
    do
    {
        printf("%s entre %i e %i : ", mensagem, minimo, maximo);
        scanf("%f", &valor);

    } while (valor < minimo || valor > maximo);
    return valor;
}
int id_estudante(t_estudante estudantes[], int numero_estudantes)
{
    int estudante_escolhido, estudante_id;
    estudante_escolhido = ler_numero_inteiro("Insira o estudante que deseja", 2230000, 2249999);
    estudante_id = procurar_estudante(estudantes, numero_estudantes, estudante_escolhido);

    return estudante_id;
}
int id_ficha(t_fichas ficha[], int num_fichas)
{
    int ficha_procurada, id_ficha;
    ficha_procurada = ler_numero_inteiro("Insira o ID da ficha que deseja procurar", 1, MAX_FICHAS);
    id_ficha = procurar_ficha(num_fichas, ficha, ficha_procurada);
    return id_ficha;
}
int id_exercicio(t_fichas ficha[], int num_fichas, int id_ficha)
{
    int num_exercicio, ex_procurado, id_exercicio;

    num_exercicio = ficha[id_ficha].numero_de_exercicios;
    ex_procurado = ler_numero_inteiro("Insira o ID do exercicio que deseja procurar", 1, num_exercicio);
    id_exercicio = procurar_exercicio(num_fichas, ficha, id_ficha, ex_procurado);
    return id_exercicio;
}
int validador_ano()
{

    int ano;
    do
    {
        printf("\nANO: ");
        scanf("%i", &ano);
    } while (ano < 2022 || ano > 2025);

    return ano;
}
int validador_mes()
{
    int mes;

    do
    {
        printf("\nMES: ");
        scanf("%i", &mes);
    } while (mes > 12 || mes < 1);

    return mes;
}
int validador_dia(int mes, int ano)
{
    int dia, max = 0, indice;
    do
    {
        printf("\nDIA: ");
        scanf("%i", &dia);
        if (mes == 2)
        {
            if ((ano % 4 == 0 && ano % 100 != 0) || ano % 400 == 0)
            {
                max = 29;
            }else
            {
                max = 28;
            }
        }else if (mes == 4 || mes == 6 || mes == 9 || mes == 11)
        {
            max = 30;
        }else
        {
            max = 31;
        }
    } while (dia < 0 || dia > max);
    return dia;
}
void gravar_dados_binario(t_estudante estudantes[], int numero_estudantes, t_fichas fichas[], int numero_fichas, t_submissoes submissao[], int numero_submissoes)
{
    FILE *ficheiro = fopen("dados.bin", "wb");
    if (ficheiro != NULL)
    {
        // Gravar estudantes
        fwrite(&numero_estudantes, sizeof(int), 1, ficheiro);
        fwrite(estudantes, sizeof(t_estudante), numero_estudantes, ficheiro);
        // Gravar fichas
        fwrite(&numero_fichas, sizeof(int), 1, ficheiro);
        fwrite(fichas, sizeof(t_fichas), numero_fichas, ficheiro);
        // Gravar submissões
        fwrite(&numero_submissoes, sizeof(int), 1, ficheiro);
        fwrite(submissao, sizeof(t_submissoes), numero_submissoes, ficheiro);
        printf("--DADDOS GRAVADOS COM SUCESSO!--\n");
    }
    else
    {
        printf("ERRO! Ao abrir o arquivo!\n");
    }
    fclose(ficheiro);
}
void ler_dados_binario(t_estudante estudantes[], int *numero_estudantes, t_fichas fichas[], int *numero_fichas, t_submissoes submissao[], int *numero_submissoes)
{
    FILE *ficheiro = fopen("dados.bin", "rb");
    if (ficheiro != NULL)
    {
        // Ler estudantes
        fread(numero_estudantes, sizeof(int), 1, ficheiro);
        fread(estudantes, sizeof(t_estudante), *numero_estudantes, ficheiro);
        // Ler fichas
        fread(numero_fichas, sizeof(int), 1, ficheiro);
        fread(fichas, sizeof(t_fichas), *numero_fichas, ficheiro);
        // Ler submissões
        fread(numero_submissoes, sizeof(int), 1, ficheiro);
        fread(submissao, sizeof(t_submissoes), *numero_submissoes, ficheiro);
        printf("\n--DADOS LIDOS COM SUCESSO!--\n");
    }
    else
    {
        printf("\nERRO! Ao abrir o arquivo!\n");
    }
    fclose(ficheiro);
}
