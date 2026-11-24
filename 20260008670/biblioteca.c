#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Livros
struct tLivro{
    char titulo[50];
    char autor[50];
    int ano;
    int codigo;
    int status;
    char email[50];
    struct tLivro *prox;
};

// Usuários
struct tUsuario{
    char email[50];
    char nome[50];
    struct tUsuario *prox;
};

// Cadastro
void cadastrarlivro(struct tLivro **livros) {
    struct tLivro *novo = malloc(sizeof(struct tLivro));

    if(novo == NULL){
        return;
    }
    
    printf("Titulo: \n");
    scanf("%s", novo->titulo);
    printf("Autor: \n");
    scanf("%s", novo->autor);
    printf("Ano de publicação: \n");
    scanf("%d", &novo->ano);
    printf("Código: \n");
    scanf("%d", &novo->codigo);
    novo->status = 0;
    novo->email[0] = '\0';
    
    novo->prox = *livros;
    *livros = novo;
}

void cadastrarusuario(struct tUsuario **usuarios){
    struct tUsuario *novo = malloc(sizeof(struct tUsuario));
    struct tUsuario *atual;
    int i, igual = 0;

    if(novo == NULL){
        return;
    }
    printf("Email: ");
    scanf("%s", novo->email);
    atual = *usuarios;
    while(atual != NULL && igual == 0){
        i = 0;
        while(atual->email[i] == novo->email[i] && novo->email[i] != '\0'){
            i++;
        }
        if(atual->email[i] == novo->email[i]){
            igual = 1;
        }
        atual = atual->prox;
    }
    if(igual == 1){
        printf("Email já cadastrado\n");
        free(novo);
        return;
    }

    printf("Nome: ");
    scanf("%s", novo->nome);
    novo->prox = *usuarios;
    *usuarios = novo;
}

void cadastro(struct tLivro **livros, struct tUsuario **usuarios){
    int alternativacadastro = -1;
    while(alternativacadastro != 0){
        printf("===============\n");
        printf("1. Livros\n");
        printf("2. Usuários\n");
        printf("0. Voltar\n");
        printf("===============\n");

        printf("Opção: ");
        scanf("%d", &alternativacadastro);

        if(alternativacadastro == 1){
            cadastrarlivro(livros);
        }else{
            if(alternativacadastro == 2){
                cadastrarusuario(usuarios);
            }else{
                if(alternativacadastro != 0){
                    printf("opção inválida\n");
                }
                }
            }
    }
    return;
}

// Consulta
void consultarlivro(struct tLivro *livros){
    int consultarlivrocodigo = 0;
    printf("código do livro para a consulta: ");
    scanf("%d", &consultarlivrocodigo);

    while(livros != NULL && livros->codigo != consultarlivrocodigo){
        livros = livros->prox;
    }
    if(livros == NULL){
        printf("=========================\n");
        printf("livro não encontrado\n");
        printf("=========================\n");
    }else{
        printf("Titulo: %s\n", livros->titulo);
        printf("Autor: %s\n", livros->autor);
        printf("Ano: %d\n", livros->ano);
        printf("Código: %d\n", livros->codigo);
        printf("Status: %d\n", livros->status);
        printf("Email: %s\n", livros->email);
    }
}

void consultarusuario(struct tUsuario *usuarios){
    int opcao = 0;
    int i;
    int achou = 0;
    char busca[50];
    printf("1. Buscar por email\n");
    printf("2. Buscar por nome\n");
    printf("opção: ");
    scanf("%d", &opcao);

    if(opcao == 1){
        printf("email: ");
        scanf("%s", busca);
        while(usuarios != NULL && achou == 0){
            i = 0;
            while(usuarios->email[i] == busca[i] && busca[i] != '\0'){
                i++;
            }

            if(usuarios->email[i] == busca[i]){
                printf("nome: %s\n", usuarios->nome);
                printf("email: %s\n", usuarios->email);
                achou = 1;
            }
            usuarios = usuarios->prox;
        }
    }else{
        if(opcao == 2){
            printf("nome: ");
            scanf("%s", busca);

            while(usuarios != NULL){
                i = 0;
                while(usuarios->nome[i] == busca[i] && busca[i] != '\0'){
                    i++;
                }

                if(usuarios->nome[i] == busca[i]){
                    printf("nome: %s\n", usuarios->nome);
                    printf("email: %s\n", usuarios->email);
                    achou = 1;
                }
                usuarios = usuarios->prox;
            }
        }else{
            printf("opção inválida\n");
            return;
        }
    }
    if(achou == 0){
        printf("usuário não cadastrado\n");
    }
}

void consultaremprestimo(struct tLivro *livros, struct tUsuario *usuarios){
    char emailconsulta[50];
    int i;
    int achou = 0;
    printf("email do usuário: ");
    scanf("%s", emailconsulta);

    while(usuarios != NULL){
        i = 0;
        while(usuarios->email[i] == emailconsulta[i] && emailconsulta[i] != '\0'){
            i++;
        }
        if(usuarios->email[i] == emailconsulta[i]){
            while(livros != NULL){
                if(livros->status == 1){
                    i = 0;
                    while(livros->email[i] == emailconsulta[i] && emailconsulta[i] != '\0'){
                        i++;
                    }
                    if(livros->email[i] == emailconsulta[i]){
                        printf("código: %d\n", livros->codigo);
                        printf("título: %s\n", livros->titulo);
                        printf("autor: %s\n", livros->autor);
                        achou = 1;
                    }
                }
                livros = livros->prox;
            }
            if(achou == 0){
                printf("esse usuário não possui livros emprestados\n");
            }
            return;
        }
        usuarios = usuarios->prox;
    }
    printf("usuário não cadastrado\n");

}

void consulta(struct tLivro *livros, struct tUsuario *usuarios){
    int alternativaconsulta = -1;
    while(alternativaconsulta != 0){
        printf("==============\n");
        printf("1. Livros\n");
        printf("2. Usuários\n");
        printf("3. Empréstimos\n");
        printf("0. Voltar\n");
        printf("==============\n");

        printf("opção: ");
        scanf("%d", &alternativaconsulta);

        if(alternativaconsulta == 1){
            consultarlivro(livros);
        }else{
            if(alternativaconsulta == 2){
                consultarusuario(usuarios);
            }else{
                if(alternativaconsulta == 3){
                    consultaremprestimo(livros, usuarios);
                }else{
                    if(alternativaconsulta != 0){
                        printf("opção inválida\n");
                    }
                }
            }
        }
    }
}

// Atualização
void atualizarlivro(struct tLivro *livros){
    int idatualizar = 0;
    printf("informe o ID do livro: ");
    scanf("%d", &idatualizar);
    
    while(livros != NULL && livros->codigo != idatualizar){
        livros = livros->prox;
    }
    if(livros != NULL){
        printf("Novo nome: ");
        scanf("%s", livros->titulo);
        printf("Novo autor: ");
        scanf("%s", livros->autor);
        printf("Novo ano: ");
        scanf("%d", &livros->ano);
    }else{
        printf("livro não encontrado\n");
    }

}

void atualizarusuario(struct tUsuario *usuarios){
    char emailatualizar[50];
    int i;
    printf("informe o email do usuário: ");
    scanf("%s", emailatualizar);

    while(usuarios != NULL){
        i = 0;
        while(usuarios->email[i] == emailatualizar[i] && emailatualizar[i] != '\0'){
            i++;
        }
        if(usuarios->email[i] == emailatualizar[i]){
            printf("novo nome: ");
            scanf("%s", usuarios->nome);
            return;
        }
        usuarios = usuarios->prox;
    }
    printf("usuário não cadastrado\n");
}

void atualizacao(struct tLivro *livros, struct tUsuario *usuarios){
    int alternativaatualizacao = -1;
    while(alternativaatualizacao != 0){
        
        printf("=============\n");
        printf("1. Livros\n");
        printf("2. Usuários\n");
        printf("0. Voltar\n");
        printf("=============\n");

        printf("opção: ");
        scanf("%d", &alternativaatualizacao);

        if(alternativaatualizacao == 1){
            atualizarlivro(livros);
        }else{
            if(alternativaatualizacao == 2){
                atualizarusuario(usuarios);
            }else{
                if(alternativaatualizacao != 0){
                    printf("opção inválida\n");
                }
            }
        }

    }
}

// Exclusão
void excluirlivro(struct tLivro **livros){
    struct tLivro *atual = *livros;
    struct tLivro *anterior = NULL;

    int idexcluir = 0;
    printf("digite o código do livro: ");
    scanf("%d", &idexcluir);

    while(atual != NULL && atual->codigo != idexcluir){
        anterior = atual;
        atual = atual->prox;
    }

    if(atual != NULL){
        if(anterior == NULL){
            *livros = atual->prox;
        }else{
            anterior->prox = atual->prox;
        }
        free(atual);
        printf("livro excluido:\n");
    }else{
        printf("Livro não encontrado\n");
    }
    
}


void excluirusuario(struct tUsuario **usuarios, struct tLivro *livros){
    struct tUsuario *atual = *usuarios;
    struct tUsuario *anterior = NULL;
    struct tLivro *aux;
    char emailexcluir[50];
    int i;
    int igual = 0;
    int emprestado = 0;
    printf("digite o email do usuario: ");
    scanf("%s", emailexcluir);

    while(atual != NULL && igual == 0){
        i = 0;
        while(atual->email[i] == emailexcluir[i] && emailexcluir[i] != '\0'){
            i++;
        }
        if(atual->email[i] == emailexcluir[i]){
            igual = 1;
        }else{
            anterior = atual;
            atual = atual->prox;
        }
    }
    if(atual != NULL){
        aux = livros;
        while(aux != NULL && emprestado == 0){
            if(aux->status == 1){
                i = 0;
                while(aux->email[i] == emailexcluir[i] && emailexcluir[i] != '\0'){
                    i++;
                }

                if(aux->email[i] == emailexcluir[i]){
                    emprestado = 1;
                }
            }
            aux = aux->prox;
        }
        if(emprestado == 1){
            printf("Usuário possui livros emprestados\n");
        }else{
            if(anterior == NULL){
                *usuarios = atual->prox;
            }else{
                anterior->prox = atual->prox;
            }
            free(atual);
            printf("Usuário excluído com sucesso\n");
        }
    }else{
        printf("Usuário não cadastrado\n");
    }
}

void exclusao(struct tLivro **livros, struct tUsuario **usuarios){
    int alternativaexclusao = -1;
    while(alternativaexclusao != 0){
        printf("=============\n");
        printf("1. Livros\n");
        printf("2. Usuários\n");
        printf("0. Voltar\n");
        printf("=============\n");

        printf("opção: ");
        scanf("%d", &alternativaexclusao);

        if(alternativaexclusao == 1){
            excluirlivro(livros);
        }else{
            if(alternativaexclusao == 2){
                excluirusuario(usuarios, *livros);
            }else{
                if(alternativaexclusao != 0){
                    printf("opção inválida");
                }
            }
        }
    }
}

// Empréstimo
void emprestimo(struct tLivro *livros, struct tUsuario *usuarios){
    int idemprestimo = 0;
    int i;
    int igual = 0;
    char emailemprestimo[50];
    printf("digite o código do livro a ser emprestado: ");
    scanf("%d", &idemprestimo);
    printf("digite o email do usuario que deseja fazer o emprestimo: ");
    scanf("%s", emailemprestimo);

    while(livros != NULL && livros->codigo != idemprestimo){
        livros = livros->prox;
    }
    while(usuarios != NULL && igual == 0){
        i = 0;
        while(usuarios->email[i] == emailemprestimo[i] && emailemprestimo[i] != '\0'){
            i++;
        }

        if(usuarios->email[i] == emailemprestimo[i]){
            igual = 1;
        }else{
            usuarios = usuarios->prox;
        }
    }
    if(usuarios == NULL){
        printf("usuário não encontrado\n");
        return;
    }
    if(livros == NULL){
        printf("livro não encontrado\n");
        return;
    }else{
        if(livros->status == 1){
            printf("livro já foi emprestado\n");
        }else{
            i = 0;
            while(emailemprestimo[i] != '\0'){
                livros->email[i] = emailemprestimo[i];
                i++;
            }
            livros->email[i] = '\0';

            livros->status = 1;
            printf("o livro foi emprestado com sucesso\n");
        }
    }
}

// Devolução
void devolucao(struct tLivro *livros){
    int iddevolucao = 0;
    printf("Código do livro a ser devolvido: ");
    scanf("%d", &iddevolucao);

    while(livros != NULL && livros->codigo != iddevolucao){
        livros = livros->prox;
    }
    if(livros == NULL){
        printf("livro não encontrado\n");
        return;
    }
    if(livros->status == 0){
        printf("livro não foi emprestado\n");
    }else{
        livros->status = 0;
        livros->email[0] = '\0';
        printf("livro foi devolvido\n");
    }
}

// Programa principal
int main() {
    struct tLivro *livros = NULL;
    struct tUsuario *usuarios = NULL;
    
    int alternativa = -1;
    while(alternativa != 0){
        printf("============\n");
        printf("1. Cadasto\n");
        printf("2. Consulta\n");
        printf("3. Atualização\n");
        printf("4. Exclusão\n");
        printf("5. Empréstimo\n");
        printf("6. Devolução\n");
        printf("0. Sair\n");
        printf("============\n");

        printf("opção: ");
        scanf("%d", &alternativa);

        if(alternativa == 1){
            cadastro( &livros, &usuarios);
        }else{
            if(alternativa == 2){
                consulta(livros, usuarios);
            }else{
                if(alternativa == 3){
                     atualizacao(livros, usuarios);                   
                }else{
                    if(alternativa == 4){
                        exclusao(&livros, &usuarios);
                    }else{
                        if(alternativa == 5){
                            emprestimo(livros, usuarios);
                        }else{
                            if(alternativa == 6){
                                devolucao(livros);
                            }else{
                                if(alternativa == 0){
                                        struct tLivro *auxlivro;
                                        struct tUsuario *auxusuario;
                                        while(livros != NULL){
                                            auxlivro = livros;
                                            livros = livros->prox;
                                            free(auxlivro);
                                        }
                                        while(usuarios != NULL){
                                            auxusuario = usuarios;
                                            usuarios = usuarios->prox;
                                            free(auxusuario);
                                        }
                                        return 0;
                                }else{
                                    printf("alternativa inválida\n");
                                }
                            }
                        }
                    }
                }
            }
        }
        
    }

}

