#ifndef LISTA_H
#define	LISTA_H
#include <stdlib.h>

template <typename T> class LISTA {
    
 public:
  //construtor: não precisa de parâmetros para criar uma nova lista
  lista(){
    primeiro = NULL;
    ultimo = NULL;
    len = 0;
}
 
  // destrutor
  ~lista();
 
  // insere "algo" no inicio da lista
  void insere(const T & algo){ 
    if(len>0){
	  Nodo *nodo = new Nodo(algo);
	  nodo->proximo = primeiro;
          primeiro->anterior = nodo;
	  primeiro = nodo;
	  len++;
    }
    else{
	  Nodo *nodo = new Nodo(algo);
	  primeiro = nodo;
	  ultimo = nodo;
	  len++;
    }
}
 
  // adiciona "algo" no final da lista
  void anexa(const T & algo){
    Nodo* nodo = new Nodo(algo);
    if(len == 0){
       primeiro = nodo;
       ultimo = nodo;
    }else{
        ultimo->proximo = nodo;
        nodo->anterior = ultimo;
    }
    
    ultimo = nodo;
    len++;
}
 
  // insere "algo" em uma posição específica da lista  
  void insere(const T & algo, int posicao){
    if(posicao>len) throw "Posição superior ao permitido";
    
    if(posicao==0)
    insere(algo);

    if(posicao == len)
    anexa(algo);
    else{


    Nodo *aux, *temp, * nodo = new Nodo(algo);
    aux = primeiro;
    for(int i=0; i < posicao; i++){
    temp = aux;
    aux = aux->proximo;
    }

    temp->proximo = nodo;
    nodo->anterior = temp;
    nodo->proximo = aux;
    aux->anterior = nodo;
    len++;
    }
    
}
  void insereOrdenado(const T & algo);
 
  // remove o dado que está na "posicao" na lista, e retorna 
  // uma cópia desse dado
  T remove(int posicao){
  
    if(len < posicao) throw "Posição Inválida";
    if(posicao == 0){
        T algo = primeiro->dado;
        primeiro = primeiro->proximo;
        len--;
        return algo;
    }
    Nodo* deletar;
    Nodo* sucessor = primeiro;
    for(int pos = 0; pos < posicao; pos++){
        deletar = sucessor;
        sucessor = sucessor->proximo;
    }
    T algo = sucessor->dado;
    if(sucessor == ultimo){
        ultimo = deletar;
        deletar->proximo = NULL;
        ultimo->proximo = NULL;
        len--;
    }else{
    deletar->proximo = sucessor->proximo;
    sucessor->proximo->anterior = deletar;
    len--;
    }
    return algo;
}

 
  // remove todos os dados que forem equivalentes a "algo"
  void retira(const T & algo){
    for(int i = 0; i<len; i++){
        if(obtem(i) == algo){
            remove(i);
            i--;
        }
    }
}
 
  // estas duas operações são idênticas: retorna
  // uma referência ao dado que está na "posicao" na lista
  T& obtem(int posicao) const {
 if(len <= posicao) throw "Posição inválida";
    Nodo *aux = primeiro;
    for(int pos = 0; pos < posicao; pos++)
        aux = aux->proximo;
    return aux->dado;
}
 
  // Retorna uma referência a um dado que seja equivalente a "algo"
  T& procura(const T &algo) const {
    	Nodo * aux;
	lista<T> * iguais = new LISTA<T>;
	for (aux=inicio; aux != NULL; aux=aux->proximo) {
		if(algo==aux->dado){
			iguais->anexa(aux->dado);
		}
	}
	return iguais;
}
 
  // Procura todos os dados equivalentes a "algo", e os
  // anexa a "lista". Retorna uma referência a "lista".
 
  // retorna a quantidade de dados armazenados na lista
  int comprimento() const {
    return len;
}
 
  // retorna true se lista estiver vazia
  bool vazia() const {
    return len == 0;
}
 
  // Esvazia a lista
  void esvazia(){
    primeiro = nullptr;
    ultimo = nullptr;
    len = 0;
}
 
  // ordena a lista
  void ordenaBolha(){

    Nodo *aux, *aux2, *aux3;
    T mostra;
    for(aux3 = ultimo;aux3!=primeiro;aux3=aux3->anterior){
        aux=primeiro;
        aux2=aux->proximo;
    
    for(aux2;aux2!=ultimo;aux2=aux2->proximo){
        if(aux2->dado<aux->dado){
            mostra=aux->dado;
            aux->dado=aux2->dado;
            aux2->dado=mostra;
	}
    aux=aux->proximo;
    }
    }
}
 
  // iteração
  void inicia(){
    atual = primeiro;
}
  void iniciaPeloFim(){
    atual = ultimo;
    interador = true;
}
  
  bool fim() const{
   return atual == NULL;
}
  bool inicio() const{
    return atual == NULL;
}
  
  T & proximo(){
    T *algo;
    if(atual == NULL) throw "Erro";
    algo = &(atual->dado);
    atual = atual->proximo;
    return *algo;
}
  T & anterior(){
    if(not interador) throw "erro na interação";
    T *algo;
    if(atual == NULL) throw "Erro";
    algo = &(atual->dado);
    atual = atual->anterior;
    return *algo;
}
 
 private:
  // declaração do tipo Nodo: privativa, porque 
  // é de uso exclusivo da lista
  // Este Nodo visa uma lista duplamente encadeada
  struct Nodo {
    Nodo * proximo, * anterior;
    T dado;
 
    // construtor do Nodo: prático para uso nos métodos
    // da lista
    Nodo(const T & algo):dado(algo) {
      //dado = algo;
      proximo = nullptr;
      anterior = nullptr;
    }
  };
 
  // ponteiros para primeiro e último nodos
  Nodo * primeiro, * ultimo;
  bool interador = false;
  // ponteiro para nodo atual da iteração
  Nodo * atual;
 
  // comprimento da lista
  long len;
};
