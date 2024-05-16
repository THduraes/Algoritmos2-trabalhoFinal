#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
int func_menu(int *num);
int func_menu_secund(int *num, char menu[]);
int listas_menu(int *num);


typedef struct
{
  int dia, mes, ano;
} date;

typedef struct
{
  char rua[50], cidade[50], estado[50];
  int numero;
} address;

typedef struct
{
  char nome[50], cpf[12];
  int telefone;
  address end;
  date data;
} client;

typedef struct
{
  char nome[50];
  int cod, quantidade, preco;
} pizza;

typedef struct
{
  client cliente;
  pizza piz;
  int qntd, vlT;
} sell;

int func_menu(int *num){
  int aux = 0;
  
  printf("MENU PRINCIPAL \n");
  printf("1- inclusao, alteracao, consulta, delecao do cliente\n");
  printf("2- inclusao, alteracao, consulta, delecao de Pizza\n");
  printf("3- inclusao, alteracao, consulta, delecao de venda\n");
  printf("4- listar clientes, pizzas ou vendas\n");
  printf("5- para sair do programa\n ");
  printf("Opcao: ");
  scanf("%d", &aux);
  *num = aux;
  return *num;
}
int func_menu_secund(int *num, char menu[]){
  int aux = 0;
  printf("\n MENU %s\n", menu);
  printf("1- Inclusao de %s\n", menu);
  printf("2- Alteracao de %s\n", menu);
  printf("3- Consulta de %s\n", menu);
  printf("4- Delecao de %s\n", menu);
  printf("5- Voltar para o menu anterior\n");
  printf("Opcao: ");
  scanf("%d", &aux);
  *num = aux;
  return *num;
}
int listas_menu(int *num){
  int aux = 0;
  printf("MENU DE LISTAS \n");
  printf("1- listar Clientes\n");
  printf("2- listar Pizzas\n");
  printf("3- listar Vendas\n");
  printf("4- clientes compraram acima de um valor\n");
  printf("5- quantidade de produtos com estoque abaixo de um certo valor\n");
  printf("6- Voltar para o menu anterior\n");
  printf("Opcao: ");
  scanf("%d", &aux);
  *num = aux;
  return *num;
}
void cadastroPi(pizza *piz, int *qntPi){
  int conf = 0, tam;

  if (piz[0].cod == 0){
    *qntPi = 0;
  }
  printf("Adicionando pizzas!");
  do{
    conf = 0;
    printf("\nDigite o codigo da pizza: ");
    scanf("%d", &tam);
    for (int j = 0; j <= *qntPi; j++){
      if (tam == piz[j].cod){
        conf = 1;
        printf("\n Nao e possivel adicionar um codigo existente\n");
      }
    }
  }while (conf != 0);
  piz[*qntPi].cod = tam;
  printf("Digite o nome da pizza: ");
  fflush(stdin);
  gets(piz[*qntPi].nome);
  printf("Digite a quantidade de estoque desta pizza: ");
  scanf("%d", &piz[*qntPi].quantidade);
  printf("Digite o preco desta pizza: ");
  scanf("%d", &piz[*qntPi].preco);
  (*qntPi)++;
}
void cadastroClt(client *cli, int *qntCl){
  char cpf[11];
  int resp = 0;
  do
  {
    resp = 0;
    fflush(stdin);
    printf(" Insira o cpf: ");
    gets(cpf);
    for (int j = 0; j < *qntCl; j++){
      if (strcmp(cpf, cli[j].cpf) == 0)
      {
        printf("Nao foi possivel adicionar, cpf ja existente\n");
        resp = 1;
      }
    }
  } while (resp != 0);
  strcpy(cli[*qntCl].cpf, cpf);

  fflush(stdin);
  printf("Digite o nome do cliente: ");
  gets(cli[*qntCl].nome);

  printf("Digite o telefone do cliente: ");
  scanf("%d", &cli[*qntCl].telefone);
  printf("Digite a rua do cliente: ");
  fflush(stdin);
  gets(cli[*qntCl].end.rua);
  printf("Digite a cidade do cliente: ");
  gets(cli[*qntCl].end.cidade);
  printf("Digite o estado do cliente: ");
  gets(cli[*qntCl].end.estado);
  printf("Digite o numero da casa do cliente: ");
  fflush(stdin);
  scanf("%d", &cli[*qntCl].end.numero);
  printf("Digite a data de aniversario do cliente\nNeste formato: 11/12/2003\nOpcao: ");
  scanf("%d/%d/%d",&cli[*qntCl].data.dia,&cli[*qntCl].data.mes,&cli[*qntCl].data.ano);
  fflush(stdin);
  (*qntCl)++;
}
void cadastroVen(sell *ven, int *qntVen, pizza *piz, client *cli, int qntCl, int qntPi){
  int i = 0, j=0, cod, qntdPi=0;
  char cpf[11];

  fflush(stdin);
  printf(" Insira o cpf: ");
  gets(cpf);

  while (i < qntCl && strcmp(cli[i].cpf,cpf) != 0){
    i++;
  }
  if (i == qntCl){
    printf("Cpf nao existe\n");
  }
  else{

    printf("Digite o codigo da pizza: ");
    scanf("%d",&cod);
    while (j < qntPi && cod!=piz[j].cod){
      j++;
    }
    if(j==qntPi){
    printf("Codigo nao existe\n");
    }
    else{
      printf("Digite a quantidade de pizza: ");
      scanf("%d",&qntdPi);
      while (piz[j].quantidade<qntdPi){
        printf("Não existe essa quantidade de pizza!\n");
        printf("Peca outra quantidade: ");
        scanf("%d",&qntdPi);
      }
      strcpy(ven[*qntVen].cliente.cpf, cpf);
      strcpy(ven[*qntVen].cliente.nome, cli[i].nome);
      ven[*qntVen].piz.cod = cod;
      strcpy(ven[*qntVen].piz.nome,piz[j].nome);
      piz[j].quantidade = piz[j].quantidade-qntdPi;
      ven[*qntVen].qntd = qntdPi;
      ven[*qntVen].vlT = qntdPi * piz[j].preco;
      printf("Venda concluida com sucesso\n");
      (*qntVen)++;
    }
  }
}
void alteracaoClt(client *cli, int qntCl){
  int i=0, op=0;
  char cpf[11];
  printf("Digite o cpf do cliente que deseja alterar os dados: ");
  fflush(stdin);
  gets(cpf);
  while (i < qntCl && strcmp(cli[i].cpf,cpf) != 0)
  {
    i++;
  }
  if(i==qntCl){
    printf("Cpf nao existe\n");
  }
  else{

    printf("Qual informacao deseja alterar:\n1- Nome\n2- Telefone\n3- Rua\n4- Cidade\n5- Estado\n6- Numero de endereco\n");
    scanf("%d",&op);
    fflush(stdin);
    switch (op)
    {
    case 1:
      printf("Digite um novo nome: ");
      gets(cli[i].nome);
      break;
    case 2:
      printf("Digite um novo Telefone: ");
      scanf("%d",&cli[i].telefone);
      break;
    case 3:
      printf("Digite uma nova rua: ");
      gets(cli[i].end.rua);
      break;
    case 4:
      printf("Digite uma nova cidade: ");
      gets(cli[i].end.cidade);
      break;
    case 5:
      printf("Digite um novo estado: ");
      gets(cli[i].end.estado);
      break;
    case 6:
      printf("Digite um novo numero de endereco: ");
      scanf("%d",&cli[i].end.numero);
      fflush(stdin);
      break;
    case 7:
      printf("Digite nova data de aniversario\nExemplo (11/12/2003)\nOpcao:");
      scanf("%d/%d/%d",&cli[i].data.dia, &cli[i].data.mes, &cli[i].data.ano);
      fflush(stdin);
      break;

    default:
      printf("Opcao invalida\n");
      break;
    }
  }
}
void alteracaoPi(pizza *piz, int qntPi){
  int i=0, op=0;
  int cod=0;
  printf("Digite o codigo da pizza que deseja alterar os dados: ");
  scanf("%d",&cod);
  fflush(stdin);
  while (i < qntPi && cod!=piz[i].cod)
  {
    i++;
  }
  if(i==qntPi){
    printf("Codigo nao existe\n");
  }
  else{
    printf("Digite qual alteracao deseja fazer nas pizzas:\n1- Nome\n2- Codigo\n3- Quantidade\n4- Preco\nOpcao: ");
    scanf("%d",&op);
    switch (op)
    {
    case 1:
      fflush(stdin);
      printf("Digite um novo nome: ");
      gets(piz[i].nome);
      break;
    case 2:
      printf("Digite um novo Codigo: ");
      scanf("%d",&piz[i].cod);
      break;
    case 3:
      printf("Digite uma nova quantidade: ");
      scanf("%d",&piz[i].quantidade);
      break;
    case 4:
      printf("Digite um novo preco: ");
      scanf("%d",&piz[i].preco);
      break;
    default:
      printf("Opcao invalida\n");
      break;
    }
  }
}
void alteracaoVen(sell *ven, int qntVen, pizza *piz, int qntPi){
  int i = 0, j=0, k=0,l=0, cod, op=0, qnt=0;
  char cpf[11];
  printf("Digite o Cpf do cliente que realizou a venda: ");
  fflush(stdin);
  gets(cpf);
  while (i < qntVen && strcmp(ven[i].cliente.cpf,cpf) != 0)
  {
    i++;
  }
  if (i == qntVen){
    printf("Cpf nao existe em nenhuma venda\n");
  }
  else{
    printf("Deseja alterar:\n1- Alteracao da Pizza\n2- Alteracao da quantidade\n");
    scanf("%d",&op);
    if(op==1){
      printf("Digite o codigo da nova pizza: ");
      scanf("%d",&cod);
      while (j < qntPi && cod!=piz[j].cod){
        j++;
      }
      if(j==qntPi){
        printf("Codigo nao existe\n");
      }
      else{
        while (k<qntPi && ven[i].piz.cod!=piz[k].cod){
          k++;
        }

        if(ven[i].qntd>piz[j].quantidade){ // conferindo a venda que ja estava no cpf, com a quantidade da nova pizza
          printf("Não existe a quantidade de pizza necessaria para alteracao!\n");
          piz[k].quantidade=piz[k].quantidade-ven[i].qntd;
        }
        else{
          piz[k].quantidade=piz[k].quantidade+ven[i].qntd;
          ven[i].piz.cod = cod;
          piz[j].quantidade = piz[j].quantidade - ven[i].qntd;
          printf("Alteracao feita com sucesso\n");
        }
      }
    }
    else if(op==2){
      printf("Digite a nova quantidade na venda: ");
      scanf("%d",&qnt);
      while (l < qntPi && ven[i].piz.cod!=piz[l].cod){
        l++;
      }
      piz[l].quantidade = piz[l].quantidade+ven[i].qntd;
      if(qnt > piz[l].cod){
        printf("Nao pode realizar a alteracao da quantidade!\n");
        piz[l].quantidade = piz[l].quantidade-ven[i].qntd;
      }
      else{
        piz[l].quantidade = piz[l].quantidade - qnt;
        ven[i].qntd = qnt;
        printf("Quantidade alterada com sucesso!\n");
      }
    }
    else{
      printf("Opcao invalida!\n");
    }
  }

}
void consultClt(client *cli, int qntCl){
  int i=0;
  char cpf[11];
  printf("Digite o cpf do cliente que deseja consultar: ");
  fflush(stdin);
  gets(cpf);
  while (i<qntCl && strcmp(cli[i].cpf,cpf) != 0)
  {
    i++;
  }
  if(i == qntCl){
    printf("Cliente nao encontrado!\n");
  }
  else{
    printf("----INFORMACOES DO CLIENTE----\n\n");
    printf("Nome: %s\n",cli[i].nome);
    printf("Cpf: %s\n",cli[i].cpf);
    printf("Telefone: %d\n",cli[i].telefone);
    printf("Data de nascimento: %d/%d/%d\n",cli[i].data.dia, cli[i].data.mes,cli[i].data.ano);
    printf("\n");
    printf("----ENDERECO DO CLIENTE----\n\n");
    printf("Rua: %s\n",cli[i].end.rua);
    printf("Cidade: %s\n",cli[i].end.cidade);
    printf("Estado: %s\n",cli[i].end.estado);
    printf("Numero da casa: %d\n",cli[i].end.numero);
  }
}
void consultPi(pizza *piz, int qntPi){
  int i=0, cod=0;
  printf("Digite o codigo da pizza que deseja consultar: ");
  scanf("%d",&cod);
  while(i<qntPi && cod!=piz[i].cod){
    i++;
  }
  if(i==qntPi){
    printf("Pizza nao encontrada!\n");
  }
  else{
    printf("----INFORMACOES DA PIZZA----\n\n");
    printf("Nome: %s\n",piz[i].nome);
    printf("Codigo: %d\n",piz[i].cod);
    printf("Quantidade: %d\n",piz[i].quantidade);
    printf("Preco: %d reais\n",piz[i].preco);
  }

}
void consultVen(sell *ven, int qntVen, int qntCl, client *cli, pizza *piz, int qntPi){

  int i=0,j=0,k=0;
  char cpf[11];
  fflush(stdin);
  gets(cpf);
  while (i<qntVen && strcmp(cpf,ven[i].cliente.cpf)!=0)
  {
    i++;
  }
  if(i==qntVen){
    printf("Nenhuma venda cadastrada com esse cpf!\n");
  }
  else{
    while (j<qntCl && strcmp(cpf,cli[j].cpf)!=0)
    {
      j++;
    }
    while (k<qntPi && ven[i].piz.cod!=piz[k].cod)
    {
      k++;
    }
    
    printf("----INFORMACOES DA VENDA----\n\n");
    printf("Nome do cliente: %s\n",cli[j].nome);
    printf("Cpf cadastrado na venda: %s\n",cli[j].cpf);
    printf("Nome da pizza: %s\n",piz[k].nome);
    printf("Valor: %d\n",ven[i].vlT);
  }
}
void deletClt(client *cli, int *qntCl,sell *ven, int qntVen){
  int i=0, j=0;
  char cpf[11];

  printf("Digite o cpf do cliente que deseja deletar: ");
  fflush(stdin);
  gets(cpf);
  while (i<*qntCl && strcmp(cpf,cli[i].cpf)!=0){
    i++;
  }
  if(i==*qntCl){
    printf("Cpf inexistente!\n");
  }
  else{
    while (j<qntVen && strcmp(cpf,ven[i].cliente.cpf)!=0){
      j++;
    }
    if(j==qntVen){
      printf("Cpf nao está em nenhuma venda, cliente pode ser excluido\n");
      for(int k=i;k<*qntCl; k++){
      cli[k]=cli[k+1];
      }
      (*qntCl)--;
    }
    else{
      printf("Cpf esta cadastrado em uma venda, não pode fazer a delecao!\n");
    }
  }
}
void deletPi (pizza *piz, int *qntPi,sell *ven, int qntVen){
  int i=0, j=0, cod=0;
  printf(" Digite o codigo da Pizza que deseja deletar: ");
  scanf("%d", &cod);
  while (i<*qntPi && cod != piz[i].cod){
    i++;
  }
  printf("%d", cod);
  if(i==*qntPi){
    printf("Codigo inexistente!\n");
  }
  else{
    while (j<qntVen && cod != ven[i].piz.cod){
      j++;
    }
    if(j==qntVen){
      printf("Codigo nao esta em nenhuma venda, Pizza pode ser excluida\n");
      for(int k=i;k<*qntPi; k++){
      piz[k]=piz[k+1];
      }
      (*qntPi)--;
    }
    else{
      printf("Codigo esta cadastrado em uma venda, não pode fazer a delecao!\n");
    }
  }
}
void deletVen(sell *ven, int *qntVen,pizza *piz, int qntPi){
  int i=0,j=0;
  char cpf[11],letra;
  fflush(stdin);
  printf("Digite o cpf do cliente que deseja fazer a exclusao da venda: ");
  gets(cpf);
  while(i<*qntVen && strcmp(ven[i].cliente.cpf,cpf)!=0){
    i++;
  }
  if(i==*qntVen){
    printf("Cpf nao esta cadastrado em nenhuma venda\n");
  }
  else{
    printf("Deseja realmente fazer a exclusao dessa venda?(s)-Sim || (n)-Nao");
    printf("Opcao: ");
    letra = getchar();
    if(letra == 's'|| letra == 'S'){
      while (j < qntPi && piz[j].cod!=ven[i].piz.cod)
      {
        j++;
      }
      piz[j].quantidade = piz[j].quantidade + ven[i].qntd;
      ven[i]=ven[i+1];
      printf("Venda excluida!\n");
    }
    else if(letra == 'n' || letra == 'N'){
      printf("Exclusao cancelada\n");
    }
  }
  }
void listClt(client *cli, int qntCl){
    int i;
    for (i=0;i<qntCl;i++) {
        printf("\nCliente %d", i+1);
        printf("\nNome: %s", cli[i].nome);
        printf("\nCPF: %s", cli[i].cpf);
        printf("\nTelefone: %d", cli[i].telefone);
        printf("\nEndereco\n");
        printf("Rua: %s", cli[i].end.rua);
        printf("\nNumero: %d", cli[i].end.numero);
        printf("\nCidade: %s", cli[i].end.cidade);
        printf("\nEstado: %s", cli[i].end.estado);
        printf("\nData de nascimento\n");
        printf("%d/%d/%d\n", cli[i].data.dia, cli[i].data.mes, cli[i].data.ano);
    }
}
void listPiz(pizza *piz, int qntPi){
    int i;
    for (i=0;i<qntPi;i++) {
        printf("\nPizza %d", i+1);
        printf("\nNome: %s", piz[i].nome);
        printf("\nCodigo: %d", piz[i].cod);
        printf("\nQuantidade: %d", piz[i].quantidade);
        printf("\nPreco: %d\n", piz[i].preco);
    }
}
void listVen(sell *venda, int qntVen){
    int i;
    for (i=0;i<qntVen;i++) {
        printf("\nVenda %d", i+1);
        printf("\nCpf cliente: %s", venda[i].cliente.cpf);
        printf("\nCodigo da Pizza: %d", venda[i].piz.cod);
        printf("\nNome da pizza: %s", venda[i].piz.nome);
        printf("\nQuantidade: %d", venda[i].qntd);
        printf("\nPreco total da Venda: %d\n", venda[i].vlT);
    }
}
void valorCmp(sell *venda, int qntVen){
    int i, cont=0, valor;
    printf("\n -- Escolha um valor para mostrar quantos clientes compraram acima dele --");
    printf("\nValor de compra: ");
    scanf("%d", &valor);
    for(i=0;i<qntVen;i++){
        if(venda[i].vlT > valor){
            cont++;
        }
    }
    printf("Quantidade de Clientes que compraram acima desse valor: ");
    printf("%d\n", cont);
}
void estoqueAbx(pizza *piz, int qntPi){
    int i, cont=0, valor;
    printf("\n - Escolha um numero para mostrar a quantidade de produtos com estoque abaixo dele -");
    printf("\nNumero: ");
    scanf("%d", &valor);
    for(i=0;i<qntPi;i++){
        if(piz[i].quantidade < valor){
            cont++;
        }
    }
    printf("\nQuantidade de Produtos com estoque abaixo do valor: ");
    printf("%d\n", cont);
}
void carregaStructs(int *qntCl, client *cli,int *qntPi, pizza *piz, int *qntVen, sell *ven){
    FILE *arq;
    arq = fopen("Clientes.txt","rb");
     if (arq == NULL) {
        printf("#Error 404#");
    }else{
        while(fread(&cli[*qntCl],sizeof(client),1,arq)==1){
            (*qntCl)++;
        }
    }
    fclose(arq);
    arq = fopen("Pizzas.txt","rb");
     if (arq == NULL) {
        printf("$Erro 404#");
    }else{
        while(fread(&piz[*qntPi],sizeof(pizza),1,arq)==1){
            (*qntPi)++;
        }
    }
    fclose(arq);
    arq = fopen("Vendas.txt","rb");
     if (arq == NULL) {
        printf("#Erro 404#");
    }else{
        while(fread(&ven[*qntVen],sizeof(sell),1,arq)==1){
            (*qntVen)++;
        }
    }
    fclose(arq);
}
void attCl(int *qntCl,client *cli){
    FILE *arq;
    arq = fopen("Clientes.txt","wb");
    if(arq==NULL){
        printf("Erro01\n");
    }else{
    for(int i=0;i<*qntCl;i++){
        fwrite(&cli[i],sizeof(client),1,arq);
    }
    }
    fclose(arq);
}
void attPi(int *qntPi,pizza *piz){
    FILE *arq;
    arq = fopen("Pizzas.txt","wb");
    if(arq==NULL){
        printf("Erro01\n");
    }else{
    for(int i=0;i<*qntPi;i++){
        fwrite(&piz[i],sizeof(pizza),1,arq);
    }
    }
    fclose(arq);
}
void attVen(int *qntVen,sell *ven){
    FILE *arq;
    arq = fopen("Vendas.txt","wb");
    if(arq==NULL){
        printf("Erro01\n");
    }else{
    for(int i=0;i<*qntVen;i++){
        fwrite(&ven[i],sizeof(sell),1,arq);
    }
    }
    fclose(arq);
}
int main()
{
  int qntCl = 0, qntPi = 0, qntVen = 0, num, i=0;

  client cli[100];
  pizza piz[100];
  sell venda[100];
  carregaStructs(&qntCl,cli,&qntPi,piz,&qntVen,venda);
  printf("π PIzzaria EXPRESS! π - BEM VINDO(A)\n");
  while (i < 3) {
        system("cls");
        printf("                                                        ^                     \n");
        printf("                                                       ( )                     \n");
        printf("                                                      (   )                     \n");
        printf("                                                     (     )                    \n");
        printf("                                                    (       )                   \n");
        printf("                                                   (         )                  \n");
        printf("                                                  (           )                 \n");
        printf("                                                 (             )                \n");
        printf("                                                (    PIzzaria   )               \n");
        printf("                                               (      EXPRESS    )              \n");
        printf("                                              (                   )              \n");
        printf("                                             (                     )             \n");
        printf("                                            (_______________________)            \n");
        Sleep(500); 
        i++;
    }
    system("cls");
  do
  {
    fflush(stdin);
    num = func_menu(&num);
    fflush(stdin);
    switch (num)
    {
    case 1:
      do
      {
        fflush(stdin);
        char menu[7] = "CLIENTE";
        num = func_menu_secund(&num, menu);
        switch (num)
        {
        case 1:
          printf(" -- CADASTRO DO CLIENTE -- \n");
          cadastroClt(cli, &qntCl);
          attCl(&qntCl,cli);
          break;
        case 2:
          printf(" -- Alterar dados de Clientes --\n");
          alteracaoClt(cli,qntCl);
          attCl(&qntCl,cli);
          break;
        case 3:
          printf(" -- Consulta de Clientes --\n");
          consultClt(cli,qntCl);
          break;
        case 4:
          printf(" -- Delecao de Clientes --\n");
          deletClt(cli,&qntCl,venda,qntCl);
          attCl(&qntCl,cli);
          break;
        case 5:
          printf(" Saindo do menu...\n");
          break;
        default:
          printf(" Opcao invalida!\n");
          break;
        }
      } while (num != 5);
      num = 0;
      break;
    case 2:
      do
      {
        fflush(stdin);
        char menu[7] = "PIZZA";
        num = func_menu_secund(&num, menu);
        switch (num)
        {
        case 1:
          printf(" -- CADASTRO DA PIZZA -- \n");
          cadastroPi(piz, &qntPi);
          attPi(&qntPi,piz);
          break;
        case 2:
          printf(" -- Alterar dados de Pizzas -- \n");
          alteracaoPi(piz,qntPi);
          attPi(&qntPi,piz);
          break;
        case 3:
          printf(" -- Consulta de Pizza --\n");
          consultPi(piz,qntPi);
          break;
        case 4:
          printf(" -- Delecao de Pizza --\n");
          deletPi (piz, &qntPi, venda, qntVen);
          attPi(&qntPi,piz);
          break;
        case 5:
          printf("Saindo do menu...\n");
          break;
        default:
          printf("Opcao invalida!\n");
          break;
        }

      } while (num != 5);
      num = 0;
      break;
    case 3:
      do
      {
        fflush(stdin);
        char menu[7] = "VENDA";

        num = func_menu_secund(&num, menu);
        switch (num)
        {
        case 1:
          printf(" -- CADASTRO DA VENDA -- \n");
          cadastroVen(venda, &qntVen, piz, cli, qntCl, qntPi);
          attVen(&qntVen,venda);
          break;
        case 2:
          printf(" -- Alterar dados da Venda --\n");
          alteracaoVen(venda, qntVen, piz, qntPi);
          attVen(&qntVen,venda);
          break;
        case 3:
          printf(" -- Consulta de Venda --\n");
          
          consultVen(venda,qntVen,qntCl,cli,piz,qntPi);
          break;
        case 4:
          printf(" -- Delecao de Venda --\n");
          deletVen(venda,&qntVen,piz,qntPi);
          attVen(&qntVen,venda);
          break;
        case 5:
          printf("Saindo do menu...\n");
          break;
        default:
          printf("Opcao invalida!\n");
          break;
        }
      } while (num != 5);
      num = 0;
      break;
    case 4:
        do{
        fflush(stdin);
        num = listas_menu(&num);
        fflush(stdin);
        switch (num)
        {
        case 1:
            printf(" LISTAR os CLIENTES ");
            listClt(cli, qntCl);
          break;
        case 2:
            printf(" LISTAR as PIZZAS ");
            listPiz(piz, qntPi);
          break;
        case 3:
            printf(" LISTAR as VENDAS ");
            listVen(venda, qntVen);
          break;
        case 4:
        printf(" LISTAR CLIENTES ACIMA DE UM VALOR ");
        valorCmp(venda, qntVen);

          break;
        case 5:
          printf(" QUANTIDADE DE PIZZAS ABAIXO DE UM CERTO VALOR\n");
          estoqueAbx(piz, qntPi);
          break;
          case 6:
          break;

        default:
          printf("Opcao invalida!\n");
          break;
        }
      } while (num != 6);
      num = 0;
        break;
    case 5:
      printf("\nSAINDO DO PROGRAMA :D\n");
      break;
    default:
      printf("Opcao invalida!\n");
      break;
    }

  } while (num != 5);

  return 0;
}